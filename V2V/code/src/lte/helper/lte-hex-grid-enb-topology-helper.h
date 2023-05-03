

#ifndef LTE_HEX_GRID_ENB_TOPOLOGY_HELPER_H
#define LTE_HEX_GRID_ENB_TOPOLOGY_HELPER_H

#include <ns3/lte-helper.h>

namespace ns3 {


class LteHexGridEnbTopologyHelper : public Object
{
public:
  LteHexGridEnbTopologyHelper (void);
  virtual ~LteHexGridEnbTopologyHelper (void);

 
  static TypeId GetTypeId (void);
  virtual void DoDispose (void);

  void SetLteHelper (Ptr<LteHelper> h);


  NetDeviceContainer SetPositionAndInstallEnbDevice (NodeContainer c);

private:
 
  Ptr<LteHelper> m_lteHelper;

  double m_offset;

  double m_d;

  double m_xMin;

  double m_yMin;

  uint32_t m_gridWidth;

  uint32_t m_siteHeight;

};


} // namespace ns3



#endif // LTE_HEX_GRID_ENB_TOPOLOGY_HELPER_H
