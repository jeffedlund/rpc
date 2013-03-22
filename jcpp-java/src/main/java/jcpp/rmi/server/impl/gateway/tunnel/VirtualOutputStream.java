package jcpp.rmi.server.impl.gateway.tunnel;

import java.io.IOException;
import java.io.OutputStream;


public class VirtualOutputStream extends OutputStream {
    private byte[] data;
    private int dataLength;
    private VirtualSocket virtualSocket;


    public VirtualOutputStream(VirtualSocket virtualSocket) {
        this.virtualSocket = virtualSocket;
        this.data = new byte[GatewayTunnel.BUFFER_SIZE];
    }


    @Override
    public void write(int b) throws IOException {
        data[dataLength++] = (byte) b;
        if (dataLength >= data.length) {
            sendData();
        }
    }

    @Override
    public void flush() throws IOException {
        sendData();
    }

    @Override
    public void close() throws IOException {
    }

    protected void sendData() throws IOException {
        if (dataLength > 0) {
            virtualSocket.getTunnel().write(data, dataLength, virtualSocket.getId());
            dataLength = 0;
        }
    }

}
