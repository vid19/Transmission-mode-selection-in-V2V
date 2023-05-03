


#ifndef EPS_BEARER
#define EPS_BEARER

#include <ns3/uinteger.h>

namespace ns3 {


struct GbrQosInformation
{
 
  GbrQosInformation ();

  uint64_t gbrDl;  /**< Guaranteed Bit Rate (bit/s) in downlink */
  uint64_t gbrUl;  /**< Guaranteed Bit Rate (bit/s) in uplink */
  uint64_t mbrDl;  /**< Maximum Bit Rate (bit/s) in downlink */
  uint64_t mbrUl;  /**< Maximum Bit Rate (bit/s) in uplink */
};



struct AllocationRetentionPriority
{
 
  AllocationRetentionPriority ();
  uint8_t priorityLevel;     // /< 1-15; 1 = highest
  bool preemptionCapability; // /< true if bearer can preempt others
  bool preemptionVulnerability; // true if bearer can be preempted by others
};


struct EpsBearer
{


  enum Qci
  {
    GBR_CONV_VOICE          = 1,
    GBR_CONV_VIDEO          = 2,
    GBR_GAMING              = 3,
    GBR_NON_CONV_VIDEO      = 4,
    NGBR_IMS                = 5,
    NGBR_VIDEO_TCP_OPERATOR = 6,
    NGBR_VOICE_VIDEO_GAMING = 7,
    NGBR_VIDEO_TCP_PREMIUM  = 8,
    NGBR_VIDEO_TCP_DEFAULT  = 9,
		GBR_ULTRA_LOW_LAT				= 99,
  } qci;

  GbrQosInformation gbrQosInfo;
  AllocationRetentionPriority arp;

  /**
   * Deault constructor. QCI will be initialized to NGBR_VIDEO_TCP_DEFAULT
   * 
   */
  EpsBearer ();

  /**
   *
   * @param x the QoS Class Indicator
   *
   */
  EpsBearer (Qci x);

  EpsBearer (Qci x, GbrQosInformation y);

  /**
   *
   * @return true if the EPS Bearer is a Guaranteed Bit Rate bearer, false otherwise
   */
  bool IsGbr () const;

  /**
   *
   * @return the priority associated with the QCI of this bearer as per 3GPP 23.203 Section 6.1.7.2
   */
  uint8_t GetPriority () const;

  /**
   *
   *
   *
   * @return the packet delay budget associated with the QCI of this bearer as per 3GPP 23.203 Section 6.1.7.2
   */
  uint16_t GetPacketDelayBudgetMs () const;

  /**
   *
   *
   *
   * @return the packet error loss rate associated with the QCI of this bearer as per 3GPP 23.203 Section 6.1.7.2
   */
  double  GetPacketErrorLossRate () const;

};

} // namespace ns3


#endif // EPS_BEARER
