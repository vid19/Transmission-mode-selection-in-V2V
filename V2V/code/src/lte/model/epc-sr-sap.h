

#ifndef EPC_S11_SAP_H
#define EPC_S11_SAP_H

#include <ns3/address.h>
#include <ns3/ptr.h>
#include <ns3/object.h>
#include <ns3/eps-bearer.h>
#include <ns3/epc-tft.h>
#include <list>

namespace ns3 {

class EpcSRSap
{
public:

  virtual ~EpcSRSap ();

  struct GtpcMessage
  {
    uint32_t teid;
  };


  struct Fteid 
  {
    uint32_t teid;
    Ipv4Address address;
  };

  
  struct Uli
  {
    uint16_t gci;
  };
  
 
};

/**
 * \ingroup lte
 *
 * MME side of the S11 Service Access Point (SAP), provides the MME
 * methods to be called when an S11 message is received by the MME. 
 */
class EpcSRSapMme : public EpcSRSap
{
public:
  
 /**
   * 3GPP TS 29.274 version 8.3.1 Release 8 section 8.28
   * 
   */
  struct BearerContextCreated
  {

    EpcSRSap::Fteid sgwFteid;
    uint8_t epsBearerId; 
    EpsBearer bearerLevelQos; 
    Ptr<EpcTft> tft;
  };


  /**     
   * Create Session Response message, see 3GPP TS 29.274 7.2.2
   */
  struct CreateSessionResponseMessage : public GtpcMessage
  {
    std::list<BearerContextCreated> bearerContextsCreated;
  };


  /** 
   * send a Create Session Response message
   * 
   * \param msg the message
   */
  virtual void CreateSessionResponse (CreateSessionResponseMessage msg) = 0;

  struct BearerContextRemoved
  {
    uint8_t epsBearerId;
  };

  /**
   * Delete Bearer Request message, see 3GPP TS 29.274 Release 9 V9.3.0 section 7.2.9.2
   */
  struct DeleteBearerRequestMessage : public GtpcMessage
  {
    std::list<BearerContextRemoved> bearerContextsRemoved;
  };

  /**
    * \brief As per 3GPP TS 29.274 Release 9 V9.3.0, a Delete Bearer Request message shall be sent on the S11 interface by PGW to SGW and from SGW to MME
    * \param msg the message
    */
  virtual void DeleteBearerRequest (DeleteBearerRequestMessage msg) = 0;




  /**     
   * Modify Bearer Response message, see 3GPP TS 29.274 7.2.7
   */
  struct ModifyBearerResponseMessage : public GtpcMessage
  {
    enum Cause {
      REQUEST_ACCEPTED = 0,
      REQUEST_ACCEPTED_PARTIALLY,
      REQUEST_REJECTED,
      CONTEXT_NOT_FOUND
    } cause;
  };

  /** 
   * send a Modify Bearer Response message
   * 
   * \param msg the message
   */
  virtual void ModifyBearerResponse (ModifyBearerResponseMessage msg) = 0;

};

/**
 * \ingroup lte
 *
 * SGW side of the S11 Service Access Point (SAP), provides the SGW
 * methods to be called when an S11 message is received by the SGW. 
 */
class EpcSRSapSgw : public EpcSRSap
{
public:

  struct BearerContextToBeCreated
  {    
    EpcSRSap::Fteid sgwFteid;
    uint8_t epsBearerId; 
    EpsBearer bearerLevelQos; 
    Ptr<EpcTft> tft;
  };

  
  /**     
   * Create Session Request message, see 3GPP TS 29.274 7.2.1
   */
  struct CreateSessionRequestMessage : public GtpcMessage
  {
    uint64_t imsi; 
    Uli uli; 
    std::list<BearerContextToBeCreated> bearerContextsToBeCreated;    
  };

  /** 
   * send a Create Session Request message
   * 
   * \param msg the message
   */
  virtual void CreateSessionRequest (CreateSessionRequestMessage msg) = 0;

  struct BearerContextToBeRemoved
  {
    uint8_t epsBearerId;
  };

  /**
   * Delete Bearer Command message, see 3GPP TS 29.274 Release 9 V9.3.0 section 7.2.17.1
   */
  struct DeleteBearerCommandMessage : public GtpcMessage
  {
    std::list<BearerContextToBeRemoved> bearerContextsToBeRemoved;
  };

