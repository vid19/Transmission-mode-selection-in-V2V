

#ifndef LTE_ANR_SAP_H
#define LTE_ANR_SAP_H

#include <ns3/lte-rrc-sap.h>

namespace ns3 {


class LteAnrSapProvider
{
public:
  virtual ~LteAnrSapProvider ();


  virtual void ReportUeMeas (LteRrcSap::MeasResults measResults) = 0;

 
  virtual void AddNeighbourRelation (uint16_t cellId) = 0;

 
  virtual bool GetNoRemove (uint16_t cellId) const = 0;


  virtual bool GetNoHo (uint16_t cellId) const = 0;

 
  virtual bool GetNoX2 (uint16_t cellId) const = 0;

}; 
class LteAnrSapUser
{
public:
  virtual ~LteAnrSapUser ();

  
  virtual uint8_t AddUeMeasReportConfigForAnr (LteRrcSap::ReportConfigEutra reportConfig) = 0;

}; 
template <class C>
class MemberLteAnrSapProvider : public LteAnrSapProvider
{
public:
  MemberLteAnrSapProvider (C* owner);

  // inherited from LteAnrSapProvider
  virtual void ReportUeMeas (LteRrcSap::MeasResults measResults);
  virtual void AddNeighbourRelation (uint16_t cellId);
  virtual bool GetNoRemove (uint16_t cellId) const;
  virtual bool GetNoHo (uint16_t cellId) const;
  virtual bool GetNoX2 (uint16_t cellId) const;

private:
  MemberLteAnrSapProvider ();
  C* m_owner;

}; // end of class MemberLteAnrSapProvider


template <class C>
MemberLteAnrSapProvider<C>::MemberLteAnrSapProvider (C* owner)
  : m_owner (owner)
{
}


template <class C>
void
MemberLteAnrSapProvider<C>::ReportUeMeas (LteRrcSap::MeasResults measResults)
{
  m_owner->DoReportUeMeas (measResults);
}


template <class C>
void
MemberLteAnrSapProvider<C>::AddNeighbourRelation (uint16_t cellId)
{
  m_owner->DoAddNeighbourRelation (cellId);
}


template <class C>
bool
MemberLteAnrSapProvider<C>::GetNoRemove (uint16_t cellId) const
{
  return m_owner->DoGetNoRemove (cellId);
}


template <class C>
bool
MemberLteAnrSapProvider<C>::GetNoHo (uint16_t cellId) const
{
  return m_owner->DoGetNoHo (cellId);
}


template <class C>
bool
MemberLteAnrSapProvider<C>::GetNoX2 (uint16_t cellId) const
{
  return m_owner->DoGetNoX2 (cellId);
}



/**
 * \brief Template for the implementation of the LteAnrSapUser as a member of an
 *        owner class of type C to which all methods are forwarded.
 */
template <class C>
class MemberLteAnrSapUser : public LteAnrSapUser
{
public:
  MemberLteAnrSapUser (C* owner);

  // inherited from LteAnrSapUser
  virtual uint8_t AddUeMeasReportConfigForAnr (LteRrcSap::ReportConfigEutra reportConfig);

private:
  MemberLteAnrSapUser ();
  C* m_owner;

}; // end of class MemberLteAnrSapUser


template <class C>
MemberLteAnrSapUser<C>::MemberLteAnrSapUser (C* owner)
  : m_owner (owner)
{
}


template <class C>
uint8_t
MemberLteAnrSapUser<C>::AddUeMeasReportConfigForAnr (LteRrcSap::ReportConfigEutra reportConfig)
{
  return m_owner->DoAddUeMeasReportConfigForAnr (reportConfig);
}


} // end of namespace ns3


#endif /* LTE_ANR_SAP_H */
