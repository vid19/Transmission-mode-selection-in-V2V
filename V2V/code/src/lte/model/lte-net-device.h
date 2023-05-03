

#ifndef LTE_NET_DEVICE_H
#define LTE_NET_DEVICE_H

#include <ns3/net-device.h>
#include <ns3/event-id.h>
#include <ns3/mac48-address.h>
#include <ns3/traced-callback.h>
#include <ns3/nstime.h>
#include <ns3/lte-phy.h>
#include <ns3/lte-control-messages.h>

namespace ns3 {

class Node;
class Packet;


class LteNetDevice : public NetDevice
{
public:
  static TypeId GetTypeId (void);

  LteNetDevice (void);
  virtual ~LteNetDevice (void);

  virtual void DoDispose (void);

  // inherited from NetDevice
  virtual void SetIfIndex (const uint32_t index);
  virtual uint32_t GetIfIndex (void) const;
  virtual Ptr<Channel> GetChannel (void) const;
  virtual bool SetMtu (const uint16_t mtu);
  virtual uint16_t GetMtu (void) const;
  virtual void SetAddress (Address address);
  virtual Address GetAddress (void) const;
  virtual bool IsLinkUp (void) const;
  virtual void AddLinkChangeCallback (Callback<void> callback);
  virtual bool IsBroadcast (void) const;
  virtual Address GetBroadcast (void) const;
  virtual bool IsMulticast (void) const;
  virtual bool IsPointToPoint (void) const;
  virtual bool IsBridge (void) const;
  virtual Ptr<Node> GetNode (void) const;
  virtual void SetNode (Ptr<Node> node);
  virtual bool NeedsArp (void) const;
  virtual void SetReceiveCallback (NetDevice::ReceiveCallback cb);
  virtual Address GetMulticast (Ipv4Address addr) const;
  virtual Address GetMulticast (Ipv6Address addr) const;
  virtual void SetPromiscReceiveCallback (PromiscReceiveCallback cb); 
  virtual bool SendFrom (Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber);
  virtual bool SupportsSendFrom (void) const;


  void Receive (Ptr<Packet> p);
  
protected:
  
  NetDevice::ReceiveCallback m_rxCallback;
  
private:
  LteNetDevice (const LteNetDevice &);
  LteNetDevice & operator= (const LteNetDevice &);

  Ptr<Node> m_node;

  TracedCallback<> m_linkChangeCallbacks;

  uint32_t m_ifIndex;
  bool m_linkUp;
  mutable uint16_t m_mtu;

  Mac48Address m_address;
};


} // namespace ns3

#endif /* LTE_NET_DEVICE_H */
