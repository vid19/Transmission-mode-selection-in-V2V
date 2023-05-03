

#ifndef LTE_VENDOR_SPECIFIC_PARAMETERS
#define LTE_VENDOR_SPECIFIC_PARAMETERS

#include <ns3/ff-mac-common.h>


#define SRS_CQI_RNTI_VSP 1


namespace ns3 {


class SrsCqiRntiVsp : public VendorSpecificValue
{
  public:
  SrsCqiRntiVsp (uint16_t rnti);
  virtual ~SrsCqiRntiVsp ();
  
  uint16_t GetRnti ();
  
  private:
  uint16_t m_rnti;
};



}; // namespace ns3

#endif /* LTE_VENDOR_SPECIFIC_PARAMETERS */

