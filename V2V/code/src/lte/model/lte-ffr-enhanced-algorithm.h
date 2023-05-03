

#ifndef LTE_FFR_ENHANCED_ALGORITHM_H
#define LTE_FFR_ENHANCED_ALGORITHM_H

#include <ns3/lte-ffr-algorithm.h>
#include <ns3/lte-ffr-sap.h>
#include <ns3/lte-ffr-rrc-sap.h>
#include <ns3/lte-rrc-sap.h>
#include <map>


#define NO_SINR -5000

namespace ns3 {

class LteFfrEnhancedAlgorithm : public LteFfrAlgorithm
{
public:
 
  LteFfrEnhancedAlgorithm ();
  virtual ~LteFfrEnhancedAlgorithm ();

  static TypeId GetTypeId ();

  // inherited from LteFfrAlgorithm
  virtual void SetLteFfrSapUser (LteFfrSapUser* s);
  virtual LteFfrSapProvider* GetLteFfrSapProvider ();

  virtual void SetLteFfrRrcSapUser (LteFfrRrcSapUser* s);
  virtual LteFfrRrcSapProvider* GetLteFfrRrcSapProvider ();

  // let the forwarder class access the protected and private members
  friend class MemberLteFfrSapProvider<LteFfrEnhancedAlgorithm>;
  friend class MemberLteFfrRrcSapProvider<LteFfrEnhancedAlgorithm>;

protected:
  // inherited from Object
  virtual void DoInitialize ();
  virtual void DoDispose ();

  virtual void Reconfigure ();

  // FFR SAP PROVIDER IMPLEMENTATION
  virtual std::vector <bool> DoGetAvailableDlRbg ();
  virtual bool DoIsDlRbgAvailableForUe (int i, uint16_t rnti);
  virtual std::vector <bool> DoGetAvailableUlRbg ();
  virtual bool DoIsUlRbgAvailableForUe (int i, uint16_t rnti);
  virtual void DoReportDlCqiInfo (const struct FfMacSchedSapProvider::SchedDlCqiInfoReqParameters& params);
  virtual void DoReportUlCqiInfo (const struct FfMacSchedSapProvider::SchedUlCqiInfoReqParameters& params);
  virtual void DoReportUlCqiInfo ( std::map <uint16_t, std::vector <double> > ulCqiMap );
  virtual uint8_t DoGetTpc (uint16_t rnti);
  virtual uint8_t DoGetMinContinuousUlBandwidth ();

  // FFR SAP RRC PROVIDER IMPLEMENTATION
  virtual void DoReportUeMeas (uint16_t rnti, LteRrcSap::MeasResults measResults);
  virtual void DoRecvLoadInformation (EpcX2Sap::LoadInformationParams params);

private:
  void SetDownlinkConfiguration (uint16_t cellId, uint8_t bandwidth);
  void SetUplinkConfiguration (uint16_t cellId, uint8_t bandwidth);
  void InitializeDownlinkRbgMaps ();
  void InitializeUplinkRbgMaps ();

  double EstimateUlSinr (uint16_t rnti, uint16_t rb, std::map <uint16_t, std::vector <double> > ulCqiMap);
  int GetCqiFromSpectralEfficiency (double s);

  // FFR SAP
  LteFfrSapUser* m_ffrSapUser;
  LteFfrSapProvider* m_ffrSapProvider;

  // FFR RRF SAP
  LteFfrRrcSapUser* m_ffrRrcSapUser;
  LteFfrRrcSapProvider* m_ffrRrcSapProvider;

  uint8_t m_dlSubBandOffset;
  uint8_t m_dlReuse3SubBandwidth;
  uint8_t m_dlReuse1SubBandwidth;

  uint8_t m_ulSubBandOffset;
  uint8_t m_ulReuse3SubBandwidth;
  uint8_t m_ulReuse1SubBandwidth;

  std::vector <bool> m_dlRbgMap;
  std::vector <bool> m_ulRbgMap;

  std::vector <bool> m_dlReuse3RbgMap;
  std::vector <bool> m_dlReuse1RbgMap;
  std::vector <bool> m_dlPrimarySegmentRbgMap;
  std::vector <bool> m_dlSecondarySegmentRbgMap;

  std::vector <bool> m_ulReuse3RbgMap;
  std::vector <bool> m_ulReuse1RbgMap;
  std::vector <bool> m_ulPrimarySegmentRbgMap;
  std::vector <bool> m_ulSecondarySegmentRbgMap;

  enum UePosition
  {
    AreaUnset,
    CenterArea,
    EdgeArea
  };

  std::map< uint16_t, uint8_t > m_ues;

  uint8_t m_rsrqThreshold;

  uint8_t m_centerAreaPowerOffset;
  uint8_t m_edgeAreaPowerOffset;

  uint8_t m_centerAreaTpc;
  uint8_t m_edgeAreaTpc;


  uint8_t m_dlCqiThreshold;
  /*
  * Map of UE's DL CQI A30 received
  */
  std::map <uint16_t,SbMeasResult_s> m_dlCqi;
  std::map <uint16_t, std::vector<bool> > m_dlRbgAvailableforUe;

  uint8_t m_ulCqiThreshold;
  std::map <uint16_t, std::vector<int> > m_ulCqi;
  std::map <uint16_t, std::vector<bool> > m_ulRbAvailableforUe;

  // The expected measurement identity
  uint8_t m_measId;

}; // end of class LteFfrEnhancedAlgorithm

} // end of namespace ns3

#endif /* LTE_FFR_ENHANCED_ALGORITHM_H */
