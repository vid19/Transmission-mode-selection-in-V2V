

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

#include "ns3/point-to-point-epc-helper.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"

#include "lte-test-cqa-ff-mac-scheduler.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("LenaTestCqaFfMacScheduler");

LenaTestCqaFfMacSchedulerSuite::LenaTestCqaFfMacSchedulerSuite ()
  : TestSuite ("lte-cqa-ff-mac-scheduler", SYSTEM)
{
  NS_LOG_INFO ("creating LenaTestCqaFfMacSchedulerSuite");

  bool errorModel = false;

  
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (1,0,232000,232000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (3,0,232000,232000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (6,0,232000,232000,200,1,errorModel), TestCase::EXTENSIVE);

  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (1,4800,232000,232000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (3,4800,232000,232000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (6,4800,230500,125000,200,1,errorModel), TestCase::EXTENSIVE);
 
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (1,6000,232000,232000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (3,6000,232000,201000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (6,6000,198500,97000,200,1,errorModel), TestCase::EXTENSIVE);

  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (1,10000,232000,232000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (3,10000,232000,137000,200,1,errorModel), TestCase::EXTENSIVE);
  AddTestCase (new LenaCqaFfMacSchedulerTestCase1 (6,10000,129166,67000,200,1,errorModel), TestCase::EXTENSIVE);
  
  std::vector<uint16_t> dist1;
  dist1.push_back (0);       // User 0 distance --> MCS 28
  dist1.push_back (4800);    // User 1 distance --> MCS 22
  dist1.push_back (6000);    // User 2 distance --> MCS 20
  dist1.push_back (10000);   // User 3 distance --> MCS 14
  std::vector<uint16_t> packetSize1;
  packetSize1.push_back (100);
  packetSize1.push_back (100);
  packetSize1.push_back (100);
  packetSize1.push_back (100);
  std::vector<uint32_t> estThrCqaDl1;
  estThrCqaDl1.push_back (132000); // User 0 estimated TTI throughput from CQA
  estThrCqaDl1.push_back (132000); // User 1 estimated TTI throughput from CQA
  estThrCqaDl1.push_back (132000); // User 2 estimated TTI throughput from CQA
  estThrCqaDl1.push_back (132000); // User 3 estimated TTI throughput from CQA
  AddTestCase (new LenaCqaFfMacSchedulerTestCase2 (dist1,estThrCqaDl1,packetSize1,1,errorModel), TestCase::QUICK);

 
  std::vector<uint16_t> dist2;
  dist2.push_back (0);       // User 0 distance --> MCS 28
  dist2.push_back (4800);    // User 1 distance --> MCS 22
  dist2.push_back (6000);    // User 2 distance --> MCS 20
  dist2.push_back (10000);   // User 3 distance --> MCS 14
  std::vector<uint16_t> packetSize2;
  packetSize2.push_back (200);
  packetSize2.push_back (200);
  packetSize2.push_back (200);
  packetSize2.push_back (200);
  std::vector<uint32_t> estThrCqaDl2;
  estThrCqaDl2.push_back (230000); // User 0 estimated TTI throughput from CQA
  estThrCqaDl2.push_back (230000); // User 1 estimated TTI throughput from CQA
  estThrCqaDl2.push_back (230000); // User 2 estimated TTI throughput from CQA
  estThrCqaDl2.push_back (230000); // User 3 estimated TTI throughput from CQA
  AddTestCase (new LenaCqaFfMacSchedulerTestCase2 (dist2,estThrCqaDl2,packetSize2,1,errorModel), TestCase::QUICK);


  std::vector<uint16_t> dist3;
  dist3.push_back (0);    // User 0 distance --> MCS 28
  dist3.push_back (4800);    // User 1 distance --> MCS 22
  dist3.push_back (6000);    // User 2 distance --> MCS 20
  std::vector<uint16_t> packetSize3;
  packetSize3.push_back (100);
  packetSize3.push_back (200);
  packetSize3.push_back (300);
  std::vector<uint32_t> estThrCqaDl3;
  estThrCqaDl3.push_back (132000); // User 0 estimated TTI throughput from CQA
  estThrCqaDl3.push_back (232000); // User 1 estimated TTI throughput from CQA
  estThrCqaDl3.push_back (332000); // User 2 estimated TTI throughput from CQA
  AddTestCase (new LenaCqaFfMacSchedulerTestCase2 (dist3,estThrCqaDl3,packetSize3,1,errorModel), TestCase::QUICK);

}

static LenaTestCqaFfMacSchedulerSuite lenaTestCqaFfMacSchedulerSuite;

// --------------- T E S T - C A S E   # 1 ------------------------------


std::string 
LenaCqaFfMacSchedulerTestCase1::BuildNameString (uint16_t nUser, uint16_t dist)
{
  std::ostringstream oss;
  oss << nUser << " UEs, distance " << dist << " m";
  return oss.str ();
}


LenaCqaFfMacSchedulerTestCase1::LenaCqaFfMacSchedulerTestCase1 (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, uint16_t packetSize, uint16_t interval,bool errorModelEnabled)
  : TestCase (BuildNameString (nUser, dist)),
    m_nUser (nUser),
    m_dist (dist),
    m_packetSize (packetSize),
    m_interval (interval),
    m_thrRefDl (thrRefDl),
    m_thrRefUl (thrRefUl),
    m_errorModelEnabled (errorModelEnabled)
{
}

LenaCqaFfMacSchedulerTestCase1::~LenaCqaFfMacSchedulerTestCase1 ()
{
}

void
LenaCqaFfMacSchedulerTestCase1::DoRun (void)
{
  NS_LOG_FUNCTION (this << GetName ());

  if (!m_errorModelEnabled)
    {
      Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
      Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
    }

  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
  lteHelper->SetEpcHelper (epcHelper);

  //LogComponentEnable ("CqaFfMacScheduler", LOG_DEBUG);

  Ptr<Node> pgw = epcHelper->GetPgwNode ();

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
  p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.001)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);

  //Config::SetDefault ("ns3::LteAmc::AmcModel", EnumValue (LteAmc::PiroEW2010));
  //Config::SetDefault ("ns3::LteAmc::Ber", DoubleValue (0.00005));
  //Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
  //Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));

  //Config::SetDefault ("ns3::LteEnbRrc::EpsBearerToRlcMapping", EnumValue (LteHelper::RLC_UM_ALWAYS));

//   LogComponentDisableAll (LOG_LEVEL_ALL);
  //LogComponentEnable ("LenaTestCqaFfMacCheduler", LOG_LEVEL_ALL);
   
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
  lteHelper->SetSchedulerType ("ns3::CqaFfMacScheduler");
  enbDevs = lteHelper->InstallEnbDevice (enbNodes);
  ueDevs = lteHelper->InstallUeDevice (ueNodes);


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

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueDevs));

  // Assign IP address to UEs
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  // Attach a UE to a eNB
  lteHelper->Attach (ueDevs, enbDevs.Get (0));

  // Activate an EPS bearer on all UEs
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<NetDevice> ueDevice = ueDevs.Get (u);
      GbrQosInformation qos;
      qos.gbrDl = (m_packetSize + 32) * (1000 / m_interval) * 8;  // bit/s, considering IP, UDP, RLC, PDCP header size
      qos.gbrUl = (m_packetSize + 32) * (1000 / m_interval) * 8;
      qos.mbrDl = 0;
      qos.mbrUl = 0;
      
      enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
      EpsBearer bearer (q, qos);
      lteHelper->ActivateDedicatedEpsBearer (ueDevice, bearer, EpcTft::Default ());  
    }

  // Install downlind and uplink applications
  uint16_t dlPort = 1234;
  uint16_t ulPort = 2000;
  PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));
  PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), ulPort));
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      ++ulPort;
      serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get (u))); // receive packets from remotehost
      serverApps.Add (ulPacketSinkHelper.Install (remoteHost));  // receive packets from UEs

      UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort); // uplink packets generator
      dlClient.SetAttribute ("Interval", TimeValue (MilliSeconds (m_interval)));
      dlClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
      dlClient.SetAttribute ("PacketSize", UintegerValue (m_packetSize));

      UdpClientHelper ulClient (remoteHostAddr, ulPort);           // downlink packets generator
      ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds (m_interval)));
      ulClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
      ulClient.SetAttribute ("PacketSize", UintegerValue (m_packetSize));

      clientApps.Add (dlClient.Install (remoteHost));
      clientApps.Add (ulClient.Install (ueNodes.Get (u)));
    }

  serverApps.Start (Seconds (0.030));
  clientApps.Start (Seconds (0.030));

  double statsStartTime = 0.04; // need to allow for RRC connection establishment + SRS
  double statsDuration = 0.5;
  double tolerance = 0.1;
  Simulator::Stop (Seconds (statsStartTime + statsDuration - 0.0001));

  lteHelper->EnableRlcTraces ();
  lteHelper->EnableMacTraces ();
  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("StartTime", TimeValue (Seconds (statsStartTime)));
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (statsDuration)));

  Simulator::Run ();

  /**
   * Check that the downlink assignation is done in a "token bank fair queue" manner
   */

  NS_LOG_INFO ("DL - Test with " << m_nUser << " user(s) at distance " << m_dist);
  std::vector <uint64_t> dlDataRxed;
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      // get the lcId
      uint8_t lcId = 4;
      uint64_t data = rlcStats->GetDlRxData (imsi, lcId);
      dlDataRxed.push_back (data);
      NS_LOG_INFO ("\tUser " << i << " imsi " << imsi << " bytes rxed " << (double)dlDataRxed.at (i) << "  thr " << (double)dlDataRxed.at (i) / statsDuration << " ref " << m_thrRefDl);
    }

  for (int i = 0; i < m_nUser; i++)
    {
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)dlDataRxed.at (i) / statsDuration, m_thrRefDl, m_thrRefDl * tolerance, " Unfair Throughput!");
    }

  /**
  * Check that the uplink assignation is done in a "round robin" manner
  */

  NS_LOG_INFO ("UL - Test with " << m_nUser << " user(s) at distance " << m_dist);
  std::vector <uint64_t> ulDataRxed;
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      // get the lcId
      uint8_t lcId = 4;
      ulDataRxed.push_back (rlcStats->GetUlRxData (imsi, lcId));
      NS_LOG_INFO ("\tUser " << i << " imsi " << imsi << " bytes rxed " << (double)ulDataRxed.at (i) << "  thr " << (double)ulDataRxed.at (i) / statsDuration << " ref " << m_thrRefUl);
    }

  for (int i = 0; i < m_nUser; i++)
    {
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)ulDataRxed.at (i) / statsDuration, m_thrRefUl, m_thrRefUl * tolerance, " Unfair Throughput!");
    }
  Simulator::Destroy ();

}



