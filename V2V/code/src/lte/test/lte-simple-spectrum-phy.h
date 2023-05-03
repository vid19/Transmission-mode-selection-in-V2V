

#ifndef LTE_SIMPLE_SPECTRUM_PHY_H
#define LTE_SIMPLE_SPECTRUM_PHY_H

#include <ns3/event-id.h>
#include <ns3/spectrum-value.h>
#include <ns3/mobility-model.h>
#include <ns3/net-device.h>
#include <ns3/spectrum-phy.h>
#include <ns3/spectrum-channel.h>
#include <ns3/traced-callback.h>

namespace ns3 {



class LteSimpleSpectrumPhy : public SpectrumPhy
{

public:
  LteSimpleSpectrumPhy ();
  virtual ~LteSimpleSpectrumPhy ();

  // inherited from Object
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

  // inherited from SpectrumPhy
  void SetChannel (Ptr<SpectrumChannel> c);
  void SetMobility (Ptr<MobilityModel> m);
  void SetDevice (Ptr<NetDevice> d);
  Ptr<MobilityModel> GetMobility ();
  Ptr<NetDevice> GetDevice () const;
  Ptr<const SpectrumModel> GetRxSpectrumModel () const;
  Ptr<AntennaModel> GetRxAntenna ();
  void StartRx (Ptr<SpectrumSignalParameters> params);

  void SetRxSpectrumModel (Ptr<const SpectrumModel> model);

  void SetCellId (uint16_t cellId);

private:
  Ptr<MobilityModel> m_mobility;
  Ptr<AntennaModel> m_antenna;
  Ptr<NetDevice> m_device;
  Ptr<SpectrumChannel> m_channel;
  Ptr<const SpectrumModel> m_rxSpectrumModel;

  uint16_t m_cellId;

  TracedCallback< Ptr<const SpectrumValue> > m_rxStart;
};






}

#endif /* LTE_SIMPLE_SPECTRUM_PHY_H */
