


#include "eps-bearer.h"

#include <ns3/fatal-error.h>


namespace ns3 {


GbrQosInformation::GbrQosInformation ()
  : gbrDl (0),
    gbrUl (0),
    mbrDl (0),
    mbrUl (0)
{
}

AllocationRetentionPriority::AllocationRetentionPriority ()
  : priorityLevel (0),
    preemptionCapability (false),
    preemptionVulnerability (false)
{
}

EpsBearer::EpsBearer ()
  : qci (NGBR_VIDEO_TCP_DEFAULT)
{
}

EpsBearer::EpsBearer (Qci x)
  : qci (x)
{
}

EpsBearer::EpsBearer (Qci x, struct GbrQosInformation y)
  : qci (x), gbrQosInfo (y)
{
}

bool
EpsBearer::IsGbr () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
    case GBR_CONV_VIDEO:
    case GBR_GAMING:
    case GBR_NON_CONV_VIDEO:
    case GBR_ULTRA_LOW_LAT:
      return true;
    case NGBR_IMS:
    case NGBR_VIDEO_TCP_OPERATOR:
    case NGBR_VOICE_VIDEO_GAMING:
    case NGBR_VIDEO_TCP_PREMIUM:
    case NGBR_VIDEO_TCP_DEFAULT:
      return false;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return false;
    }
}

uint8_t
EpsBearer::GetPriority () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
      return 2;
    case GBR_CONV_VIDEO:
      return 4;
    case GBR_GAMING:
      return 3;
    case GBR_NON_CONV_VIDEO:
      return 5;
    case NGBR_IMS:
      return 1;
    case NGBR_VIDEO_TCP_OPERATOR:
      return 6;
    case NGBR_VOICE_VIDEO_GAMING:
      return 7;
    case NGBR_VIDEO_TCP_PREMIUM:
      return 8;
    case GBR_ULTRA_LOW_LAT:
      return 1;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}

uint16_t
EpsBearer::GetPacketDelayBudgetMs () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
      return 100;
    case GBR_CONV_VIDEO:
      return 150;
    case GBR_GAMING:
      return 50;
    case GBR_NON_CONV_VIDEO:
      return 300;
    case NGBR_IMS:
      return 100;
    case NGBR_VIDEO_TCP_OPERATOR:
      return 300;
    case NGBR_VOICE_VIDEO_GAMING:
      return 100;
    case NGBR_VIDEO_TCP_PREMIUM:
      return 300;
    case NGBR_VIDEO_TCP_DEFAULT:
      return 300;
    case GBR_ULTRA_LOW_LAT:
      return 1;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}

double
EpsBearer::GetPacketErrorLossRate () const
{
  // 3GPP 23.203 Section 6.1.7.2
  switch (qci)
    {
    case GBR_CONV_VOICE:
      return 1.0e-2;
    case GBR_CONV_VIDEO:
      return 1.0e-3;
    case GBR_GAMING:
      return 1.0e-3;
    case GBR_NON_CONV_VIDEO:
      return 1.0e-6;
    case NGBR_IMS:
      return 1.0e-6;
    case NGBR_VIDEO_TCP_OPERATOR:
      return 1.0e-6;
    case NGBR_VOICE_VIDEO_GAMING:
      return 1.0e-3;
    case NGBR_VIDEO_TCP_PREMIUM:
      return 1.0e-6;
    case NGBR_VIDEO_TCP_DEFAULT:
      return 1.0e-6;
    case GBR_ULTRA_LOW_LAT:
    	return 1.0e-6;
    default:
      NS_FATAL_ERROR ("unknown QCI value " << qci);
      return 0;
    }
}



} // namespace ns3