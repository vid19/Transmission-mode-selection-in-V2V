

#ifndef ENB_LTE_PHY_H
#define ENB_LTE_PHY_H


#include <ns3/lte-control-messages.h>
#include <ns3/lte-enb-phy-sap.h>
#include <ns3/lte-enb-cphy-sap.h>
#include <ns3/lte-phy.h>
#include <ns3/lte-harq-phy.h>

#include <map>
#include <set>



namespace ns3 {

class PacketBurst;
class LteNetDevice;
class LteUePhy;


class LteEnbPhy : public LtePhy
{
  friend class EnbMemberLteEnbPhySapProvider;
  friend class MemberLteEnbCphySapProvider<LteEnbPhy>;

public:
  
  LteEnbPhy ();

  LteEnbPhy (Ptr<LteSpectrumPhy> dlPhy, Ptr<LteSpectrumPhy> ulPhy);

  virtual ~LteEnbPhy ();

  // inherited from Object
  static TypeId GetTypeId (void);
  virtual void DoInitialize (void);
  virtual void DoDispose (void);


  LteEnbPhySapProvider* GetLteEnbPhySapProvider ();

  void SetLteEnbPhySapUser (LteEnbPhySapUser* s);

 
  LteEnbCphySapProvider* GetLteEnbCphySapProvider ();

  void SetLteEnbCphySapUser (LteEnbCphySapUser* s);

  void SetTxPower (double pow);

  double GetTxPower () const;

 
  int8_t DoGetReferenceSignalPower () const;

  /**
   * \param pow the noise figure in dB
   */
  void SetNoiseFigure (double pow);

  /**
   * \return the noise figure in dB
   */
  double GetNoiseFigure () const;

  void SetMacChDelay (uint8_t delay);

  uint8_t GetMacChDelay (void) const;

  /**
   * \return a pointer to the LteSpectrumPhy instance relative to the downlink
   */
  Ptr<LteSpectrumPhy> GetDlSpectrumPhy () const;

  /**
   * \return a pointer to the LteSpectrumPhy instance relative to the uplink
   */
  Ptr<LteSpectrumPhy> GetUlSpectrumPhy () const;

  void SetDownlinkSubChannels (std::vector<int> mask );

  void SetDownlinkSubChannelsWithPowerAllocation (std::vector<int> mask);
  
  std::vector<int> GetDownlinkSubChannels (void);

  void GeneratePowerAllocationMap (uint16_t rnti, int rbId);

  /**
   * \brief Create the PSD for TX
   */
  virtual Ptr<SpectrumValue> CreateTxPowerSpectralDensity ();

  /**
   * \brief Create the PSD for TX with power allocation for each RB
   */
  virtual Ptr<SpectrumValue> CreateTxPowerSpectralDensityWithPowerAllocation ();

  /**
   * \brief Calculate the channel quality for a given UE
   * \param sinr a list of computed SINR
   * \param ue the UE
   */
  void CalcChannelQualityForUe (std::vector <double> sinr, Ptr<LteSpectrumPhy> ue);

  /**
   * \brief Receive the control message
   * \param msg the received message
   */
  virtual void ReceiveLteControlMessage (Ptr<LteControlMessage> msg);

  FfMacSchedSapProvider::SchedUlCqiInfoReqParameters CreatePuschCqiReport (const SpectrumValue& sinr);

  FfMacSchedSapProvider::SchedUlCqiInfoReqParameters CreateSrsCqiReport (const SpectrumValue& sinr);

  /**
  * \brief Send the PDCCH and PCFICH in the first 3 symbols
  * \param ctrlMsgList the list of control messages of PDCCH
  */
  void SendControlChannels (std::list<Ptr<LteControlMessage> > ctrlMsgList);

  /**
  * \brief Send the PDSCH
  * \param pb the PacketBurst to be sent
  */
  void SendDataChannels (Ptr<PacketBurst> pb);

  /**
  * \param m the UL-CQI to be queued
  */
  void QueueUlDci (UlDciLteControlMessage m);

  /**
  * \returns the list of UL-CQI to be processed
  */
  std::list<UlDciLteControlMessage> DequeueUlDci (void);


  /**
   * \brief Start a LTE frame
   */
  void StartFrame (void);
  /**
   * \brief Start a LTE sub frame
   */
  void StartSubFrame (void);
  /**
   * \brief End a LTE sub frame
   */
  void EndSubFrame (void);
  /**
   * \brief End a LTE frame
   */
  void EndFrame (void);

