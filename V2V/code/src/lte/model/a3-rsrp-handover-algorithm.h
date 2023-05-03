

#ifndef A3_RSRP_HANDOVER_ALGORITHM_H
#define A3_RSRP_HANDOVER_ALGORITHM_H

#include <ns3/lte-handover-algorithm.h>
#include <ns3/lte-handover-management-sap.h>
#include <ns3/lte-rrc-sap.h>
#include <ns3/nstime.h>

namespace ns3 {

class A3RsrpHandoverAlgorithm : public LteHandoverAlgorithm
{
public:
  /// Creates a strongest cell handover algorithm instance.
  A3RsrpHandoverAlgorithm ();

  virtual ~A3RsrpHandoverAlgorithm ();

  // inherited from Object
  static TypeId GetTypeId ();

  // inherited from LteHandoverAlgorithm
  virtual void SetLteHandoverManagementSapUser (LteHandoverManagementSapUser* s);
  virtual LteHandoverManagementSapProvider* GetLteHandoverManagementSapProvider ();

  // let the forwarder class access the protected and private members
  friend class MemberLteHandoverManagementSapProvider<A3RsrpHandoverAlgorithm>;

protected:
  // inherited from Object
  virtual void DoInitialize ();
  virtual void DoDispose ();

  // inherited from LteHandoverAlgorithm as a Handover Management SAP implementation
  void DoReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults);

private:
 
  bool IsValidNeighbour (uint16_t cellId);

  /// The expected measurement identity for A3 measurements.
  uint8_t m_measId;

  double m_hysteresisDb;
 
  Time m_timeToTrigger;

 
  LteHandoverManagementSapUser* m_handoverManagementSapUser;
  /// Receive API calls from the eNodeB RRC instance.
  LteHandoverManagementSapProvider* m_handoverManagementSapProvider;

}; // end of class A3RsrpHandoverAlgorithm


} // end of namespace ns3


#endif /* A3_RSRP_HANDOVER_ALGORITHM_H */
