
#ifndef LTE_RADIO_BEARER_INFO_H
#define LTE_RADIO_BEARER_INFO_H

#include <ns3/object.h>
#include <ns3/pointer.h>
#include <ns3/eps-bearer.h>
#include <ns3/lte-rrc-sap.h>
#include <ns3/ipv4-address.h>

namespace ns3 {

class LteRlc;
class LtePdcp;


class LteRadioBearerInfo : public Object
{

public:
  LteRadioBearerInfo (void);
  virtual ~LteRadioBearerInfo (void);
  static TypeId GetTypeId (void);

  Ptr<LteRlc> m_rlc;
  Ptr<LtePdcp> m_pdcp;  
};



class LteSignalingRadioBearerInfo : public LteRadioBearerInfo
{

public:
  static TypeId GetTypeId (void);

  uint8_t m_srbIdentity;   
  LteRrcSap::LogicalChannelConfig m_logicalChannelConfig;  
};


class LteDataRadioBearerInfo : public LteRadioBearerInfo
{

public:
  static TypeId GetTypeId (void);

  EpsBearer m_epsBearer;
  uint8_t m_epsBearerIdentity;
  uint8_t m_drbIdentity;
  LteRrcSap::RlcConfig m_rlcConfig;
  uint8_t m_logicalChannelIdentity;
  LteRrcSap::LogicalChannelConfig m_logicalChannelConfig;
  uint32_t m_gtpTeid; /**< S1-bearer GTP tunnel endpoint identifier, see 36.423 9.2.1 */
  Ipv4Address m_transportLayerAddress; /**< IP Address of the SGW, see 36.423 9.2.1 */
};

} // namespace ns3


#endif // LTE_RADIO_BEARER_INFO_H
