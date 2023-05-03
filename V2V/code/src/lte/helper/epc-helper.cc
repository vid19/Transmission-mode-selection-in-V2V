

#include <ns3/epc-helper.h>
#include <ns3/log.h>
#include <ns3/node.h>
#include <ns3/ipv4-address.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("EpcHelper");

NS_OBJECT_ENSURE_REGISTERED (EpcHelper);


EpcHelper::EpcHelper () 
{
  NS_LOG_FUNCTION (this);
}

EpcHelper::~EpcHelper ()
{
  NS_LOG_FUNCTION (this);
}

TypeId
EpcHelper::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::EpcHelper")
    .SetParent<Object> ()
    .SetGroupName("Lte")
    ;
  return tid;
}

void
EpcHelper::DoDispose ()
{
  NS_LOG_FUNCTION (this);
  Object::DoDispose ();
}



} // namespace ns3
