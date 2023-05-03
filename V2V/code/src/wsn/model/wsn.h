/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef WSN_H
#define WSN_H
#include <iostream>
#include <ctime>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
using namespace std;
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

namespace ns3 {

/* ... */

class manetthee3d
{

public:
int alpha=9; //we fix delta=1
long seed[1];
float ran2(long *);
int SimulationP(double p);
void initiate_cell_state(int *cell_state,long time_slot,int m);
void update_node_position(int *pos,int n,int m);
int IsTwoHopNeighbor(int dest,int source,int m);
int IfTwoHopOfActiveCell(int *cell_state,int cell_id,int m);
void transmission_scheduling(int *pos,int *cell_state,int *carry,int *IN
       ,int &send_index,int &copy_index,int &recv_ct,int f,int g,int m,int n,
       ofstream& fout,long time_slot);
int RandomSelectTransmitter(int cell_id,int *pos,int n);
void SDTransmission(int *IN,int &recv_ct,int &send_index,int &copy_index
     ,int g,ofstream& fout,long time_slot);
int RandomSelectReceiver(int cell_id,int *pos,int n,int m,int K);
void RDTransmission(int *IN,int *carry,int &recv_ct,int K,ofstream &fout
     ,long time_slot);
void SRTransmission(int *carry,int &send_index,int &copy_index,int f,int
     g,int V, ofstream& fout,long time_slot);
};


}

#endif /* WSN_H */

