#ifndef LTE_PROPAGATION_LOSS_MODEL_H_
#define LTE_PROPAGATION_LOSS_MODEL_H_
#include <ns3/propagation-loss-model.h>
#include "ns3/object.h"
#include "ns3/random-variable-stream.h"
#include <ns3/vector.h>
#include <map>
using namespace ns3;
struct channelCondition
{
	  char m_channelCondition;
	  double m_shadowing;
	  Vector m_position;
	  double m_hE; 
	  double m_carPenetrationLoss; 
};
typedef std::map< std::pair< Ptr<MobilityModel>, Ptr<MobilityModel> >, channelCondition> channelConditionMap_t;
class LtePropagationLossModel : public PropagationLossModel
{
public:
  static TypeId GetTypeId (void);
  LtePropagationLossModel ();
  void SetFrequency (double frequency);
  void SetMinLoss (double minLoss);
  double GetMinLoss (void) const;
  double GetFrequency (void) const;
  char GetChannelCondition(Ptr<MobilityModel> a, Ptr<MobilityModel> b);
  std::string GetScenario();
  double GetSlice (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
private:
  LtePropagationLossModel (const LtePropagationLossModel &o);
  LtePropagationLossModel & operator = (const LtePropagationLossModel &o);
  virtual double DoCalcRxPower (double txPowerDbm,Ptr<MobilityModel> a,Ptr<MobilityModel> b) const;
  virtual int64_t DoAssignStreams (int64_t stream);
  void UpdateConditionMap (Ptr<MobilityModel> a, Ptr<MobilityModel> b, channelCondition cond) const;
  double m_lambda;
  double m_frequency;
  double m_minLoss;
  mutable channelConditionMap_t m_channelConditionMap;
  std::string m_channelConditions; 
  std::string m_scenario;
  bool m_optionNlosEnabled;
  Ptr<NormalRandomVariable> m_norVar;
  Ptr<UniformRandomVariable> m_uniformVar;
  bool m_shadowingEnabled;
  bool m_inCar;
};
#endif
