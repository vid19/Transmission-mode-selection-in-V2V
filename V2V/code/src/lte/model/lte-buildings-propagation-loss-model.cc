#include "lte-buildings-propagation-loss-model.h"
#include "ns3/log.h"
#include "ns3/mobility-model.h"
#include "ns3/double.h"
#include <ns3/mobility-building-info.h>
#include <ns3/building-list.h>
#include <ns3/angles.h>
#include "ns3/config-store.h"
#include <ns3/node.h>
#include "ns3/boolean.h"
NS_LOG_COMPONENT_DEFINE ("LteBuildingsPropagationLossModel");
namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED (LteBuildingsPropagationLossModel);
std::ofstream LteBuildingsPropagationLossModel::m_enbUeLocTrace;
LteBuildingsPropagationLossModel::LteBuildingsPropagationLossModel ()
{
	_Los = CreateObject<LtePropagationLossModel> ();
	_Nlos = CreateObject<LtePropagationLossModel> ();
	m_prevTime = Time(0);

	if(!m_enbUeLocTrace.is_open())
	{
		m_enbUeLocTrace.open("ENB-UE.txt");
		if (!m_enbUeLocTrace.is_open ())
		{
		  NS_FATAL_ERROR ("Can't open file ENB-UE.txt");
		  return;
		}
	}
	m_enbUeLocTrace.close();
}

LteBuildingsPropagationLossModel::~LteBuildingsPropagationLossModel ()
{
	if (m_enbUeLocTrace.is_open ())
	{
		m_enbUeLocTrace.close ();
	}
}

TypeId
LteBuildingsPropagationLossModel::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::LteBuildingsPropagationLossModel")
		.SetParent<BuildingsPropagationLossModel> ()
		.AddConstructor<LteBuildingsPropagationLossModel> ()
		.AddAttribute ("Frequency",
					   "The Frequency  (default is 28 GHz).",
					   DoubleValue (28e9),
					   MakeDoubleAccessor (&LteBuildingsPropagationLossModel::SetFrequency),
					   MakeDoubleChecker<double> ())
		.AddAttribute ("UpdateCondition",
					"Update los/nlos condition while UE moves",
					BooleanValue (true),
					MakeBooleanAccessor (&LteBuildingsPropagationLossModel::m_updateCondition),
					MakeBooleanChecker ())
	;
	return tid;
}



void
LteBuildingsPropagationLossModel::SetFrequency (double freq)
{
	m_frequency = freq;
	static const double C = 299792458.0; 
	m_lambda = C / freq;
}

double
LteBuildingsPropagationLossModel::DoCalcRxPower (double txPowerDbm, Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
	return txPowerDbm - GetLoss (a, b);
}

