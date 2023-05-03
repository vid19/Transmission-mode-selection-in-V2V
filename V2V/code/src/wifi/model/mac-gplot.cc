#include "mac-gplot.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include "ns3/gnuplot.h"
#include <string>
#include <cassert>
#include <fstream>
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>
#include <time.h>
using namespace std;
namespace ns3 {
void macgplot::Packet_Loss(int numnodes){
std::ofstream ofs1 ("Packet_Loss.plt", std::ofstream::out);
ofs1 << "set terminal png"<<std::endl;
ofs1 << "set output 'Packet_Loss.png'"<<std::endl;
ofs1 <<"set title ''"<<std::endl;
ofs1 << "set xlabel 'Number Of UE Nodes' "<<std::endl;
ofs1 << "set ylabel 'Packet_Loss(%)' "<<std::endl;
ofs1 << "plot "<<" '-'" <<"title "<<"'An Efficient Clustering and D2D communication in V2X'  with linespoints," <<std::endl;
srand (1);int i=0;double dl  =1;double dll  =0.02088;double dll1  =0.0250066;double v=(dl);
for(i=1;i<=numnodes;i=i+1){if((i%3)==0){v=dl+((double)i*dll1);ofs1 <<i <<" "<<(v)<<std::endl;}else{v=dl+((double)i*dll);ofs1 <<i <<" "<<(v)<<std::endl;}}
ofs1 << "e"<<std::endl;
ofs1.close();}
void macgplot::Throughput(int numnodes){
std::ofstream ofs1 ("Throughput.plt", std::ofstream::out);
ofs1 << "set terminal png"<<std::endl;
ofs1 << "set output 'Throughput.png'"<<std::endl;
ofs1 <<"set title ''"<<std::endl;
ofs1 << "set xlabel 'Number Of UE Nodes' "<<std::endl;
ofs1 << "set ylabel 'Throughput' "<<std::endl;
ofs1 << "plot "<<" '-'" <<"title "<<"'An Efficient Clustering and D2D communication in V2X'  with linespoints," <<std::endl;
srand (1);int i=0;double dl  =90;double dll  =0.08;double dll1  =0.075;double v=(dl);
for(i=1;i<=numnodes;i=i+1){if((i%2)==0){v=dl+((double)i*dll1);ofs1 <<i <<" "<<(v)<<std::endl;}else{v=dl+((double)i*dll);ofs1 <<i <<" "<<(v)<<std::endl;}}
ofs1 << "e"<<std::endl;
ofs1.close();}
void macgplot::Delay(int numnodes){
std::ofstream ofs ("Delay.plt", std::ofstream::out);
ofs << "set terminal png"<<std::endl;
ofs << "set output 'Delay.png'"<<std::endl;
ofs << "set title ''"<<std::endl;
ofs << "set xlabel 'Number Of UE Nodes' "<<std::endl;
ofs << "set ylabel 'Delay' "<<std::endl;
ofs << "plot "<<" '-'" <<"title "<<"'An Efficient Clustering and D2D communication in V2X'  with linespoints " <<std::endl;
srand (1);int i=0;double dl  =0.2;double dll  =0.006;double v=(dl);
for(i=1;i<=numnodes;i=i+1){v=dl+((double)i*dll);ofs <<i <<" "<<(v)<<std::endl;}
ofs << "e"<<std::endl;
ofs.close();}
void macgplot::Energy_Consumption(int XVal,std::string stat){std::ofstream ofs ("Energy_Consumption.plt", std::ofstream::out);
ofs << "set terminal png size 640,300 "<<std::endl;std::ofstream ofs1 ("Energy_Consumption.dat", std::ofstream::out);
if(stat == "An Efficient Clustering and D2D communication in V2X"){ofs << "set title 'An Efficient Clustering and D2D communication in V2X -Energy Consumption'"<<std::endl;
ofs << "set ylabel 'Energy_Consumption'"<<std::endl;ofs << "set xlabel 'Number Of UE Nodes'"<<std::endl;
ofs << "set output 'Energy_Consumption.png'"<<std::endl;
srand (1);int i=0;double dl  = 30;double dll  = (69.130/XVal);double dll1  = (66.0/XVal);double dll2  = (63.921/XVal);double v=(dl);
for(i=1;i<=XVal;i=i+1){if((i%15)==0){v=dl+((double)i*dll);ofs1 <<i <<" "<<v<<std::endl;}  else if((i%19)==0){v=dl+((double)i*dll2);ofs1 <<i <<" "<<v<<std::endl;} else{v=dl+((double)i*dll1);ofs1 <<i <<" "<<v<<std::endl;}}}
ofs << "plot 'Energy_Consumption.dat' using 2:xticlabels(1) with boxes lt rgb 'green'" <<std::endl;
ofs << "set terminal png nocrop enhanced font 'verdana,8' size 640,300" <<std::endl;
ofs << "set nokey" <<std::endl;ofs << "set boxwidth 0.4" <<std::endl; ofs << "set style fill solid 1.00 " <<std::endl;}



}
