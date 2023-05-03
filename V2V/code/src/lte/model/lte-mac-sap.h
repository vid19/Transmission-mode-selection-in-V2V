

#ifndef LTE_MAC_SAP_H
#define LTE_MAC_SAP_H

#include <ns3/packet.h>

namespace ns3 {




class LteMacSapProvider
{
public:
  virtual ~LteMacSapProvider ();

 
  struct TransmitPduParameters
  {
    Ptr<Packet> pdu;  
    uint16_t    rnti; 
    uint8_t     lcid; 
    uint8_t     layer; 
    uint8_t     harqProcessId; 
  };


  virtual void TransmitPdu (TransmitPduParameters params) = 0;


 
  struct ReportBufferStatusParameters
  {
    uint16_t rnti;  /**< the C-RNTI identifying the UE */
    uint8_t lcid;  /**< the logical channel id corresponding to the sending RLC instance */
    uint32_t txQueueSize;  /**< the current size of the RLC transmission queue */
    uint16_t txQueueHolDelay;  /**< the Head Of Line delay of the transmission queue */
    uint32_t retxQueueSize;  /**<  the current size of the RLC retransmission queue in bytes */
    uint16_t retxQueueHolDelay;  /**<  the Head Of Line delay of the retransmission queue */
    uint16_t statusPduSize;  /**< the current size of the pending STATUS RLC  PDU message in bytes */

    // RDF: Added for MmWave low-latency schedulers
		std::list<uint32_t>	txPacketSizes;
		std::list<uint32_t>	retxPacketSizes;
		std::list<double>	txPacketDelays;
		std::list<double>	retxPacketDelays;
		double arrivalRate;		// average bits per s
  };

 
  virtual void ReportBufferStatus (ReportBufferStatusParameters params) = 0;


};



class LteMacSapUser
{
public:
  virtual ~LteMacSapUser ();
 
  virtual void NotifyTxOpportunity (uint32_t bytes, uint8_t layer, uint8_t harqId) = 0;

 
  virtual void NotifyHarqDeliveryFailure () = 0;

  virtual void NotifyDlHarqDeliveryFailure (uint8_t harqId);

  virtual void NotifyUlHarqDeliveryFailure (uint8_t harqId);

 
  virtual void ReceivePdu (Ptr<Packet> p) = 0;

};


template <class C>
class EnbMacMemberLteMacSapProvider : public LteMacSapProvider
{
public:
  EnbMacMemberLteMacSapProvider (C* mac);


  virtual void TransmitPdu (TransmitPduParameters params);
  virtual void ReportBufferStatus (ReportBufferStatusParameters params);

private:
  C* m_mac;
};


template <class C>
EnbMacMemberLteMacSapProvider<C>::EnbMacMemberLteMacSapProvider (C* mac)
  : m_mac (mac)
{
}

template <class C>
void EnbMacMemberLteMacSapProvider<C>::TransmitPdu (TransmitPduParameters params)
{
  m_mac->DoTransmitPdu (params);
}

template <class C>
void EnbMacMemberLteMacSapProvider<C>::ReportBufferStatus (ReportBufferStatusParameters params)
{
  m_mac->DoReportBufferStatus (params);
}


} // namespace ns3


#endif // LTE_MAC_SAP_H
