
#ifndef LTE_HANDOVER_MANAGEMENT_SAP_H
#define LTE_HANDOVER_MANAGEMENT_SAP_H

#include <ns3/lte-rrc-sap.h>

namespace ns3 {



class LteHandoverManagementSapProvider
{
public:
  virtual ~LteHandoverManagementSapProvider ();


  virtual void ReportUeMeas (uint16_t rnti,
                             LteRrcSap::MeasResults measResults) = 0;

}; 
class LteHandoverManagementSapUser
{
public:
  virtual ~LteHandoverManagementSapUser ();

 
  virtual uint8_t AddUeMeasReportConfigForHandover (LteRrcSap::ReportConfigEutra reportConfig) = 0;

 
  virtual void TriggerHandover (uint16_t rnti, uint16_t targetCellId) = 0;

}; 
template <class C>
class MemberLteHandoverManagementSapProvider : public LteHandoverManagementSapProvider
{
public:
  MemberLteHandoverManagementSapProvider (C* owner);

  // inherited from LteHandoverManagemenrSapProvider
  virtual void ReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults);

private:
  MemberLteHandoverManagementSapProvider ();
  C* m_owner;

}; // end of class MemberLteHandoverManagementSapProvider


template <class C>
MemberLteHandoverManagementSapProvider<C>::MemberLteHandoverManagementSapProvider (C* owner)
  : m_owner (owner)
{
}


template <class C>
void
MemberLteHandoverManagementSapProvider<C>::ReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults)
{
  m_owner->DoReportUeMeas (rnti, measResults);
}

template <class C>
class MemberLteHandoverManagementSapUser : public LteHandoverManagementSapUser
{
public:
  MemberLteHandoverManagementSapUser (C* owner);

  // inherited from LteHandoverManagementSapUser
  virtual uint8_t AddUeMeasReportConfigForHandover (LteRrcSap::ReportConfigEutra reportConfig);
  virtual void TriggerHandover (uint16_t rnti, uint16_t targetCellId);

private:
  MemberLteHandoverManagementSapUser ();
  C* m_owner;

}; // end of class MemberLteAnrSapUser


template <class C>
MemberLteHandoverManagementSapUser<C>::MemberLteHandoverManagementSapUser (C* owner)
  : m_owner (owner)
{
}


template <class C>
uint8_t
MemberLteHandoverManagementSapUser<C>::AddUeMeasReportConfigForHandover (LteRrcSap::ReportConfigEutra reportConfig)
{
  return m_owner->DoAddUeMeasReportConfigForHandover (reportConfig);
}


template <class C>
void
MemberLteHandoverManagementSapUser<C>::TriggerHandover (uint16_t rnti, uint16_t targetCellId)
{
  return m_owner->DoTriggerHandover (rnti, targetCellId);
}


} // end of namespace ns3


#endif /* LTE_HANDOVER_MANAGEMENT_SAP_H */
