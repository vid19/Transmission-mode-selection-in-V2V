#ifndef LTE_AS_SAP_H
#define LTE_AS_SAP_H

#include <stdint.h>
#include <ns3/ptr.h>
#include <ns3/packet.h>

namespace ns3 {

class LteEnbNetDevice;

class LteAsSapProvider
{
public:
  virtual ~LteAsSapProvider ();

  
  virtual void SetCsgWhiteList (uint32_t csgId) = 0;

  virtual void StartCellSelection (uint16_t dlEarfcn) = 0;

 
  virtual void ForceCampedOnEnb (uint16_t cellId, uint16_t dlEarfcn) = 0;

  virtual void Connect (void) = 0;

  virtual void SendData (Ptr<Packet> packet, uint8_t bid) = 0;


  virtual void Disconnect () = 0;

};

class LteAsSapUser
{
public:
  virtual ~LteAsSapUser ();

 
  virtual void NotifyConnectionSuccessful () = 0;

  virtual void NotifyConnectionFailed () = 0;

  virtual void NotifyConnectionReleased () = 0;

  virtual void RecvData (Ptr<Packet> packet) = 0;

};


template <class C>
class MemberLteAsSapProvider : public LteAsSapProvider
{
public:
  MemberLteAsSapProvider (C* owner);

  // inherited from LteAsSapProvider
  virtual void SetCsgWhiteList (uint32_t csgId);
  virtual void StartCellSelection (uint16_t dlEarfcn);
  virtual void ForceCampedOnEnb (uint16_t cellId, uint16_t dlEarfcn);
  virtual void Connect (void);
  virtual void SendData (Ptr<Packet> packet, uint8_t bid);
  virtual void Disconnect ();

private:
  MemberLteAsSapProvider ();
  C* m_owner;
};

template <class C>
MemberLteAsSapProvider<C>::MemberLteAsSapProvider (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteAsSapProvider<C>::MemberLteAsSapProvider ()
{
}

template <class C>
void
MemberLteAsSapProvider<C>::SetCsgWhiteList (uint32_t csgId)
{
  m_owner->DoSetCsgWhiteList (csgId);
}

template <class C>
void
MemberLteAsSapProvider<C>::StartCellSelection (uint16_t dlEarfcn)
{
  m_owner->DoStartCellSelection (dlEarfcn);
}

template <class C>
void
MemberLteAsSapProvider<C>::ForceCampedOnEnb (uint16_t cellId, uint16_t dlEarfcn)
{
  m_owner->DoForceCampedOnEnb (cellId, dlEarfcn);
}

template <class C>
void 
MemberLteAsSapProvider<C>::Connect ()
{
  m_owner->DoConnect ();
}

template <class C>
void
MemberLteAsSapProvider<C>::SendData (Ptr<Packet> packet, uint8_t bid)
{
  m_owner->DoSendData (packet, bid);
}

template <class C>
void 
MemberLteAsSapProvider<C>::Disconnect ()
{
  m_owner->DoDisconnect ();
}


template <class C>
class MemberLteAsSapUser : public LteAsSapUser
{
public:
  MemberLteAsSapUser (C* owner);

  // inherited from LteAsSapUser
  virtual void NotifyConnectionSuccessful ();
  virtual void NotifyConnectionFailed ();
  virtual void RecvData (Ptr<Packet> packet);
  virtual void NotifyConnectionReleased ();

private:
  MemberLteAsSapUser ();
  C* m_owner;
};

template <class C>
MemberLteAsSapUser<C>::MemberLteAsSapUser (C* owner)
  : m_owner (owner)
{
}

template <class C>
MemberLteAsSapUser<C>::MemberLteAsSapUser ()
{
}

template <class C>
void 
MemberLteAsSapUser<C>::NotifyConnectionSuccessful ()
{
  m_owner->DoNotifyConnectionSuccessful ();
}

template <class C>
void 
MemberLteAsSapUser<C>::NotifyConnectionFailed ()
{
  m_owner->DoNotifyConnectionFailed ();
}

template <class C>
void 
MemberLteAsSapUser<C>::RecvData (Ptr<Packet> packet)
{
  m_owner->DoRecvData (packet);
}

template <class C>
void 
MemberLteAsSapUser<C>::NotifyConnectionReleased ()
{
  m_owner->DoNotifyConnectionReleased ();
}


} // namespace ns3

#endif // LTE_AS_SAP_H
