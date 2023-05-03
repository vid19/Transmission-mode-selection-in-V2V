

#ifndef LTE_SIMPLE_NET_DEVICE_H
#define LTE_SIMPLE_NET_DEVICE_H

#include "ns3/event-id.h"
#include "ns3/node.h"
#include "ns3/error-model.h"
#include "ns3/simple-channel.h"
#include "ns3/simple-net-device.h"
#include "ns3/lte-rlc.h"

namespace ns3 {



class LteSimpleNetDevice : public SimpleNetDevice
{

public:
  static TypeId GetTypeId (void);

  LteSimpleNetDevice (void);
  LteSimpleNetDevice (Ptr<Node> node);

  virtual ~LteSimpleNetDevice (void);
  virtual void DoDispose ();


  // inherited from NetDevice
  virtual bool Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);


protected:
  // inherited from Object
  virtual void DoInitialize (void);

};

} // namespace ns3


#endif // LTE_SIMPLE_NET_DEVICE_H
