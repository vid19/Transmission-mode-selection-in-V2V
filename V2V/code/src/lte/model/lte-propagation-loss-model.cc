#include "lte-propagation-loss-model.h"
#include <ns3/log.h>
#include "ns3/mobility-model.h"
#include "ns3/boolean.h"
#include "ns3/double.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include <ns3/simulator.h>
#include <ns3/node.h>
using namespace ns3;
NS_LOG_COMPONENT_DEFINE ("LtePropagationLossModel");
NS_OBJECT_ENSURE_REGISTERED (LtePropagationLossModel);
TypeId
LtePropagationLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::LtePropagationLossModel")
    .SetParent<PropagationLossModel> ()
    .AddConstructor<LtePropagationLossModel> ()
    .AddAttribute ("Frequency",
                   "The carrier frequency (in Hz) at which propagation occurs  (default is 28 GHz).",
                   DoubleValue (28e9),
                   MakeDoubleAccessor (&LtePropagationLossModel::SetFrequency,
                                       &LtePropagationLossModel::GetFrequency),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("MinLoss",
                   "The minimum value (dB) of the total loss, used at short ranges.",
                   DoubleValue (0.0),
                   MakeDoubleAccessor (&LtePropagationLossModel::SetMinLoss,
                                       &LtePropagationLossModel::GetMinLoss),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("ChannelCondition",
					"'l' for LOS, 'n' for NLOS, 'a' for all",
					StringValue ("a"),
					MakeStringAccessor (&LtePropagationLossModel::m_channelConditions),
					MakeStringChecker ())
	.AddAttribute ("Scenario",
				"The available channel scenarios are 'SR', 'S1R', 'HO', 'InH-OfficeMixed', 'InH-OfficeOpen', 'InH-ShoppingMall'",
				StringValue ("SR"),
				MakeStringAccessor (&LtePropagationLossModel::m_scenario),
				MakeStringChecker ())
	.AddAttribute ("OptionalNlos",
				"Use the optional NLoS propagation loss model",
				BooleanValue (false),
				MakeBooleanAccessor (&LtePropagationLossModel::m_optionNlosEnabled),
				MakeBooleanChecker ())
	.AddAttribute ("Shadowing",
				"Enable shadowing effect",
				BooleanValue (true),
				MakeBooleanAccessor (&LtePropagationLossModel::m_shadowingEnabled),
				MakeBooleanChecker ())
    .AddAttribute ("InCar",
                   "If inside a vehicle, car penetration loss should be added to propagation loss",
                   BooleanValue (false),
                   MakeBooleanAccessor (&LtePropagationLossModel::m_inCar),
                   MakeBooleanChecker ())
  ;
  return tid;
}
LtePropagationLossModel::LtePropagationLossModel ()
{
  m_channelConditionMap.clear ();
  m_norVar = CreateObject<NormalRandomVariable> ();
  m_norVar->SetAttribute ("Mean", DoubleValue (0));
  m_norVar->SetAttribute ("Variance", DoubleValue (1));
  m_uniformVar = CreateObject<UniformRandomVariable> ();
  m_uniformVar->SetAttribute ("Min", DoubleValue (0));
  m_uniformVar->SetAttribute ("Max", DoubleValue (1));
}
void
LtePropagationLossModel::SetMinLoss (double minLoss)
{
  m_minLoss = minLoss;
}
double
LtePropagationLossModel::GetMinLoss (void) const
{
  return m_minLoss;
}

void
LtePropagationLossModel::SetFrequency (double frequency)
{
  m_frequency = frequency;
  static const double C = 299792458.0; 
  m_lambda = C / frequency;
}
double
LtePropagationLossModel::GetFrequency (void) const
{
  return m_frequency;
}
double
LtePropagationLossModel::DoCalcRxPower (double txPowerDbm,Ptr<MobilityModel> a,Ptr<MobilityModel> b) const
{
	  return (txPowerDbm - GetSlice (a, b));
}
double
LtePropagationLossModel::GetSlice (Ptr<MobilityModel> a, Ptr<MobilityModel> b) const
{
	Ptr<MobilityModel> ueMob, enbMob;
	Vector uePos = ueMob->GetPosition();
	Vector enbPos = enbMob->GetPosition();
	double x = uePos.x-enbPos.x;
	double y = uePos.y-enbPos.y;
	double distance2D = sqrt (x*x +y*y);
	double hBs = enbPos.z;
	double hUt = uePos.z;

	double distance3D = a->GetDistanceFrom (b);

	if (distance3D < 3*m_lambda)
	{
		NS_LOG_UNCOND ("distance not within the far field region => inaccurate propagation loss value");
	}
	if (distance3D <= 0)
	{
		return  m_minLoss;
	}


	channelConditionMap_t::const_iterator it;
	it = m_channelConditionMap.find(std::make_pair(a,b));
	if (it == m_channelConditionMap.end ())
	{
		channelCondition condition;

		if (m_channelConditions.compare("l")==0 )
		{
			condition.m_channelCondition = 'l';
			NS_LOG_UNCOND (m_scenario << " scenario, channel condition is fixed to be " << condition.m_channelCondition<<", h_BS="<<hBs<<",h_UT="<<hUt);
		}
		else if (m_channelConditions.compare("n")==0)
		{
			condition.m_channelCondition = 'n';
			NS_LOG_UNCOND (m_scenario << " scenario, channel condition is fixed to be " << condition.m_channelCondition<<", h_BS="<<hBs<<",h_UT="<<hUt);
		}
		else if (m_channelConditions.compare("a")==0)
		{
			double PRef = m_uniformVar->GetValue();
			double probLos;
			if (m_scenario == "SR")
			{
				if(distance2D <= 10)
				{
					probLos = 1;
				}
				else
				{
					probLos = exp(-(distance2D-10)/1000);
				}
			}
			else if (m_scenario == "S1R")
			{
				if(distance2D <= 18)
				{
					probLos = 1;
				}
				else
				{
					double C_hUt;
					if (hUt <= 13)
					{
						C_hUt = 0;
					}
					else if(hUt <=23)
					{
						C_hUt = pow((hUt-13)/10,1.5);
					}
					else
					{
						NS_FATAL_ERROR ("From Table 7.4.2-1, S1R scenario hUT cannot be larger than 23 m");
					}
					probLos = (18/distance2D+exp(-distance2D/63)*(1-18/distance2D))*(1+C_hUt*5/4*pow(distance2D/100,3)*exp(-distance2D/150));
				}
			}
			else if (m_scenario == "HO")
			{
				if(distance2D <= 18)
				{
					probLos = 1;
				}
				else
				{
					probLos = 18/distance2D+exp(-distance2D/36)*(1-18/distance2D);
				}
			}
			else if (m_scenario == "InH-OfficeMixed")
			{
				if(distance2D <= 1.2)
				{
					probLos = 1;
				}
				else if (distance2D <= 6.5)
				{
					probLos = exp(-(distance2D-1.2)/4.7);
				}
				else
				{
					probLos = exp(-(distance2D-6.5)/32.6)*0.32;
				}
			}
			else if (m_scenario == "InH-OfficeOpen")
			{
				if(distance2D <= 5)
				{
					probLos = 1;
				}
				else if (distance2D <= 49)
				{
					probLos = exp(-(distance2D-5)/70.8);
				}
				else
				{
					probLos = exp(-(distance2D-49)/211.7)*0.54;
				}
			}
			else if (m_scenario == "InH-ShoppingMall")
			{
				probLos = 1;

			}
			else
			{
				NS_FATAL_ERROR ("Unknown channel condition");
			}

			if (PRef <= probLos)
			{
				condition.m_channelCondition = 'l';
			}
			else
			{
				condition.m_channelCondition = 'n';
			}
			NS_LOG_UNCOND (m_scenario << " scenario, 2D distance = " << distance2D <<"m, Prob_LOS = " << probLos
					<< ", Prob_REF = " << PRef << ", the channel condition is " << condition.m_channelCondition<<", h_BS="<<hBs<<",h_UT="<<hUt);

		}
		else
		{
			NS_FATAL_ERROR ("Wrong channel condition configuration");
		}
		condition.m_shadowing = -1e6;
		condition.m_hE = 0;
                condition.m_carPenetrationLoss = 9+m_norVar->GetValue()*5;
		std::pair<channelConditionMap_t::const_iterator, bool> ret;
		ret = m_channelConditionMap.insert (std::make_pair(std::make_pair (a,b), condition));
		m_channelConditionMap.insert (std::make_pair(std::make_pair (b,a), condition));
		it = ret.first;
	}
	double lossDb = 0;
	double freqGHz = m_frequency/1e9;
	double shadowingStd = 0;
	double shadowingCorDistance = 0;
	if (m_scenario == "SR")
	{
		if(distance2D < 10)
		{
			NS_LOG_UNCOND ("The 2D distance is smaller than 10 meters, the 3GPP SR model may not be accurate");
		}

		if (hBs < 10 || hBs > 150 )
		{
			NS_FATAL_ERROR ("According to table 7.4.1-1, the SR scenario need to satisfy the following condition, 10 m <= hBS <= 150 m");
		}

		if (hUt < 1 || hUt > 10 )
		{
			NS_FATAL_ERROR ("According to table 7.4.1-1, the SR scenario need to satisfy the following condition, 1 m <= hUT <= 10 m");
		}
		double W = 20; 
		double h = 5; 
		double dBP = 2*M_PI*hBs*hUt*m_frequency/3e8; 
		double PL1 = 20*log10(40*M_PI*distance3D*freqGHz/3) + std::min(0.03*pow(h,1.72),10.0)*log10(distance3D) - std::min(0.044*pow(h,1.72),14.77) + 0.002*log10(h)*distance3D;
		if(distance2D <= dBP)
		{
			lossDb = PL1;
			shadowingStd = 4;
		}
		else
		{
			lossDb = PL1 + 40*log10(distance3D/dBP);
			shadowingStd= 6;
		}

		switch ((*it).second.m_channelCondition)
		{
			case 'l':
			{
				shadowingCorDistance = 37;
				break;
			}
			case 'n':
			{
				shadowingCorDistance = 120;
				double PLNlos = 161.04-7.1*log10(W)+7.5*log10(h)-(24.37-3.7*pow((h/hBs),2))*log10(hBs)+(43.42-3.1*log10(hBs))*(log10(distance3D)-3)+20*log10(freqGHz)-(3.2*pow(log10(11.75*hUt),2)-4.97);
				lossDb = std::max(PLNlos, lossDb);
				shadowingStd = 8;
				break;
			}
			default:
				NS_FATAL_ERROR ("Programming Error.");
		}

	}
	else if (m_scenario == "S1R")
	{
		if(distance2D < 10)
		{
			NS_LOG_UNCOND ("The 2D distance is smaller than 10 meters, the 3GPP S1R model may not be accurate");
		}
		if (hUt < 1.5 || hUt > 22.5 )
		{
			NS_FATAL_ERROR ("According to table 7.4.1-1, the S1R scenario need to satisfy the following condition, 1.5 m <= hUT <= 22.5 m");
		}
		if((*it).second.m_hE == 0)
		{
			channelCondition condition;
			condition = (*it).second;
			if (hUt <= 18)
			{
				condition.m_hE = 1;
			}
			else
			{
				double g_d2D = 1.25*pow(distance2D/100,3)*exp(-1*distance2D/150);
				double C_d2D_hUT = pow((hUt-13)/10,1.5)*g_d2D;
				double prob = 1/(1+C_d2D_hUT);

				if(m_uniformVar->GetValue() < prob)
				{
					condition.m_hE = 1;
				}
				else
				{
					int random = m_uniformVar->GetInteger(12, (int)(hUt-1.5));
					condition.m_hE = (double)floor(random/3)*3;
				}
			}
			UpdateConditionMap(a,b,condition);
		}
		double dBP = 4*(hBs-(*it).second.m_hE)*(hUt-(*it).second.m_hE)*m_frequency/3e8;
		if(distance2D <= dBP)
		{
			lossDb = 32.4+20*log10(distance3D)+20*log10(freqGHz);
		}
		else
		{
			lossDb = 32.4+40*log10(distance3D)+20*log10(freqGHz)-10*log10(pow(dBP,2)+pow(hBs-hUt,2));
		}
		switch ((*it).second.m_channelCondition)
		{
			case 'l':
			{
				shadowingStd = 4;
				shadowingCorDistance = 37;
				break;
			}
			case 'n':
			{
				shadowingCorDistance = 50;
				if(m_optionNlosEnabled)
				{
					lossDb = 32.4+20*log10(freqGHz)+30*log10(distance3D);
					shadowingStd = 7.8;
				}
				else
				{
					double PLNlos = 13.54+39.08*log10(distance3D)+20*log10(freqGHz)-0.6*(hUt-1.5);
					shadowingStd = 6;
					lossDb = std::max(PLNlos, lossDb);
				}


				break;
			}
			default:
				NS_FATAL_ERROR ("Programming Error.");
		}
	}
	else if (m_scenario == "HO")
	{

		if(distance2D < 10)
		{
			NS_LOG_UNCOND ("The 2D distance is smaller than 10 meters, the 3GPP HO model may not be accurate");
		}
		if (hUt < 1.5 || hUt > 22.5 )
		{
			NS_FATAL_ERROR ("According to table 7.4.1-1, the HO scenario need to satisfy the following condition, 1.5 m <= hUT <= 22.5 m");
		}
		double dBP = 4*(hBs-1)*(hUt-1)*m_frequency/3e8;
		if(distance2D <= dBP)
		{
			lossDb = 32.4+21*log10(distance3D)+20*log10(freqGHz);
		}
		else
		{
			lossDb = 32.4+40*log10(distance3D)+20*log10(freqGHz)-9.5*log10(pow(dBP,2)+pow(hBs-hUt,2));
		}


		switch ((*it).second.m_channelCondition)
		{
			case 'l':
			{
				shadowingStd = 4;
				shadowingCorDistance = 10;
				break;
			}
			case 'n':
			{
				shadowingCorDistance = 13;
				if(m_optionNlosEnabled)
				{
					lossDb = 32.4+20*log10(freqGHz)+31.9*log10(distance3D);
					shadowingStd = 8.2;
				}
				else
				{
					double PLNlos = 35.3*log10(distance3D)+22.4+21.3*log10(freqGHz)-0.3*(hUt-1.5);
					shadowingStd = 7.82;
					lossDb = std::max(PLNlos, lossDb);
				}

				break;
			}
			default:
				NS_FATAL_ERROR ("Programming Error.");
		}
	}
	else if (m_scenario == "InH-OfficeMixed" || m_scenario == "InH-OfficeOpen")
	{
		if(distance3D < 1 || distance3D > 100)
		{
			NS_LOG_UNCOND ("The pathloss might not be accurate since 3GPP InH-Office model LoS condition is accurate only within 3D distance between 1 m and 100 m");
		}

		lossDb = 32.4+17.3*log10(distance3D)+20*log10(freqGHz);


		switch ((*it).second.m_channelCondition)
		{
			case 'l':
			{
				shadowingStd = 3;
				shadowingCorDistance = 10;
				break;
			}
			case 'n':
			{
				shadowingCorDistance = 6;
				if(distance3D > 86)
				{
					NS_LOG_UNCOND ("The pathloss might not be accurate since 3GPP InH-Office model NLoS condition only supports 3D distance between 1 m and 86 m");
				}

				if(m_optionNlosEnabled)
				{
					double PLNlos = 32.4+20*log10(freqGHz)+31.9*log10(distance3D);
					shadowingStd = 8.29;
					lossDb = std::max(PLNlos, lossDb);

				}
				else
				{
					double PLNlos = 38.3*log10(distance3D)+17.3+24.9*log10(freqGHz);
					shadowingStd = 8.03;
					lossDb = std::max(PLNlos, lossDb);
				}
				break;
			}
			default:
				NS_FATAL_ERROR ("Programming Error.");
		}
	}

	else if (m_scenario == "InH-ShoppingMall")
	{
		shadowingCorDistance = 10; 
		if(distance3D < 1 || distance3D > 150)
		{
			NS_LOG_UNCOND ("The pathloss might not be accurate since 3GPP InH-Shopping mall model only supports 3D distance between 1 m and 150 m");\
		}
		lossDb = 32.4+17.3*log10(distance3D)+20*log10(freqGHz);
		shadowingStd = 2;
	}
	else
	{
		NS_FATAL_ERROR ("Unknown channel condition");
	}

	if(m_shadowingEnabled)
	{
		channelCondition cond;
		cond = (*it).second;
		if((*it).second.m_shadowing < -1e5)
		{
			cond.m_shadowing = m_norVar->GetValue()*shadowingStd;
		}
		else
		{
			double deltaX = uePos.x-(*it).second.m_position.x;
			double deltaY = uePos.y-(*it).second.m_position.y;
			double disDiff = sqrt (deltaX*deltaX +deltaY*deltaY);
			double R = exp(-1*disDiff/shadowingCorDistance); 
			cond.m_shadowing = R*(*it).second.m_shadowing + sqrt(1-R*R)*m_norVar->GetValue()*shadowingStd;
		}

		lossDb += cond.m_shadowing;
		cond.m_position = ueMob->GetPosition();
		UpdateConditionMap(a,b,cond);
	}

    if(m_inCar)
    {
        lossDb += (*it).second.m_carPenetrationLoss;
    }
	return std::max (lossDb, m_minLoss);
}

int64_t
LtePropagationLossModel::DoAssignStreams (int64_t stream)
{
  return 0;
}

void
LtePropagationLossModel::UpdateConditionMap (Ptr<MobilityModel> a, Ptr<MobilityModel> b, channelCondition cond) const
{
	m_channelConditionMap[std::make_pair (a,b)] = cond;
	m_channelConditionMap[std::make_pair (b,a)] = cond;

}

char
LtePropagationLossModel::GetChannelCondition(Ptr<MobilityModel> a, Ptr<MobilityModel> b)
{
	channelConditionMap_t::const_iterator it;
	it = m_channelConditionMap.find(std::make_pair(a,b));
	if (it == m_channelConditionMap.end ())
	{
		NS_FATAL_ERROR ("Cannot find the link in the map");
	}
	return (*it).second.m_channelCondition;

}

std::string
LtePropagationLossModel::GetScenario ()
{
	return m_scenario;
}
