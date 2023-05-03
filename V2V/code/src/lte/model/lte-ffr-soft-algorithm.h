

#ifndef LTE_FFR_SOFT_ALGORITHM_H
#define LTE_FFR_SOFT_ALGORITHM_H

#include <ns3/lte-ffr-algorithm.h>
#include <ns3/lte-ffr-sap.h>
#include <ns3/lte-ffr-rrc-sap.h>
#include <ns3/lte-rrc-sap.h>
#include <map>

namespace ns3 {


class LteFfrSoftAlgorithm : public LteFfrAlgorithm
{
public:

  LteFfrSoftAlgorithm ();

  virtual ~LteFfrSoftAlgorithm ();

  // inherited from Object
  static TypeId GetTypeId ();

  // inherited from LteFfrAlgorithm
  virtual void SetLteFfrSapUser (LteFfrSapUser* s);
  virtual LteFfrSapProvider* GetLteFfrSapProvider ();

  virtual void SetLteFfrRrcSapUser (LteFfrRrcSapUser* s);
  virtual LteFfrRrcSapProvider* GetLteFfrRrcSapProvider ();

  // let the forwarder class access the protected and private members
  friend class MemberLteFfrSapProvider<LteFfrSoftAlgorithm>;
  friend class MemberLteFfrRrcSapProvider<LteFfrSoftAlgorithm>;

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


  // FFR SAP
  LteFfrSapUser* m_ffrSapUser;
  LteFfrSapProvider* m_ffrSapProvider;

  // FFR RRF SAP
  LteFfrRrcSapUser* m_ffrRrcSapUser;
  LteFfrRrcSapProvider* m_ffrRrcSapProvider;

  uint8_t m_dlCommonSubBandwidth;
  uint8_t m_dlEgdeSubBandOffset;
  uint8_t m_dlEdgeSubBandwidth;

  uint8_t m_ulCommonSubBandwidth;
  uint8_t m_ulEgdeSubBandOffset;
  uint8_t m_ulEdgeSubBandwidth;

  std::vector <bool> m_dlRbgMap;
  std::vector <bool> m_ulRbgMap;

  std::vector <bool> m_dlCenterRbgMap;
  std::vector <bool> m_ulCenterRbgMap;

  std::vector <bool> m_dlMediumRbgMap;
  std::vector <bool> m_ulMediumRbgMap;

  std::vector <bool> m_dlEdgeRbgMap;
  std::vector <bool> m_ulEdgeRbgMap;

  enum UePosition
  {
    AreaUnset,
    CenterArea,
    MediumArea,
    EdgeArea
  };

  std::map< uint16_t, uint8_t > m_ues;

  uint8_t m_centerSubBandThreshold;
  uint8_t m_egdeSubBandThreshold;

  uint8_t m_centerAreaPowerOffset;
  uint8_t m_mediumAreaPowerOffset;
  uint8_t m_edgeAreaPowerOffset;

  uint8_t m_centerAreaTpc;
  uint8_t m_mediumAreaTpc;
  uint8_t m_edgeAreaTpc;

  // The expected measurement identity
  uint8_t m_measId;

}; // end of class LteFfrSoftAlgorithm


} // end of namespace ns3


#endif /* LTE_FFR_SOFT_ALGORITHM_H */
