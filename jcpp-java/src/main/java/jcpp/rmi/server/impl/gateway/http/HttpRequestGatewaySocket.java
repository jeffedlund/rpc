package jcpp.rmi.server.impl.gateway.http;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;
import java.net.UnknownHostException;

import jcpp.rmi.server.impl.compression.CompressionInputStream;
import jcpp.rmi.server.impl.gateway.Address;
import jcpp.rmi.server.impl.gateway.GatewayConfiguration;
import jcpp.rmi.server.impl.gateway.IGatewaySocket;
import jcpp.rmi.server.impl.gateway.Route;

public class HttpRequestGatewaySocket extends Socket implements IGatewaySocket {
    private HttpURLConnection httpURLConnection;
    private OutputStream requestOutputStream;
    private InputStream requestInputStream;
    private Route route;
    private Address address;
    private boolean isGateway;
    private GatewayConfiguration gatewayConfiguration;

    public HttpRequestGatewaySocket(Route route, boolean isGateway, GatewayConfiguration gatewayConfiguration) throws UnknownHostException, IOException, ClassNotFoundException {
        this.route = route;
        this.address = route.popAddress();
        this.isGateway = isGateway;
        this.gatewayConfiguration = gatewayConfiguration;
        this.requestOutputStream =new HttpRequestGatewayOutputStream(this, route, isGateway, gatewayConfiguration);
        this.requestInputStream = new HttpRequestGatewayInputStream(null, this);
    }

    protected OutputStream createOutputSream() throws MalformedURLException, IOException {
        URLConnection urlConnection = new URL("http", address.getHostName(), address.getPort(), "/").openConnection();
        httpURLConnection = (HttpURLConnection) urlConnection;
        httpURLConnection.setDoInput(true);
        httpURLConnection.setDoOutput(true);
        httpURLConnection.setUseCaches(false);
        httpURLConnection.setRequestMethod("POST");
        httpURLConnection.setRequestProperty("content-type", "application/zip");
        httpURLConnection.setRequestProperty("content-length", "");
        return httpURLConnection.getOutputStream();
    }

    protected InputStream createInputStream() throws IOException {
        requestOutputStream.close();
        requestOutputStream = null;
        InputStream input = httpURLConnection.getInputStream();
        String contentType = httpURLConnection.getContentType();
        if(contentType == null || !httpURLConnection.getContentType().equals("application/zip")) {
            String message;
            if(contentType == null) {
                message = "Missing content type in response \r\n";
            } else {
                message = "Invalid content type in response: " + contentType + "\r\n";
            }
            message += "HttpSendSocket.createInputStream: response body: ";
            try {
                DataInputStream dataInputStream = new DataInputStream(input);
                String line;
                while ((line = dataInputStream.readLine()) != null ) {
                    message += line + "\r\n";
                }
            } catch (Throwable throwable) {
            }
            throw new IOException("HTTP request failed." + message);
        }

        if(gatewayConfiguration.isCompressionEnabled() && !isGateway) {
            input = new CompressionInputStream(input, gatewayConfiguration.getReceiveBufferSize());
        }
        return input;
    }

    public HttpURLConnection getHttpUrlConnection() {
        return httpURLConnection;
    }

    public InputStream getInputStream() throws IOException {
        return requestInputStream;
    }

    public OutputStream getOutputStream() throws IOException {
        return requestOutputStream;
    }

    public Route getRoute() {
        return route;
    }

    public boolean isReausable() {
        return false;
    }

    public void close() throws IOException {
        httpURLConnection.disconnect();
    }

    public String toString() {
        return "HttpRequestGatewaySocket[" + super.toString() + "]";
    }
}
