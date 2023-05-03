
#ifndef LTE_HELPER_H
#define LTE_HELPER_H

#include <ns3/config.h>
#include <ns3/simulator.h>
#include <ns3/names.h>
#include <ns3/net-device.h>
#include <ns3/net-device-container.h>
#include <ns3/node.h>
#include <ns3/node-container.h>
#include <ns3/eps-bearer.h>
#include <ns3/phy-stats-calculator.h>
#include <ns3/phy-tx-stats-calculator.h>
#include <ns3/phy-rx-stats-calculator.h>
#include <ns3/mac-stats-calculator.h>
#include <ns3/radio-bearer-stats-calculator.h>
#include <ns3/radio-bearer-stats-connector.h>
#include <ns3/epc-tft.h>
#include <ns3/mobility-model.h>

namespace ns3 {


class LteUePhy;
class LteEnbPhy;
class SpectrumChannel;
class EpcHelper;
class PropagationLossModel;
class SpectrumPropagationLossModel;


class LteHelper : public Object
{
public:
  LteHelper (void);
  virtual ~LteHelper (void);

  static TypeId GetTypeId (void);
  virtual void DoDispose (void);

  void SetEpcHelper (Ptr<EpcHelper> h);


  void SetPathlossModelType (std::string type);

  void SetPathlossModelAttribute (std::string n, const AttributeValue &v);

  void SetSchedulerType (std::string type);

 
  std::string GetSchedulerType () const; 

  void SetSchedulerAttribute (std::string n, const AttributeValue &v);

  void SetFfrAlgorithmType (std::string type);

 
  std::string GetFfrAlgorithmType () const;

  void SetFfrAlgorithmAttribute (std::string n, const AttributeValue &v);

  void SetHandoverAlgorithmType (std::string type);

 
  std::string GetHandoverAlgorithmType () const;

  void SetHandoverAlgorithmAttribute (std::string n, const AttributeValue &v);

  
  void SetEnbDeviceAttribute (std::string n, const AttributeValue &v);

  void SetEnbAntennaModelType (std::string type);

  void SetEnbAntennaModelAttribute (std::string n, const AttributeValue &v);

  void SetUeDeviceAttribute (std::string n, const AttributeValue &v);

  void SetUeAntennaModelType (std::string type);

  void SetUeAntennaModelAttribute (std::string n, const AttributeValue &v);

  void SetSpectrumChannelType (std::string type);

  void SetSpectrumChannelAttribute (std::string n, const AttributeValue &v);

  NetDeviceContainer InstallEnbDevice (NodeContainer c);

  NetDeviceContainer InstallUeDevice (NodeContainer c);


  void Attach (NetDeviceContainer ueDevices);

  void Attach (Ptr<NetDevice> ueDevice);

  void Attach (NetDeviceContainer ueDevices, Ptr<NetDevice> enbDevice);

  void Attach (Ptr<NetDevice> ueDevice, Ptr<NetDevice> enbDevice);

  
  void AttachToClosestEnb (NetDeviceContainer ueDevices, NetDeviceContainer enbDevices);

  
  void AttachToClosestEnb (Ptr<NetDevice> ueDevice, NetDeviceContainer enbDevices);

  
  uint8_t ActivateDedicatedEpsBearer (NetDeviceContainer ueDevices, EpsBearer bearer, Ptr<EpcTft> tft);

  
  uint8_t ActivateDedicatedEpsBearer (Ptr<NetDevice> ueDevice, EpsBearer bearer, Ptr<EpcTft> tft);


  void DeActivateDedicatedEpsBearer (Ptr<NetDevice> ueDevice, Ptr<NetDevice> enbDevice, uint8_t bearerId);
  /**
   * Create an X2 interface between all the eNBs in a given set.
   *
   * \param enbNodes the set of eNB nodes
   */
  void AddX2Interface (NodeContainer enbNodes);

  /**
   * Create an X2 interface between two eNBs.
   *
   * \param enbNode1 one eNB of the X2 interface
   * \param enbNode2 the other eNB of the X2 interface
   */
  void AddX2Interface (Ptr<Node> enbNode1, Ptr<Node> enbNode2);


  void HandoverRequest (Time hoTime, Ptr<NetDevice> ueDev,
                        Ptr<NetDevice> sourceEnbDev, Ptr<NetDevice> targetEnbDev);



  void ActivateDataRadioBearer (NetDeviceContainer ueDevices,  EpsBearer bearer);


  void ActivateDataRadioBearer (Ptr<NetDevice> ueDevice,  EpsBearer bearer);

  
  void SetFadingModel (std::string type);


  void SetFadingModelAttribute (std::string n, const AttributeValue &v);

  /**
   * Enables full-blown logging for major components of the LENA architecture.
   */
  void EnableLogComponents (void);

  /**
   * Enables trace sinks for PHY, MAC, RLC and PDCP. To make sure all nodes are
   * traced, traces should be enabled once all UEs and eNodeBs are in place and
   * connected, just before starting the simulation.
   */
  void EnableTraces (void);

  /**
   * Enable trace sinks for PHY layer.
   */
  void EnablePhyTraces (void);

  /**
   * Enable trace sinks for DL PHY layer.
   */
  void EnableDlPhyTraces (void);

