

#ifndef LTE_PDCP_SAP_H
#define LTE_PDCP_SAP_H

#include "ns3/packet.h"

namespace ns3 {


class LtePdcpSapProvider
{
public:
  virtual ~LtePdcpSapProvider ();

 
  struct TransmitPdcpSduParameters
  {
    Ptr<Packet> pdcpSdu;  /**< the RRC PDU */
    uint16_t    rnti; /**< the C-RNTI identifying the UE */
    uint8_t     lcid; /**< the logical channel id corresponding to the sending RLC instance */
  };

 
  virtual void TransmitPdcpSdu (TransmitPdcpSduParameters params) = 0;
};



class LtePdcpSapUser
{
public:
  virtual ~LtePdcpSapUser ();

  
  struct ReceivePdcpSduParameters
  {
    Ptr<Packet> pdcpSdu;  /**< the RRC PDU */
    uint16_t    rnti; /**< the C-RNTI identifying the UE */
    uint8_t     lcid; /**< the logical channel id corresponding to the sending RLC instance */
  };

 
  virtual void ReceivePdcpSdu (ReceivePdcpSduParameters params) = 0;
};

///////////////////////////////////////

template <class C>
class LtePdcpSpecificLtePdcpSapProvider : public LtePdcpSapProvider
{
public:
  LtePdcpSpecificLtePdcpSapProvider (C* pdcp);

  // Interface implemented from LtePdcpSapProvider
  virtual void TransmitPdcpSdu (TransmitPdcpSduParameters params);

private:
  LtePdcpSpecificLtePdcpSapProvider ();
  C* m_pdcp;
};

template <class C>
LtePdcpSpecificLtePdcpSapProvider<C>::LtePdcpSpecificLtePdcpSapProvider (C* pdcp)
  : m_pdcp (pdcp)
{
}

template <class C>
LtePdcpSpecificLtePdcpSapProvider<C>::LtePdcpSpecificLtePdcpSapProvider ()
{
}

template <class C>
void LtePdcpSpecificLtePdcpSapProvider<C>::TransmitPdcpSdu (TransmitPdcpSduParameters params)
{
  m_pdcp->DoTransmitPdcpSdu (params.pdcpSdu);
}

///////////////////////////////////////

template <class C>
class LtePdcpSpecificLtePdcpSapUser : public LtePdcpSapUser
{
public:
  LtePdcpSpecificLtePdcpSapUser (C* rrc);

  // Interface implemented from LtePdcpSapUser
  virtual void ReceivePdcpSdu (ReceivePdcpSduParameters params);

private:
  LtePdcpSpecificLtePdcpSapUser ();
  C* m_rrc;
};

template <class C>
LtePdcpSpecificLtePdcpSapUser<C>::LtePdcpSpecificLtePdcpSapUser (C* rrc)
  : m_rrc (rrc)
{
}

template <class C>
LtePdcpSpecificLtePdcpSapUser<C>::LtePdcpSpecificLtePdcpSapUser ()
{
}

template <class C>
void LtePdcpSpecificLtePdcpSapUser<C>::ReceivePdcpSdu (ReceivePdcpSduParameters params)
{
  m_rrc->DoReceivePdcpSdu (params);
}


} // namespace ns3

#endif // LTE_PDCP_SAP_H
