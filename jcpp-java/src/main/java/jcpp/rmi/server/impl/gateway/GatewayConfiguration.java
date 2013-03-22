package jcpp.rmi.server.impl.gateway;

import java.io.Serializable;

import java.util.HashMap;
import java.util.Map;
import java.util.zip.Deflater;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


@XmlRootElement(name = "gateway")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "RemotingGateway")
public class GatewayConfiguration implements Serializable {
    private static final long serialVersionUID = 7816914239055009789L;

    protected static final int BACKLOG = 400;
    protected static final int RECEIVE_BUFFER_SIZE = 20480;
    protected static final int SEND_BUFFER_SIZE = 20480;
    protected static final int READ_TIMEOUT = 24 * 3600 * 1000; // 24 hours
    protected static final int CONNECTION_TIME_OUT = 60000;
    protected static final int COMPRESION_THRESHOLD = 1024;
    protected static final int COMPRESION_LEVEL = Deflater.DEFAULT_COMPRESSION;
    protected static final boolean COMPRESSION_ENABLED = false;

    @XmlElement
    private Integer backLog;
    @XmlElement
    private Integer receiveBufferSize;
    @XmlElement
    private Integer sendBufferSize;
    @XmlElement
    private Integer readTimeout;
    @XmlElement
    private Integer connectionTimeout;
    @XmlElement
    private Integer compressionThreshold;
    @XmlElement
    private Integer compressionLevel;
    @XmlElement
    private Boolean compressionEnabled;

    public GatewayConfiguration(int backLog, int receiveBufferSize, int sendBufferSize, int readTimeout, int compressionThreshold, int compressionLevel, boolean compressionEnabled) {
        this.backLog = backLog;
        this.receiveBufferSize = receiveBufferSize;
        this.sendBufferSize = sendBufferSize;
        this.readTimeout = readTimeout;
        this.compressionThreshold = compressionThreshold;
        this.compressionLevel = compressionLevel;
        this.compressionEnabled = compressionEnabled;
    }

    public GatewayConfiguration() {
    }


    public int getBackLog() {
        if (backLog == null) {
            backLog = BACKLOG;
        }
        return backLog;
    }

    public int getReceiveBufferSize() {
        if (receiveBufferSize == null) {
            receiveBufferSize = RECEIVE_BUFFER_SIZE;
        }
        return receiveBufferSize;
    }

    public int getSendBufferSize() {
        if (sendBufferSize == null) {
            sendBufferSize = SEND_BUFFER_SIZE;
        }
        return sendBufferSize;
    }

    public int getReadTimeout() {
        if (readTimeout == null) {
            readTimeout = READ_TIMEOUT;
        }
        return readTimeout;
    }

    public int getConnectionTimeout() {
        if (connectionTimeout == null) {
            connectionTimeout = CONNECTION_TIME_OUT;
        }
        return connectionTimeout;
    }

    public int getCompressionThreshold() {
        if (compressionThreshold == null) {
            compressionThreshold = COMPRESION_THRESHOLD;
        }
        return compressionThreshold;
    }

    public int getCompressionLevel() {
        if (compressionLevel == null) {
            compressionLevel = COMPRESION_LEVEL;
        }
        return compressionLevel;
    }

    public boolean isCompressionEnabled() {
        if (compressionEnabled == null) {
            compressionEnabled = COMPRESSION_ENABLED;
        }
        return compressionEnabled;
    }

    public void setBackLog(int backLog) {
        this.backLog = backLog;
    }

    public void setReceiveBufferSize(int receiveBufferSize) {
        this.receiveBufferSize = receiveBufferSize;
    }

    public void setSendBufferSize(int sendBufferSize) {
        this.sendBufferSize = sendBufferSize;
    }

    public void setReadTimeout(int readTimeout) {
        this.readTimeout = readTimeout;
    }

    public void setConnectionTimeout(int connectionTimeout) {
        this.connectionTimeout = connectionTimeout;
    }

    public void setCompressionThreshold(int compressionThreshold) {
        this.compressionThreshold = compressionThreshold;
    }

    public void setCompressionLevel(int compressionLevel) {
        this.compressionLevel = compressionLevel;
    }

    public void setCompressionEnabled(boolean compressionEnabled) {
        this.compressionEnabled = compressionEnabled;
    }
}
