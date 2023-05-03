
#ifndef NO_OP_HANDOVER_ALGORITHM_H
#define NO_OP_HANDOVER_ALGORITHM_H

#include <ns3/lte-handover-algorithm.h>
#include <ns3/lte-handover-management-sap.h>
#include <ns3/lte-rrc-sap.h>

namespace ns3 {

class NoOpHandoverAlgorithm : public LteHandoverAlgorithm
{
public:
  /// Creates a No-op handover algorithm instance.
  NoOpHandoverAlgorithm ();

  virtual ~NoOpHandoverAlgorithm ();

  // inherited from Object
  static TypeId GetTypeId ();

  // inherited from LteHandoverAlgorithm
  virtual void SetLteHandoverManagementSapUser (LteHandoverManagementSapUser* s);
  virtual LteHandoverManagementSapProvider* GetLteHandoverManagementSapProvider ();

  // let the forwarder class access the protected and private members
  friend class MemberLteHandoverManagementSapProvider<NoOpHandoverAlgorithm>;

protected:
  // inherited from Object
  virtual void DoInitialize ();
  virtual void DoDispose ();

  // inherited from LteHandoverAlgorithm as a Handover Management SAP implementation
  void DoReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults);

private:
  /// Interface to the eNodeB RRC instance.
  LteHandoverManagementSapUser* m_handoverManagementSapUser;
  /// Receive API calls from the eNodeB RRC instance.
  LteHandoverManagementSapProvider* m_handoverManagementSapProvider;

}; // end of class NoOpHandoverAlgorithm


} // end of namespace ns3


#endif /* NO_OP_HANDOVER_ALGORITHM_H */