// --------------- T E S T - C A S E   # 2 ------------------------------


std::string 
LenaCqaFfMacSchedulerTestCase2::BuildNameString (uint16_t nUser, std::vector<uint16_t> dist)
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


LenaCqaFfMacSchedulerTestCase2::LenaCqaFfMacSchedulerTestCase2 (std::vector<uint16_t> dist, std::vector<uint32_t> estThrCqaDl, std::vector<uint16_t> packetSize, uint16_t interval,bool errorModelEnabled)
  : TestCase (BuildNameString (dist.size (), dist)),
    m_nUser (dist.size ()),
    m_dist (dist),
    m_packetSize (packetSize),
    m_interval (interval),
    m_estThrCqaDl (estThrCqaDl),
    m_errorModelEnabled (errorModelEnabled)
{
}

LenaCqaFfMacSchedulerTestCase2::~LenaCqaFfMacSchedulerTestCase2 ()
{
}

void
LenaCqaFfMacSchedulerTestCase2::DoRun (void)
{

  if (!m_errorModelEnabled)
    {
      Config::SetDefault ("ns3::LteSpectrumPhy::CtrlErrorModelEnabled", BooleanValue (false));
      Config::SetDefault ("ns3::LteSpectrumPhy::DataErrorModelEnabled", BooleanValue (false));
    }

  Config::SetDefault ("ns3::LteHelper::UseIdealRrc", BooleanValue (true));


  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
  lteHelper->SetEpcHelper (epcHelper);

  Ptr<Node> pgw = epcHelper->GetPgwNode ();

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
  p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.001)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);


