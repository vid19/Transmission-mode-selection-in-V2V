

#ifndef EPC_SGW_PGW_APPLICATION_H
#define EPC_SGW_PGW_APPLICATION_H

#include <ns3/address.h>
#include <ns3/socket.h>
#include <ns3/virtual-net-device.h>
#include <ns3/traced-callback.h>
#include <ns3/callback.h>
#include <ns3/ptr.h>
#include <ns3/object.h>
#include <ns3/eps-bearer.h>
#include <ns3/epc-tft.h>
#include <ns3/epc-tft-classifier.h>
#include <ns3/lte-common.h>
#include <ns3/application.h>
#include <ns3/epc-s1ap-sap.h>
#include <ns3/epc-sr-sap.h>
#include <map>

namespace ns3 {


class EpcSgwPgwApplication : public Application
{
  friend class MemberEpcSRSapSgw<EpcSgwPgwApplication>;

public:

  // inherited from Object
  static TypeId GetTypeId (void);
  virtual void DoDispose ();


  EpcSgwPgwApplication (const Ptr<VirtualNetDevice> tunDevice, const Ptr<Socket> s1uSocket);

  virtual ~EpcSgwPgwApplication (void);
  

  bool RecvFromTunDevice (Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber);



  void RecvFromS1uSocket (Ptr<Socket> socket);


  void SendToTunDevice (Ptr<Packet> packet, uint32_t teid);



  void SendToS1uSocket (Ptr<Packet> packet, Ipv4Address enbS1uAddress, uint32_t teid);
  

  void SetS11SapMme (EpcSRSapMme * s);

  
  EpcSRSapSgw* GetS11SapSgw ();


  void AddEnb (uint16_t cellId, Ipv4Address enbAddr, Ipv4Address sgwAddr);

  void AddUe (uint64_t imsi);

  void SetUeAddress (uint64_t imsi, Ipv4Address ueAddr);

private:

  // S11 SAP SGW methods
  void DoCreateSessionRequest (EpcSRSapSgw::CreateSessionRequestMessage msg);
  void DoModifyBearerRequest (EpcSRSapSgw::ModifyBearerRequestMessage msg);  

  void DoDeleteBearerCommand (EpcSRSapSgw::DeleteBearerCommandMessage req);
  void DoDeleteBearerResponse (EpcSRSapSgw::DeleteBearerResponseMessage req);


  class UeInfo : public SimpleRefCount<UeInfo>
  {
public:
    UeInfo ();  

   
    void AddBearer (Ptr<EpcTft> tft, uint8_t epsBearerId, uint32_t teid);

    void RemoveBearer (uint8_t bearerId);

    uint32_t Classify (Ptr<Packet> p);

    /** 
     * \return the address of the eNB to which the UE is connected
     */
    Ipv4Address GetEnbAddr ();

    /** 
     * set the address of the eNB to which the UE is connected
     * 
     * \param addr the address of the eNB
     */
    void SetEnbAddr (Ipv4Address addr);

    /** 
     * \return the address of the UE
     */
    Ipv4Address GetUeAddr ();

    /** 
     * set the address of the UE
     * 
     * \param addr the address of the UE
     */
    void SetUeAddr (Ipv4Address addr);


  private:
    EpcTftClassifier m_tftClassifier;
    Ipv4Address m_enbAddr;
    Ipv4Address m_ueAddr;
    std::map<uint8_t, uint32_t> m_teidByBearerIdMap;
  };


 /**
  * UDP socket to send and receive GTP-U packets to and from the S1-U interface
  */
  Ptr<Socket> m_s1uSocket;
  
  /**
   * TUN VirtualNetDevice used for tunneling/detunneling IP packets
   * from/to the internet over GTP-U/UDP/IP on the S1 interface 
   */
  Ptr<VirtualNetDevice> m_tunDevice;

  /**
   * Map telling for each UE address the corresponding UE info 
   */
  std::map<Ipv4Address, Ptr<UeInfo> > m_ueInfoByAddrMap;

  /**
   * Map telling for each IMSI the corresponding UE info 
   */
  std::map<uint64_t, Ptr<UeInfo> > m_ueInfoByImsiMap;

  /**
   * UDP port to be used for GTP
   */
  uint16_t m_gtpuUdpPort;

  uint32_t m_teidCount;

  /**
   * MME side of the S11 SAP
   * 
   */
  EpcSRSapMme* m_s11SapMme;

  /**
   * SGW side of the S11 SAP
   * 
   */
  EpcSRSapSgw* m_s11SapSgw;

  struct EnbInfo
  {
    Ipv4Address enbAddr;
    Ipv4Address sgwAddr;    
  };

  std::map<uint16_t, EnbInfo> m_enbInfoByCellId;
};

} //namespace ns3

#endif /* EPC_SGW_PGW_APPLICATION_H */

