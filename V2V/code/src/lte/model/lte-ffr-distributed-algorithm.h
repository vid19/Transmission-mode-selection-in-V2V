

#ifndef LTE_FFR_DISTRIBUTED_ALGORITHM_H
#define LTE_FFR_DISTRIBUTED_ALGORITHM_H

#include <ns3/lte-ffr-algorithm.h>
#include <ns3/lte-ffr-sap.h>
#include <ns3/lte-ffr-rrc-sap.h>
#include <ns3/lte-rrc-sap.h>

namespace ns3 {


class LteFfrDistributedAlgorithm : public LteFfrAlgorithm
{
public:
  LteFfrDistributedAlgorithm ();
  virtual ~LteFfrDistributedAlgorithm ();

  // inherited from Object
  static TypeId GetTypeId ();

  // inherited from LteFfrAlgorithm
  virtual void SetLteFfrSapUser (LteFfrSapUser* s);
  virtual LteFfrSapProvider* GetLteFfrSapProvider ();

  virtual void SetLteFfrRrcSapUser (LteFfrRrcSapUser* s);
  virtual LteFfrRrcSapProvider* GetLteFfrRrcSapProvider ();

  // let the forwarder class access the protected and private members
  friend class MemberLteFfrSapProvider<LteFfrDistributedAlgorithm>;
  friend class MemberLteFfrRrcSapProvider<LteFfrDistributedAlgorithm>;

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

  void UpdateNeighbourMeasurements (uint16_t rnti, uint16_t cellId, uint8_t rsrp, uint8_t rsrq);

  void Calculate ();
  void SendLoadInformation (uint16_t targetCellId);

  // FFR SAP
  LteFfrSapUser* m_ffrSapUser;
  LteFfrSapProvider* m_ffrSapProvider;

  // FFR RRF SAP
  LteFfrRrcSapUser* m_ffrRrcSapUser;
  LteFfrRrcSapProvider* m_ffrRrcSapProvider;

  std::vector <bool> m_dlRbgMap;
  std::vector <bool> m_ulRbgMap;

  uint8_t m_edgeRbNum;
  std::vector <bool> m_dlEdgeRbgMap;
  std::vector <bool> m_ulEdgeRbgMap;

  enum UePosition
  {
    AreaUnset,
    CenterArea,
    EdgeArea
  };

  std::map< uint16_t, uint8_t > m_ues;

  uint8_t m_egdeSubBandRsrqThreshold;

  uint8_t m_centerPowerOffset;
  uint8_t m_edgePowerOffset;

  uint8_t m_centerAreaTpc;
  uint8_t m_edgeAreaTpc;

  Time m_calculationInterval;
  EventId m_calculationEvent;

  // The expected measurement identity
  uint8_t m_rsrqMeasId;
  uint8_t m_rsrpMeasId;

  /**
   * \brief Measurements reported by a UE for a cell ID.
   *
   * The values are quantized according 3GPP TS 36.133 section 9.1.4 and 9.1.7.
   */
  class UeMeasure : public SimpleRefCount<UeMeasure>
  {
public:
    uint16_t m_cellId;
    uint8_t m_rsrp;
    uint8_t m_rsrq;
  };

  //               cellId
  typedef std::map<uint16_t, Ptr<UeMeasure> > MeasurementRow_t;
  //               rnti
  typedef std::map<uint16_t, MeasurementRow_t> MeasurementTable_t;
  MeasurementTable_t m_ueMeasures;

  std::vector<uint16_t> m_neigborCell;

  uint8_t m_rsrpDifferenceThreshold;

  std::map<uint16_t, uint32_t> m_cellWeightMap;

  std::map<uint16_t, std::vector <bool> > m_rntp;

}; // end of class LteFfrDistributedAlgorithm

} // end of namespace ns3

#endif /* LTE_FR_DISTRIBUTED_ALGORITHM_H */
