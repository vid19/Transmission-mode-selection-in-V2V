
#include "lte-radio-bearer-info.h"
#include "lte-ue-rrc.h"
#include "lte-rlc.h"
#include "lte-pdcp.h"

#include <ns3/log.h>



namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (LteRadioBearerInfo);

LteRadioBearerInfo::LteRadioBearerInfo (void)
{
}

LteRadioBearerInfo::~LteRadioBearerInfo (void)
{
}
  
TypeId 
LteRadioBearerInfo::GetTypeId (void)
{
  static TypeId
    tid =
    TypeId ("ns3::LteRadioBearerInfo")
    .SetParent<Object> ()
    .AddConstructor<LteRadioBearerInfo> ()
    ;
  return tid;
}
  
  
TypeId 
LteDataRadioBearerInfo::GetTypeId (void)
{
  static TypeId
    tid =
    TypeId ("ns3::LteDataRadioBearerInfo")
    .SetParent<LteRadioBearerInfo> ()
    .AddConstructor<LteDataRadioBearerInfo> ()
    .AddAttribute ("DrbIdentity", "The id of this Data Radio Bearer",
                   TypeId::ATTR_GET, 
                   UintegerValue (0),
                   MakeUintegerAccessor (&LteDataRadioBearerInfo::m_drbIdentity),
                   MakeUintegerChecker<uint8_t> ())
    .AddAttribute ("EpsBearerIdentity", "The id of the EPS bearer corresponding to this Data Radio Bearer",
                   TypeId::ATTR_GET, 
                   UintegerValue (0),
                   MakeUintegerAccessor (&LteDataRadioBearerInfo::m_epsBearerIdentity),
                   MakeUintegerChecker<uint8_t> ())
    .AddAttribute ("logicalChannelIdentity", "The id of the Logical Channel corresponding to this Data Radio Bearer",
                   TypeId::ATTR_GET, 
                   UintegerValue (0),
                   MakeUintegerAccessor (&LteDataRadioBearerInfo::m_logicalChannelIdentity),
                   MakeUintegerChecker<uint8_t> ())
    .AddAttribute ("LteRlc", "RLC instance of the radio bearer.",
                   PointerValue (),
                   MakePointerAccessor (&LteRadioBearerInfo::m_rlc),
                   MakePointerChecker<LteRlc> ())
    .AddAttribute ("LtePdcp", "PDCP instance of the radio bearer.",
                   PointerValue (),
                   MakePointerAccessor (&LteRadioBearerInfo::m_pdcp),
                   MakePointerChecker<LtePdcp> ())
    ;
  return tid;
}


TypeId 
LteSignalingRadioBearerInfo::GetTypeId (void)
{
  static TypeId
    tid =
    TypeId ("ns3::LteSignalingRadioBearerInfo")
    .SetParent<LteRadioBearerInfo> ()
    .AddConstructor<LteSignalingRadioBearerInfo> ()
    .AddAttribute ("SrbIdentity", "The id of this Signaling Radio Bearer",
                   TypeId::ATTR_GET, // allow only getting it.
                   UintegerValue (0), // unused (attribute is read-only
                   MakeUintegerAccessor (&LteSignalingRadioBearerInfo::m_srbIdentity),
                   MakeUintegerChecker<uint8_t> ())
    .AddAttribute ("LteRlc", "RLC instance of the radio bearer.",
                   PointerValue (),
                   MakePointerAccessor (&LteRadioBearerInfo::m_rlc),
                   MakePointerChecker<LteRlc> ())
    .AddAttribute ("LtePdcp", "PDCP instance of the radio bearer.",
                   PointerValue (),
                   MakePointerAccessor (&LteRadioBearerInfo::m_pdcp),
                   MakePointerChecker<LtePdcp> ())
    ;
  return tid;
}



} // namespace ns3
