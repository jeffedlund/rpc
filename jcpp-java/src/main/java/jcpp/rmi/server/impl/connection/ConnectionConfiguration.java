package jcpp.rmi.server.impl.connection;

import java.io.Serializable;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;

import jcpp.rmi.server.impl.transport.TransportConfiguration;

@XmlRootElement(name="connection")
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name="RemotingConnection")
public class ConnectionConfiguration implements Serializable {
    private static final long serialVersionUID = -7733929591819747912L;
    protected static final long GC_TIMEOUT                              = 10 * 60000;
    protected static final long GCCLIENT_TIMEOUT                        = 1 * 60000;
    protected static final int GCCLIENT_EXCEPTION_THRESHOLD             = 10;
    protected static final int EXECUTOR_CORE_POOL_SIZE                  = 2; 

    @XmlElement
    private TransportConfiguration transportConfiguration;
    @XmlElement
    private Long gcTimeout;
    @XmlElement
    private Long gcClientTimeout;
    @XmlElement
    private Long queueReaderTimeout;
    @XmlElement
    private Long queuePopTimeout;
    @XmlElement
    private Integer gcClientExceptionThreshold;
    @XmlElement
    private Integer executorCorePoolSize;
    @XmlElement
    private Integer connectionStatisticHistorySize;
    @XmlElement
    private Integer methodStatisticHistorySize;
    @XmlElement
    private Boolean recordStats;

    /**
     * All timeout values are in milliseconds.
     */
    public ConnectionConfiguration(TransportConfiguration transportConfiguration, long gcTimeout, long gcClientTimeout, long queueReaderTimeout, long queuePopTimeout, int gcClientExceptionThreshold, int executorCorePoolSize, int connectionStatisticHistorySize, int methodStatisticHistorySize, boolean recordStats) {
        this.transportConfiguration = transportConfiguration;
        this.gcTimeout = gcTimeout;
        this.gcClientTimeout = gcClientTimeout;
        this.queueReaderTimeout = queueReaderTimeout;
        this.queuePopTimeout = queuePopTimeout;
        this.gcClientExceptionThreshold = gcClientExceptionThreshold;
        this.executorCorePoolSize = executorCorePoolSize;
        this.connectionStatisticHistorySize = connectionStatisticHistorySize;
        this.methodStatisticHistorySize = methodStatisticHistorySize;
        this.recordStats = recordStats;
    }

    public ConnectionConfiguration() {
    }
    
    public TransportConfiguration getTransportConfiguration() {
        if(transportConfiguration == null) {
            transportConfiguration = new TransportConfiguration();
        }
        return transportConfiguration;
    }

    public void setTransportConfiguration(TransportConfiguration transportConfiguration) {
        this.transportConfiguration = transportConfiguration;
    }

    public long getGcTimeout() {
        if(gcTimeout == null) {
            gcTimeout = GC_TIMEOUT;
        }
        return gcTimeout;
    }

    /**
     * Timeout value in milliseconds.
     */
    public void setGcTimeout(long gcTimeout) {
        this.gcTimeout = gcTimeout;
    }

    public long getGcClientTimeout() {
        if(gcClientTimeout == null) {
            gcClientTimeout = GCCLIENT_TIMEOUT;
        }
        return gcClientTimeout;
    }

    /**
     * Timeout value in milliseconds.
     */
    public void setGcClientTimeout(long gcClientTimeout) {
        this.gcClientTimeout = gcClientTimeout;
    }

    public int getGcClientExceptionThreshold() {
        if(gcClientExceptionThreshold == null) {
            gcClientExceptionThreshold = GCCLIENT_EXCEPTION_THRESHOLD;
        }
        return gcClientExceptionThreshold;
    }

    public void setGcClientExceptionThreshold(int gcClientExceptionThreshold) {
        this.gcClientExceptionThreshold = gcClientExceptionThreshold;
    }

    public int getExecutorCorePoolSize() {
        if(executorCorePoolSize == null) {
            executorCorePoolSize = EXECUTOR_CORE_POOL_SIZE;
        }
        return executorCorePoolSize;
    }

    public void setExecutorCorePoolSize(int executorCorePoolSize) {
        this.executorCorePoolSize = executorCorePoolSize;
    }
}
