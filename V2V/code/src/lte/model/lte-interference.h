


#ifndef LTE_INTERFERENCE_H
#define LTE_INTERFERENCE_H

#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/nstime.h>
#include <ns3/spectrum-value.h>

#include <list>

namespace ns3 {




class LteChunkProcessor;

class LteInterference : public Object
{
public:
  LteInterference ();
  virtual ~LteInterference ();

  // inherited from Object
  static TypeId GetTypeId (void);
  virtual void DoDispose ();

 
  void AddSinrChunkProcessor (Ptr<LteChunkProcessor> p);


  void AddInterferenceChunkProcessor (Ptr<LteChunkProcessor> p);


  void AddRsPowerChunkProcessor (Ptr<LteChunkProcessor> p);


  void StartRx (Ptr<const SpectrumValue> rxPsd);


  void EndRx ();


  void AddSignal (Ptr<const SpectrumValue> spd, const Time duration);

  void SetNoisePowerSpectralDensity (Ptr<const SpectrumValue> noisePsd);

private:
  void ConditionallyEvaluateChunk ();
  void DoAddSignal  (Ptr<const SpectrumValue> spd);
  void DoSubtractSignal  (Ptr<const SpectrumValue> spd, uint32_t signalId);



  bool m_receiving;

  Ptr<SpectrumValue> m_rxSignal; 

  Ptr<SpectrumValue> m_allSignals; 

  Ptr<const SpectrumValue> m_noise;

  Time m_lastChangeTime;    

  uint32_t m_lastSignalId;
  uint32_t m_lastSignalIdBeforeReset;

  std::list<Ptr<LteChunkProcessor> > m_rsPowerChunkProcessorList;

  std::list<Ptr<LteChunkProcessor> > m_sinrChunkProcessorList;

  std::list<Ptr<LteChunkProcessor> > m_interfChunkProcessorList;


};



} // namespace ns3





#endif /* LTE_INTERFERENCE_H */
