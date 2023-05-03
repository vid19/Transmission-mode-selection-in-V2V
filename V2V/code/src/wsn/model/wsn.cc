/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "wsn.h"
#include <iostream>
#include <ctime>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/csma-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

using namespace std;
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






float manetthee3d::ran2(long *idum)
{
 int j;
 long k;
 static long idum2=123456789;
 static long iy=0;
 static long iv[NTAB];
 float temp;
 if (*idum <= 0) {
  if (-(*idum) < 1) *idum=1;
  else *idum = -(*idum);
  idum2=(*idum);
  for (j=NTAB+7;j>=0;j--) {
   k=(*idum)/IQ1;
   *idum=IA1*(*idum-k*IQ1)-k*IR1;
   if (*idum < 0) *idum += IM1;
   if (j < NTAB) iv[j] = *idum;
  }
  iy=iv[0];
 }
 k=(*idum)/IQ1;
 *idum=IA1*(*idum-k*IQ1)-k*IR1;
 if (*idum < 0) *idum += IM1;
 k=idum2/IQ2;
 idum2=IA2*(idum2-k*IQ2)-k*IR2;
 if (idum2 < 0) idum2 += IM2;
 j=iy/NDIV;
 iy=iv[j]-idum2;
 iv[j] = *idum;
 if (iy < 1) iy += IMM1;
 if ((temp=AM*iy) > RNMX)
  return RNMX;
 else return temp;
}



int manetthee3d::SimulationP(double p)
{
 double sim=ran2(seed);
 if(sim<p) return 1;
 else return 0;
}



int manetthee3d::RandomSelectTransmitter(int cell_id,int *pos,int n)
{
 int count = 0;
 int i;
 int *array = NULL;
 array = new int[n];
 for(i=1;i<=n;i++)
 {
  if(pos[i]==cell_id)
   array[count++]=i;
 }
 if(count==0)
 {
  delete []array;
  return -1;
 }

 int sim = (int)(count*ran2(seed));
 int index = array[sim];
 delete []array;
 return index;
}



int manetthee3d::RandomSelectReceiver(int cell_id,int *pos,int n,int m,int K)
{

 int count=0;
 int i;
 int *array=NULL;
 array=new int[n];
 for(i=1;i<=n;i++)
 {
  if(i==K)
   continue;
  if(IsTwoHopNeighbor(pos[i],cell_id,m))
   array[count++]=i;
 }

 if(count==0)
 {
  delete []array;
  return -1;
 }

 int sim=(int)(count*ran2(seed));
 int index=array[sim];
 delete []array;
 return index;
}



void manetthee3d::SDTransmission(int *IN,int &recv_ct,int &send_index,int &copy_index
     ,int g,ofstream& fout,long time_slot)
{
 int i;
 if(send_index>g)
 {
  for(i=1;i<=g;i++)
   if(IN[i]==0) break;
   IN[i] = 1;
   recv_ct++;

   fout<<time_slot<<": S-->D packet ["<<i<<", "<<recv_ct<<"]"<<endl;
 }
 else if(send_index==g)
 {
  if(IN[send_index]==0)
  {
   IN[send_index]=1;
   recv_ct++;

   fout<<time_slot<<": S-->D packet ["<<send_index<<", "<<
    recv_ct<<"]"<<endl;
   send_index++;
   copy_index = 1;
  }
  else
  {
   for(i=1;i<=g;i++)
    if(IN[i]==0) break;
    IN[i] = 1;
    recv_ct++;

    fout<<time_slot<<": S-->D packet ["<<i<<", "<<recv_ct<<"]"<<
     endl;

    send_index++;
    copy_index=1;
  }
 }
 else
 {
  if(IN[send_index]==0)
  {
   IN[send_index]=1;
   recv_ct++;

   fout<<time_slot<<": S-->D packet ["<<send_index<<", "<<
    recv_ct<<"]"<<endl;
   send_index++;
   copy_index=1;
  }
  else
  {
  
   if(send_index>recv_ct)
   {
    for(i=1;i<send_index;i++)
     if(IN[i]==0) break;
     IN[i]=1;
     recv_ct++;

     fout<<time_slot<<": S-->D packet ["<<i<<", "<<recv_ct<<
      "]"<<endl;

     send_index++;
     copy_index=1;
   }
   
   else
   {
    IN[send_index+1]=1;
    recv_ct++;

    fout<<time_slot<<": S-->D packet ["<<send_index+1<<", "
     <<recv_ct<<"]"<<endl;

    send_index=send_index+2;
    copy_index=1;
   }
  }
 }
}



