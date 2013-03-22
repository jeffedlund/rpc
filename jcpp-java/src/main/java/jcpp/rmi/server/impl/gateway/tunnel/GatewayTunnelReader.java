package jcpp.rmi.server.impl.gateway.tunnel;

import java.io.EOFException;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;

import java.net.Socket;

import java.util.concurrent.Callable;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import jcpp.rmi.server.impl.gateway.Route;


public class GatewayTunnelReader implements Callable<Void> {
    private static Log log = LogFactory.getLog(GatewayTunnelReader.class);

    private GatewayTunnel tunnel;
    private Socket tunnelSocket;


    public GatewayTunnelReader(GatewayTunnel tunnel, Socket tunnelSocket) {
        this.tunnel = tunnel;
        this.tunnelSocket = tunnelSocket;
    }


    @Override
    public Void call() throws Exception {

        // TODO support HTTP
        while (!tunnelSocket.isClosed()) {
            try {
                InputStream in = tunnelSocket.getInputStream();
                int socketId = readIntFromStream(in);
                int opType = in.read();
                if (opType == GatewayTunnel.CREATE) {
                    Route route = (Route) new ObjectInputStream(in).readObject();
                    tunnel.accept(socketId, route);

                } else {
                    VirtualSocket virtualSocket = tunnel.getVirtualSocket(socketId);
                    if ((virtualSocket == null) && log.isWarnEnabled()) {
                        log.warn("Virtual socket not found. ID: " + socketId);
                    }
                    if (opType == GatewayTunnel.CLOSE) {
                        if (virtualSocket != null) {
                            tunnel.removeVirtualSocket(socketId);
                            virtualSocket.close();
                        }
                    } else if (opType == GatewayTunnel.WRITE) {
                        int socketDataLength = readIntFromStream(in);
                        if (socketDataLength == -1) {
                            virtualSocket.getInputStream().endStream();
                        } else {
                            byte[] socketData = new byte[socketDataLength];
                            int lengthSum = 0;
                            while (lengthSum < socketDataLength) {
                                int cnt = in.read(socketData, lengthSum, socketDataLength - lengthSum);
                                if (cnt == -1) {
                                    throw new EOFException("End of stream reached before number of bytes read reaches virtual packet data length");
                                }
                                lengthSum += cnt;
                            }
                            assert (lengthSum == socketDataLength);
                            if (virtualSocket != null) {
                                virtualSocket.getInputStream().addData(socketData, 0, socketDataLength);
                            }
                        }
                    } else {
                        throw new IOException("Stream is corrupted. Invalid virtual operation byte: 0x" + Integer.toHexString(opType));
                    }
                }
            } catch (IOException e) {
                // TODO review this
                tunnelSocket.close();
            }

        }
        return null;
    }

    private int readIntFromStream(InputStream in) throws IOException {
        int[] len = new int[4];
        for (int i = 0; i < 4; i++) {
            len[i] = in.read();
            if (len[i] == -1) {
                throw new IOException("Could not read integer from stream. End of stream reached");
            }
        }
        int integer = (len[0] << 24) ^ (len[1] << 16) ^ (len[2] << 8) ^ len[3];
        return integer;
    }
}
