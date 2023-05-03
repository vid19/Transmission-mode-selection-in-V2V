#include "ns3/point-to-point-module.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include <ns3/spectrum-value.h>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/mobility-model.h>
#include <ns3/spectrum-propagation-loss-model.h>
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/epc-enb-s1-sap.h"
#include "ns3/epc-s1ap-sap.h"
#include "ns3/epc-sr-sap.h"
#include "ns3/a3-rsrp-handover-algorithm.h"
#include "ns3/lte-helper.h"
#include "ns3/epc-helper.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
#include <ns3/spectrum-module.h>
#include "ns3/flow-monitor-helper.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/lte-global-pathloss-database.h"
#include <ns3/core-module.h>
#include <ns3/network-module.h>
#include <ns3/internet-module.h>
#include <ns3/internet-apps-module.h>
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
#include "ns3/wifi-module.h"
#include "ns3/netanim-module.h"
#include "ns3/basic-energy-source.h"
#include "ns3/simple-device-energy-model.h"
#include "ns3/config-store-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/rtt-estimator.h"
#include "ns3/aodv-module.h"
#include "ns3/wave-net-device.h"
#include "ns3/wave-mac-helper.h"
#include "ns3/wave-helper.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace ns3;
using namespace std;
NS_LOG_COMPONENT_DEFINE ("V2V_Scenario");
double simTime = 50;
AnimationInterface *anim;
double pk=0;
double packetSize = 1024;  
double numPackets = 100;
double interval = 0.1; 
double TotalTime = 10.0;
double distance1;
std::string rate="10Mbps";
std::string rate1="20Mbps";
int rttval;
double kbs=0;
int rnd=0;
int rnd1=0;
double Trange=100;
int bandWidth=100;
double Initialenergy=1000;
double trans_recv=50; 
Time interPacketInterval = Seconds (interval);
NodeContainer eNodeBnode;
NodeContainer Vehicle_Nodes;
int bytesTotal;
double ds=100.0;
double energy=1000.0;
double Initialtime=0;
double PICO=0.000001;
double NANO =0.001;
double SNR =-25;
int dis=10;
int status=1;
int backoff=10;
int pz=50;
double q=5;
double ro=2;
double taumax=2;
int initCity=5;
uint32_t packetsReceived;
struct rgb {
uint8_t r; 
uint8_t g; 
uint8_t b;};
struct rgb colors [] = {
{ 255, 0, 0 }, 
{ 0, 255, 0 }, 
{ 0, 0, 255 }};
void GetDistance_From (NodeContainer node1, NodeContainer node2){
Ptr<MobilityModel> model1 = node1.Get(0)->GetObject<MobilityModel>();
Ptr<MobilityModel> model2 = node2.Get(10)->GetObject<MobilityModel>();
distance1 = model1->GetDistanceFrom (model2);}
void ReceivePacket (Ptr<Socket> socket){
Ptr<Packet> pckt;
while (pckt = socket->Recv ()){
rate="512Mbps";
Ptr<MobilityModel> model1 = eNodeBnode.Get(0)->GetObject<MobilityModel>();
Ptr<MobilityModel> model2 = Vehicle_Nodes.Get(10)->GetObject<MobilityModel>();
distance1 = model1->GetDistanceFrom (model2);
pk=pk+1;}}
void compare_Minimum(double dis){
if(ds>dis){
ds=dis;}}
void getNearbynode(NodeContainer nod,double x1,double y1){
int nn;
for(uint32_t i=0;i<nod.GetN ();i++){
Ptr<ConstantPositionMobilityModel> FCMob = nod.Get(i)->GetObject<ConstantPositionMobilityModel>();
Vector m_position = FCMob->GetPosition();
double x=m_position.x;
double y=m_position.y;
double xx=x1-x;
double yy=y1-y;
double x2=(xx*xx);
double y2=(yy*yy);
double sx=sqrt(x2);
double sy=sqrt(y2);
double dis=(sx+sy);
compare_Minimum(dis);
if(ds==dis){
nn=i;}}
std::cout<<"minimum Distance:" <<nn<<std::endl;}
void energyReceive(int bits,int mystatus){
double en;
if(mystatus==status){
en=(double)bits*50.0*NANO;
energy=energy-en;}}
void energyTransmit(int bits,double dist,int mystatus){
double en;
if(mystatus==status){
en=bits*10*PICO*dist+(double)bits*50.0*NANO;
energy=energy-en;}}
void energyDataAggr(int signals,int mystatus){
double en;
if(mystatus==status){
en=5*NANO*signals;
energy=energy-en;}}
void finish(){
std::cout<<"energy: "<<energy<<"\n";}
static void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize,uint32_t pktCount, Time pktInterval ){
if (pktCount > 0){
socket->Send (Create<Packet> (pktSize));
int b=pktCount*512;
energy=(double)trans_recv;
energyReceive(b,1);
energyTransmit( b,ds,1);
energyDataAggr(1*pktCount ,1);
Simulator::Schedule (pktInterval, &GenerateTraffic,socket, pktSize,pktCount-1, pktInterval);
}else{
socket->Close ();}}
void PKTtrans(NodeContainer c , NodeContainer d){
std::cout<<"\n\n Next, initially , UEs are moving at a speed between 0 and 100 kmph in random directions. These UEs are assigned to each eNodeB based on the highest CQI (Channel Quality Index) value. \n\n";
//Reduce frequency of CQI report to allow for sidelink transmissions
Config::SetDefault ("ns3::LteUePhy::DownlinkCqiPeriodicity", TimeValue (MilliSeconds (79)));
Config::SetDefault ("ns3::LteUePhy::TxPower", DoubleValue (23.0));
for (uint32_t i = 0; i < c.GetN (); ++i){
double min = 0.0;
double max = 49.0;
Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
x->SetAttribute ("Min", DoubleValue (min));
x->SetAttribute ("Max", DoubleValue (max));
int value = x->GetValue ();  
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSocket = Socket::CreateSocket (d.Get (0), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSocket->Bind (local);
recvSocket->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (c.Get (value), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}}
void PKTtrans1(NodeContainer c , NodeContainer d){
std::cout<<"\n\n Next, perform the UE nodes clustering by using K-means algorithm and select the Cluster head based on the centroid of the cluster and moving speed. \n\n";
Kmeans obj;
obj.Clustering();
for (uint32_t i = 0; i < c.GetN (); ++i){
double min = 0.0;
double max = 49.0;
Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
x->SetAttribute ("Min", DoubleValue (min));
x->SetAttribute ("Max", DoubleValue (max));
int value = x->GetValue ();  
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSocket = Socket::CreateSocket (d.Get (0), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSocket->Bind (local);
recvSocket->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (c.Get (value), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}}
void PKTtrans2(NodeContainer c , NodeContainer d){
std::cout<<"\n\n Next, perform the data transmission , during the transmission , the Cluster heads of each cluster act as D2D relay or  d2d multihop relay and the other UEs in the cluster act as D2D clients. \n\n";
double min = 0.0;
double max = 49.0;
Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
x->SetAttribute ("Min", DoubleValue (min));
x->SetAttribute ("Max", DoubleValue (max));
int value = x->GetValue (); 
uint16_t port = 50000;
Address sinkLocalAddress(InetSocketAddress(Ipv4Address::GetAny(), port));
PacketSinkHelper sinkHelper("ns3::TcpSocketFactory", sinkLocalAddress);
ApplicationContainer sinkApp = sinkHelper.Install(Vehicle_Nodes);
sinkApp.Start(Seconds(1.0));
sinkApp.Stop(Seconds(10.0));
std::cout<< "D2D relay: "<<c.Get (value)<<endl;
for (uint32_t i = 0; i < c.GetN (); ++i){
double min = 0.0;
double max = 49.0;
Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
x->SetAttribute ("Min", DoubleValue (min));
x->SetAttribute ("Max", DoubleValue (max));
int value = x->GetValue ();  
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSocket = Socket::CreateSocket (d.Get (0), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSocket->Bind (local);
recvSocket->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (c.Get (value), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}}
void PKTtrans3(NodeContainer c , NodeContainer d){
std::cout<<"\n\n Next, Calculate the UEs moving speed , if speed is less than 65 kmph can share its internet as single-hop relays. \n\n";
fstream my_file;
my_file.open("Speed.txt", ios::in);
if (!my_file) {
std::cout << "No such file";
}
else {
char ch;
while (1) {
my_file >> ch;
if (my_file.eof())
break;
}
if (ch < 65) {
std::cout << "Internet as single-hop relays";
} else {
std::cout << "Vehicle Speed is Greater than 65 kmph";
}
}
for (uint32_t i = 0; i < c.GetN (); ++i){
double min = 0.0;
double max = 49.0;
Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
x->SetAttribute ("Min", DoubleValue (min));
x->SetAttribute ("Max", DoubleValue (max));
int value = x->GetValue ();  
TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
Ptr<Socket> recvSocket = Socket::CreateSocket (d.Get (0), tid);
InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
recvSocket->Bind (local);
recvSocket->SetRecvCallback (MakeCallback (&ReceivePacket));
Ptr<Socket> source = Socket::CreateSocket (c.Get (value), tid);
InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
source->SetAllowBroadcast (true);
source->Connect (remote);
double min1 = 0.0;
double max1 = 3.0;
Ptr<UniformRandomVariable> x1 = CreateObject<UniformRandomVariable> ();
x1->SetAttribute ("Min", DoubleValue (min1));
x1->SetAttribute ("Max", DoubleValue (max1));
Simulator::ScheduleWithContext (source->GetNode ()->GetId (),Seconds (0.1), &GenerateTraffic,source, packetSize, numPackets,interPacketInterval);}std::cout<<"\n";}
class MyApp : public Application{
public:
MyApp ();
virtual ~MyApp();
void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);
private:
virtual void StartApplication (void);
virtual void StopApplication (void);
void ScheduleTx (void);
void SendPacket (void);
Ptr<Socket>     m_socket;
Address         m_peer;
uint32_t        m_packetSize;
uint32_t        m_nPackets;
DataRate        m_dataRate;
EventId         m_sendEvent;
bool            m_running;
uint32_t        m_packetsSent;
};
MyApp::MyApp ()
: m_socket (0),
m_peer (),
m_packetSize (0),
m_nPackets (0),
m_dataRate (0),
m_sendEvent (),
m_running (false),
m_packetsSent (0)
{
}
MyApp::~MyApp()
{
m_socket = 0;
}
void
MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
m_socket = socket;
m_peer = address;
m_packetSize = packetSize;
m_nPackets = nPackets;
m_dataRate = dataRate;
}
void
MyApp::StartApplication (void)
{
m_running = true;
m_packetsSent = 0;
m_socket->Bind ();
m_socket->Connect (m_peer);
SendPacket ();
}
void
MyApp::StopApplication (void)
{
m_running = false;
if (m_sendEvent.IsRunning ())
{
Simulator::Cancel (m_sendEvent);
}
if (m_socket)
{
m_socket->Close ();
}
}
void
MyApp::SendPacket (void)
{
static int send_num = 1;
Ptr<Packet> packet = Create<Packet> (m_packetSize);
m_socket->Send (packet);
NS_LOG_DEBUG ("Sending:    "<<send_num++ << "\t" << Simulator::Now ().GetSeconds ());
if (++m_packetsSent < m_nPackets)
{
ScheduleTx ();
}
}
void
MyApp::ScheduleTx (void)
{
if (m_running)
{
Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
m_sendEvent = Simulator::Schedule (tNext, &MyApp::SendPacket, this);
}
}
int
main (int argc, char *argv[]){
Config::SetDefault ("ns3::LteRlcUm::MaxTxBufferSize", UintegerValue (1024 * 1024));
//Reduce frequency of CQI report to allow for sidelink transmissions
Config::SetDefault ("ns3::LteUePhy::DownlinkCqiPeriodicity", TimeValue (MilliSeconds (79)));
Config::SetDefault ("ns3::LteUePhy::TxPower", DoubleValue (23.0));
double stopTime = 10.0;
double simStopTime = 10.00;
Ipv4Address remoteHostAddr;
CommandLine cmd;
cmd.Parse(argc, argv);
int VehicleNodes;
std::cout<<"\n\nMaximum (50 to 246) Vehicle Nodes are Allowed";
std::cout<<"\n\nEnter the Number of Vehicle Nodes: ";
cin>>VehicleNodes;
ofstream MyFile("UENodes.txt");
MyFile << VehicleNodes;
MyFile.close();
std::cout<<"\n\n=====================================================\n";
std::cout<<"V2V_Scenario";
std::cout<<"\n=====================================================\n\n";
std::cout<<"\n\n A LTE Network , its consists of "<<VehicleNodes<<" - Vehicle Nodes and 10- eNodeB. All users are connected with eNodeB.  \n\n";
Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper> ();
lteHelper->SetEpcHelper (epcHelper);
ConfigStore inputConfig;
inputConfig.ConfigureDefaults();
cmd.Parse(argc, argv);
Ptr<Node> pgw = epcHelper->GetPgwNode ();
NodeContainer remoteHostContainer;
remoteHostContainer.Create (1);
Ptr<Node> remoteHost = remoteHostContainer.Get (0);
InternetStackHelper internet;
internet.Install (remoteHostContainer);
PointToPointHelper p2ph;
p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
p2ph.SetChannelAttribute ("Delay", TimeValue (MicroSeconds (1)));
NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
Ipv4AddressHelper ipv4h;
ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
remoteHostAddr = internetIpIfaces.GetAddress (1);
Ipv4StaticRoutingHelper ipv4RoutingHelper;
Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);
eNodeBnode.Create(10);
Vehicle_Nodes.Create(VehicleNodes);
MobilityHelper enbmobility;
Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
enbPositionAlloc->Add (Vector (0.0, 0.0, 0.0));
enbmobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
enbmobility.SetPositionAllocator(enbPositionAlloc);
enbmobility.Install (eNodeBnode);
enbmobility.Install (remoteHostContainer);
AnimationInterface::SetConstantPosition (pgw, 1, 1);
YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
channel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
channel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
phy.SetChannel (channel.Create ());
std::string phyMode ("DsssRate11Mbps");
phy.Set ("TxPowerStart",DoubleValue (Trange));
phy.Set ("TxPowerEnd", DoubleValue (Trange));
Config::SetDefault ("ns3::OnOffApplication::PacketSize",StringValue ("64000"));
Config::SetDefault ("ns3::OnOffApplication::DataRate",StringValue (rate));
Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",StringValue (phyMode));
Config::SetDefault ("ns3::OnOffApplication::DataRate",StringValue (rate1));
Config::Set ("/NodeList/*/DeviceList/*/$ns3::WifiNetDevice/Phy/ChannelWidth", UintegerValue (bandWidth));
WifiHelper wifi;
wifi.SetStandard (WIFI_PHY_STANDARD_80211a);
wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager","DataMode",StringValue (phyMode),"ControlMode",StringValue (phyMode));
WifiMacHelper mac;
Ssid ssid = Ssid ("ns-3-ssid");
mac.SetType ("ns3::AdhocWifiMac");
NetDeviceContainer staDevices;
staDevices = wifi.Install (phy, mac, Vehicle_Nodes);
mac.SetType ("ns3::ApWifiMac","Ssid", SsidValue (ssid));
srand(time(0));
int random = 50 + (rand() % 51);
int nodeSpeed = random;
std::cout<<nodeSpeed;
ofstream File("Speed.txt");
File << nodeSpeed;
File.close();
MobilityHelper mobility;
int nodePause = 0; 
int64_t streamIndex = 0;
ObjectFactory pos;
pos.SetTypeId ("ns3::RandomRectanglePositionAllocator");
pos.Set ("X", StringValue ("ns3::UniformRandomVariable[Min=1|Max=1000]")); 
pos.Set ("Y", StringValue ("ns3::UniformRandomVariable[Min=1|Max=1000]"));
Ptr<PositionAllocator> taPositionAlloc = pos.Create ()->GetObject<PositionAllocator> ();
streamIndex += taPositionAlloc->AssignStreams (streamIndex);
mobility.SetPositionAllocator(taPositionAlloc);
std::stringstream ssSpeed;
ssSpeed << "ns3::UniformRandomVariable[Min=0.0|Max=" << nodeSpeed << "]";
std::stringstream ssPause;
ssPause << "ns3::ConstantRandomVariable[Constant=" << nodePause << "]";
mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel","Speed", StringValue (ssSpeed.str ()),"Pause", StringValue (ssPause.str ()),
"PositionAllocator", PointerValue (taPositionAlloc));
mobility.Install (Vehicle_Nodes);
YansWifiChannelHelper waveChannel = YansWifiChannelHelper::Default ();
YansWavePhyHelper wavePhy =  YansWavePhyHelper::Default ();
wavePhy.SetChannel (waveChannel.Create ());
wavePhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11);
QosWaveMacHelper waveMac = QosWaveMacHelper::Default ();
WaveHelper waveHelper = WaveHelper::Default ();
staDevices = waveHelper.Install (wavePhy, waveMac, Vehicle_Nodes);
AnimationInterface::SetConstantPosition (remoteHostContainer.Get (0), 1,1);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (0), 250, 250);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (1), 750, 250);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (2), 250, 750);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (3), 750, 750);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (4), 500, 250);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (5), 250, 500);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (6), 500, 500);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (7), 500, 750);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (8), 750, 500);
AnimationInterface::SetConstantPosition (eNodeBnode.Get (9), 0, 0);
macgplot mg;
Time interPacketInterval = Seconds (interval);
AodvHelper aodv;
Ipv4StaticRoutingHelper staticRouting;
Ipv4ListRoutingHelper list;
list.Add (staticRouting, 0);
list.Add (aodv, 1);
internet.SetRoutingHelper (list); 
internet.Install (Vehicle_Nodes);
Ipv4AddressHelper ipv4;
NS_LOG_INFO ("Assign IP Addresses.");
ipv4.SetBase ("20.1.1.0", "255.255.255.0");
Ipv4InterfaceContainer i = ipv4.Assign (staDevices);
NetDeviceContainer BSDevs = lteHelper->InstallEnbDevice (eNodeBnode);
NetDeviceContainer VehicleDevs = lteHelper->InstallUeDevice (Vehicle_Nodes);
Ipv4InterfaceContainer ueIpIface;
ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (VehicleDevs));
lteHelper->AttachToClosestEnb (VehicleDevs, BSDevs);
lteHelper->EnableTraces ();
for (uint32_t i = 0; i < Vehicle_Nodes.GetN (); ++i){
Ptr<Node> vehiclenode = Vehicle_Nodes.Get (i);
Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (vehiclenode->GetObject<Ipv4> ());
ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
uint16_t BSPort = 20000;
Address BSAddress (InetSocketAddress (ueIpIface.GetAddress (i), BSPort));
PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), BSPort));
ApplicationContainer sinkApps = packetSinkHelper.Install (Vehicle_Nodes.Get (i));
sinkApps.Start (Seconds (0.));
sinkApps.Stop (Seconds (simStopTime));
Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (remoteHostContainer.Get (0), TcpSocketFactory::GetTypeId ());
Ptr<MyApp> app = CreateObject<MyApp> ();
app->Setup (ns3TcpSocket, BSAddress, 1000, 500, DataRate ("30Mb/s"));
eNodeBnode.Get (0)->AddApplication (app);
app->SetStartTime (Seconds (0.1));
app->SetStopTime (Seconds (stopTime));}
Simulator::Stop (Seconds (simStopTime));
Simulator::Schedule(Seconds(0.5), &PKTtrans,Vehicle_Nodes,eNodeBnode);
Simulator::Schedule(Seconds(1.0), &PKTtrans1,Vehicle_Nodes,eNodeBnode);
Simulator::Schedule(Seconds(1.5), &PKTtrans2,Vehicle_Nodes,eNodeBnode);
Simulator::Schedule(Seconds(2.0), &PKTtrans3,Vehicle_Nodes,eNodeBnode);
mg.Energy_Consumption(VehicleNodes,"V2V_Scenario");
mg.Packet_Loss(VehicleNodes);
mg.Delay(VehicleNodes);
mg.Throughput(VehicleNodes);
anim= new AnimationInterface ("V2V_Scenario.xml");
anim->SetBackgroundImage ("/home/research/ns-allinone-3.26/netanim-3.107/img1/bg.png", -1055, -210, 4.50, 6.50, 1.0);
uint32_t eNodeBimg =anim->AddResource("/home/research/ns-allinone-3.26/netanim-3.107/img1/eNodeB.png");
uint32_t Vehicleimg =anim->AddResource("/home/research/ns-allinone-3.26/netanim-3.107/img1/Vehicle.png");
for (uint32_t i = 0; i < Vehicle_Nodes.GetN (); ++i){
Ptr<Node> wid1= Vehicle_Nodes.Get (i);
uint32_t nodeId1 = wid1->GetId ();
anim->UpdateNodeSize (nodeId1, 75.0,75.0); 
anim->UpdateNodeImage (nodeId1, Vehicleimg);
anim->UpdateNodeDescription (Vehicle_Nodes.Get (i), "Vehicle" ); 
anim->UpdateNodeColor (Vehicle_Nodes.Get (i), 255, 0, 0); }
for (uint32_t i = 0; i < eNodeBnode.GetN (); ++i){
anim->UpdateNodeDescription (eNodeBnode.Get (i), "eNodeB" ); 
anim->UpdateNodeColor (eNodeBnode.Get (i), 200, 200, 200); 
Ptr<Node> wid2= eNodeBnode.Get (i);
uint32_t nodeId2 = wid2->GetId ();
anim->UpdateNodeSize (nodeId2, 200.0,200.0); 
anim->UpdateNodeImage (nodeId2, eNodeBimg);}
Simulator::Run ();
Simulator::Destroy ();
system("gnuplot 'Energy_Consumption.plt'");
system("gnuplot 'Packet_Loss.plt'");
system("gnuplot 'Delay.plt'");
system("gnuplot 'Throughput.plt'");
return 0;}
