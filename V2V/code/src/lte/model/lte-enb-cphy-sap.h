

#ifndef LTE_ENB_CPHY_SAP_H
#define LTE_ENB_CPHY_SAP_H

#include <stdint.h>
#include <ns3/ptr.h>

#include <ns3/lte-rrc-sap.h>

namespace ns3 {

class LteEnbNetDevice;


class LteEnbCphySapProvider
{
public:


  virtual ~LteEnbCphySapProvider ();


  virtual void SetCellId (uint16_t cellId) = 0;

 
  virtual void SetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth) = 0;

  virtual void SetEarfcn (uint16_t ulEarfcn, uint16_t dlEarfcn) = 0;
  
  /** 
   * Add a new UE to the cell
   * 
   * \param rnti the UE id relative to this cell
   */
  virtual void AddUe (uint16_t rnti) = 0;

  /** 
   * Remove an UE from the the cell
   * 
   * \param rnti the UE id relative to this cell
   */
  virtual void RemoveUe (uint16_t rnti) = 0;
  
  
  virtual void SetPa (uint16_t rnti, double pa) = 0;

  /**
   * \param rnti the RNTI of the user
   * \param txMode the transmissionMode of the user
   */
  virtual void SetTransmissionMode (uint16_t rnti, uint8_t txMode) = 0;

  /**
   * \param rnti the RNTI of the user
   * \param srsCi the SRS Configuration Index of the user
   */
  virtual void SetSrsConfigurationIndex (uint16_t rnti, uint16_t srsCi) = 0;

  /** 
   * 
   * \param mib the Master Information Block to be sent on the BCH
   */
  virtual void SetMasterInformationBlock (LteRrcSap::MasterInformationBlock mib) = 0;

  /**
   *
   * \param sib1 the System Information Block Type 1 to be sent on the BCH
   */
  virtual void SetSystemInformationBlockType1 (LteRrcSap::SystemInformationBlockType1 sib1) = 0;

  /**
   *
   * \return Reference Signal Power for SIB2
   */
  virtual int8_t GetReferenceSignalPower () = 0;
};


class LteEnbCphySapUser
{
public:
  
  /** 
   * destructor
   */
  virtual ~LteEnbCphySapUser ();

};


template <class C>
class MemberLteEnbCphySapProvider : public LteEnbCphySapProvider
{
public:
  MemberLteEnbCphySapProvider (C* owner);

  virtual void SetCellId (uint16_t cellId);
  virtual void SetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth);
  virtual void SetEarfcn (uint16_t ulEarfcn, uint16_t dlEarfcn);
  virtual void AddUe (uint16_t rnti);
  virtual void RemoveUe (uint16_t rnti);
  virtual void SetPa (uint16_t rnti, double pa);
  virtual void SetTransmissionMode (uint16_t  rnti, uint8_t txMode);
  virtual void SetSrsConfigurationIndex (uint16_t  rnti, uint16_t srsCi);
  virtual void SetMasterInformationBlock (LteRrcSap::MasterInformationBlock mib);
  virtual void SetSystemInformationBlockType1 (LteRrcSap::SystemInformationBlockType1 sib1);
  virtual int8_t GetReferenceSignalPower ();
  
private:
  MemberLteEnbCphySapProvider ();
  C* m_owner;
};

template <class C>
MemberLteEnbCphySapProvider<C>::MemberLteEnbCphySapProvider (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteEnbCphySapProvider<C>::MemberLteEnbCphySapProvider ()
{
}

template <class C>
void 
MemberLteEnbCphySapProvider<C>::SetCellId (uint16_t cellId)
{
  m_owner->DoSetCellId (cellId);
}


template <class C>
void 
MemberLteEnbCphySapProvider<C>::SetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth)
{
  m_owner->DoSetBandwidth (ulBandwidth, dlBandwidth);
}

template <class C>
void 
MemberLteEnbCphySapProvider<C>::SetEarfcn (uint16_t ulEarfcn, uint16_t dlEarfcn)
{
  m_owner->DoSetEarfcn (ulEarfcn, dlEarfcn);
}

template <class C>
void 
MemberLteEnbCphySapProvider<C>::AddUe (uint16_t rnti)
{
  m_owner->DoAddUe (rnti);
}

template <class C>
void 
MemberLteEnbCphySapProvider<C>::RemoveUe (uint16_t rnti)
{
  m_owner->DoRemoveUe (rnti);
}

template <class C>
void 
MemberLteEnbCphySapProvider<C>::SetPa (uint16_t rnti, double pa)
{
  m_owner->DoSetPa (rnti, pa);
}

template <class C>
void
MemberLteEnbCphySapProvider<C>::SetTransmissionMode (uint16_t  rnti, uint8_t txMode)
{
  m_owner->DoSetTransmissionMode (rnti, txMode);
}

template <class C>
void 
MemberLteEnbCphySapProvider<C>::SetSrsConfigurationIndex (uint16_t  rnti, uint16_t srsCi)
{
  m_owner->DoSetSrsConfigurationIndex (rnti, srsCi);
}

template <class C> 
void 
MemberLteEnbCphySapProvider<C>::SetMasterInformationBlock (LteRrcSap::MasterInformationBlock mib)
{
  m_owner->DoSetMasterInformationBlock (mib);
}

template <class C>
void
MemberLteEnbCphySapProvider<C>::SetSystemInformationBlockType1 (LteRrcSap::SystemInformationBlockType1 sib1)
{
  m_owner->DoSetSystemInformationBlockType1 (sib1);
}

template <class C>
int8_t
MemberLteEnbCphySapProvider<C>::GetReferenceSignalPower ()
{
  return m_owner->DoGetReferenceSignalPower ();
}

/**
 * Template for the implementation of the LteEnbCphySapUser as a member
 * of an owner class of type C to which all methods are forwarded
 * 
 */
template <class C>
class MemberLteEnbCphySapUser : public LteEnbCphySapUser
{
public:
  MemberLteEnbCphySapUser (C* owner);

  // methods inherited from LteEnbCphySapUser go here

private:
  MemberLteEnbCphySapUser ();
  C* m_owner;
};

template <class C>
MemberLteEnbCphySapUser<C>::MemberLteEnbCphySapUser (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteEnbCphySapUser<C>::MemberLteEnbCphySapUser ()
{
}






} // namespace ns3


#endif // LTE_ENB_CPHY_SAP_H
