

#ifndef LTE_RLC_SAP_H
#define LTE_RLC_SAP_H

#include "ns3/packet.h"

namespace ns3 {


class LteRlcSapProvider
{
public:
  virtual ~LteRlcSapProvider ();

  
  struct TransmitPdcpPduParameters
  {
    Ptr<Packet> pdcpPdu; 
    uint16_t    rnti; 
    uint8_t     lcid; 
  };

  virtual void TransmitPdcpPdu (TransmitPdcpPduParameters params) = 0;
};


class LteRlcSapUser
{
public:
  virtual ~LteRlcSapUser ();

  virtual void ReceivePdcpPdu (Ptr<Packet> p) = 0;
};

///////////////////////////////////////

template <class C>
class LteRlcSpecificLteRlcSapProvider : public LteRlcSapProvider
{
public:
  LteRlcSpecificLteRlcSapProvider (C* rlc);

  // Interface implemented from LteRlcSapProvider
  virtual void TransmitPdcpPdu (TransmitPdcpPduParameters params);

private:
  LteRlcSpecificLteRlcSapProvider ();
  C* m_rlc;
};

template <class C>
LteRlcSpecificLteRlcSapProvider<C>::LteRlcSpecificLteRlcSapProvider (C* rlc)
  : m_rlc (rlc)
{
}

template <class C>
LteRlcSpecificLteRlcSapProvider<C>::LteRlcSpecificLteRlcSapProvider ()
{
}

template <class C>
void LteRlcSpecificLteRlcSapProvider<C>::TransmitPdcpPdu (TransmitPdcpPduParameters params)
{
  m_rlc->DoTransmitPdcpPdu (params.pdcpPdu);
}

///////////////////////////////////////

template <class C>
class LteRlcSpecificLteRlcSapUser : public LteRlcSapUser
{
public:
  LteRlcSpecificLteRlcSapUser (C* pdcp);

  // Interface implemented from LteRlcSapUser
  virtual void ReceivePdcpPdu (Ptr<Packet> p);

private:
  LteRlcSpecificLteRlcSapUser ();
  C* m_pdcp;
};

template <class C>
LteRlcSpecificLteRlcSapUser<C>::LteRlcSpecificLteRlcSapUser (C* pdcp)
  : m_pdcp (pdcp)
{
}

template <class C>
LteRlcSpecificLteRlcSapUser<C>::LteRlcSpecificLteRlcSapUser ()
{
}

template <class C>
void LteRlcSpecificLteRlcSapUser<C>::ReceivePdcpPdu (Ptr<Packet> p)
{
  m_pdcp->DoReceivePdcpPdu (p);
}


} // namespace ns3

#endif // LTE_RLC_SAP_H
