

#ifndef EPC_MME_H
#define EPC_MME_H

#include <ns3/object.h>
#include <ns3/epc-s1ap-sap.h>
#include <ns3/epc-sr-sap.h>

#include <map>
#include <list>

namespace ns3 {

class Node;
class NetDevice;

class EpcMme : public Object
{

  friend class MemberEpcS1apSapMme<EpcMme>;
  friend class MemberEpcSRSapMme<EpcMme>;
  
public:
  
  /** 
   * Constructor
   */
  EpcMme ();

  /** 
   * Destructor
   */  
  virtual ~EpcMme ();
  
  // inherited from Object  
  static TypeId GetTypeId (void);
protected:
  virtual void DoDispose ();

public:


  /** 
   * 
   * \return the MME side of the S1-AP SAP 
   */
  EpcS1apSapMme* GetS1apSapMme ();

  /** 
   * Set the SGW side of the S11 SAP 
   * 
   * \param s the SGW side of the S11 SAP 
   */
  void SetS11SapSgw (EpcSRSapSgw * s);

  /** 
   * 
   * \return the MME side of the S11 SAP 
   */
  EpcSRSapMme* GetS11SapMme ();

  void AddEnb (uint16_t ecgi, Ipv4Address enbS1UAddr, EpcS1apSapEnb* enbS1apSap);
 
  void AddUe (uint64_t imsi);

  uint8_t AddBearer (uint64_t imsi, Ptr<EpcTft> tft, EpsBearer bearer);


private:

  // S1-AP SAP MME forwarded methods
  void DoInitialUeMessage (uint64_t mmeUeS1Id, uint16_t enbUeS1Id, uint64_t imsi, uint16_t ecgi);
  void DoInitialContextSetupResponse (uint64_t mmeUeS1Id, uint16_t enbUeS1Id, std::list<EpcS1apSapMme::ErabSetupItem> erabSetupList);
  void DoPathSwitchRequest (uint64_t enbUeS1Id, uint64_t mmeUeS1Id, uint16_t cgi, std::list<EpcS1apSapMme::ErabSwitchedInDownlinkItem> erabToBeSwitchedInDownlinkList);
  void DoErabReleaseIndication (uint64_t mmeUeS1Id, uint16_t enbUeS1Id, std::list<EpcS1apSapMme::ErabToBeReleasedIndication> erabToBeReleaseIndication);

  // S11 SAP MME forwarded methods
  void DoCreateSessionResponse (EpcSRSapMme::CreateSessionResponseMessage msg);
  void DoModifyBearerResponse (EpcSRSapMme::ModifyBearerResponseMessage msg);
  void DoDeleteBearerRequest (EpcSRSapMme::DeleteBearerRequestMessage msg);


  /**
   * Hold info on an EPS bearer to be activated
   * 
   */
  struct BearerInfo
  {
    Ptr<EpcTft> tft;
    EpsBearer bearer;
    uint8_t bearerId;
  };
  
  /**
   * Hold info on a UE
   * 
   */
  struct UeInfo : public SimpleRefCount<UeInfo>
  {
    uint64_t mmeUeS1Id;
    uint16_t enbUeS1Id;
    uint64_t imsi;
    uint16_t cellId;
    std::list<BearerInfo> bearersToBeActivated;
    uint16_t bearerCounter;
  };

  /**
   * UeInfo stored by IMSI
   * 
   */  
  std::map<uint64_t, Ptr<UeInfo> > m_ueInfoMap;

  
  void RemoveBearer (Ptr<UeInfo> ueInfo, uint8_t epsBearerId);

  /**
   * Hold info on a ENB
   * 
   */
  struct EnbInfo : public SimpleRefCount<EnbInfo>
  {
    uint16_t gci;
    Ipv4Address s1uAddr;
    EpcS1apSapEnb* s1apSapEnb;
  };

  /**
   * EnbInfo stored by EGCI
   * 
   */
  std::map<uint16_t, Ptr<EnbInfo> > m_enbInfoMap;


  

  EpcS1apSapMme* m_s1apSapMme;

  EpcSRSapMme* m_s11SapMme;
  EpcSRSapSgw* m_s11SapSgw;
  
};




} // namespace ns3

#endif // EPC_MME_H
