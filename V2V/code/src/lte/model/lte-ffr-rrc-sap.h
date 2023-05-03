

#ifndef LTE_FFR_RRC_SAP_H
#define LTE_FFR_RRC_SAP_H

#include <ns3/lte-rrc-sap.h>
#include <ns3/epc-x2-sap.h>

namespace ns3 {


class LteFfrRrcSapProvider
{
public:
  virtual ~LteFfrRrcSapProvider ();

 
  virtual void SetCellId (uint16_t cellId ) = 0;


  virtual void SetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth) = 0;

  virtual void ReportUeMeas (uint16_t rnti,
                             LteRrcSap::MeasResults measResults) = 0;

 
  virtual void  RecvLoadInformation (EpcX2Sap::LoadInformationParams params) = 0;

}; 
class LteFfrRrcSapUser
{
public:
  virtual ~LteFfrRrcSapUser ();
  virtual uint8_t AddUeMeasReportConfigForFfr (LteRrcSap::ReportConfigEutra reportConfig) = 0;

  virtual void SetPdschConfigDedicated (uint16_t rnti, LteRrcSap::PdschConfigDedicated pdschConfigDedicated) = 0;

  virtual void  SendLoadInformation (EpcX2Sap::LoadInformationParams params) = 0;

}; 
template <class C>
class MemberLteFfrRrcSapProvider : public LteFfrRrcSapProvider
{
public:
  MemberLteFfrRrcSapProvider (C* owner);

  virtual void SetCellId (uint16_t cellId );
  virtual void SetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth);
  virtual void ReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults);
  virtual void RecvLoadInformation (EpcX2Sap::LoadInformationParams params);

private:
  MemberLteFfrRrcSapProvider ();
  C* m_owner;

}; // end of class MemberLteFfrRrcSapProvider


template <class C>
MemberLteFfrRrcSapProvider<C>::MemberLteFfrRrcSapProvider (C* owner)
  : m_owner (owner)
{
}

template <class C>
void
MemberLteFfrRrcSapProvider<C>::SetCellId (uint16_t cellId )
{
  m_owner->DoSetCellId (cellId);
}

template <class C>
void
MemberLteFfrRrcSapProvider<C>::SetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth)
{
  m_owner->DoSetBandwidth (ulBandwidth, dlBandwidth);
}

template <class C>
void
MemberLteFfrRrcSapProvider<C>::ReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults)
{
  m_owner->DoReportUeMeas (rnti, measResults);
}

template <class C>
void
MemberLteFfrRrcSapProvider<C>::RecvLoadInformation (EpcX2Sap::LoadInformationParams params)
{
  m_owner->DoRecvLoadInformation (params);
}

template <class C>
class MemberLteFfrRrcSapUser : public LteFfrRrcSapUser
{
public:
  MemberLteFfrRrcSapUser (C* owner);

  // inherited from LteFfrRrcSapUser
  virtual uint8_t AddUeMeasReportConfigForFfr (LteRrcSap::ReportConfigEutra reportConfig);

  virtual void SetPdschConfigDedicated (uint16_t rnti, LteRrcSap::PdschConfigDedicated pdschConfigDedicated);

  virtual void  SendLoadInformation (EpcX2Sap::LoadInformationParams params);
private:
  MemberLteFfrRrcSapUser ();
  C* m_owner;

}; // end of class LteFfrRrcSapUser

template <class C>
MemberLteFfrRrcSapUser<C>::MemberLteFfrRrcSapUser (C* owner)
  : m_owner (owner)
{
}

template <class C>
uint8_t
MemberLteFfrRrcSapUser<C>::AddUeMeasReportConfigForFfr (LteRrcSap::ReportConfigEutra reportConfig)
{
  return m_owner->DoAddUeMeasReportConfigForFfr (reportConfig);
}

template <class C>
void
MemberLteFfrRrcSapUser<C>::SetPdschConfigDedicated (uint16_t rnti, LteRrcSap::PdschConfigDedicated pdschConfigDedicated)
{
  m_owner->DoSetPdschConfigDedicated (rnti, pdschConfigDedicated);
}

template <class C>
void
MemberLteFfrRrcSapUser<C>::SendLoadInformation (EpcX2Sap::LoadInformationParams params)
{
  m_owner->DoSendLoadInformation (params);
}

} // end of namespace ns3


#endif /* LTE_FFR_RRC_SAP_H */
