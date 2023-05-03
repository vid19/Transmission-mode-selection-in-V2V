#include "lte-channel.h"
#include <ns3/log.h>
#include <ns3/math.h>
#include <ns3/simulator.h>
#include <ns3/node.h>
#include <ns3/double.h>
#include <algorithm>
#include <random>    
#include <ns3/boolean.h>
#include <ns3/integer.h>
namespace ns3{
NS_LOG_COMPONENT_DEFINE ("LteChannel");
NS_OBJECT_ENSURE_REGISTERED (LteChannel);
static const double offSetAlpha[20] = {
0.0447,-0.0447,0.1413,-0.1413,0.2492,-0.2492,0.3715,-0.3715,0.5129,-0.5129,0.6797,-0.6797,0.8844,-0.8844,1.1481,-1.1481,1.5195,-1.5195,2.1551,-2.1551
};
static const double sqrtC_RMa_LOS[7][7] = {
		{1, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0},
		{-0.5, 0, 0.866025, 0, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0.5, -0, 0.866025, 0},
		{-0.8, 0, -0.46188, 0, 0, 0, 0.382971},
};
static const double sqrtC_RMa_NLOS[6][6] = {
		{1, 0, 0, 0, 0, 0},
		{-0.5, 0.866025, 0, 0, 0, 0},
		{0.6, -0.11547, 0.791623, 0, 0, 0},
		{0, 0, 0, 1, 0, 0},
		{0, -0.57735, 0.547399, 0, 0.605823, 0},
		{-0.4, -0.23094, 0.143166, 0, -0.349446, 0.802532},
};
static const double sqrtC_UMa_LOS[7][7] = {
		{1, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0},
		{-0.4, -0.4, 0.824621, 0, 0, 0, 0},
		{-0.5, 0, 0.242536, 0.83137, 0, 0, 0},
		{-0.5, -0.2, 0.630593, -0.484671, 0.278293, 0, 0},
		{0, 0, -0.242536, 0.672172, 0.642214, 0.27735, 0},
		{-0.8, 0, -0.388057, -0.367926, 0.238537, -3.58949e-15, 0.130931},
};
static const double sqrtC_UMa_NLOS[6][6] = {
		{1, 0, 0, 0, 0, 0},
		{-0.4, 0.916515, 0, 0, 0, 0},
		{-0.6, 0.174574, 0.78072, 0, 0, 0},
		{0, 0.654654, 0.365963, 0.661438, 0, 0},
		{0, -0.545545, 0.762422, 0.118114, 0.327327, 0},
		{-0.4, -0.174574, -0.396459, 0.392138, 0.49099, 0.507445},
};
static const double sqrtC_UMa_O2I[6][6] = {
		{1, 0, 0, 0, 0, 0},
		{-0.5, 0.866025, 0, 0, 0, 0},
		{0, 0.46188, 0.886942, 0, 0, 0},
		{0.53, 0.305996, -0.159349, 0.774645, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0.4, -0.381051, 0.671972, 0.0150753, -0, 0.492978},

};
static const double sqrtC_UMi_LOS[7][7] = {
		{1, 0, 0, 0, 0, 0, 0},
		{0.5, 0.866025, 0, 0, 0, 0, 0},
		{-0.4, -0.57735, 0.711805, 0, 0, 0, 0},
		{-0.5, 0.057735, 0.468293, 0.726201, 0, 0, 0},
		{-0.4, -0.11547, 0.805464, -0.23482, 0.350363, 0, 0},
		{0, 0, 0, 0.688514, 0.461454, 0.559471, 0},
		{0, 0, 0.280976, 0.231921, -0.490509, 0.11916, 0.782603},
};
static const double sqrtC_UMi_NLOS[6][6] = {
		{1, 0, 0, 0, 0, 0},
		{-0.7, 0.714143, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{-0.4, 0.168034, 0, 0.90098, 0, 0},
		{0, -0.70014, 0.5, 0.130577, 0.4927, 0},
		{0, 0, 0.5, 0.221981, -0.566238, 0.616522},
};
static const double sqrtC_UMi_O2I[6][6] = {
		{1, 0, 0, 0, 0, 0},
		{-0.5, 0.866025, 0, 0, 0, 0},
		{0, 0.46188, 0.886942, 0, 0, 0},
		{0.53, 0.305996, -0.159349, 0.774645, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0.4, -0.381051, 0.671972, 0.0150753, -0, 0.492978},
};
static const double sqrtC_office_LOS[7][7] = {
		{1, 0, 0, 0, 0, 0, 0},
		{0.5, 0.866025, 0, 0, 0, 0, 0},
		{-0.8, -0.11547, 0.588784, 0, 0, 0, 0},
		{-0.4, 0.23094, 0.520847, 0.717903, 0, 0, 0},
		{-0.5, 0.288675, 0.73598, -0.348236, 0.0610847, 0, 0},
		{0.2, -0.11547, 0.418943, 0.123222, -0.525329, 0.69282, 0},
		{-0.1, 0.173205, 0.237778, -0.00535748, 0.378725, 0.490748, 0.720532},
};
static const double sqrtC_office_NLOS[6][6] = {
		{1, 0, 0, 0, 0, 0},
		{-0.5, 0.866025, 0, 0, 0, 0},
		{0, 0.46188, 0.886942, 0, 0, 0},
		{-0.4, -0.23094, 0.120263, 0.878751, 0, 0},
		{0, -0.11547, 0.398372, 0.0289317, 0.909466, 0},
		{-0.1, -0.173205, 0.315691, -0.134243, 0.283816, 0.872792},
};
LteChannel::LteChannel ()
{
	m_uniformRv = CreateObject<UniformRandomVariable> ();
	m_uniformRvBlockage = CreateObject<UniformRandomVariable> ();
	m_expRv = CreateObject<ExponentialRandomVariable> ();
	m_normalRv = CreateObject<NormalRandomVariable> ();
	m_normalRv->SetAttribute ("Mean", DoubleValue (0));
	m_normalRv->SetAttribute ("Variance", DoubleValue (1));
	m_normalRvBlockage = CreateObject<NormalRandomVariable> ();
	m_normalRvBlockage->SetAttribute ("Mean", DoubleValue (0));
	m_normalRvBlockage->SetAttribute ("Variance", DoubleValue (1));
}
TypeId
LteChannel::GetTypeId (void)
{
	static TypeId tid = TypeId ("ns3::LteChannel")
	.SetParent<Object> ()
	.AddAttribute ("UpdatePeriod",
				"Enable spatially-consistent UT mobility modeling procedure A, the update period unit is in ms, set to 0 ms to disable update",
				TimeValue (MilliSeconds (0)),
				MakeTimeAccessor (&LteChannel::m_updatePeriod),
				MakeTimeChecker ())
	.AddAttribute ("CellScan",
				"Use beam search method to determine beamforming vector, the default is long-term covariance matrix method",
				BooleanValue (false),
				MakeBooleanAccessor (&LteChannel::m_cellScan),
				MakeBooleanChecker ())
	.AddAttribute ("Blockage",
				"Enable blockage model A (sec 7.6.4.1)",
				BooleanValue (false),
				MakeBooleanAccessor (&LteChannel::m_blockage),
				MakeBooleanChecker ())
	.AddAttribute ("NumNonselfBlocking",
				"number of non-self-blocking regions",
				IntegerValue (4),
				MakeIntegerAccessor (&LteChannel::m_numNonSelfBloking),
				MakeIntegerChecker<uint16_t> ())
	.AddAttribute ("BlockerSpeed",
				"The speed of moving blockers, the unit is m/s",
				DoubleValue (1),
				MakeDoubleAccessor (&LteChannel::m_blockerSpeed),
				MakeDoubleChecker<double> ())
	.AddAttribute ("PortraitMode",
				"true for portrait mode, false for landscape mode",
				BooleanValue (true),
				MakeBooleanAccessor (&LteChannel::m_portraitMode),
				MakeBooleanChecker ())
	;
	return tid;
}
LteChannel::~LteChannel ()
{

}

void
LteChannel::DoDispose ()
{
	NS_LOG_FUNCTION (this);
}

void
LteChannel::ConnectDevices (Ptr<NetDevice> dev1, Ptr<NetDevice> dev2)
{
	key_t key = std::make_pair(dev1,dev2);

	std::map< key_t, int >::iterator iter = m_connectedPair.find(key);
	if (iter != m_connectedPair.end ())
	{
		m_connectedPair.erase (iter);
	}
	m_connectedPair.insert(std::make_pair(key,1));
}


void
LteChannel::LongTermCovMatrixBeamforming(Ptr<Params3gpp> params) const
{
	uint8_t txSize = params->m_channel.at(0).size();
	uint8_t rxSize = params->m_channel.size();
	complex2DVector_t txQ;
	txQ.resize(txSize);
	for (uint8_t txIndex = 0; txIndex < txSize; txIndex++)
	{
		txQ.at(txIndex).resize(txSize);
	}
	for (uint8_t t1Index = 0; t1Index < txSize; t1Index++)
	{
		for (uint8_t t2Index = 0; t2Index < txSize; t2Index++)
		{
			for(uint8_t rxIndex = 0; rxIndex < rxSize; rxIndex++)
			{
				std::complex<double> cSum (0,0);
				for (uint8_t cIndex = 0; cIndex < params->m_channel.at(rxIndex).at(t1Index).size(); cIndex++)
				{
					cSum = cSum + std::conj(params->m_channel.at(rxIndex).at(t1Index).at(cIndex))*
							(params->m_channel.at(rxIndex).at(t2Index).at(cIndex));
				}
				txQ[t1Index][t2Index] += cSum;
			}

		}
	}
	complexVector_t antennaWeights;
	uint8_t txAntenna = txQ.size ();
	for (uint8_t eIndex = 0; eIndex < txAntenna; eIndex++)
	{
		antennaWeights.push_back(txQ.at (0).at (eIndex));
	}
	int iter = 10;
	double diff = 1;
	while(iter != 0 && diff>1e-10)
	{
		complexVector_t antennaWeights_New;

		for(uint8_t row = 0; row<txAntenna; row++)
		{
			std::complex<double> sum(0,0);
			for (uint8_t col = 0; col< txAntenna; col++)
			{
				sum += txQ.at (row).at (col)*antennaWeights.at (col);
			}

		    antennaWeights_New.push_back(sum);
		}
		double weightSum = 0;
		for (uint8_t i = 0; i< txAntenna; i++)
		{
			weightSum += norm(antennaWeights_New. at(i));
		}
		for (uint8_t i = 0; i< txAntenna; i++)
		{
			antennaWeights_New. at(i) = antennaWeights_New. at(i)/sqrt(weightSum);
		}
		diff = 0;
		for (uint8_t i = 0; i< txAntenna; i++)
		{
			diff += std::norm(antennaWeights_New. at(i)-antennaWeights. at(i));
		}
		iter--;
		antennaWeights = antennaWeights_New;
	}
	params->m_txW = antennaWeights;
	complex2DVector_t rxQ;
	rxQ.resize(rxSize);
	for (uint8_t r1Index = 0; r1Index < rxSize; r1Index++)
	{
		rxQ.at(r1Index).resize(rxSize);
	}
	for (uint8_t r1Index = 0; r1Index < rxSize; r1Index++)
	{
		for (uint8_t r2Index = 0; r2Index < rxSize; r2Index++)
		{
			for(uint8_t txIndex = 0; txIndex < txSize; txIndex++)
            {
				std::complex<double> cSum (0,0);
				for (uint8_t cIndex = 0; cIndex < params->m_channel.at(r1Index).at(txIndex).size(); cIndex++)
				{
					cSum = cSum + params->m_channel.at(r1Index).at(txIndex).at(cIndex)*
							std::conj(params->m_channel.at(r2Index).at(txIndex).at(cIndex));
				}
				rxQ[r1Index][r2Index] += cSum;
            }

		}
	}
	antennaWeights.clear();
	uint8_t rxAntenna = rxQ.size ();
	for (uint8_t eIndex = 0; eIndex < rxAntenna; eIndex++)
	{
		antennaWeights.push_back(rxQ.at (0).at (eIndex));
	}
	iter = 10;
	diff = 1;
	while(iter != 0 && diff>1e-10)
	{
		complexVector_t antennaWeights_New;

		for(uint8_t row = 0; row<rxAntenna; row++)
		{
			std::complex<double> sum(0,0);
			for (uint8_t col = 0; col< rxAntenna; col++)
			{
				sum += rxQ.at (row).at (col)*antennaWeights.at (col);
			}

		    antennaWeights_New.push_back(sum);
		}
		double weightSum = 0;
		for (uint8_t i = 0; i< rxAntenna; i++)
		{
			weightSum += norm(antennaWeights_New. at(i));
		}
		for (uint8_t i = 0; i< rxAntenna; i++)
		{
			antennaWeights_New. at(i) = antennaWeights_New. at(i)/sqrt(weightSum);
		}
		diff = 0;
		for (uint8_t i = 0; i< rxAntenna; i++)
		{
			diff += std::norm(antennaWeights_New. at(i)-antennaWeights. at(i));
		}
		iter--;
		antennaWeights = antennaWeights_New;
	}

	params->m_rxW = antennaWeights;
}

Ptr<SpectrumValue>
LteChannel::CalBeamformingGain (Ptr<const SpectrumValue> txPsd, Ptr<Params3gpp> params, Vector speed) const
{
	NS_LOG_FUNCTION (this);
	Ptr<SpectrumValue> tempPsd = Copy<SpectrumValue> (txPsd);
	uint8_t numCluster = params->m_delay.size();
	Values::iterator vit = tempPsd->ValuesBegin ();
	uint16_t iSubband = 0;
	double slotTime = Simulator::Now ().GetSeconds ();
	complexVector_t doppler;
	for (uint8_t cIndex = 0; cIndex < numCluster; cIndex++)
	{
	double temp_doppler = 2*M_PI*(sin(params->m_angle.at(ZOA_INDEX).at(cIndex)*M_PI/180)*cos(params->m_angle.at(AOA_INDEX).at(cIndex)*M_PI/180)*speed.x+ sin(params->m_angle.at(ZOA_INDEX).at(cIndex)*M_PI/180)*sin(params->m_angle.at(AOA_INDEX).at(cIndex)*M_PI/180)*speed.y+ cos(params->m_angle.at(ZOA_INDEX).at(cIndex)*M_PI/180)*speed.z)*slotTime;
	doppler.push_back(exp(std::complex<double> (0, temp_doppler)));
	}
	while (vit != tempPsd->ValuesEnd ())
	{
		std::complex<double> subsbandGain (0.0,0.0);
		if ((*vit) != 0.00)
		{
			double fsb = GetSystemBandwidth ()/2 + iSubband ;
			for (uint8_t cIndex = 0; cIndex < numCluster; cIndex++)
			{
				double delay = -2*M_PI*fsb*(params->m_delay.at (cIndex));
				std::complex<double> txSum(0,0);
				subsbandGain = subsbandGain + params->m_longTerm.at(cIndex)*doppler.at(cIndex)*exp(std::complex<double>(0, delay));
			}
			*vit = (*vit)*(norm (subsbandGain));
		}
		vit++;
		iSubband++;
	}
	return tempPsd;
}
double
LteChannel::GetSystemBandwidth () const
{
	double bw = 100.00;
	return bw;
}
void
LteChannel::SetPathlossModel (Ptr<PropagationLossModel> pathloss)
{
	m_3gppPathloss = pathloss;
	if (DynamicCast<LtePropagationLossModel> (m_3gppPathloss)!=0)
	{
		m_scenario = m_3gppPathloss->GetObject<LtePropagationLossModel> ()->GetScenario();
	}
	else if (DynamicCast<LteBuildingsPropagationLossModel> (m_3gppPathloss)!=0)
	{
		m_scenario = m_3gppPathloss->GetObject<LteBuildingsPropagationLossModel> ()->GetScenario();
	}
	else
	{
		NS_FATAL_ERROR("unkonw pathloss model");
	}
}
void
LteChannel::CalLongTerm (Ptr<Params3gpp> params) const
{
	uint8_t txAntenna = params->m_txW.size();
	uint8_t rxAntenna = params->m_rxW.size();
	complexVector_t longTerm;
	uint8_t numCluster = params->m_delay.size();
	for (uint8_t cIndex = 0; cIndex < numCluster; cIndex++)
	{
		std::complex<double> txSum(0,0);
		for(uint8_t txIndex = 0; txIndex < txAntenna; txIndex++)
		{
			std::complex<double> rxSum(0,0);
			for (uint8_t rxIndex = 0; rxIndex < rxAntenna; rxIndex++)
			{
				rxSum = rxSum + std::conj(params->m_rxW.at(rxIndex))*params->m_channel.at(rxIndex).at(txIndex).at(cIndex);
			}
			txSum = txSum + params->m_txW.at(txIndex)*rxSum;
		}
		longTerm.push_back(txSum);
	}
	params->m_longTerm = longTerm;

}

Ptr<ParamsTable>
LteChannel::GetSliceTable (bool los, bool o2i, double hBS, double hUT, double distance2D) const
{
	double fcGHz = 1920;
	Ptr<ParamsTable> table3gpp = CreateObject<ParamsTable> ();
	if (m_scenario == "SR")
	{
		if(los)
		{
		table3gpp->SetParams(11, 20, -7.49, 0.55, 0.90, 0.38, 1.52, 0.24, 0.60, 0.16,0.3, 0.4, 0, 3.91e-9, 2, 3, 3, 7, 4, 3.8, 3);
			for (uint8_t row = 0; row < 7; row++)
			{
				for (uint8_t column = 0; column < 7; column++)
				{
					table3gpp->m_sqrtC[row][column] = sqrtC_RMa_LOS[row][column];
				}
			}
		}
		else
		{
			double offsetZod = atan((35-5)/distance2D)-atan((35-1.5)/distance2D);
			table3gpp->SetParams(10, 20, -7.43, 0.48, 0.95, 0.45, 1.52, 0.13, 0.88, 0.16,
					0.3, 0.49, offsetZod, 3.91e-9, 2, 3, 3, 0, 0, 1.7 ,3);
			for (uint8_t row = 0; row < 6; row++)
			{
				for (uint8_t column = 0; column < 6; column++)
				{
					table3gpp->m_sqrtC[row][column] = sqrtC_RMa_NLOS[row][column];
				}
			}
		}
	}
	else if (m_scenario == "S1R")
	{
		if(los && !o2i)
		{
			double uLgZSD = std::max(-0.5, -2.1*distance2D/1000-0.01*(hUT-1.5)+0.75);
			double cDs = std::max(0.25, -3.4084*log10(fcGHz)+6.5622)*1e-9;
			table3gpp->SetParams(12, 20, -6.955-0.0963*log10(fcGHz), 0.66, 1.06+0.1114*log10(fcGHz),
					0.28, 1.81, 0.20, 0.95, 0.16, uLgZSD, 0.40, 0, cDs, 5, 11, 7, 9, 3.5, 2.5, 3);
			for (uint8_t row = 0; row < 7; row++)
			{
				for (uint8_t column = 0; column < 7; column++)
				{
					table3gpp->m_sqrtC[row][column] = sqrtC_UMa_LOS[row][column];
				}
			}
		}
		else
		{
			double uLgZSD = std::max(-0.5, -2.1*distance2D/1000-0.01*(hUT-1.5)+0.9);
			double afc = 0.208*log10(fcGHz)-0.782;
			double bfc = 25;
			double cfc = -0.13*log10(fcGHz)+2.03;
			double efc = 7.66*log10(fcGHz)-5.96;
			double offsetZOD = efc-std::pow(10, afc*log10(std::max(bfc,distance2D))+cfc);
			double cDS = std::max(0.25, -3.4084*log10(fcGHz)+6.5622)*1e-9;
			if (!los && !o2i)
			{
				table3gpp->SetParams(20, 20, -6.28-0.204*log10(fcGHz), 0.39, 1.5-0.1144*log10(fcGHz),
						0.28, 2.08-0.27*log10(fcGHz), 0.11, -0.3236*log10(fcGHz)+1.512, 0.16, uLgZSD,
						0.49, offsetZOD, cDS, 2, 15, 7, 0, 0, 2.3, 3);
				for (uint8_t row = 0; row < 6; row++)
				{
					for (uint8_t column = 0; column < 6; column++)
					{
						table3gpp->m_sqrtC[row][column] = sqrtC_UMa_NLOS[row][column];
					}
				}
			}
			else
			{
				table3gpp->SetParams(12, 20, -6.62, 0.32, 1.25, 0.42, 1.76, 0.16, 1.01, 0.43,
						uLgZSD, 0.49, offsetZOD, 11e-9, 5, 20, 6, 0, 0, 2.2, 4);
				for (uint8_t row = 0; row < 6; row++)
				{
					for (uint8_t column = 0; column < 6; column++)
					{
						table3gpp->m_sqrtC[row][column] = sqrtC_UMa_O2I[row][column];
					}
				}

			}

		}

	}
	else if (m_scenario == "HO")
	{
		if(los && !o2i)
		{
			double uLgZSD = std::max(-0.21, -14.8*distance2D/1000+0.01*std::abs(hUT-hBS)+0.83);
			table3gpp->SetParams(12, 20, -0.24*log10(1+fcGHz)-7.14, 0.38, -0.05*log10(1+fcGHz)+1.21, 0.41,
					-0.08*log10(1+fcGHz)+1.73, 0.014*log10(1+fcGHz)+0.28, -0.1*log10(1+fcGHz)+0.73, -0.04*log10(1+fcGHz)+0.34,
					uLgZSD, 0.35, 0, 5e-9, 3, 17, 7, 9, 5, 3, 3);
			for (uint8_t row = 0; row < 7; row++)
			{
				for (uint8_t column = 0; column < 7; column++)
				{
					table3gpp->m_sqrtC[row][column] = sqrtC_UMi_LOS[row][column];
				}
			}
		}
		else
		{
			double uLgZSD = std::max(-0.5, -3.1*distance2D/1000+0.01*std::max(hUT-hBS,0.0)+0.2);
			double offsetZOD = -1*std::pow(10, -1.5*log10(std::max(10.0, distance2D))+3.3);
			if (!los && !o2i)
			{
				table3gpp->SetParams(19, 20, -0.24*log10(1+fcGHz)-6.83, 0.16*log10(1+fcGHz)+0.28, -0.23*log10(1+fcGHz)+1.53,
						0.11*log10(1+fcGHz)+0.33, -0.08*log10(1+fcGHz)+1.81, 0.05*log10(1+fcGHz)+0.3,
						-0.04*log10(1+fcGHz)+0.92, -0.07*log10(1+fcGHz)+0.41, uLgZSD, 0.35, offsetZOD,
						11e-9, 10, 22, 7, 0, 0, 2.1, 3);
				for (uint8_t row = 0; row < 6; row++)
				{
					for (uint8_t column = 0; column < 6; column++)
					{
						table3gpp->m_sqrtC[row][column] = sqrtC_UMi_NLOS[row][column];
					}
				}
			}
			else
			{
				table3gpp->SetParams(12, 20, -6.62, 0.32, 1.25, 0.42, 1.76, 0.16, 1.01, 0.43,
						uLgZSD, 0.35, offsetZOD, 11e-9, 5, 20, 6, 0, 0, 2.2, 4);
				for (uint8_t row = 0; row < 6; row++)
				{
					for (uint8_t column = 0; column < 6; column++)
					{
						table3gpp->m_sqrtC[row][column] = sqrtC_UMi_O2I[row][column];
					}
				}
			}
		}
	}
	else if (m_scenario == "InH-OfficeMixed"||m_scenario == "InH-OfficeOpen")
	{
		NS_ASSERT_MSG (!o2i, "The indoor scenario does out support outdoor to indoor");
		if(los)
		{
			table3gpp->SetParams(8, 20, -0.01*log10(1+fcGHz)-7.79, -0.16*log10(1+fcGHz)+0.50, 1.60, 0.18,
					-0.19*log10(1+fcGHz)+1.86, 0.12*log10(1+fcGHz), -0.26*log10(1+fcGHz)+1.21, -0.04*log10(1+fcGHz)+0.17,
					-1.43*log10(1+fcGHz)+2.25, 0.13*log10(1+fcGHz)+0.15, 0, 3.91e-9, 7, -6.2*log10(1+fcGHz)+16.72,
					-3.85*log10(1+fcGHz)+10.28, 0.84*log10(1+fcGHz)+2.12, -0.58*log10(1+fcGHz)+6.19, 2.15, 6);
			for (uint8_t row = 0; row < 7; row++)
			{
				for (uint8_t column = 0; column < 7; column++)
				{
					table3gpp->m_sqrtC[row][column] = sqrtC_office_LOS[row][column];
				}
			}
		}
		else
		{
			table3gpp->SetParams(10, 20, -0.28*log10(1+fcGHz)-7.29, 0.1*log10(1+fcGHz)+0.11, 1.49, 0.17,
					-0.11*log10(1+fcGHz)+1.8, 0.12*log10(1+fcGHz), -0.15*log10(1+fcGHz)+1.04, -0.09*log10(1+fcGHz)+0.24,
					1.37, 0.38, 0, 3.91e-9, 3, -13.0*log10(1+fcGHz)+30.53, -3.72*log10(1+fcGHz)+10.25, 0, 0, 1.84, 3);
			for (uint8_t row = 0; row < 6; row++)
			{
				for (uint8_t column = 0; column < 6; column++)
				{
					table3gpp->m_sqrtC[row][column] = sqrtC_office_NLOS[row][column];
				}
			}
		}
	}
	else
	{
		NS_FATAL_ERROR("unkonw scenarios");
	}
	return table3gpp;
}
void
LteChannel::DeleteChannel(Ptr<const MobilityModel> a, Ptr<const MobilityModel> b) const
{
	Ptr<NetDevice> dev1 = a->GetObject<Node> ()->GetDevice (0);
	Ptr<NetDevice> dev2 = b->GetObject<Node> ()->GetDevice (0);
	NS_LOG_INFO("a position " << a->GetPosition() << " b " << b->GetPosition());
	Ptr<Params3gpp> params = m_channelMap.find(std::make_pair(dev1,dev2))->second;
	NS_LOG_INFO("params " << params);
	NS_LOG_INFO("params m_channel size" << params->m_channel.size());
	NS_ASSERT_MSG(m_channelMap.find(std::make_pair(dev1,dev2)) != m_channelMap.end(), "Channel not found");
	params->m_channel.clear();
	m_channelMap[std::make_pair(dev1,dev2)] = params;
}
doubleVector_t
LteChannel::CalAttenuationOfBlockage (Ptr<Params3gpp> params,
		doubleVector_t clusterAOA, doubleVector_t clusterZOA) const
{
	doubleVector_t powerAttenuation;
	uint8_t clusterNum = clusterAOA.size ();
	for(uint8_t cInd = 0; cInd < clusterNum; cInd++)
	{
		powerAttenuation.push_back(0); 
	}
	double phi_sb, x_sb, theta_sb, y_sb;
	if(m_portraitMode)
	{
		phi_sb = 260;
		x_sb = 120;
		theta_sb = 100;
		y_sb = 80;
	}
	else
	{
		phi_sb = 40;
		x_sb = 160;
		theta_sb = 110;
		y_sb = 75;
	}
	if(params->m_nonSelfBlocking.size ()==0)
	{
		for(uint16_t blockInd=0; blockInd<m_numNonSelfBloking; blockInd++)
		{
			doubleVector_t table;
			table.push_back (m_normalRvBlockage->GetValue()); 
			if(m_scenario == "InH-OfficeMixed" || m_scenario == "InH-OfficeOpen")
			{
				table.push_back (m_uniformRvBlockage->GetValue(15, 45)); 
				table.push_back (90); 
				table.push_back (m_uniformRvBlockage->GetValue(5, 15)); 
				table.push_back (2); 
			}
			else
			{
				table.push_back (m_uniformRvBlockage->GetValue(5, 15)); 
				table.push_back (90); 
				table.push_back (5); 
				table.push_back (10);
			}
			params->m_nonSelfBlocking.push_back(table);
		}
	}
	else
	{
		double deltaX =sqrt(pow(params->m_preLocUT.x-params->m_locUT.x, 2)+pow(params->m_preLocUT.y-params->m_locUT.y, 2));
		if(deltaX > 1e-6 || m_blockerSpeed > 1e-6)
		{
			double corrDis;
			if(m_scenario == "InH-OfficeMixed" || m_scenario == "InH-OfficeOpen")
			{
				corrDis = 5;
			}
			else
			{
				if(params->m_o2i)
				{
					corrDis = 5;
				}
				else 
				{
					corrDis = 10;
				}
			}
			double R;
			if(m_blockerSpeed > 1e-6) 
			{
				double corrT = corrDis/m_blockerSpeed;
				R = exp(-1*(deltaX/corrDis+(Now().GetSeconds()-params->m_generatedTime.GetSeconds())/corrT));
			}
			else
			{
				R = exp(-1*(deltaX/corrDis));
			}

			NS_LOG_INFO ("Distance change:"<<deltaX<<" Speed:"<<m_blockerSpeed
					<<" Time difference:"<<Now().GetSeconds()-params->m_generatedTime.GetSeconds()
					<<" correlation:"<<R);
			if(R*R*(-0.069)+R*1.074-0.002 < 1)
			{
				R = R*R*(-0.069)+R*1.074-0.002;
			}
			for(uint16_t blockInd=0; blockInd<m_numNonSelfBloking; blockInd++)
			{
				params->m_nonSelfBlocking.at(blockInd).at(PHI_INDEX) =
						R*params->m_nonSelfBlocking.at(blockInd).at(PHI_INDEX) + sqrt(1-R*R)*m_normalRvBlockage->GetValue ();
			}
		}

	}
	for(uint8_t cInd = 0; cInd < clusterNum; cInd++)
	{
		NS_ASSERT_MSG(clusterAOA.at (cInd)>=0 && clusterAOA.at (cInd)<=360, "the AOA should be the range of [0,360]");
		NS_ASSERT_MSG(clusterZOA.at (cInd)>=0 && clusterZOA.at (cInd)<=180, "the ZOA should be the range of [0,180]");
		NS_LOG_INFO ("AOA="<<clusterAOA.at (cInd) << " Block Region[" << phi_sb - x_sb/2<< ","<<phi_sb + x_sb/2<<"]");
		NS_LOG_INFO ("ZOA="<<clusterZOA.at (cInd) << " Block Region[" << theta_sb - y_sb/2<< ","<<theta_sb + y_sb/2<<"]");
		if( std::abs(clusterAOA.at (cInd)-phi_sb)<(x_sb/2) && std::abs(clusterZOA.at (cInd)-theta_sb)<(y_sb/2))
		{
			powerAttenuation.at (cInd) += 30; 
			NS_LOG_INFO ("Cluster["<<(int)cInd<<"] is blocked by self blocking region and reduce 30 dB power,"
					"the attenuation is ["<<powerAttenuation.at (cInd)<<" dB]");
		}
		double phiK, xK, thetaK, yK;
		for(uint16_t blockInd=0; blockInd<m_numNonSelfBloking; blockInd++)
		{
			phiK = (0.5*erfc(-1*params->m_nonSelfBlocking.at(blockInd).at(PHI_INDEX)/sqrt(2)))*360;
			while(phiK > 360)
			{
				phiK -= 360;
			}

			while (phiK < 0)
			{
				phiK += 360;
			}

			xK = params->m_nonSelfBlocking.at(blockInd).at(X_INDEX);
			thetaK = params->m_nonSelfBlocking.at(blockInd).at(THETA_INDEX);
			yK = params->m_nonSelfBlocking.at(blockInd).at(Y_INDEX);
			NS_LOG_INFO ("AOA="<<clusterAOA.at (cInd) << " Block Region[" << phiK - xK<< ","<<phiK + xK<<"]");
			NS_LOG_INFO ("ZOA="<<clusterZOA.at (cInd) << " Block Region[" << thetaK - yK<< ","<<thetaK + yK<<"]");

			if( std::abs(clusterAOA.at (cInd)-phiK)<(xK)
					&& std::abs(clusterZOA.at (cInd)-thetaK)<(yK))
			{
				double A1 = clusterAOA.at (cInd)-(phiK+xK/2); 
				double A2 = clusterAOA.at (cInd)-(phiK-xK/2); 
				double Z1 = clusterZOA.at (cInd)-(thetaK+yK/2);
				double Z2 = clusterZOA.at (cInd)-(thetaK-yK/2);
				int signA1, signA2, signZ1, signZ2;
				if (xK/2<clusterAOA.at (cInd)-phiK && clusterAOA.at (cInd)-phiK<=xK)
				{
					signA1 = -1;
				}
				else
				{
					signA1 = 1;
				}
				if (-1*xK<clusterAOA.at (cInd)-phiK && clusterAOA.at (cInd)-phiK<=-1*xK/2)
				{
					signA2 = -1;
				}
				else
				{
					signA2 = 1;
				}

				if (yK/2<clusterZOA.at (cInd)-thetaK && clusterZOA.at (cInd)-thetaK<=yK)
				{
					signZ1 = -1;
				}
				else
				{
					signZ1 = 1;
				}
				if (-1*yK<clusterZOA.at (cInd)-thetaK && clusterZOA.at (cInd)-thetaK<=-1*yK/2)
				{
					signZ2 = -1;
				}
				else
				{
					signZ2 = 1;
				}
				double lambda = 3e8/1920;
				double F_A1 = atan(signA1*M_PI/2*sqrt(M_PI/lambda*
						params->m_nonSelfBlocking.at(blockInd).at(R_INDEX)*(1/cos(A1*M_PI/180)-1)))/M_PI; 
				double F_A2 = atan(signA2*M_PI/2*sqrt(M_PI/lambda*
						params->m_nonSelfBlocking.at(blockInd).at(R_INDEX)*(1/cos(A2*M_PI/180)-1)))/M_PI;
				double F_Z1 = atan(signZ1*M_PI/2*sqrt(M_PI/lambda*
						params->m_nonSelfBlocking.at(blockInd).at(R_INDEX)*(1/cos(Z1*M_PI/180)-1)))/M_PI;
				double F_Z2 = atan(signZ2*M_PI/2*sqrt(M_PI/lambda*
						params->m_nonSelfBlocking.at(blockInd).at(R_INDEX)*(1/cos(Z2*M_PI/180)-1)))/M_PI;
				double L_dB = -20*log10(1-(F_A1+F_A2)*(F_Z1+F_Z2));
				powerAttenuation.at(cInd) += L_dB;
				NS_LOG_INFO ("Cluster["<<(int)cInd<<"] is blocked by no-self blocking, "
						"the loss is ["<<L_dB<<"]"<<" dB");

			}
		}
	}
	return powerAttenuation;
}
}
