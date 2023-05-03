

#include "ns3/lte-mac-sap.h"


namespace ns3 {


LteMacSapProvider::~LteMacSapProvider ()
{
}

LteMacSapUser::~LteMacSapUser ()
{
}

void
LteMacSapUser::NotifyDlHarqDeliveryFailure (uint8_t harqId)
{
}

void
LteMacSapUser::NotifyUlHarqDeliveryFailure (uint8_t harqId)
{
}


} // namespace ns3