double
LteBuildingsPropagationLossModel::GetLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
	NS_ASSERT_MSG ((a->GetPosition ().z >= 0) && (b->GetPosition ().z >= 0),
			"LteBuildingsPropagationLossModel does not support underground nodes (placed at z < 0)");
	Ptr<MobilityBuildingInfo> a1 = a->GetObject<MobilityBuildingInfo> ();
	Ptr<MobilityBuildingInfo> b1 = b->GetObject<MobilityBuildingInfo> ();
	NS_ASSERT_MSG ((a1 != 0) && (b1 != 0), "LteBuildingsPropagationLossModel only works with MobilityBuildingInfo");

	double loss = 0.0;
	channelConditionMap_t::const_iterator it;
	it = m_conditionMap.find(std::make_pair(a,b));
	if (it == m_conditionMap.end () || m_updateCondition)
	{
		channelCondition condition;
		if (a1->IsOutdoor () && b1->IsOutdoor ())
		{
			bool intersect = IsLineIntersectBuildings(a->GetPosition(), b->GetPosition());
			if(!intersect)
			{
				condition.m_channelCondition = 'l';
				condition.m_shadowing = 0;
			}
			else
			{
				condition.m_channelCondition = 'n';
				condition.m_shadowing = 0;
			}

		}
		else if(a1->IsIndoor () && b1->IsIndoor ())
		{
			NS_FATAL_ERROR("indoor propagation loss not implemented yet");
		}
		else 
		{			
			condition.m_channelCondition = 'i';
					if(it == m_conditionMap.end () || (*it).second.m_channelCondition != 'i')
			{
				double lossIndoor = 0;
				double PL_tw;
				double stdP;
				if(_Nlos->GetScenario ()== "SR")
				{				
					PL_tw = 5-10*log10(0.3*pow(10,-1*(2+0.2*m_frequency*1e-9)/10)+0.7*pow(10,-1*(5+4*m_frequency*1e-9)/10));
					stdP = 4.4;
				}
				else
				{
					if (a1->IsIndoor () && b1->IsOutdoor ())
					{
						if(a1->GetBuilding()->GetBuildingType () == Building::Commercial || a1->GetBuilding()->GetBuildingType () == Building::Office)
						{
							NS_LOG_DEBUG ("Commercial and office building use high-loss model for S1R and UMi, use low-loss model for SR");
							PL_tw = 5-10*log10(0.7*pow(10,-1*(23+0.3*m_frequency*1e-9)/10)+0.3*pow(10,-1*(5+4*m_frequency*1e-9)/10));
							stdP = 6.5;
						}
						else
						{
							NS_LOG_DEBUG ("Residential building use low-loss model");
							PL_tw = 5-10*log10(0.3*pow(10,-1*(2+0.2*m_frequency*1e-9)/10)+0.7*pow(10,-1*(5+4*m_frequency*1e-9)/10));
							stdP = 4.4;

						}

					}
					else if (b1->IsIndoor () && a1->IsOutdoor ())
					{
						if(b1->GetBuilding()->GetBuildingType () == Building::Commercial || b1->GetBuilding()->GetBuildingType () == Building::Office)
						{
							NS_LOG_DEBUG("Commercial and office building use high-loss model for S1R and UMi, use low-loss model for SR");
							PL_tw = 5-10*log10(0.7*pow(10,-1*(23+0.3*m_frequency*1e-9)/10)+0.3*pow(10,-1*(5+4*m_frequency*1e-9)/10));
							stdP = 6.5;
						}

						else
						{
							NS_LOG_DEBUG ("Residential building use low-loss model");
							PL_tw = 5-10*log10(0.3*pow(10,-1*(2+0.2*m_frequency*1e-9)/10)+0.7*pow(10,-1*(5+4*m_frequency*1e-9)/10));
							stdP = 4.4;
						}

					}
					else
					{
						NS_FATAL_ERROR("Programming Error");
					}
				}
				lossIndoor += PL_tw;
				Ptr<UniformRandomVariable> uniRv1 = CreateObject<UniformRandomVariable> ();
				Ptr<UniformRandomVariable> uniRv2 = CreateObject<UniformRandomVariable> ();
				double dis_2D_in;
				if(_Nlos->GetScenario ()== "SR")
				{
					dis_2D_in = std::min(uniRv1->GetValue(0,10), uniRv2->GetValue(0,10));
				}
				else
				{
					dis_2D_in = std::min(uniRv1->GetValue(0,25), uniRv2->GetValue(0,25));
				}
				lossIndoor += 0.5*dis_2D_in;
				Ptr<NormalRandomVariable> norRv = CreateObject<NormalRandomVariable> ();
				lossIndoor += stdP*norRv->GetValue();
				condition.m_shadowing = lossIndoor;
			}
			else
			{
				condition.m_shadowing = (*it).second.m_shadowing;
			}
		}


		if (it == m_conditionMap.end ())
		{
			m_conditionMap.insert (std::make_pair(std::make_pair (a,b), condition));
			m_conditionMap.insert (std::make_pair(std::make_pair (b,a), condition));
			it = m_conditionMap.find(std::make_pair(a,b));
		}
		else if ((*it).second.m_channelCondition != condition.m_channelCondition)
		{
			m_conditionMap.erase (std::make_pair (a,b));
			m_conditionMap.erase (std::make_pair (b,a));
			m_conditionMap.insert (std::make_pair(std::make_pair (a,b), condition));
			m_conditionMap.insert (std::make_pair(std::make_pair (b,a), condition));
			it = m_conditionMap.find(std::make_pair(a,b));
		}

	}

	if((*it).second.m_channelCondition == 'l')
	{
		loss = _Los->GetSlice (a,b);

	}
	else if ((*it).second.m_channelCondition == 'n')
	{
		loss = _Nlos->GetSlice (a,b);

	}
	else if ((*it).second.m_channelCondition == 'i')
	{
		loss =  _Nlos->GetSlice (a,b) + (*it).second.m_shadowing;
	}
	else
	{
		NS_FATAL_ERROR("Programming error");
	}
	if(Now().GetSeconds()-m_prevTime.GetSeconds()>3)
	{
		m_prevTime = Now();
	}

	if (Now().GetSeconds() - m_prevTime.GetSeconds()<0.00009)
	{
	}
	return loss;
}
double
LteBuildingsPropagationLossModel::LosLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
	return 0;
}
double
LteBuildingsPropagationLossModel::NlosLoss (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
	return 0;
}

