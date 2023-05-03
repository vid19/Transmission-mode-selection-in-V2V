

#ifndef EPC_ENB_APPLICATION_H
#define EPC_ENB_APPLICATION_H

#include <ns3/address.h>
#include <ns3/socket.h>
#include <ns3/virtual-net-device.h>
#include <ns3/traced-callback.h>
#include <ns3/callback.h>
#include <ns3/ptr.h>
#include <ns3/object.h>
#include <ns3/lte-common.h>
#include <ns3/application.h>
#include <ns3/eps-bearer.h>
#include <ns3/epc-enb-s1-sap.h>
#include <ns3/epc-s1ap-sap.h>
#include <map>

namespace ns3 {
class EpcEnbS1SapUser;
class EpcEnbS1SapProvider;


class EpcEnbApplication : public Application
{

  friend class MemberEpcEnbS1SapProvider<EpcEnbApplication>;
  friend class MemberEpcS1apSapEnb<EpcEnbApplication>;


  // inherited from Object
public:
  static TypeId GetTypeId (void);
protected:
  void DoDispose (void);

public:
  
  
  EpcEnbApplication (Ptr<Socket> lteSocket, Ptr<Socket> s1uSocket, Ipv4Address enbS1uAddress, Ipv4Address sgwS1uAddress, uint16_t cellId);

  virtual ~EpcEnbApplication (void);

  void SetS1SapUser (EpcEnbS1SapUser * s);

  EpcEnbS1SapProvider* GetS1SapProvider ();

  void SetS1apSapMme (EpcS1apSapMme * s);

  EpcS1apSapEnb* GetS1apSapEnb ();
 
  void RecvFromLteSocket (Ptr<Socket> socket);

  void RecvFromS1uSocket (Ptr<Socket> socket);


  struct EpsFlowId_t
  {
    uint16_t  m_rnti;
    uint8_t   m_bid;

  public:
    EpsFlowId_t ();
    EpsFlowId_t (const uint16_t a, const uint8_t b);

    friend bool operator == (const EpsFlowId_t &a, const EpsFlowId_t &b);
    friend bool operator < (const EpsFlowId_t &a, const EpsFlowId_t &b);
  };


private:

  // ENB S1 SAP provider methods
  void DoInitialUeMessage (uint64_t imsi, uint16_t rnti);
  void DoPathSwitchRequest (EpcEnbS1SapProvider::PathSwitchRequestParameters params);
  void DoUeContextRelease (uint16_t rnti);
  
  // S1-AP SAP ENB methods
  void DoInitialContextSetupRequest (uint64_t mmeUeS1Id, uint16_t enbUeS1Id, std::list<EpcS1apSapEnb::ErabToBeSetupItem> erabToBeSetupList);
  void DoPathSwitchRequestAcknowledge (uint64_t enbUeS1Id, uint64_t mmeUeS1Id, uint16_t cgi, std::list<EpcS1apSapEnb::ErabSwitchedInUplinkItem> erabToBeSwitchedInUplinkList);


  void DoReleaseIndication (uint64_t imsi, uint16_t rnti, uint8_t bearerId);


  void SendToLteSocket (Ptr<Packet> packet, uint16_t rnti, uint8_t bid);


  void SendToS1uSocket (Ptr<Packet> packet, uint32_t teid);

  void SetupS1Bearer (uint32_t teid, uint16_t rnti, uint8_t bid);

  Ptr<Socket> m_lteSocket;

  Ptr<Socket> m_s1uSocket;

  Ipv4Address m_enbS1uAddress;

  Ipv4Address m_sgwS1uAddress;

  std::map<uint16_t, std::map<uint8_t, uint32_t> > m_rbidTeidMap;  

  /**
   * map telling for each S1-U TEID the corresponding RNTI,BID
   * 
   */
  std::map<uint32_t, EpsFlowId_t> m_teidRbidMap;
 
  /**
   * UDP port to be used for GTP
   */
  uint16_t m_gtpuUdpPort;

  /**
   * Provider for the S1 SAP 
   */
  EpcEnbS1SapProvider* m_s1SapProvider;

  /**
   * User for the S1 SAP 
   */
  EpcEnbS1SapUser* m_s1SapUser;

  /**
   * MME side of the S1-AP SAP
   * 
   */
  EpcS1apSapMme* m_s1apSapMme;

  /**
   * ENB side of the S1-AP SAP
   * 
   */
  EpcS1apSapEnb* m_s1apSapEnb;

  /**
   * UE context info
   * 
   */
  std::map<uint64_t, uint16_t> m_imsiRntiMap;

  uint16_t m_cellId;

};

} //namespace ns3

#endif /* EPC_ENB_APPLICATION_H */

