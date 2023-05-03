
#ifndef LTE_HANDOVER_ALGORITHM_H
#define LTE_HANDOVER_ALGORITHM_H

#include <ns3/object.h>
#include <ns3/lte-rrc-sap.h>

namespace ns3 {


class LteHandoverManagementSapUser;
class LteHandoverManagementSapProvider;



class LteHandoverAlgorithm : public Object
{
public:
  LteHandoverAlgorithm ();
  virtual ~LteHandoverAlgorithm ();

  // inherited from Object
  static TypeId GetTypeId ();

  virtual void SetLteHandoverManagementSapUser (LteHandoverManagementSapUser* s) = 0;

 
  virtual LteHandoverManagementSapProvider* GetLteHandoverManagementSapProvider () = 0;

protected:

  // inherited from Object
  virtual void DoDispose ();

  
  virtual void DoReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults) = 0;

}; // end of class LteHandoverAlgorithm


} // end of namespace ns3


#endif /* LTE_HANDOVER_ALGORITHM_H */
