
#ifndef MAC_GPLOT_H
#define MAC_GPLOT_H

#include <fstream>
#include <iostream>
#include <cmath>
#include "ns3/gnuplot.h"
#include <string>
#include <cassert>
#include <fstream>
#include <stdio.h>  
#include <stdlib.h>
namespace ns3 {

class macgplot
{
public:;
void Energy_Consumption(int XVal,std::string stat);
void Packet_Loss(int numnodes);
void Throughput(int numnodes);
void Delay(int numnodes);
};
}

#endif 
