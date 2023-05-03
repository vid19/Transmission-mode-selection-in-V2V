

#ifndef LTE_PDCP_H
#define LTE_PDCP_H

#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"

#include "ns3/object.h"

#include "ns3/lte-pdcp-sap.h"
#include "ns3/lte-rlc-sap.h"

namespace ns3 {

class LtePdcp : public Object // SimpleRefCount<LtePdcp>
{
  friend class LtePdcpSpecificLteRlcSapUser;
  friend class LtePdcpSpecificLtePdcpSapProvider<LtePdcp>;
public:
  LtePdcp ();
  virtual ~LtePdcp ();
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

  void SetRnti (uint16_t rnti);

  
  void SetLcId (uint8_t lcId);

  void SetLtePdcpSapUser (LtePdcpSapUser * s);

  LtePdcpSapProvider* GetLtePdcpSapProvider ();

  
  void SetLteRlcSapProvider (LteRlcSapProvider * s);

 
  LteRlcSapUser* GetLteRlcSapUser ();

  static const uint16_t MAX_PDCP_SN = 4096;

 
  struct Status
  {
    uint16_t txSn; ///< TX sequence number
    uint16_t rxSn; ///< RX sequence number
  };

  
  Status GetStatus ();

  void SetStatus (Status s);

  typedef void (* PduTxTracedCallback)
    (uint16_t rnti, uint8_t lcid, uint32_t size);

  
  typedef void (* PduRxTracedCallback)
    (const uint16_t rnti, const uint8_t lcid,
     const uint32_t size, const uint64_t delay);

protected:
  // Interface provided to upper RRC entity
  virtual void DoTransmitPdcpSdu (Ptr<Packet> p);

  LtePdcpSapUser* m_pdcpSapUser;
  LtePdcpSapProvider* m_pdcpSapProvider;

  // Interface provided to lower RLC entity
  virtual void DoReceivePdu (Ptr<Packet> p);

  LteRlcSapUser* m_rlcSapUser;
  LteRlcSapProvider* m_rlcSapProvider;

  uint16_t m_rnti;
  uint8_t m_lcid;

  
  TracedCallback<uint16_t, uint8_t, uint32_t> m_txPdu;
  
  TracedCallback<uint16_t, uint8_t, uint32_t, uint64_t> m_rxPdu;

private:
 
  uint16_t m_txSequenceNumber;
  uint16_t m_rxSequenceNumber;

  static const uint16_t m_maxPdcpSn = 4095;

};


} // namespace ns3

#endif // LTE_PDCP_H
