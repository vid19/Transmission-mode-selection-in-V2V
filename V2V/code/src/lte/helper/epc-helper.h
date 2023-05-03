

#ifndef EPC_HELPER_H
#define EPC_HELPER_H

#include <ns3/object.h>
#include <ns3/ipv4-address-helper.h>
#include <ns3/data-rate.h>
#include <ns3/epc-tft.h>
#include <ns3/eps-bearer.h>

namespace ns3 {

class Node;
class NetDevice;
class VirtualNetDevice;
class EpcSgwPgwApplication;
class EpcX2;
class EpcMme;


class EpcHelper : public Object
{
public:
  
 
  EpcHelper ();

   
  virtual ~EpcHelper ();
  
  
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

  virtual void AddEnb (Ptr<Node> enbNode, Ptr<NetDevice> lteEnbNetDevice, uint16_t cellId) = 0;

  virtual void AddUe (Ptr<NetDevice> ueLteDevice, uint64_t imsi) = 0;

  virtual void AddX2Interface (Ptr<Node> enbNode1, Ptr<Node> enbNode2) = 0;

  virtual uint8_t ActivateEpsBearer (Ptr<NetDevice> ueLteDevice, uint64_t imsi, Ptr<EpcTft> tft, EpsBearer bearer) = 0;


  virtual Ptr<Node> GetPgwNode () = 0;

  virtual Ipv4InterfaceContainer AssignUeIpv4Address (NetDeviceContainer ueDevices) = 0;


  virtual Ipv4Address GetUeDefaultGatewayAddress () = 0;


};




} // namespace ns3

#endif // EPC_HELPER_H
