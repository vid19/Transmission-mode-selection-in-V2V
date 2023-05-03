

#ifndef LTE_RLC_UM_LOWLAT_H
#define LTE_RLC_UM_LOWLAT_H

#include "ns3/lte-rlc-sequence-number.h"
#include "ns3/lte-rlc.h"

#include <ns3/event-id.h>
#include <map>
#include <deque>

namespace ns3 {

class LteRlcUmLowLat : public LteRlc
{
public:
  LteRlcUmLowLat ();
  virtual ~LteRlcUmLowLat ();
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

  
  virtual void DoTransmitPdcpPdu (Ptr<Packet> p);

  virtual void DoNotifyTxOpportunity (uint32_t bytes, uint8_t layer, uint8_t harqId);
  virtual void DoNotifyHarqDeliveryFailure ();
  virtual void DoReceivePdu (Ptr<Packet> p);

private:
  void ExpireReorderingTimer (void);
  void ExpireRbsTimer (void);

  bool IsInsideReorderingWindow (SequenceNumber10 seqNumber);

  void ReassembleOutsideWindow (void);
  void ReassembleSnInterval (SequenceNumber10 lowSeqNumber, SequenceNumber10 highSeqNumber);

  void ReassembleAndDeliver (Ptr<Packet> packet);

  void DoReportBufferStatus ();

private:
  uint32_t m_maxTxBufferSize;
  uint32_t m_txBufferSize;
  std::vector < Ptr<Packet> > m_txBuffer;       // Transmission buffer
  std::map <uint16_t, Ptr<Packet> > m_rxBuffer; // Reception buffer
  std::vector < Ptr<Packet> > m_reasBuffer;     // Reassembling buffer

  std::list < Ptr<Packet> > m_sdusBuffer;       // List of SDUs in a packet

  /**
   * State variables. See section 7.1 in TS 36.322
   */
  SequenceNumber10 m_sequenceNumber; // VT(US)

  SequenceNumber10 m_vrUr;           // VR(UR)
  SequenceNumber10 m_vrUx;           // VR(UX)
  SequenceNumber10 m_vrUh;           // VR(UH)

  /**
   * Constants. See section 7.2 in TS 36.322
   */
  uint16_t m_windowSize;

  /**
   * Timers. See section 7.3 in TS 36.322
   */
  EventId m_reorderingTimer;
  EventId m_rbsTimer;
  Time    m_rbsTimerValue;

  /**
   * Reassembling state
   */
  typedef enum { NONE            = 0,
                 WAITING_S0_FULL = 1,
                 WAITING_SI_SF   = 2 } ReassemblingState_t;
  ReassemblingState_t m_reassemblingState;
  Ptr<Packet> m_keepS0;

  /**
   * Expected Sequence Number
   */
  SequenceNumber10 m_expectedSeqNumber;

  std::deque <uint32_t> m_recentArrivalTimes;
  std::deque <uint32_t> m_recentPacketSizes;
  uint32_t	m_currTotalPacketSize;
  //uint64_t m_lastArrivalTime;
  double m_arrivalRate;
  static uint32_t m_numArrivalsToAvg;				// average last N arrivals
  //double	m_forgetFactor;
  Time m_reorderingTimeExpires;
  bool m_bsrReported;
};


} // namespace ns3

#endif // MMWAVE_RLC_UM_H