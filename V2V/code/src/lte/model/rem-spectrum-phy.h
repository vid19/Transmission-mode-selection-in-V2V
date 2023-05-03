

#ifndef REM_SPECTRUM_PHY_H
#define REM_SPECTRUM_PHY_H


#include <ns3/spectrum-value.h>
#include <ns3/mobility-model.h>
#include <ns3/packet.h>
#include <ns3/nstime.h>
#include <ns3/net-device.h>
#include <ns3/spectrum-phy.h>
#include <ns3/spectrum-channel.h>
#include <string>
#include <fstream>

namespace ns3 {


class RemSpectrumPhy : public SpectrumPhy
{

public:
  RemSpectrumPhy ();
  virtual ~RemSpectrumPhy ();

  // inherited from Object
  void DoDispose ();
  static TypeId GetTypeId (void);

  // inherited from SpectrumPhy
  void SetChannel (Ptr<SpectrumChannel> c);
  void SetMobility (Ptr<MobilityModel> m);
  void SetDevice (Ptr<NetDevice> d);
  Ptr<MobilityModel> GetMobility ();
  Ptr<NetDevice> GetDevice () const;
  Ptr<const SpectrumModel> GetRxSpectrumModel () const;
  Ptr<AntennaModel> GetRxAntenna ();
  void StartRx (Ptr<SpectrumSignalParameters> params);


  void SetRxSpectrumModel (Ptr<const SpectrumModel> m);


  double GetSinr (double noisePower);

 
  void Deactivate ();

  
  bool IsActive ();


  void Reset ();


  void SetUseDataChannel (bool value);


  void SetRbId (int32_t rbId);

private:
  Ptr<MobilityModel> m_mobility;
  Ptr<const SpectrumModel> m_rxSpectrumModel;

  double m_referenceSignalPower;
  double m_sumPower;

  bool m_active;

  bool m_useDataChannel;
  int32_t m_rbId;

};






}





#endif /* REM_SPECTRUM_PHY_H */
