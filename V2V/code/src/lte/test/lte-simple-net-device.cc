

#include "ns3/simulator.h"
#include "ns3/pointer.h"
#include "ns3/log.h"
#include "lte-simple-net-device.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("LteSimpleNetDevice");

NS_OBJECT_ENSURE_REGISTERED (LteSimpleNetDevice);


TypeId LteSimpleNetDevice::GetTypeId (void)
{
  static TypeId
    tid =
    TypeId ("ns3::LteSimpleNetDevice")
    .SetParent<SimpleNetDevice> ()
    .AddConstructor<LteSimpleNetDevice> ()
  ;

  return tid;
}


LteSimpleNetDevice::LteSimpleNetDevice (void)
{
  NS_LOG_FUNCTION (this);
}


LteSimpleNetDevice::LteSimpleNetDevice (Ptr<Node> node)
{
  NS_LOG_FUNCTION (this);
  SetNode (node);
}

LteSimpleNetDevice::~LteSimpleNetDevice (void)
{
  NS_LOG_FUNCTION (this);
}

void
LteSimpleNetDevice::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  SimpleNetDevice::DoDispose ();
}


void
LteSimpleNetDevice::DoInitialize (void)
{
  NS_LOG_FUNCTION (this);
}

bool
LteSimpleNetDevice::Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber)
{
  NS_LOG_FUNCTION (this << dest << protocolNumber);
  return SimpleNetDevice::Send (packet, dest, protocolNumber);
}


} // namespace ns3
