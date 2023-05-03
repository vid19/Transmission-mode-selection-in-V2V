

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

#include "lte-test-pf-ff-mac-scheduler.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LenaTestPfFfMacScheduler");

LenaTestPfFfMacSchedulerSuite::LenaTestPfFfMacSchedulerSuite ()
  : TestSuite ("lte-pf-ff-mac-scheduler", SYSTEM)
{
  NS_LOG_INFO ("creating LenaTestPfFfMacSchedulerSuite");

  bool errorModel = false;



  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (1,0,2196000,2292000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (3,0,732000,749000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (6,0,366000,373000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (12,0,183000,184670,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (15,0,146400,147730,errorModel), TestCase::EXTENSIVE);
  
 
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (1,4800,1383000,807000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (3,4800,461000,253000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (6,4800,230500,125000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (12,4800,115250,62000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (15,4800,92200,49600,errorModel), TestCase::EXTENSIVE);
  

  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (1,6000,1191000,621000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (3,6000,397000,201000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (6,6000,198500,97000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (12,6000,99250,48667,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (15,6000,79400,38993,errorModel), TestCase::EXTENSIVE);


  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (1,10000,775000,437000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (3,10000,258333,137000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (6,10000,129167,67000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (12,10000,64583,32667,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (15,10000,51667,26133,errorModel), TestCase::EXTENSIVE);

  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (1,20000,421000,137000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (3,20000,140333,41000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (6,20000,70167,22000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (12,20000,35083,12000,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaPfFfMacSchedulerTestCase1 (15,20000,28067,9600,errorModel), TestCase::EXTENSIVE);


  // Test Case 2: fairness check

  std::vector<uint16_t> dist;
  dist.push_back (0);    // User 0 distance --> MCS 28
  dist.push_back (4800);    // User 1 distance --> MCS 22
  dist.push_back (6000);    // User 2 distance --> MCS 16
  dist.push_back (10000);    // User 3 distance --> MCS 8
  dist.push_back (20000);    // User 4 distance --> MCS 8
  std::vector<uint32_t> estThrPfDl;
  estThrPfDl.push_back (90000); // User 0 estimated TTI throughput from PF
  estThrPfDl.push_back (37000); // User 1 estimated TTI throughput from PF
  estThrPfDl.push_back (37000); // User 2 estimated TTI throughput from PF
  estThrPfDl.push_back (17400); // User 3 estimated TTI throughput from PF
  estThrPfDl.push_back (17400); // User 4 estimated TTI throughput from PF
  std::vector<uint32_t> estThrPfUl;
  estThrPfUl.push_back (469000); // User 0 estimated TTI throughput from PF
  estThrPfUl.push_back (157000); // User 1 estimated TTI throughput from PF
  estThrPfUl.push_back (125000); // User 2 estimated TTI throughput from PF
  estThrPfUl.push_back (85000); // User 3 estimated TTI throughput from PF
  estThrPfUl.push_back (26000); // User 4 estimated TTI throughput from PF
  AddTestCase (new LenaPfFfMacSchedulerTestCase2 (dist, estThrPfDl, estThrPfUl,errorModel), TestCase::QUICK);


}

static LenaTestPfFfMacSchedulerSuite lenaTestPfFfMacSchedulerSuite;


// --------------- T E S T - C A S E   # 1 ------------------------------


std::string 
LenaPfFfMacSchedulerTestCase1::BuildNameString (uint16_t nUser, uint16_t dist)
{
  std::ostringstream oss;
  oss << nUser << " UEs, distance " << dist << " m";
  return oss.str ();
}

LenaPfFfMacSchedulerTestCase1::LenaPfFfMacSchedulerTestCase1 (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, bool errorModelEnabled)
  : TestCase (BuildNameString (nUser, dist)),
    m_nUser (nUser),
    m_dist (dist),
    m_thrRefDl (thrRefDl),
    m_thrRefUl (thrRefUl),
    m_errorModelEnabled (errorModelEnabled)
{
}

LenaPfFfMacSchedulerTestCase1::~LenaPfFfMacSchedulerTestCase1 ()
{
}

void
LenaPfFfMacSchedulerTestCase1::DoRun (void)
{
  NS_LOG_FUNCTION (this << m_nUser << m_dist);

  if (!m_errorModelEnabled)
    {
      Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
      Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
    }
  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));

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
  lteHelper->SetSchedulerType ("ns3::PfFfMacScheduler");
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
   * Check that the downlink assignation is done in a "proportional fair" manner
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
  * Check that the assignation is done in a "proportional fair" manner among users
  * with equal SINRs: the bandwidht should be distributed according to the 
  * ratio of the estimated throughput per TTI of each user; therefore equally 
  * partitioning the whole bandwidth achievable from a single users in a TTI
  */
  for (int i = 0; i < m_nUser; i++)
    {
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)dlDataRxed.at (i) / statsDuration, m_thrRefDl, m_thrRefDl * tolerance, " Unfair Throughput!");
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



// --------------- T E S T - C A S E   # 2 ------------------------------


std::string 
LenaPfFfMacSchedulerTestCase2::BuildNameString (uint16_t nUser, std::vector<uint16_t> dist)
{
  std::ostringstream oss;
  oss << "distances (m) = [ " ;
  for (std::vector<uint16_t>::iterator it = dist.begin (); it != dist.end (); ++it)
    {
      oss << *it << " ";
    }
  oss << "]";
  return oss.str ();
}


LenaPfFfMacSchedulerTestCase2::LenaPfFfMacSchedulerTestCase2 (std::vector<uint16_t> dist, std::vector<uint32_t> estThrPfDl, std::vector<uint32_t> estThrPfUl, bool errorModelEnabled)
  : TestCase (BuildNameString (dist.size (), dist)),
    m_nUser (dist.size ()),
    m_dist (dist),
    m_estThrPfDl (estThrPfDl),
    m_estThrPfUl (estThrPfUl),
    m_errorModelEnabled (errorModelEnabled)
{
}

LenaPfFfMacSchedulerTestCase2::~LenaPfFfMacSchedulerTestCase2 ()
{
}

void
LenaPfFfMacSchedulerTestCase2::DoRun (void)
{
  NS_LOG_FUNCTION (this);
  if (!m_errorModelEnabled)
    {
      Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
      Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
    }
  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (false));

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
  lteHelper->SetSchedulerType ("ns3::PfFfMacScheduler");
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
      mm->SetPosition (Vector (m_dist.at (i), 0.0, 0.0));
      Ptr<LteUeNetDevice> lteUeDev = ueDevs.Get (i)->GetObject<LteUeNetDevice> ();
      Ptr<LteUePhy> uePhy = lteUeDev->GetPhy ();
      uePhy->SetAttribute ("TxPower", DoubleValue (23.0));
      uePhy->SetAttribute ("NoiseFigure", DoubleValue (9.0));
    }

  double statsStartTime = 0.300; // need to allow for RRC connection establishment + SRS
  double statsDuration = 0.4;
  double tolerance = 0.1;
  Simulator::Stop (Seconds (statsStartTime + statsDuration - 0.000001));

  lteHelper->EnableRlcTraces ();
  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("StartTime", TimeValue (Seconds (statsStartTime)));
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (statsDuration)));


  Simulator::Run ();

  NS_LOG_INFO ("DL - Test with " << m_nUser << " user(s)");
  std::vector <uint64_t> dlDataRxed;
  double totalData = 0;
  double totalEstThrPf = 0;
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      // get the lcId
      uint8_t lcId = 3;
      dlDataRxed.push_back (rlcStats->GetDlRxData (imsi, lcId));
      totalData += (double)dlDataRxed.at (i);
      NS_LOG_INFO ("\tUser " << i << " dist " << m_dist.at (i) << " imsi " << imsi << " bytes rxed " << (double)dlDataRxed.at (i) << "  thr " << (double)dlDataRxed.at (i) / statsDuration);
      totalEstThrPf += m_estThrPfDl.at (i);
    }

  /**
  * Check that the assignation is done in a "proportional fair" manner among users
  * with different SINRs: the bandwidht should be distributed according to the 
  * ratio of the estimated throughput per TTI of each user.
  */
  for (int i = 0; i < m_nUser; i++)
    {
      double thrRatio = (double)dlDataRxed.at (i) / totalData;
      double estThrRatio = (double)m_estThrPfDl.at (i) / totalEstThrPf;
      NS_LOG_INFO ("\tUser " << i << " thrRatio " << thrRatio << " estThrRatio " << estThrRatio);
      NS_TEST_ASSERT_MSG_EQ_TOL (estThrRatio, thrRatio, tolerance, " Unfair Throughput!");
    }

  /**
  * Check that the assignation in uplink is done in a round robin manner.
  */

  NS_LOG_INFO ("UL - Test with " << m_nUser);
  std::vector <uint64_t> ulDataRxed;
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      // get the lcId
      uint8_t lcId = 3;
      ulDataRxed.push_back (rlcStats->GetUlRxData (imsi, lcId));
      NS_LOG_INFO ("\tUser " << i << " dist " << m_dist.at (i) << " bytes rxed " << (double)ulDataRxed.at (i) << "  thr " << (double)ulDataRxed.at (i) / statsDuration << " ref " << (double)m_estThrPfUl.at (i));
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)ulDataRxed.at (i) / statsDuration, (double)m_estThrPfUl.at (i), (double)m_estThrPfUl.at (i) * tolerance, " Unfair Throughput!");
    }
  Simulator::Destroy ();

}
