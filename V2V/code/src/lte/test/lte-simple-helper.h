

#ifndef LTE_SIMPLE_HELPER_H
#define LTE_SIMPLE_HELPER_H

#include "ns3/net-device-container.h"
#include "ns3/simple-channel.h"
#include "ns3/node-container.h"
#include "ns3/radio-bearer-stats-calculator.h"

#include "ns3/lte-pdcp.h"
#include "ns3/lte-rlc.h"
#include "ns3/lte-rlc-um.h"
#include "ns3/lte-rlc-am.h"

namespace ns3 {

class LteTestRrc;
class LteTestMac;


class LteSimpleHelper : public Object
{
public:
  LteSimpleHelper (void);
  virtual ~LteSimpleHelper (void);

  static TypeId GetTypeId (void);
  virtual void DoDispose (void);



  NetDeviceContainer InstallEnbDevice (NodeContainer c);


  NetDeviceContainer InstallUeDevice (NodeContainer c);


 
  void EnableLogComponents (void);


  void EnableTraces (void);


 
  void EnableRlcTraces (void);


  void EnableDlRlcTraces (void);

  /**
   * Enable trace sinks for UL RLC layer
   */
  void EnableUlRlcTraces (void);


  /**
   * Enable trace sinks for PDCP layer
   */
  void EnablePdcpTraces (void);

  /**
   * Enable trace sinks for DL PDCP layer
   */
  void EnableDlPdcpTraces (void);

  /**
   * Enable trace sinks for UL PDCP layer
   */
  void EnableUlPdcpTraces (void);


protected:
  // inherited from Object
  virtual void DoInitialize (void);

private:
  Ptr<NetDevice> InstallSingleEnbDevice (Ptr<Node> n);
  Ptr<NetDevice> InstallSingleUeDevice (Ptr<Node> n);

  Ptr<SimpleChannel> m_phyChannel;

public:

  Ptr<LteTestRrc> m_enbRrc;
  Ptr<LteTestRrc> m_ueRrc;

  Ptr<LteTestMac> m_enbMac;
  Ptr<LteTestMac> m_ueMac;

private:

  Ptr<LtePdcp>    m_enbPdcp;
  Ptr<LteRlc>     m_enbRlc;

  Ptr<LtePdcp>    m_uePdcp;
  Ptr<LteRlc>     m_ueRlc;

  ObjectFactory   m_enbDeviceFactory;
  ObjectFactory   m_ueDeviceFactory;

  enum LteRlcEntityType_t {RLC_UM = 1,
                           RLC_AM = 2 } m_lteRlcEntityType;

};


} // namespace ns3


#endif // LTE_SIMPLE_HELPER_H
