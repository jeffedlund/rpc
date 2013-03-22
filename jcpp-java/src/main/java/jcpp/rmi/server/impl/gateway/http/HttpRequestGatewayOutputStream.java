package jcpp.rmi.server.impl.gateway.http;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.concurrent.atomic.AtomicLong;

import jcpp.rmi.server.impl.gateway.GatewayCompressionOutputStream;
import jcpp.rmi.server.impl.gateway.GatewayConfiguration;
import jcpp.rmi.server.impl.gateway.Route;

public class HttpRequestGatewayOutputStream extends ByteArrayOutputStream  {
    private GatewayCompressionOutputStream gatewayOutputStream;
    private HttpRequestGatewaySocket httpGatewaySocket;
    private Route route;
    private AtomicLong networkByteCounter;
    private boolean usesCompressionStream;
    private ByteArrayOutputStream bos;
    private boolean closed;
    private GatewayConfiguration gatewayConfiguration;

    public HttpRequestGatewayOutputStream(HttpRequestGatewaySocket httpGatewaySocket, Route route, boolean isGateway, GatewayConfiguration gatewayConfiguration) {
        super(2 * gatewayConfiguration.getSendBufferSize());
        this.httpGatewaySocket = httpGatewaySocket;
        this.route = route;
        this.gatewayConfiguration = gatewayConfiguration;
        this.usesCompressionStream = gatewayConfiguration.isCompressionEnabled() && !isGateway;
        this.networkByteCounter = new AtomicLong();
        this.bos = new ByteArrayOutputStream(2 * gatewayConfiguration.getSendBufferSize());
    }

    public void flush() throws IOException {
        if(gatewayOutputStream == null) {
            gatewayOutputStream = new GatewayCompressionOutputStream(bos, route, usesCompressionStream, gatewayConfiguration.getSendBufferSize(), 2 * gatewayConfiguration.getSendBufferSize(), gatewayConfiguration.getCompressionThreshold(), gatewayConfiguration.getCompressionLevel());
        }
        writeTo(gatewayOutputStream);
        gatewayOutputStream.flush();
        reset();
    }

    public void close() throws IOException {
        if(!closed) {
            closed = true;
            flush();
            gatewayOutputStream.close();
            if(bos.size() > 0) {
                OutputStream out = httpGatewaySocket.createOutputSream();
                bos.writeTo(out);
                out.flush();
                out.close();
            }
            httpGatewaySocket.getHttpUrlConnection().getInputStream();
        }
    }

    public boolean isClosed() {
        return closed;
    }
}
