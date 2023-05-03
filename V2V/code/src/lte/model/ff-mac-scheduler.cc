

#include "ff-mac-scheduler.h"
#include <ns3/log.h>
#include <ns3/enum.h>


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("FfMacScheduler");

NS_OBJECT_ENSURE_REGISTERED (FfMacScheduler);


FfMacScheduler::FfMacScheduler ()
: m_ulCqiFilter (ALL_UL_CQI)
{
  NS_LOG_FUNCTION (this);
}


FfMacScheduler::~FfMacScheduler ()
{
  NS_LOG_FUNCTION (this);
}

void
FfMacScheduler::DoDispose ()
{
  NS_LOG_FUNCTION (this);
}

TypeId
FfMacScheduler::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::FfMacScheduler")
    .SetParent<Object> ()
    .SetGroupName("Lte")
    .AddAttribute ("UlCqiFilter",
                   "The filter to apply on UL CQIs received",
                   EnumValue (FfMacScheduler::ALL_UL_CQI),
                   MakeEnumAccessor (&FfMacScheduler::m_ulCqiFilter),
                   MakeEnumChecker (FfMacScheduler::SRS_UL_CQI, "SRS_UL_CQI",
                                    FfMacScheduler::PUSCH_UL_CQI, "PUSCH_UL_CQI",
                                    FfMacScheduler::ALL_UL_CQI, "ALL_UL_CQI"))
    ;
  return tid;
}


} // namespace ns3



