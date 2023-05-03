

#ifndef LTE_UE_NET_DEVICE_H
#define LTE_UE_NET_DEVICE_H

#include "ns3/lte-net-device.h"
#include "ns3/event-id.h"
#include "ns3/mac48-address.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/lte-phy.h"
#include "ns3/eps-bearer.h"


namespace ns3 {

class Packet;
class PacketBurst;
class Node;
class LtePhy;
class LteUePhy;
class LteEnbNetDevice;
class LteUeMac;
class LteUeRrc;
class EpcUeNas;
class EpcTft;


class LteUeNetDevice : public LteNetDevice
{

public:
  static TypeId GetTypeId (void);

  LteUeNetDevice (void);
  virtual ~LteUeNetDevice (void);
  virtual void DoDispose ();


  // inherited from NetDevice
  virtual bool Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);


  Ptr<LteUeMac> GetMac (void) const;

  Ptr<LteUeRrc> GetRrc () const;

  Ptr<LteUePhy> GetPhy (void) const;

  Ptr<EpcUeNas> GetNas (void) const;

  uint64_t GetImsi () const;


  uint16_t GetDlEarfcn () const;

 
  void SetDlEarfcn (uint16_t earfcn);

 
  uint32_t GetCsgId () const;

 
  void SetCsgId (uint32_t csgId);


  void SetTargetEnb (Ptr<LteEnbNetDevice> enb);


  Ptr<LteEnbNetDevice> GetTargetEnb (void);


protected:
  // inherited from Object
  virtual void DoInitialize (void);


private:
  bool m_isConstructed;


  void UpdateConfig ();

  Ptr<LteEnbNetDevice> m_targetEnb;

  Ptr<LteUeMac> m_mac;
  Ptr<LteUePhy> m_phy;
  Ptr<LteUeRrc> m_rrc;
  Ptr<EpcUeNas> m_nas;

  uint64_t m_imsi;

  uint16_t m_dlEarfcn; /**< downlink carrier frequency */

  uint32_t m_csgId;

}; // end of class LteUeNetDevice

} // namespace ns3

#endif /* LTE_UE_NET_DEVICE_H */
