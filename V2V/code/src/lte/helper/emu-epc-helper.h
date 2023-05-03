

#ifndef EMU_EPC_HELPER_H
#define EMU_EPC_HELPER_H

#include <ns3/object.h>
#include <ns3/ipv4-address-helper.h>
#include <ns3/data-rate.h>
#include <ns3/epc-tft.h>
#include <ns3/eps-bearer.h>
#include <ns3/epc-helper.h>

namespace ns3 {

class Node;
class NetDevice;
class VirtualNetDevice;
class EpcSgwPgwApplication;
class EpcX2;
class EpcMme;

class EmuEpcHelper : public EpcHelper
{
public:
  
  
  EmuEpcHelper ();

   
  virtual ~EmuEpcHelper ();
  
  static TypeId GetTypeId (void);
  virtual void DoInitialize ();
  virtual void DoDispose ();

  // inherited from EpcHelper
  virtual void AddEnb (Ptr<Node> enbNode, Ptr<NetDevice> lteEnbNetDevice, uint16_t cellId);
  virtual void AddUe (Ptr<NetDevice> ueLteDevice, uint64_t imsi);
  virtual void AddX2Interface (Ptr<Node> enbNode1, Ptr<Node> enbNode2);
  virtual uint8_t ActivateEpsBearer (Ptr<NetDevice> ueLteDevice, uint64_t imsi, Ptr<EpcTft> tft, EpsBearer bearer);
  virtual Ptr<Node> GetPgwNode ();
  virtual Ipv4InterfaceContainer AssignUeIpv4Address (NetDeviceContainer ueDevices);
  virtual Ipv4Address GetUeDefaultGatewayAddress ();



private:

  Ipv4AddressHelper m_ueAddressHelper; 

   
  Ptr<Node> m_sgwPgw; 

  Ptr<EpcSgwPgwApplication> m_sgwPgwApp;

  Ptr<VirtualNetDevice> m_tunDevice;

  Ptr<EpcMme> m_mme;

 
  Ipv4AddressHelper m_epcIpv4AddressHelper; 

 
  uint16_t m_gtpuUdpPort;

  /**
   * Map storing for each IMSI the corresponding eNB NetDevice
   * 
   */
  std::map<uint64_t, Ptr<NetDevice> > m_imsiEnbDeviceMap;

  /**
   * Container for Ipv4Interfaces of the SGW/PGW
   */
  Ipv4InterfaceContainer m_sgwIpIfaces; 

  /**
   * The name of the device used for the S1-U interface of the SGW
   */
  std::string m_sgwDeviceName;

  /**
   * The name of the device used for the S1-U interface of the eNB
   */
  std::string m_enbDeviceName;

  /**
   * MAC address used for the SGW
   */
  std::string m_sgwMacAddress;

  /**
   * First 5 bytes of the Enb MAC address base
   */
  std::string m_enbMacAddressBase;
};




} // namespace ns3

#endif // EMU_EPC_HELPER_H