void manetthee3d::RDTransmission(int *IN,int *carry,int &recv_ct,int K,ofstream &fout
     ,long time_slot)
{
 if(carry[K]==0)
  return;
 if(IN[carry[K]]==1) 
 {
 
  return;
 }
 IN[carry[K]] = 1;
 recv_ct++;

 fout<<time_slot<<": R-->D node "<<K<<" packet ["<<carry[K]<<", "<<
  recv_ct<<"]"<<endl;
 carry[K] = 0;
}



void manetthee3d::SRTransmission(int *carry,int &send_index,int &copy_index,int f,int
     g,int V, ofstream& fout,long time_slot)
{
 if(carry[V]) 
  return;
 if(send_index>g) 
  return;
 carry[V]=send_index;

 fout<<time_slot<<": S-->R copy "<<copy_index<<" of packet "<<
  send_index<<" to node "<<V<<endl;
 copy_index++;
 if(copy_index>f)
 {
  send_index++;
  copy_index=1;
 }
}


int manetthee3d::IsTwoHopNeighbor(int dest,int source,int m)
{
 int r1,c1,h1,tmp;
 h1=source/(m*m);
 tmp=source-m*m*h1;
 r1=tmp/m;
 c1=tmp%m;
 
 int r2,c2,h2;
 h2=dest/(m*m);
 tmp=dest-m*m*h2;
 r2=tmp/m;
 c2=tmp%m;
 
 int r_d;
 if(r1>=r2)
  r_d=r1-r2;
 else
  r_d=r2-r1;
 
 int c_d;
 if(c1>=c2)
  c_d=c1-c2;
 else
  c_d=c2-c1;
 
    int h_d;
    if(h1>=h2)
        h_d=h1-h2;
    else
        h_d=h2-h1;


 if(r_d>1 && r_d!=m-1)
  return 0;

 if(c_d>1 && c_d!=m-1)
  return 0;
    if(h_d>1 && h_d!=m-1)
        return 0;
 return 1;
}


int manetthee3d::IfTwoHopOfActiveCell(int *cell_state,int cell_id,int m)
{

 
 
 int H0=cell_id/(m*m);
 int tmp=cell_id-m*m*H0;
 int R0=tmp/m;
 int C0=tmp%m;
 int i,j,k;
 int index;
 int H_index,R_index,C_index;
 for(k=H0-1;k<=H0+1;k++)
  for(i=R0-1;i<=R0+1;i++)
   for(j=C0-1;j<=C0+1;j++)
   {
    R_index=i%m;
    if(R_index==-1)
     R_index=m-1;
    C_index=j%m;
    if(C_index==-1)
     C_index=m-1;
    H_index=k%m;
    if(H_index==-1)
     H_index=m-1;
    index=H_index*m*m+R_index*m+C_index;
    if(cell_state[index])
     return index;
   }
   return -1;
  
}


