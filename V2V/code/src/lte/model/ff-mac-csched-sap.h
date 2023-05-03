

#ifndef FF_MAC_CSCHED_SAP_H
#define FF_MAC_CSCHED_SAP_H

#include <stdint.h>
#include <vector>

#include "ff-mac-common.h"

namespace ns3 {


class FfMacCschedSapProvider
{
public:
  virtual ~FfMacCschedSapProvider ();

  
  struct CschedCellConfigReqParameters
  {
    uint8_t m_puschHoppingOffset;

    enum HoppingMode_e
    {
      inter,
      interintra
    } m_hoppingMode;

    uint8_t m_nSb;

    enum PhichResource_e
    {
      PHICH_R_ONE_SIXTH,
      PHICH_R_HALF,
      PHICH_R_ONE,
      PHICH_R_TWO
    } m_phichResource;


    enum NormalExtended_e m_phichDuration;

    uint8_t m_initialNrOfPdcchOfdmSymbols;

    struct SiConfiguration_s m_siConfiguration;

    uint8_t m_ulBandwidth;
    uint8_t m_dlBandwidth;

    enum NormalExtended_e m_ulCyclicPrefixLength;
    enum NormalExtended_e m_dlCyclicPrefixLength;

    uint8_t m_antennaPortsCount;

    enum DuplexMode_e
    {
      DM_TDD,
      DM_FDD
    } m_duplexMode;

    uint8_t m_subframeAssignment;
    uint8_t m_specialSubframePatterns;
    std::vector <uint8_t> m_mbsfnSubframeConfigRfPeriod;
    std::vector <uint8_t> m_mbsfnSubframeConfigRfOffset;
    std::vector <uint8_t> m_mbsfnSubframeConfigSfAllocation;
    uint8_t m_prachConfigurationIndex;
    uint8_t m_prachFreqOffset;
    uint8_t m_raResponseWindowSize;
    uint8_t m_macContentionResolutionTimer;
    uint8_t m_maxHarqMsg3Tx;
    uint16_t m_n1PucchAn;
    uint8_t m_deltaPucchShift;
    uint8_t m_nrbCqi;
    uint8_t m_ncsAn;
    uint8_t m_srsSubframeConfiguration;
    uint8_t m_srsSubframeOffset;
    uint8_t m_srsBandwidthConfiguration;
    bool    m_srsMaxUpPts;

    enum Enable64Qam_e
    {
      MOD_16QAM,
      MOD_64QAM
    } m_enable64Qam;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  
  struct CschedUeConfigReqParameters
  {
    uint16_t  m_rnti;
    bool      m_reconfigureFlag;
    bool      m_drxConfigPresent;
    struct DrxConfig_s m_drxConfig;
    uint16_t  m_timeAlignmentTimer;

    enum MeasGapConfigPattern_e
    {
      MGP_GP1,
      MGP_GP2,
      OFF
    } m_measGapConfigPattern;

    uint8_t   m_measGapConfigSubframeOffset;
    bool      m_spsConfigPresent;
    struct SpsConfig_s m_spsConfig;
    bool      m_srConfigPresent;
    struct SrConfig_s m_srConfig;
    bool      m_cqiConfigPresent;
    struct CqiConfig_s m_cqiConfig;
    uint8_t   m_transmissionMode;
    uint64_t  m_ueAggregatedMaximumBitrateUl;
    uint64_t  m_ueAggregatedMaximumBitrateDl;
    struct UeCapabilities_s m_ueCapabilities;

    enum OpenClosedLoop_e
    {
      noneloop,
      openloop,
      closedloop
    } m_ueTransmitAntennaSelection;

    bool      m_ttiBundling;
    uint8_t   m_maxHarqTx;
    uint8_t   m_betaOffsetAckIndex;
    uint8_t   m_betaOffsetRiIndex;
    uint8_t   m_betaOffsetCqiIndex;
    bool      m_ackNackSrsSimultaneousTransmission;
    bool      m_simultaneousAckNackAndCqi;

