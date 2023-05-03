

#ifndef LTE_SPECTRUM_SIGNAL_PARAMETERS_H
#define LTE_SPECTRUM_SIGNAL_PARAMETERS_H


#include <ns3/spectrum-signal-parameters.h>

namespace ns3 {

class PacketBurst;
class LteControlMessage;



struct LteSpectrumSignalParameters : public SpectrumSignalParameters
{

  
  virtual Ptr<SpectrumSignalParameters> Copy ();

  LteSpectrumSignalParameters ();

 
  LteSpectrumSignalParameters (const LteSpectrumSignalParameters& p);

  Ptr<PacketBurst> packetBurst;
};


struct LteSpectrumSignalParametersDataFrame : public SpectrumSignalParameters
{
  
  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();
  
 
  LteSpectrumSignalParametersDataFrame ();
  
  LteSpectrumSignalParametersDataFrame (const LteSpectrumSignalParametersDataFrame& p);
  
  Ptr<PacketBurst> packetBurst;
  
  std::list<Ptr<LteControlMessage> > ctrlMsgList;
  
  uint16_t cellId;
};


struct LteSpectrumSignalParametersDlCtrlFrame : public SpectrumSignalParameters
{
  
  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();
  
  LteSpectrumSignalParametersDlCtrlFrame ();
  
  LteSpectrumSignalParametersDlCtrlFrame (const LteSpectrumSignalParametersDlCtrlFrame& p);


  std::list<Ptr<LteControlMessage> > ctrlMsgList;
  
  uint16_t cellId;
  bool pss; // primary synchronization signal
};


struct LteSpectrumSignalParametersUlSrsFrame : public SpectrumSignalParameters
{
  
  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();
  
  LteSpectrumSignalParametersUlSrsFrame ();
  
  LteSpectrumSignalParametersUlSrsFrame (const LteSpectrumSignalParametersUlSrsFrame& p);
  
  uint16_t cellId;
};


}  // namespace ns3


#endif /* LTE_SPECTRUM_SIGNAL_PARAMETERS_H */