void manetthee3d::transmission_scheduling(int *pos,int *cell_state,int *carry,int *IN
       ,int &send_index,int &copy_index,int &recv_ct,int f,int g,int m,int n,
       ofstream& fout,long time_slot)
{
 int distribution = 0;
 if(cell_state[pos[1]]==0)
  distribution = 3;
 else
 {
  if(IsTwoHopNeighbor(pos[n],pos[1],m))
   distribution = 1;
  else
   distribution = 2;
 }
 int K,V,index;
 switch(distribution)
 {
 case 1:
  K = RandomSelectTransmitter(pos[1],pos,n);
  if(K==-1)
   break;
  else if(K==n)
   break;
  else if(K==1)
  {
   SDTransmission(IN,recv_ct,send_index,copy_index,g,
    fout,time_slot);
   break;
  }
  else
  {
   
   if(IsTwoHopNeighbor(pos[K-1],pos[K],m)) 
    break;
   else
   {
    V = RandomSelectReceiver(pos[K],pos,n,m,K);
    if(V==-1)
     break;
    else if(V==n && SimulationP(0.50))
    {
     RDTransmission(IN,carry,recv_ct,K,fout,
      time_slot);
     break;
    }
   }
  }
  break;
 case 2: /**check for S-->R **/
  K = RandomSelectTransmitter(pos[1],pos,n);
  if(K==1)
  {
   V = RandomSelectReceiver(pos[1],pos,n,m,K);
   if(V==-1)
   {;}
   else
   {
    if(SimulationP(0.50))
     SRTransmission(carry,send_index,copy_index,f
     ,g,V,fout,time_slot);
   }
  }
  else
  {;}
  /**check for R-->D **/
  index = IfTwoHopOfActiveCell(cell_state,pos[n],m);
  if(index>=0)
  {
   K = RandomSelectTransmitter(index,pos,n);
   if(K==n)
   {;}
   else if(K==-1)
   {;}
   else
   {
    if(IsTwoHopNeighbor(pos[K-1],pos[K],m))
    {;}
    else
    {
     V = RandomSelectReceiver(pos[K],pos,n,m,K);
     if(V==n && SimulationP(0.50))
      RDTransmission(IN,carry,recv_ct,K,fout,
      time_slot);
    }
   }
  }
  else
  {;}
  break;
 case 3: /**check for R-->D **/
  index = IfTwoHopOfActiveCell(cell_state,pos[n],m);
  if(index>=0)
  {
   K = RandomSelectTransmitter(index,pos,n);
   if(K==n)
   {}
   else if(K==-1)
   {}
   else
   {
    if(IsTwoHopNeighbor(pos[K-1],pos[K],m))
    {}
    else
    {
     V  =RandomSelectReceiver(pos[K],pos,n,m,K);
     if(V==n && SimulationP(0.50))
      RDTransmission(IN,carry,recv_ct,K,fout,
      time_slot);
    }
   }
  }
  else
  {}
  break;
 }
}


void manetthee3d::initiate_cell_state(int *cell_state,long time_slot,int m)
{
 int k = m/alpha;
 int *origin = NULL;
 origin=new int[k*k*k];
 int i,j,h;
 for(i=0;i<k*k*k;i++)
  origin[i]  = 0;
 int ct = 0;
    for(h=0;h<k;h++)
  for(i=0;i<k;i++)
   for(j=0;j<k;j++)
   {
    origin[ct] = h*m*m*alpha+i*m*alpha+j*alpha;
    ct++;
   }
   //reset the state of all m*m*m cells
   for(i=0; i<m*m*m; i++)
    cell_state[i] = 0;
   int t0 = time_slot%(alpha*alpha*alpha); ///There are in total alpha*alpha*alpha groups
   int offset;
   int tmp;
   tmp =  t0%(alpha*alpha);
   offset = (t0/(alpha*alpha))*m*m + (tmp/alpha)*m + tmp%alpha;
   ///offset = (t0/alpha)*m + t0%alpha;
   for(i=0; i<ct; i++)
    cell_state[origin[i]+offset] = 1;
   delete []origin;
}

///////////////////////////////////////////////////////////////////////////////
/**
Update the position of each node at the beginning of each time slot
**/
void manetthee3d::update_node_position(int *pos,int n,int m)
{
 int i;
 for(i=1;i<=n;i++)
  pos[i]=-1;
 double RAN=m*m*m;
 for(i=1;i<=n;i++)
 {
 
  int sim=(int)(RAN*ran2(seed));
  pos[i]=sim;
 }
}





}