  /**
    * \brief As per 3GPP TS 29.274 Release 9 V9.3.0, a Delete Bearer Command message shall be sent on the S11 interface by the MME to the SGW
    */
  virtual void DeleteBearerCommand (DeleteBearerCommandMessage msg) = 0;


  struct BearerContextRemovedSgwPgw
  {
    uint8_t epsBearerId;
  };

  /**
   * Delete Bearer Response message, see 3GPP TS 29.274 Release 9 V9.3.0 section 7.2.10.2
   */
  struct DeleteBearerResponseMessage : public GtpcMessage
  {
    std::list<BearerContextRemovedSgwPgw> bearerContextsRemoved;
  };

  /**
    * \brief As per 3GPP TS 29.274 Release 9 V9.3.0, a Delete Bearer Command message shall be sent on the S11 interface by the MME to the SGW
    * \param msg the message
    */
  virtual void DeleteBearerResponse (DeleteBearerResponseMessage msg) = 0;

  /**     
   * Modify Bearer Request message, see 3GPP TS 29.274 7.2.7
   */
  struct ModifyBearerRequestMessage : public GtpcMessage
  {
    Uli uli;
  };

  /** 
   * send a Modify Bearer Request message
   * 
   * \param msg the message
   */
  virtual void ModifyBearerRequest (ModifyBearerRequestMessage msg) = 0;

};







/**
 * Template for the implementation of the EpcSRSapMme as a member
 * of an owner class of type C to which all methods are forwarded
 * 
 */
template <class C>
class MemberEpcSRSapMme : public EpcSRSapMme
{
public:
  MemberEpcSRSapMme (C* owner);

  // inherited from EpcSRSapMme
  virtual void CreateSessionResponse (CreateSessionResponseMessage msg);
  virtual void ModifyBearerResponse (ModifyBearerResponseMessage msg);
  virtual void DeleteBearerRequest (DeleteBearerRequestMessage msg);

private:
  MemberEpcSRSapMme ();
  C* m_owner;
};

template <class C>
MemberEpcSRSapMme<C>::MemberEpcSRSapMme (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberEpcSRSapMme<C>::MemberEpcSRSapMme ()
{
}

template <class C>
void MemberEpcSRSapMme<C>::CreateSessionResponse (CreateSessionResponseMessage msg)
{
  m_owner->DoCreateSessionResponse (msg);
}

template <class C>
void MemberEpcSRSapMme<C>::DeleteBearerRequest (DeleteBearerRequestMessage msg)
{
  m_owner->DoDeleteBearerRequest (msg);
}

template <class C>
void MemberEpcSRSapMme<C>::ModifyBearerResponse (ModifyBearerResponseMessage msg)
{
  m_owner->DoModifyBearerResponse (msg);
}





/**
 * Template for the implementation of the EpcSRSapSgw as a member
 * of an owner class of type C to which all methods are forwarded
 * 
 */
template <class C>
class MemberEpcSRSapSgw : public EpcSRSapSgw
{
public:
  MemberEpcSRSapSgw (C* owner);

  // inherited from EpcSRSapSgw
  virtual void CreateSessionRequest (CreateSessionRequestMessage msg);
  virtual void ModifyBearerRequest (ModifyBearerRequestMessage msg);
  virtual void DeleteBearerCommand (DeleteBearerCommandMessage msg);
  virtual void DeleteBearerResponse (DeleteBearerResponseMessage msg);

private:
  MemberEpcSRSapSgw ();
  C* m_owner;
};

template <class C>
MemberEpcSRSapSgw<C>::MemberEpcSRSapSgw (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberEpcSRSapSgw<C>::MemberEpcSRSapSgw ()
{
}

template <class C>
void MemberEpcSRSapSgw<C>::CreateSessionRequest (CreateSessionRequestMessage msg)
{
  m_owner->DoCreateSessionRequest (msg);
}

template <class C>
void MemberEpcSRSapSgw<C>::ModifyBearerRequest (ModifyBearerRequestMessage msg)
{
  m_owner->DoModifyBearerRequest (msg);
}

template <class C>
void MemberEpcSRSapSgw<C>::DeleteBearerCommand (DeleteBearerCommandMessage msg)
{
  m_owner->DoDeleteBearerCommand (msg);
}

template <class C>
void MemberEpcSRSapSgw<C>::DeleteBearerResponse (DeleteBearerResponseMessage msg)
{
  m_owner->DoDeleteBearerResponse (msg);
}




} //namespace ns3

#endif /* EPC_S11_SAP_H */

