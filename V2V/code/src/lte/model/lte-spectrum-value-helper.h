
#ifndef LTE_SPECTRUM_VALUE_HELPER_H
#define LTE_SPECTRUM_VALUE_HELPER_H


#include <ns3/spectrum-value.h>
#include <vector>

namespace ns3 {



class LteSpectrumValueHelper
{
public:
 
  static double GetCarrierFrequency (uint16_t earfcn);


  static double GetDownlinkCarrierFrequency (uint16_t earfcn);

  
  static double GetUplinkCarrierFrequency (uint16_t earfcn);

  
  static double GetChannelBandwidth (uint8_t txBandwidthConf);

 
  static Ptr<SpectrumModel> GetSpectrumModel (uint16_t earfcn, uint8_t bandwidth);


  static Ptr<SpectrumValue> CreateTxPowerSpectralDensity (uint16_t earfcn,
                                                          uint8_t bandwidth,
                                                          double powerTx,
                                                          std::vector <int> activeRbs);


  static Ptr<SpectrumValue> CreateTxPowerSpectralDensity (uint16_t earfcn,
                                                          uint8_t bandwidth,
                                                          double powerTx,
                                                          std::map<int, double> powerTxMap,
                                                          std::vector <int> activeRbs);


  static Ptr<SpectrumValue> CreateNoisePowerSpectralDensity (uint16_t earfcn, uint8_t bandwidth, double noiseFigure);


  static Ptr<SpectrumValue> CreateNoisePowerSpectralDensity (double noiseFigure, Ptr<SpectrumModel> spectrumModel);

};


} 
#endif 
