

#ifndef LTE_ENB_NET_DEVICE_H
#define LTE_ENB_NET_DEVICE_H

#include "ns3/lte-net-device.h"
#include "ns3/event-id.h"
#include "ns3/mac48-address.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/lte-phy.h"
#include <vector>

namespace ns3 {

class Packet;
class PacketBurst;
class Node;
class LtePhy;
class LteEnbPhy;
class LteEnbMac;
class LteEnbRrc;
class FfMacScheduler;
class LteHandoverAlgorithm;
class LteAnr;
class LteFfrAlgorithm;

class LteEnbNetDevice : public LteNetDevice
{
public:
  static TypeId GetTypeId (void);

  LteEnbNetDevice ();

  virtual ~LteEnbNetDevice (void);
  virtual void DoDispose (void);

  // inherited from NetDevice
  virtual bool Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);

  /**
   * \return a pointer to the MAC 
   */
  Ptr<LteEnbMac> GetMac (void) const;

  /**
   * \return a pointer to the physical layer.
   */
  Ptr<LteEnbPhy> GetPhy (void) const;

  /** 
   * \return a pointer to the Radio Resource Control instance of the eNB
   */
  Ptr<LteEnbRrc> GetRrc () const;

  /** 
   * \return the Cell Identifier of this eNB
   */
  uint16_t GetCellId () const;

  /** 
   * \return the uplink bandwidth in RBs
   */
  uint8_t GetUlBandwidth () const;

  /** 
   * \param bw the uplink bandwidth in RBs
   */
  void SetUlBandwidth (uint8_t bw);

  /** 
   * \return the downlink bandwidth in RBs
   */
  uint8_t GetDlBandwidth () const;

  /** 
   * \param bw the downlink bandwidth in RBs
   */
  void SetDlBandwidth (uint8_t bw);

  /** 
   * \return the downlink carrier frequency (EARFCN)
   */
  uint16_t GetDlEarfcn () const;

  /** 
   * \param earfcn the downlink carrier frequency (EARFCN)
   */
  void SetDlEarfcn (uint16_t earfcn);

  /** 
   * \return the uplink carrier frequency (EARFCN)
   */
  uint16_t GetUlEarfcn () const;

  /** 
   * \param earfcn the uplink carrier frequency (EARFCN)
   */
  void SetUlEarfcn (uint16_t earfcn);

  /**
   * \brief Returns the CSG ID of the eNodeB.
   * \return the Closed Subscriber Group identity
   * \sa LteEnbNetDevice::SetCsgId
   */
  uint32_t GetCsgId () const;

  void SetCsgId (uint32_t csgId);

  bool GetCsgIndication () const;

  void SetCsgIndication (bool csgIndication);

protected:
  // inherited from Object
  virtual void DoInitialize (void);


private:
  bool m_isConstructed;
  bool m_isConfigured;

 
  void UpdateConfig ();

  Ptr<LteEnbMac> m_mac;

  Ptr<LteEnbPhy> m_phy;

  Ptr<LteEnbRrc> m_rrc;

  Ptr<FfMacScheduler> m_scheduler;

  Ptr<LteHandoverAlgorithm> m_handoverAlgorithm;

  Ptr<LteAnr> m_anr;

  Ptr<LteFfrAlgorithm> m_ffrAlgorithm;

  uint16_t m_cellId; /**< Cell Identifer. Part of the CGI, see TS 29.274, section 8.21.1  */

  uint8_t m_dlBandwidth; /**< downlink bandwidth in RBs */
  uint8_t m_ulBandwidth; /**< uplink bandwidth in RBs */

  uint16_t m_dlEarfcn;  /**< downlink carrier frequency */
  uint16_t m_ulEarfcn;  /**< uplink carrier frequency */

  uint16_t m_csgId;
  bool m_csgIndication;

}; // end of class LteEnbNetDevice

} // namespace ns3

#endif /* LTE_ENB_NET_DEVICE_H */