//   LogComponentDisableAll (LOG_LEVEL_ALL);
  //LogComponentEnable ("LenaTestCqaFfMacCheduler", LOG_LEVEL_ALL);
   
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
  lteHelper->SetSchedulerType ("ns3::CqaFfMacScheduler");
  enbDevs = lteHelper->InstallEnbDevice (enbNodes);
  ueDevs = lteHelper->InstallUeDevice (ueNodes);

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

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueDevs));

  // Assign IP address to UEs
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  // Attach a UE to a eNB
  lteHelper->Attach (ueDevs, enbDevs.Get (0));

  // Activate an EPS bearer on all UEs

  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<NetDevice> ueDevice = ueDevs.Get (u);
      GbrQosInformation qos;
      qos.gbrDl = (m_packetSize.at (u) + 32) * (1000 / m_interval) * 8;  // bit/s, considering IP, UDP, RLC, PDCP header size
      qos.gbrUl = (m_packetSize.at (u) + 32) * (1000 / m_interval) * 8;
      qos.mbrDl = qos.gbrDl;
      qos.mbrUl = qos.gbrUl;
  
      enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
      EpsBearer bearer (q, qos);
      lteHelper->ActivateDedicatedEpsBearer (ueDevice, bearer, EpcTft::Default ());  
    }


  // Install downlind and uplink applications
  uint16_t dlPort = 1234;
  uint16_t ulPort = 2000;
  PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));
  PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), ulPort));
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      ++ulPort;
      serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get (u))); // receive packets from remotehost
      serverApps.Add (ulPacketSinkHelper.Install (remoteHost));  // receive packets from UEs

      UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort); // uplink packets generator
      dlClient.SetAttribute ("Interval", TimeValue (MilliSeconds (m_interval)));
      dlClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
      dlClient.SetAttribute ("PacketSize", UintegerValue (m_packetSize.at (u)));

      UdpClientHelper ulClient (remoteHostAddr, ulPort);           // downlink packets generator
      ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds (m_interval)));
      ulClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
      ulClient.SetAttribute ("PacketSize", UintegerValue (m_packetSize.at (u)));

      clientApps.Add (dlClient.Install (remoteHost));
      clientApps.Add (ulClient.Install (ueNodes.Get (u)));
   }

  serverApps.Start (Seconds (0.030));
  clientApps.Start (Seconds (0.030));

  double statsStartTime = 0.04; // need to allow for RRC connection establishment + SRS
  double statsDuration = 0.5;
  double tolerance = 0.1;
  Simulator::Stop (Seconds (statsStartTime + statsDuration - 0.0001));

  lteHelper->EnableRlcTraces ();
  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("StartTime", TimeValue (Seconds (statsStartTime)));
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (statsDuration)));


  Simulator::Run ();

  /**
   * Check that the downlink assignation is done in a "token bank fair queue" manner
   */

  NS_LOG_INFO ("DL - Test with " << m_nUser << " user(s)");
  std::vector <uint64_t> dlDataRxed;
  for (int i = 0; i < m_nUser; i++)
    {
      // get the imsi
      uint64_t imsi = ueDevs.Get (i)->GetObject<LteUeNetDevice> ()->GetImsi ();
      // get the lcId
      uint8_t lcId = 4;
      dlDataRxed.push_back (rlcStats->GetDlRxData (imsi, lcId));
      NS_LOG_INFO ("\tUser " << i << " dist " << m_dist.at (i) << " imsi " << imsi << " bytes rxed " << (double)dlDataRxed.at (i) << "  thr " << (double)dlDataRxed.at (i) / statsDuration << " ref " << m_estThrCqaDl.at (i));
    }

  for (int i = 0; i < m_nUser; i++)
    {
      NS_TEST_ASSERT_MSG_EQ_TOL ((double)dlDataRxed.at (i) / statsDuration, m_estThrCqaDl.at (i), m_estThrCqaDl.at (i) * tolerance, " Unfair Throughput!");
    }

  Simulator::Destroy ();

}
