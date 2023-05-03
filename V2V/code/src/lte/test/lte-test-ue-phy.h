

#ifndef LTE_TEST_UE_PHY_H
#define LTE_TEST_UE_PHY_H

#include "ns3/lte-phy.h"

#include "ns3/lte-control-messages.h"

namespace ns3 {

class LteTestUePhy : public LtePhy
{
public:
 
  LteTestUePhy ();

 
  LteTestUePhy (Ptr<LteSpectrumPhy> dlPhy, Ptr<LteSpectrumPhy> ulPhy);

  virtual ~LteTestUePhy ();

  virtual void DoDispose ();
  static TypeId GetTypeId (void);

  
  virtual void DoSendMacPdu (Ptr<Packet> p);


  virtual Ptr<SpectrumValue> CreateTxPowerSpectralDensity ();

  virtual void GenerateCtrlCqiReport (const SpectrumValue& sinr);
  
  virtual void GenerateDataCqiReport (const SpectrumValue& sinr);

  virtual void ReportInterference (const SpectrumValue& interf);

  virtual void ReportRsReceivedPower (const SpectrumValue& power);

  virtual void ReceiveLteControlMessage (Ptr<LteControlMessage> msg);

  SpectrumValue GetSinr ();

private:
  SpectrumValue m_sinr;
};


} // namespace ns3

#endif /* LTE_TEST_UE_PHY_H */