  /**
   * Enable trace sinks for UL PHY layer.
   */
  void EnableUlPhyTraces (void);

  /**
   * Enable trace sinks for DL transmission PHY layer.
   */
  void EnableDlTxPhyTraces (void);

  /**
   * Enable trace sinks for UL transmission PHY layer.
   */
  void EnableUlTxPhyTraces (void);

  /**
   * Enable trace sinks for DL reception PHY layer.
   */
  void EnableDlRxPhyTraces (void);

  /**
   * Enable trace sinks for UL reception PHY layer.
   */
  void EnableUlRxPhyTraces (void);

  /**
   * Enable trace sinks for MAC layer.
   */
  void EnableMacTraces (void);

  /**
   * Enable trace sinks for DL MAC layer.
   */
  void EnableDlMacTraces (void);

  /**
   * Enable trace sinks for UL MAC layer.
   */
  void EnableUlMacTraces (void);

  /**
   * Enable trace sinks for RLC layer.
   */
  void EnableRlcTraces (void);

  /** 
   * 
   * \return the RLC stats calculator object
   */
  Ptr<RadioBearerStatsCalculator> GetRlcStats (void);

  /**
   * Enable trace sinks for PDCP layer
   */
  void EnablePdcpTraces (void);

  /** 
   * 
   * \return the PDCP stats calculator object
   */
  Ptr<RadioBearerStatsCalculator> GetPdcpStats (void);


  int64_t AssignStreams (NetDeviceContainer c, int64_t stream);

protected:
  // inherited from Object
  virtual void DoInitialize (void);

private:

  Ptr<NetDevice> InstallSingleEnbDevice (Ptr<Node> n);


  Ptr<NetDevice> InstallSingleUeDevice (Ptr<Node> n);


  void DoHandoverRequest (Ptr<NetDevice> ueDev,
                          Ptr<NetDevice> sourceEnbDev,
                          Ptr<NetDevice> targetEnbDev);


  
  void DoDeActivateDedicatedEpsBearer (Ptr<NetDevice> ueDevice, Ptr<NetDevice> enbDevice, uint8_t bearerId);


  /// The downlink LTE channel used in the simulation.
  Ptr<SpectrumChannel> m_downlinkChannel;
  /// The uplink LTE channel used in the simulation.
  Ptr<SpectrumChannel> m_uplinkChannel;
  /// The path loss model used in the downlink channel.
  Ptr<Object> m_downlinkPathlossModel;
  /// The path loss model used in the uplink channel.
  Ptr<Object> m_uplinkPathlossModel;

  /// Factory of MAC scheduler object.
  ObjectFactory m_schedulerFactory;
  /// Factory of FFR (frequency reuse) algorithm object.
  ObjectFactory m_ffrAlgorithmFactory;
  /// Factory of handover algorithm object.
  ObjectFactory m_handoverAlgorithmFactory;
  /// Factory of LteEnbNetDevice objects.
  ObjectFactory m_enbNetDeviceFactory;
  /// Factory of antenna object for eNodeB.
  ObjectFactory m_enbAntennaModelFactory;
  /// Factory for LteUeNetDevice objects.
  ObjectFactory m_ueNetDeviceFactory;
  /// Factory of antenna object for UE.
  ObjectFactory m_ueAntennaModelFactory;
  /// Factory of path loss model object for the downlink channel.
  ObjectFactory m_dlPathlossModelFactory;
  /// Factory of path loss model object for the uplink channel.
  ObjectFactory m_ulPathlossModelFactory;
  /// Factory of both the downlink and uplink LTE channels.
  ObjectFactory m_channelFactory;

  /// Name of fading model type, e.g., "ns3::TraceFadingLossModel".
  std::string m_fadingModelType;
  /// Factory of fading model object for both the downlink and uplink channels.
  ObjectFactory m_fadingModelFactory;
  /// The fading model used in both the downlink and uplink channels.
  Ptr<SpectrumPropagationLossModel> m_fadingModule;
  /**
   * True if a random variable stream number has been assigned for the fading
   * model. Used to prevent such assignment to be done more than once.
   */
  bool m_fadingStreamsAssigned;

  /// Container of PHY layer statistics.
  Ptr<PhyStatsCalculator> m_phyStats;
  /// Container of PHY layer statistics related to transmission.
  Ptr<PhyTxStatsCalculator> m_phyTxStats;
  /// Container of PHY layer statistics related to reception.
  Ptr<PhyRxStatsCalculator> m_phyRxStats;
  /// Container of MAC layer statistics.
  Ptr<MacStatsCalculator> m_macStats;
  /// Container of RLC layer statistics.
  Ptr<RadioBearerStatsCalculator> m_rlcStats;
  /// Container of PDCP layer statistics.
  Ptr<RadioBearerStatsCalculator> m_pdcpStats;
  /// Connects RLC and PDCP statistics containers to appropriate trace sources
  RadioBearerStatsConnector m_radioBearerStatsConnector;

  
  Ptr<EpcHelper> m_epcHelper;

 
  uint64_t m_imsiCounter;
 
  uint16_t m_cellIdCounter;

 
  bool m_useIdealRrc;
  
  bool m_isAnrEnabled;
 
  bool m_usePdschForCqiGeneration;

}; // end of `class LteHelper`


} // namespace ns3



#endif // LTE_HELPER_H
