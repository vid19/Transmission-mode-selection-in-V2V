/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "sdnnfv.h"
#include "ns3/lte-helper.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
#include "ns3/network-module.h"
#include "ns3/ipv4.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <memory.h>
using namespace ns3;
using namespace std;

namespace ns3 {

/* ... */

void SDN_NFV::getAllRegisterUser(NodeContainer User)
{
std::ofstream ofs ("reg.temp", std::ofstream::out);

for(uint32_t i=0;i<User.GetN();i++){
 Ptr <Node>   node = User.Get (i); // Get pointer to ith node in container
 Ptr<Ipv4> ipv4= node->GetObject<Ipv4> (); // Get Ipv4 instance of the node
Ipv4Address addr = ipv4->GetAddress (1, 0).GetLocal (); 
std::cout <<"IoT Device:  "<<i<<" IP Address "<< addr << endl;
ofs <<"IoT Device:  "<<i<<" IP Address " << addr<<std::endl;
 }
ofs.close();

}


}

