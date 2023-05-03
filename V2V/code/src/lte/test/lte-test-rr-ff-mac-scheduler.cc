

#include <ns3/object.h>
#include <ns3/spectrum-interference.h>
#include <ns3/spectrum-error-model.h>
#include <ns3/log.h>
#include <ns3/test.h>
#include <ns3/simulator.h>
#include <ns3/packet.h>
#include <ns3/ptr.h>
#include <iostream>
#include "ns3/radio-bearer-stats-calculator.h"
#include <ns3/constant-position-mobility-model.h>
#include <ns3/eps-bearer.h>
#include <ns3/node-container.h>
#include <ns3/mobility-helper.h>
#include <ns3/net-device-container.h>
#include <ns3/lte-ue-net-device.h>
#include <ns3/lte-enb-net-device.h>
#include <ns3/lte-ue-rrc.h>
#include <ns3/lte-helper.h>
#include "ns3/string.h"
#include "ns3/double.h"
#include <ns3/lte-enb-phy.h>
#include <ns3/lte-ue-phy.h>
#include <ns3/boolean.h>
#include <ns3/enum.h>
#include <ns3/config-store-module.h>

#include "lte-test-rr-ff-mac-scheduler.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LenaTestRrFfMacScheduler");

LenaTestRrFfMacSchedulerSuite::LenaTestRrFfMacSchedulerSuite ()
  : TestSuite ("lte-rr-ff-mac-scheduler", SYSTEM)
{
  NS_LOG_INFO ("creating LenaRrFfMacSchedulerTestCase");

  bool errorModel = true;

  AddTestCase (new LenaRrFfMacSchedulerTestCase (1,0,2196000,2292000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (3,0,749000,749000,errorModel), TestCase::QUICK);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (6,0,373000,373000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (9,0,185000,246220,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (12,0,185000,184670,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (15,0,148000,147730,errorModel), TestCase::EXTENSIVE);

  AddTestCase (new LenaRrFfMacSchedulerTestCase (1,4800,1383000,807000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (3,4800,469000,253000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (6,4800,233000,125000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (9,4800,113000,82667,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (12,4800,113000,62000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (15,4800,90400,49600,errorModel), TestCase::EXTENSIVE);


  AddTestCase (new LenaRrFfMacSchedulerTestCase (1,6000,1191000,621000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (3,6000,389000,201000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (6,6000,193000,97000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (9,6000,97000,64889,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (12,6000,97000,48667,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (15,6000,77600,38993,errorModel), TestCase::EXTENSIVE);


  AddTestCase (new LenaRrFfMacSchedulerTestCase (1,20000,421000,137000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (3,20000,137000,41000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (6,20000,67000,22000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (9,20000,32000,16000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (12,20000,32000,12000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaRrFfMacSchedulerTestCase (15,20000,25600,9600,errorModel), TestCase::EXTENSIVE);

}

static LenaTestRrFfMacSchedulerSuite lenaTestRrFfMacSchedulerSuite;

std::string 
LenaRrFfMacSchedulerTestCase::BuildNameString (uint16_t nUser, uint16_t dist)
{
  std::ostringstream oss;
  oss << nUser << " UEs, distance " << dist << " m";
  return oss.str ();
}

LenaRrFfMacSchedulerTestCase::LenaRrFfMacSchedulerTestCase (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, bool errorModelEnabled)
  : TestCase (BuildNameString (nUser, dist)),              
    m_nUser (nUser),
    m_dist (dist),
    m_thrRefDl (thrRefDl),
    m_thrRefUl (thrRefUl),
    m_errorModelEnabled (errorModelEnabled)
{
}

LenaRrFfMacSchedulerTestCase::~LenaRrFfMacSchedulerTestCase ()
{
}

void
LenaRrFfMacSchedulerTestCase::DoRun (void)
{
  NS_LOG_FUNCTION (this << m_nUser << m_dist);
  if (!m_errorModelEnabled)
    {
      Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
      Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
    }
  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (false));

  // This is needed as the RR scheduler does not allocate resources properly for retransmission
  Config::SetDefault ("ns3::LteRlcAm::TxOpportunityForRetxAlwaysBigEnough", BooleanValue (true));

  //Disable Uplink Power Control
  Config::SetDefault ("ns3::LteUePhy::EnableUplinkPowerControl", BooleanValue (false));

  /**
   * Initialize Simulation Scenario: 1 eNB and m_nUser UEs
   */

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  
  lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::FriisSpectrumPropagationLossModel"));

  // Create Nodes: eNodeB and UE
  NodeContainer enbNodes;
  NodeContainer ueNodes;
  enbNodes.Create (1);
  ueNodes.Create (m_nUser);

  // Install Mobility Model
  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (enbNodes);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (ueNodes);

  // Create Devices and install them in the Nodes (eNB and UE)
  NetDeviceContainer enbDevs;
  NetDeviceContainer ueDevs;
  lteHelper->SetSchedulerType ("ns3::RrFfMacScheduler");
  enbDevs = lteHelper->InstallEnbDevice (enbNodes);
  ueDevs = lteHelper->InstallUeDevice (ueNodes);

  // Attach a UE to a eNB
  lteHelper->Attach (ueDevs, enbDevs.Get (0));

  // Activate an EPS bearer
  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  lteHelper->ActivateDataRadioBearer (ueDevs, bearer);
  
 
  Ptr<LteEnbNetDevice> lteEnbDev = enbDevs.Get (0)->GetObject<LteEnbNetDevice> ();
  Ptr<LteEnbPhy> enbPhy = lteEnbDev->GetPhy ();
  enbPhy->SetAttribute ("TxPower", DoubleValue (30.0));
  enbPhy->SetAttribute ("NoiseFigure", DoubleValue (5.0));

  // Set UEs' position and power
  for (int i = 0; i < m_nUser; i++)
    {
      Ptr<ConstantPositionMobilityModel> mm = ueNodes.Get (i)->GetObject<ConstantPositionMobilityModel> ();
      mm->SetPosition (Vector (m_dist, 0.0, 0.0));
      Ptr<LteUeNetDevice> lteUeDev = ueDevs.Get (i)->GetObject<LteUeNetDevice> ();
      Ptr<LteUePhy> uePhy = lteUeDev->GetPhy ();
      uePhy->SetAttribute ("TxPower", DoubleValue (23.0));
      uePhy->SetAttribute ("NoiseFigure", DoubleValue (9.0));
    }


  double statsStartTime = 0.300; // need to allow for RRC connection establishment + SRS
  double statsDuration = 0.4;
  double tolerance = 0.1;
  Simulator::Stop (Seconds (statsStartTime + statsDuration - 0.0001));

  lteHelper->EnableRlcTraces ();
  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("StartTime", TimeValue (Seconds (statsStartTime)));
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (statsDuration)));

  Simulator::Run ();

  /**
   * Check that the assignation is done in a RR fashion
   */
  NS_LOG_INFO ("DL - Test with " << m_nUser << " user(s) at distance " << m_dist);
  std::vector <uint64_t> dlDataRxed;
  if (m_errorModelEnabled)
    {
      m_thrRefDl *= 0.95; // for couting the Vienna AMC behavior: BLER between 0% and 10%
    }
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      uint8_t lcId = 3;
      dlDataRxed.push_back (rlcStats->GetDlRxData (imsi, lcId));
      NS_LOG_INFO ("\tUser " << i << " imsi " << imsi << " lcid " << (uint16_t) lcId << " bytes rxed " << (double)dlDataRxed.at (i) << "  thr " << (double)dlDataRxed.at (i) / statsDuration << " ref " << m_thrRefDl);
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)dlDataRxed.at (i) / statsDuration, m_thrRefDl, m_thrRefDl * tolerance, " Unfair Throughput!");
    }

  NS_LOG_INFO ("UL - Test with " << m_nUser << " user(s) at distance " << m_dist);
  std::vector <uint64_t> ulDataRxed;
  if (m_errorModelEnabled)
    {
      m_thrRefUl *= 0.95; // for couting the Vienna AMC behavior: BLER between 0% and 10%
    }
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      // get the lcId
      uint8_t lcId = 3;
      ulDataRxed.push_back (rlcStats->GetUlRxData (imsi, lcId));
      NS_LOG_INFO ("\tUser " << i << " imsi " << imsi << " lcid " << (uint16_t) lcId << " bytes rxed " << (double)ulDataRxed.at (i) << "  thr " << (double)ulDataRxed.at (i) / statsDuration << " ref " << m_thrRefUl << " txed " << rlcStats->GetUlTxData (imsi, lcId) / statsDuration);
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)ulDataRxed.at (i) / statsDuration, m_thrRefUl, m_thrRefUl * tolerance, " Unfair Throughput!");
    }

  Simulator::Destroy ();
}
