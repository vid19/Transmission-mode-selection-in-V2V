

#ifndef LTE_PHY_H
#define LTE_PHY_H


#include <ns3/spectrum-value.h>
#include <ns3/mobility-model.h>
#include <ns3/packet.h>
#include <ns3/nstime.h>
#include <ns3/spectrum-phy.h>
#include <ns3/spectrum-channel.h>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/spectrum-interference.h>
#include <ns3/generic-phy.h>
#include <ns3/lte-spectrum-phy.h>

namespace ns3 {

class PacketBurst;
class LteNetDevice;
class LteControlMessage;


class LtePhy : public Object
{

public:

  LtePhy ();

  LtePhy (Ptr<LteSpectrumPhy> dlPhy, Ptr<LteSpectrumPhy> ulPhy);

  virtual ~LtePhy ();

  static TypeId GetTypeId (void);

  void SetDevice (Ptr<LteNetDevice> d);

  Ptr<LteNetDevice> GetDevice () const;
  Ptr<LteSpectrumPhy> GetDownlinkSpectrumPhy ();
  Ptr<LteSpectrumPhy> GetUplinkSpectrumPhy ();
  virtual void DoSendMacPdu (Ptr<Packet> p) = 0;
  void SetDownlinkChannel (Ptr<SpectrumChannel> c);
  void SetUplinkChannel (Ptr<SpectrumChannel> c);
  virtual Ptr<SpectrumValue> CreateTxPowerSpectralDensity () = 0;
  void DoDispose ();
  void SetTti (double tti);
  double GetTti (void) const;
  void DoSetCellId (uint16_t cellId);

  uint8_t GetRbgSize (void) const;
  
  
  uint16_t GetSrsPeriodicity (uint16_t srcCi) const;
  
  uint16_t GetSrsSubframeOffset (uint16_t srcCi) const;

  void SetMacPdu (Ptr<Packet> p);

  Ptr<PacketBurst> GetPacketBurst (void);

  void SetControlMessages (Ptr<LteControlMessage> m);

  std::list<Ptr<LteControlMessage> > GetControlMessages (void);


  virtual void GenerateCtrlCqiReport (const SpectrumValue& sinr) = 0;
  
 
  virtual void GenerateDataCqiReport (const SpectrumValue& sinr) = 0;
  virtual void ReportInterference (const SpectrumValue& interf) = 0;
  virtual void ReportRsReceivedPower (const SpectrumValue& power) = 0;

protected:
  
  Ptr<LteNetDevice> m_netDevice;
  Ptr<LteSpectrumPhy> m_downlinkSpectrumPhy;
 
  Ptr<LteSpectrumPhy> m_uplinkSpectrumPhy;

  double m_txPower;

  double m_noiseFigure;

  /// Transmission time interval.
  double m_tti;
  /**
   * The UL bandwidth in number of PRBs.
   * Specified by the upper layer through CPHY SAP.
   */
  uint8_t m_ulBandwidth;
  /**
   * The DL bandwidth in number of PRBs.
   * Specified by the upper layer through CPHY SAP.
   */
  uint8_t m_dlBandwidth;
  /// The RB gruop size according to the bandwidth.
  uint8_t m_rbgSize;
  /**
   * The downlink carrier frequency.
   * Specified by the upper layer through CPHY SAP.
   */
  uint16_t m_dlEarfcn;
  /**
   * The uplink carrier frequency.
   * Specified by the upper layer through CPHY SAP.
   */
  uint16_t m_ulEarfcn;

  /// A queue of packet bursts to be sent.
  std::vector< Ptr<PacketBurst> > m_packetBurstQueue;
  /// A queue of control messages to be sent.
  std::vector< std::list<Ptr<LteControlMessage> > > m_controlMessagesQueue;
  /**
   * Delay between MAC and channel layer in terms of TTIs. It is the delay that
   * occurs between a scheduling decision in the MAC and the actual start of
   * the transmission by the PHY. This is intended to be used to model the
   * latency of real PHY and MAC implementations.
   *
   * In LteEnbPhy, it is 2 TTIs by default and can be configured through the
   * `MacToChannelDelay` attribute. In LteUePhy, it is 4 TTIs.
   */
  uint8_t m_macChTtiDelay;

  /**
   * Cell identifier. In LteEnbPhy, this corresponds to the ID of the cell
   * which hosts this PHY layer. In LteUePhy, this corresponds to the ID of the
   * eNodeB which this PHY layer is synchronized with.
   */
  uint16_t m_cellId;

}; // end of `class LtePhy`


}

#endif /* LTE_PHY_H */