bool
LteBuildingsPropagationLossModel::IsLineIntersectBuildings(Vector L1, Vector L2 ) const
{
	for (BuildingList::Iterator bit = BuildingList::Begin (); bit != BuildingList::End (); ++bit)
	{
		Box boundaries = (*bit)->GetBoundaries ();

		Vector boxSize (0.5*(boundaries.xMax - boundaries.xMin),
				0.5*(boundaries.yMax - boundaries.yMin),
				0.5*(boundaries.zMax - boundaries.zMin));
		Vector boxCenter (boundaries.xMin + boxSize.x,
				boundaries.yMin + boxSize.y,
				boundaries.zMin + boxSize.z);
		Vector LB1 (L1.x-boxCenter.x, L1.y-boxCenter.y, L1.z-boxCenter.z);
		Vector LB2 (L2.x-boxCenter.x, L2.y-boxCenter.y, L2.z-boxCenter.z);
		Vector LMid (0.5*(LB1.x+LB2.x), 0.5*(LB1.y+LB2.y), 0.5*(LB1.z+LB2.z));
		Vector L (LB1.x - LMid.x, LB1.y - LMid.y, LB1.z - LMid.z);
		Vector LExt ( std::abs(L.x), std::abs(L.y), std::abs(L.z) );
		if ( std::abs( LMid.x ) > boxSize.x + LExt.x ) continue;
		if ( std::abs( LMid.y ) > boxSize.y + LExt.y ) continue;
		if ( std::abs( LMid.z ) > boxSize.z + LExt.z ) continue;
		if ( std::abs( LMid.y * L.z - LMid.z * L.y)  >  (boxSize.y * LExt.z + boxSize.z * LExt.y) ) continue;
		if ( std::abs( LMid.x * L.z - LMid.z * L.x)  >  (boxSize.x * LExt.z + boxSize.z * LExt.x) ) continue;
		if ( std::abs( LMid.x * L.y - LMid.y * L.x)  >  (boxSize.x * LExt.y + boxSize.y * LExt.x) ) continue;
		return true;
	}
	return false;
}

void
LteBuildingsPropagationLossModel::LocationTrace (Vector enbLoc, Vector ueLoc, bool los) const
{
	if(!m_enbUeLocTrace.is_open())
	{
		m_enbUeLocTrace.open("ENB-UE.txt",std::ofstream::app);
		if (!m_enbUeLocTrace.is_open ())
		{
		  NS_FATAL_ERROR ("Can't open file ENB-UE.txt");
		  return;
		}
	}
	m_enbUeLocTrace << Simulator::Now ().GetNanoSeconds () / (double) 1e9 << "\t";
	m_enbUeLocTrace << enbLoc.x<< "\t";
	m_enbUeLocTrace << enbLoc.y<< "\t";
	m_enbUeLocTrace << enbLoc.z<< "\t";
	m_enbUeLocTrace << ueLoc.x<< "\t";
	m_enbUeLocTrace << ueLoc.y<< "\t";
	m_enbUeLocTrace << ueLoc.z << "\t";
	m_enbUeLocTrace << los << "\n";
	m_enbUeLocTrace.close();
}

std::string
LteBuildingsPropagationLossModel::GetScenario ()
{
	return _Los->GetScenario();
}

char
LteBuildingsPropagationLossModel::GetChannelCondition(Ptr<MobilityModel> a, Ptr<MobilityModel> b)
{
	channelConditionMap_t::const_iterator it;
	it = m_conditionMap.find(std::make_pair(a,b));
	if (it == m_conditionMap.end ())
	{
		NS_FATAL_ERROR ("Cannot find the link in the map");
	}
	return (*it).second.m_channelCondition;

}
} 
