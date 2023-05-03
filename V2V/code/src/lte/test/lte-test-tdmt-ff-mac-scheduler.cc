

#include <iostream>
#include <sstream>
#include <string>

#include <ns3/object.h>
#include <ns3/spectrum-interference.h>
#include <ns3/spectrum-error-model.h>
#include <ns3/log.h>
#include <ns3/test.h>
#include <ns3/simulator.h>
#include <ns3/packet.h>
#include <ns3/ptr.h>
#include "ns3/radio-bearer-stats-calculator.h"
#include <ns3/constant-position-mobility-model.h>
#include "lte-test-tdmt-ff-mac-scheduler.h"
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


#include "lte-test-tdmt-ff-mac-scheduler.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LenaTestTdMtFfMacScheduler");

LenaTestTdMtFfMacSchedulerSuite::LenaTestTdMtFfMacSchedulerSuite ()
  : TestSuite ("lte-tdmt-ff-mac-scheduler", SYSTEM)
{
  NS_LOG_INFO ("creating LenaTestTdMtFfMacSchedulerSuite");

  bool errorModel = false;

 
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (1,0,2196000,2292000, errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (3,0,2196000,749000,errorModel), TestCase::QUICK);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (6,0,2196000,373000, errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (12,0,2196000,184670, errorModel), TestCase::EXTENSIVE);
 
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (1,4800,1383000,807000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (3,4800,1383000,253000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (6,4800,1383000,125000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (12,4800,1383000,62000,errorModel), TestCase::EXTENSIVE);

  
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (1,6000,1191000,621000, errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (3,6000,1191000,201000, errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (6,6000,1191000,97000, errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (12,6000,1191000,48667, errorModel), TestCase::EXTENSIVE);

  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (1,10000,775000,437000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (3,10000,775000,137000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (6,10000,775000,67000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (12,10000,775000,32667,errorModel), TestCase::EXTENSIVE);
 

  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (1,20000,421000,137000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (3,20000,421000,41000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (6,20000,421000,22000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaTdMtFfMacSchedulerTestCase (12,20000,421000,12000,errorModel), TestCase::EXTENSIVE);

}

static LenaTestTdMtFfMacSchedulerSuite lenaTestTdMtFfMacSchedulerSuite;


// --------------- T E S T - C A S E ------------------------------

std::string 
LenaTdMtFfMacSchedulerTestCase::BuildNameString (uint16_t nUser, uint16_t dist)
{
  std::ostringstream oss;
  oss << nUser << " UEs, distance " << dist << " m";
  return oss.str ();
}

LenaTdMtFfMacSchedulerTestCase::LenaTdMtFfMacSchedulerTestCase (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, bool errorModelEnabled)
  : TestCase (BuildNameString (nUser, dist)),
    m_nUser (nUser),
    m_dist (dist),
    m_thrRefDl (thrRefDl),
    m_thrRefUl (thrRefUl),
    m_errorModelEnabled (errorModelEnabled)
{
}

LenaTdMtFfMacSchedulerTestCase::~LenaTdMtFfMacSchedulerTestCase ()
{
}


void
LenaTdMtFfMacSchedulerTestCase::DoRun (void)
{

  NS_LOG_FUNCTION (this << m_nUser << m_dist);

  if (!m_errorModelEnabled)
    {
      Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
      Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
    }

  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));

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
  lteHelper->SetSchedulerType ("ns3::TdMtFfMacScheduler");
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
  double statsDuration = 0.6;
  double tolerance = 0.1;
  Simulator::Stop (Seconds (statsStartTime + statsDuration - 0.000001));

  lteHelper->EnableMacTraces ();
  lteHelper->EnableRlcTraces ();
  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("StartTime", TimeValue (Seconds (statsStartTime)));
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (statsDuration)));


  Simulator::Run ();

  /**
   * Check that the downlink assignation is done in a "time domain maximum throughput" manner
   */
  NS_LOG_INFO ("DL - Test with " << m_nUser << " user(s) at distance " << m_dist);
  std::vector <uint64_t> dlDataRxed;
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      uint8_t lcId = 3;
      dlDataRxed.push_back (rlcStats->GetDlRxData (imsi, lcId));
      NS_LOG_INFO ("\tUser " << i << " imsi " << imsi << " bytes rxed " << (double)dlDataRxed.at (i) << "  thr " << (double)dlDataRxed.at (i) / statsDuration << " ref " << m_thrRefDl);
    }

  /**
  * Check that the assignation is done in a "time domain maximum throughput" manner among users
  * with maximum SINRs: without fading, current FD MT always assign all resources to one UE
  */

  uint8_t found = 0;
  for (int i = 0; i < m_nUser; i++)
    {
      double throughput = (double)dlDataRxed.at (i) / statsDuration;
      if (throughput != 0 && found == 0)
        {
          NS_TEST_ASSERT_MSG_EQ_TOL (throughput, m_thrRefDl, m_thrRefDl * tolerance, " Unfair Throughput!");
          found = 1;
        }
      else if (throughput != 0 && found == 1)
        {
           NS_TEST_ASSERT_MSG_EQ_TOL (0, m_thrRefDl, m_thrRefDl * tolerance, " Unfair Throughput!");
        }
      else
        NS_TEST_ASSERT_MSG_EQ_TOL (throughput, 0, 0, " Unfair Throughput!");
    }

  /**
  * Check that the uplink assignation is done in a "proportional fair" manner
  */
  NS_LOG_INFO ("UL - Test with " << m_nUser << " user(s) at distance " << m_dist);
  std::vector <uint64_t> ulDataRxed;
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      // get the lcId
      uint8_t lcId = 3;
      ulDataRxed.push_back (rlcStats->GetUlRxData (imsi, lcId));
      NS_LOG_INFO ("\tUser " << i << " imsi " << imsi << " bytes rxed " << (double)ulDataRxed.at (i) << "  thr " << (double)ulDataRxed.at (i) / statsDuration << " ref " << m_thrRefUl);
    }
  /**
  * Check that the assignation is done in a "proportional fair" manner among users
  * with equal SINRs: the bandwidht should be distributed according to the 
  * ratio of the estimated throughput per TTI of each user; therefore equally 
  * partitioning the whole bandwidth achievable from a single users in a TTI
  */
  for (int i = 0; i < m_nUser; i++)
    {
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)ulDataRxed.at (i) / statsDuration, m_thrRefUl, m_thrRefUl * tolerance, " Unfair Throughput!");
    }
  Simulator::Destroy ();

}

