#ifndef BUILDINGS_OBSTACLE_PROPAGATION_LOSS_MODEL_H_
#define BUILDINGS_OBSTACLE_PROPAGATION_LOSS_MODEL_H_
#include "lte-propagation-loss-model.h"
#include <ns3/buildings-propagation-loss-model.h>
#include <ns3/simulator.h>
#include <fstream>
namespace ns3 {
class LteBuildingsPropagationLossModel : public BuildingsPropagationLossModel
{
public:
	static TypeId GetTypeId (void);
	LteBuildingsPropagationLossModel ();
	~LteBuildingsPropagationLossModel ();
	virtual double GetLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
	virtual double DoCalcRxPower (double txPowerDbm, Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
	void SetFrequency (double freq);
	std::string GetScenario();
	char GetChannelCondition(Ptr<MobilityModel> a, Ptr<MobilityModel> b);
private:
	bool IsLineIntersectBuildings (Vector L1, Vector L2 ) const;
	void LocationTrace (Vector enbLoc, Vector ueLoc, bool los) const;
	double LosLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
	double NlosLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const;
	double m_frequency;
	double m_lambda;
	static std::ofstream m_enbUeLocTrace;
	Ptr<LtePropagationLossModel> _Los;
	Ptr<LtePropagationLossModel> _Nlos;
	mutable channelConditionMap_t m_conditionMap;
	bool m_updateCondition;
	mutable Time m_prevTime;
};
}
#endif 