    enum RepMode_e
    {
      rm12, rm20, rm22, rm30, rm31, nonemode
    } m_aperiodicCqiRepMode;

    enum FeedbackMode_e
    {
      bundling,
      multiplexing
    } m_tddAckNackFeedbackMode;

    uint8_t   m_ackNackRepetitionFactor;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  struct CschedLcConfigReqParameters
  {
    uint16_t  m_rnti;
    bool      m_reconfigureFlag;

    std::vector <struct LogicalChannelConfigListElement_s> m_logicalChannelConfigList;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  
  struct CschedLcReleaseReqParameters
  {
    uint16_t  m_rnti;

    std::vector <uint8_t> m_logicalChannelIdentity;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  struct CschedUeReleaseReqParameters
  {
    uint16_t  m_rnti;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

 
  virtual void CschedCellConfigReq (const struct CschedCellConfigReqParameters& params) = 0;

  virtual void CschedUeConfigReq (const struct CschedUeConfigReqParameters& params) = 0;

  virtual void CschedLcConfigReq (const struct CschedLcConfigReqParameters& params) = 0;

  virtual void CschedLcReleaseReq (const struct CschedLcReleaseReqParameters& params) = 0;

  virtual void CschedUeReleaseReq (const struct CschedUeReleaseReqParameters& params) = 0;

private:
};


class FfMacCschedSapUser
{
public:
  virtual ~FfMacCschedSapUser ();

  struct CschedCellConfigCnfParameters
  {
    enum Result_e m_result;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  
  struct CschedUeConfigCnfParameters
  {
    uint16_t  m_rnti;
    enum Result_e m_result;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  struct CschedLcConfigCnfParameters
  {
    uint16_t  m_rnti;
    enum Result_e m_result;

    std::vector <uint8_t> m_logicalChannelIdentity;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

 
  struct CschedLcReleaseCnfParameters
  {
    uint16_t  m_rnti;
    enum Result_e m_result;

    std::vector <uint8_t> m_logicalChannelIdentity;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  struct CschedUeReleaseCnfParameters
  {
    uint16_t  m_rnti;
    enum Result_e m_result;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

 
  struct CschedUeConfigUpdateIndParameters
  {
    uint16_t  m_rnti;
    uint8_t   m_transmissionMode;
    bool      m_spsConfigPresent;
    struct SpsConfig_s m_spsConfig;
    bool      m_srConfigPresent;
    struct SrConfig_s m_srConfig;
    bool      m_cqiConfigPresent;
    struct CqiConfig_s m_cqiConfig;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  
  struct CschedCellConfigUpdateIndParameters
  {
    uint8_t   m_prbUtilizationDl;
    uint8_t   m_prbUtilizationUl;

    std::vector <struct VendorSpecificListElement_s> m_vendorSpecificList;
  };

  //
  // CSCHED - MAC Scheduler Control SAP primitives
  // (See 4.1 for description of the primitives)
  //

  virtual void CschedCellConfigCnf (const struct CschedCellConfigCnfParameters& params) = 0;

  virtual void CschedUeConfigCnf (const struct CschedUeConfigCnfParameters& params) = 0;

  virtual void CschedLcConfigCnf (const struct CschedLcConfigCnfParameters& params) = 0;

  virtual void CschedLcReleaseCnf (const struct CschedLcReleaseCnfParameters& params) = 0;

  virtual void CschedUeReleaseCnf (const struct CschedUeReleaseCnfParameters& params) = 0;

  virtual void CschedUeConfigUpdateInd (const struct CschedUeConfigUpdateIndParameters& params) = 0;

  virtual void CschedCellConfigUpdateInd (const struct CschedCellConfigUpdateIndParameters& params) = 0;

private:
};

} // end namespace ns3

#endif /* FF_MAC_CSCHED_SAP_H */
