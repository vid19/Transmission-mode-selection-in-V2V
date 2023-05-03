
#ifndef LTE_UE_MAC_ENTITY_H
#define LTE_UE_MAC_ENTITY_H



#include <map>

#include <ns3/lte-mac-sap.h>
#include <ns3/lte-ue-cmac-sap.h>
#include <ns3/lte-ue-phy-sap.h>
#include <ns3/nstime.h>
#include <ns3/event-id.h>
#include <vector>
#include <ns3/packet.h>
#include <ns3/packet-burst.h>


namespace ns3 {

class UniformRandomVariable;

class LteUeMac :   public Object
{
  friend class UeMemberLteUeCmacSapProvider;
  friend class UeMemberLteMacSapProvider;
  friend class UeMemberLteUePhySapUser;

public:
  static TypeId GetTypeId (void);

  LteUeMac ();
  virtual ~LteUeMac ();
  virtual void DoDispose (void);

  LteMacSapProvider*  GetLteMacSapProvider (void);
  void  SetLteUeCmacSapUser (LteUeCmacSapUser* s);
  LteUeCmacSapProvider*  GetLteUeCmacSapProvider (void);

  LteUePhySapUser* GetLteUePhySapUser ();

  void SetLteUePhySapProvider (LteUePhySapProvider* s);
  
  void DoSubframeIndication (uint32_t frameNo, uint32_t subframeNo);

  int64_t AssignStreams (int64_t stream);

private:
  
  void DoTransmitPdu (LteMacSapProvider::TransmitPduParameters params);
  void DoReportBufferStatus (LteMacSapProvider::ReportBufferStatusParameters params);

  // forwarded from UE CMAC SAP
  void DoConfigureRach (LteUeCmacSapProvider::RachConfig rc);
  void DoStartContentionBasedRandomAccessProcedure ();
  void DoStartNonContentionBasedRandomAccessProcedure (uint16_t rnti, uint8_t rapId, uint8_t prachMask);
  void DoAddLc (uint8_t lcId, LteUeCmacSapProvider::LogicalChannelConfig lcConfig, LteMacSapUser* msu);
  void DoRemoveLc (uint8_t lcId);
  void DoReset ();

  // forwarded from PHY SAP
  void DoReceivePhyPdu (Ptr<Packet> p);
  void DoReceiveLteControlMessage (Ptr<LteControlMessage> msg);
  
  // internal methods
  void RandomlySelectAndSendRaPreamble ();
  void SendRaPreamble (bool contention);
  void StartWaitingForRaResponse ();
  void RecvRaResponse (BuildRarListElement_s raResponse);
  void RaResponseTimeout (bool contention);
  void SendReportBufferStatus (void);
  void RefreshHarqProcessesPacketBuffer (void);

private:

  struct LcInfo
  {
    LteUeCmacSapProvider::LogicalChannelConfig lcConfig;
    LteMacSapUser* macSapUser;
  };

  std::map <uint8_t, LcInfo> m_lcInfoMap;

  LteMacSapProvider* m_macSapProvider;

  LteUeCmacSapUser* m_cmacSapUser;
  LteUeCmacSapProvider* m_cmacSapProvider;

  LteUePhySapProvider* m_uePhySapProvider;
  LteUePhySapUser* m_uePhySapUser;
  
  std::map <uint8_t, LteMacSapProvider::ReportBufferStatusParameters> m_ulBsrReceived; // BSR received from RLC (the last one)
  
  
  Time m_bsrPeriodicity;
  Time m_bsrLast;
  
  bool m_freshUlBsr; // true when a BSR has been received in the last TTI

  uint8_t m_harqProcessId;
  std::vector < Ptr<PacketBurst> > m_miUlHarqProcessesPacket; // Packets under trasmission of the UL HARQ processes
  std::vector < uint8_t > m_miUlHarqProcessesPacketTimer; // timer for packet life in the buffer

  uint16_t m_rnti;

  bool m_rachConfigured;
  LteUeCmacSapProvider::RachConfig m_rachConfig;
  uint8_t m_raPreambleId;
  uint8_t m_preambleTransmissionCounter;
  uint16_t m_backoffParameter;
  EventId m_noRaResponseReceivedEvent;
  Ptr<UniformRandomVariable> m_raPreambleUniformVariable;

  uint32_t m_frameNo;
  uint32_t m_subframeNo;
  uint8_t m_raRnti;
  bool m_waitingForRaResponse;
};

} // namespace ns3

#endif // LTE_UE_MAC_ENTITY
