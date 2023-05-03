#ifndef LTE_CHANNEL_H_
#define LTE_CHANNEL_H_
#include <ns3/spectrum-value.h>
#include <complex>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/mobility-model.h>
#include <ns3/spectrum-propagation-loss-model.h>
#include <ns3/net-device.h>
#include <map>
#include <ns3/angles.h>
#include <ns3/net-device-container.h>
#include <ns3/random-variable-stream.h>
#include "lte-propagation-loss-model.h"
#include "lte-buildings-propagation-loss-model.h"
#define AOA_INDEX 0
#define ZOA_INDEX 1
#define AOD_INDEX 2
#define ZOD_INDEX 3
#define PHI_INDEX 0
#define X_INDEX 1
#define THETA_INDEX 2
#define Y_INDEX 3
#define R_INDEX 4
namespace ns3{
typedef std::vector<double> doubleVector_t;
typedef std::vector<doubleVector_t> double2DVector_t;
typedef std::vector< std::complex<double> > complexVector_t;
typedef std::vector<complexVector_t> complex2DVector_t;
typedef std::vector<complex2DVector_t> complex3DVector_t;
typedef std::pair<Ptr<NetDevice>, Ptr<NetDevice> > key_t;
struct Params3gpp : public SimpleRefCount<Params3gpp>
{
	complexVector_t 		m_txW; 
	complexVector_t 		m_rxW; 
	complex3DVector_t  		m_channel;
	doubleVector_t  		m_delay; 
	double2DVector_t		m_angle; 
	complexVector_t 		m_longTerm;
	double2DVector_t		m_nonSelfBlocking; 
	Vector m_preLocUT; 
	Vector m_locUT; 
	double2DVector_t m_norRvAngles;
	Time m_generatedTime;
	double m_DS; 
	double m_K; 
	uint8_t m_numCluster; 
	double2DVector_t m_clusterPhase;
	double m_losPhase;
	bool m_los;
	bool m_o2i;
	Vector m_speed;
	double m_dis2D;
	double m_dis3D;
};
struct ParamsTable: public Object
{
	uint8_t m_numOfCluster = 0;
	uint8_t m_raysPerCluster = 0;
	double m_uLgDS = 0;
	double m_sigLgDS = 0;
	double m_uLgASD = 0;
	double m_sigLgASD = 0;
	double m_uLgASA = 0;
	double m_sigLgASA = 0;
	double m_uLgZSA = 0;
	double m_sigLgZSA = 0;
	double m_uLgZSD = 0;
	double m_sigLgZSD = 0;
	double m_offsetZOD = 0;
	double m_cDS = 0;
	double m_cASD = 0;
	double m_cASA = 0;
	double m_cZSA = 0;
	double m_uK = 0;
	double m_sigK = 0;
	double m_rTau = 0;
	double m_shadowingStd = 0;

	double m_sqrtC[7][7];

	ParamsTable(){}
	void SetParams(uint8_t numOfCluster, uint8_t raysPerCluster, double uLgDS, double sigLgDS,
			double uLgASD, double sigLgASD, double uLgASA, double sigLgASA,
			double uLgZSA, double sigLgZSA, double uLgZSD, double sigLgZSD, double offsetZOD,
			double cDS, double cASD, double cASA, double cZSA,
			double uK, double sigK, double rTau, double shadowingStd)
	{
		m_numOfCluster = numOfCluster;
		m_raysPerCluster = raysPerCluster;
		m_uLgDS = uLgDS;
		m_sigLgDS = sigLgDS;
		m_uLgASD = uLgASD;
		m_sigLgASD = sigLgASD;
		m_uLgASA = uLgASA;
		m_sigLgASA = sigLgASA;
		m_uLgZSA = uLgZSA;
		m_sigLgZSA = sigLgZSA;
		m_uLgZSD = uLgZSD;
		m_sigLgZSD = sigLgZSD;
		m_offsetZOD = offsetZOD;
		m_cDS = cDS;
		m_cASD = cASD;
		m_cASA = cASA;
		m_cZSA = cZSA;
		m_uK = uK;
		m_sigK = sigK;
		m_rTau = rTau;
		m_shadowingStd = shadowingStd;
	}

};
class LteChannel : public SpectrumPropagationLossModel
{
public:
LteChannel ();
	virtual ~LteChannel ();
	static TypeId GetTypeId (void);
	void DoDispose ();
	void ConnectDevices (Ptr<NetDevice> dev1, Ptr<NetDevice> dev2);

	void Initial(NetDeviceContainer ueDevices, NetDeviceContainer enbDevices);
	void SetBeamformingVector (Ptr<NetDevice> ueDevice, Ptr<NetDevice> enbDevice);
	void SetPathlossModel (Ptr<PropagationLossModel> pathloss);

private:
	void LongTermCovMatrixBeamforming (Ptr<Params3gpp> params) const;
	void CalLongTerm (Ptr<Params3gpp> params) const;

	Ptr<SpectrumValue> CalBeamformingGain (Ptr<const SpectrumValue> txPsd,
												Ptr<Params3gpp> params, Vector speed) const;
	
	double GetSystemBandwidth () const;

	Ptr<ParamsTable> GetSliceTable (bool los, bool o2i,
										double hBS, double hUT, double distance2D) const;

	
	void DeleteChannel(Ptr<const MobilityModel> a,
			Ptr<const MobilityModel> b) const;
	
	doubleVector_t CalAttenuationOfBlockage(Ptr<Params3gpp> params,
			doubleVector_t clusterAOA, doubleVector_t clusterZOA) const;

	mutable std::map< key_t, int > m_connectedPair;
	mutable std::map< key_t, Ptr<Params3gpp> > m_channelMap;

	Ptr<UniformRandomVariable> m_uniformRv;
	Ptr<UniformRandomVariable> m_uniformRvBlockage;

	Ptr<NormalRandomVariable> m_normalRv; 
	Ptr<NormalRandomVariable> m_normalRvBlockage;
	Ptr<ExponentialRandomVariable> m_expRv;
	Ptr<PropagationLossModel> m_3gppPathloss;
	Ptr<ParamsTable> m_table3gpp;
	Time m_updatePeriod;
	bool m_cellScan;
	bool m_blockage;
	uint16_t m_numNonSelfBloking; 
	bool m_portraitMode;
	std::string m_scenario;
	double m_blockerSpeed;
};
}
#endif 
