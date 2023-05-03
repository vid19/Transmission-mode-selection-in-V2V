

#ifndef LTE_RLC_TM_H
#define LTE_RLC_TM_H

#include "ns3/lte-rlc.h"

#include <ns3/event-id.h>
#include <map>

namespace ns3 {


class LteRlcTm : public LteRlc
{
public:
  LteRlcTm ();
  virtual ~LteRlcTm ();
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

  
  virtual void DoTransmitPdcpPdu (Ptr<Packet> p);

  virtual void DoNotifyTxOpportunity (uint32_t bytes, uint8_t layer, uint8_t harqId);
  virtual void DoNotifyHarqDeliveryFailure ();
  virtual void DoReceivePdu (Ptr<Packet> p);

private:
  void ExpireRbsTimer (void);
  void DoReportBufferStatus ();

private:
  uint32_t m_maxTxBufferSize;
  uint32_t m_txBufferSize;
  std::vector < Ptr<Packet> > m_txBuffer;       // Transmission buffer

  EventId m_rbsTimer;

};


} // namespace ns3

#endif // LTE_RLC_TM_H