  /**
   * \brief PhySpectrum received a new PHY-PDU
   */
  void PhyPduReceived (Ptr<Packet> p);

  /**
  * \brief PhySpectrum received a new list of LteControlMessage
  */
  virtual void ReceiveLteControlMessageList (std::list<Ptr<LteControlMessage> >);

  // inherited from LtePhy
  virtual void GenerateCtrlCqiReport (const SpectrumValue& sinr);
  virtual void GenerateDataCqiReport (const SpectrumValue& sinr);
  virtual void ReportInterference (const SpectrumValue& interf);
  virtual void ReportRsReceivedPower (const SpectrumValue& power);



  /**
  * \brief PhySpectrum generated a new UL HARQ feedback
  */
  virtual void ReceiveLteUlHarqFeedback (UlInfoListElement_s mes);

  void SetHarqPhyModule (Ptr<LteHarqPhy> harq);

  
  typedef void (* ReportUeSinrTracedCallback)
    (uint16_t cellId, uint16_t rnti, double sinrLinear);

 
  typedef void (* ReportInterferenceTracedCallback)
    (uint16_t cellId, Ptr<SpectrumValue> spectrumValue);

private:

  // LteEnbCphySapProvider forwarded methods
  void DoSetBandwidth (uint8_t ulBandwidth, uint8_t dlBandwidth);
  void DoSetEarfcn (uint16_t dlEarfcn, uint16_t ulEarfcn);
  void DoAddUe (uint16_t rnti);
  void DoRemoveUe (uint16_t rnti);
  void DoSetPa (uint16_t rnti, double pa);
  void DoSetTransmissionMode (uint16_t  rnti, uint8_t txMode);
  void DoSetSrsConfigurationIndex (uint16_t  rnti, uint16_t srcCi);
  void DoSetMasterInformationBlock (LteRrcSap::MasterInformationBlock mib);
  void DoSetSystemInformationBlockType1 (LteRrcSap::SystemInformationBlockType1 sib1);

  // LteEnbPhySapProvider forwarded methods
  void DoSendMacPdu (Ptr<Packet> p);
  void DoSendLteControlMessage (Ptr<LteControlMessage> msg);
  uint8_t DoGetMacChTtiDelay ();

  bool AddUePhy (uint16_t rnti);
  /**
   * Remove the given RNTI from the list of attached UE #m_ueAttached.
   * \param rnti RNTI of a UE
   * \return true if the RNTI has existed before, or false otherwise.
   */
  bool DeleteUePhy (uint16_t rnti);

  void CreateSrsReport (uint16_t rnti, double srs);

  /**
   * List of RNTI of attached UEs. Used for quickly determining whether a UE is
   * attached to this eNodeB or not.
   */
  std::set <uint16_t> m_ueAttached;


  /// P_A per UE RNTI.
  std::map <uint16_t,double> m_paMap;

  /// DL power allocation map.
  std::map <int, double> m_dlPowerAllocationMap;

  std::vector <int> m_listOfDownlinkSubchannel;

  std::vector <int> m_dlDataRbMap;

  /// For storing info on future receptions.
  std::vector< std::list<UlDciLteControlMessage> > m_ulDciQueue;

  LteEnbPhySapProvider* m_enbPhySapProvider;
  LteEnbPhySapUser* m_enbPhySapUser;

  LteEnbCphySapProvider* m_enbCphySapProvider;
  LteEnbCphySapUser* m_enbCphySapUser;

  uint32_t m_nrFrames;
  
  uint32_t m_nrSubFrames;

  uint16_t m_srsPeriodicity;
  Time m_srsStartTime;
  std::map <uint16_t,uint16_t> m_srsCounter;
  std::vector <uint16_t> m_srsUeOffset;
  uint16_t m_currentSrsOffset;

 
  LteRrcSap::MasterInformationBlock m_mib;
  
  LteRrcSap::SystemInformationBlockType1 m_sib1;

  Ptr<LteHarqPhy> m_harqPhyModule;

  TracedCallback<uint16_t, uint16_t, double> m_reportUeSinr;
  
  uint16_t m_srsSamplePeriod;
  std::map <uint16_t,uint16_t> m_srsSampleCounterMap;

  TracedCallback<uint16_t, Ptr<SpectrumValue> > m_reportInterferenceTrace;
  
  uint16_t m_interferenceSamplePeriod;
  uint16_t m_interferenceSampleCounter;

  TracedCallback<PhyTransmissionStatParameters> m_dlPhyTransmission;

}; // end of `class LteEnbPhy`


}

#endif /* LTE_ENB_PHY_H */
