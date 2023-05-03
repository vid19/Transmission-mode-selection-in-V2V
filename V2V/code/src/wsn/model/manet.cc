#include <iostream>
#include <fstream>
#include <math.h>
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

///////////////////////////////////////////////////////////////////////////////
int alpha=9; //we fix delta=1
long seed[1];
float ran2(long *);
void initiate_cell_state(int *cell_state,long time_slot,int m);
void update_node_position(int *pos,int n,int m);
int IsOneHopNeighbor(int dest,int source,int m);
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
int IfOneHopOfActiveCell(int *cell_state,int cell_id,int m);


///////////////////////////////////////////////////////////////////////////////
/**
Long period (> 2*10^18) random number generator of L'Ecuyer with
Bays-Durham shuffle
and added safeguards. Returns a uniform random deviate between 0.0 and
1.0 (exclusive of
the endpoint values). Call with idum a negative integer to initialize;
thereafter, do not alter
idum between successive deviates in a sequence. RNMX should approximate
the largest floating
value that is less than 1.
**/
float ran2(long *idum)
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


///////////////////////////////////////////////////////////////////////////////
/**
randomly generate a number x range from 0 to 99
if x sit inside 0 to 100*p-1
then it says the event e happens
otherwise not.
obviously, e happens with probability p.
**/
int SimulationP(double p)
{
 double sim=ran2(seed);
 if(sim<p) return 1;
 else return 0;
}


///////////////////////////////////////////////////////////////////////////////
/***
randomly select one node from the cell with given cell_id
return the index of selected node
***/
int RandomSelectTransmitter(int cell_id,int *pos,int n)
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
 //there are count nodes in the node_1 cell, i.e., cell tgt
 //now randomly choose one out of them as transmitter
 //output a double from [0,count-1]
 int sim = (int)(count*ran2(seed));
 int index = array[sim];
 delete []array;
 return index;
}


///////////////////////////////////////////////////////////////////////////////
/***
randomly select one node except node K from the cell with given
cell_id
return its index
***/
int RandomSelectReceiver(int cell_id,int *pos,int n,int m,int K)
{
 //first iterate the nodes except the node K in one-hop neighbor of cell_id
 int count=0;
 int i;
 int *array=NULL;
 array=new int[n];
 for(i=1;i<=n;i++)
 {
  if(i==K)
   continue;
  if(IsOneHopNeighbor(pos[i],cell_id,m))
   array[count++]=i;
 }
 //if there is no other nodes in one-hop neighbor
 if(count==0)
 {
  delete []array;
  return -1;
 }
 //output a double from [0,count-1]
 int sim=(int)(count*ran2(seed));
 int index=array[sim];
 delete []array;
 return index;
}


///////////////////////////////////////////////////////////////////////////////
/**
Source-->Destination Transmission
**/
void SDTransmission(int *IN,int &recv_ct,int &send_index,int &copy_index
     ,int g,ofstream& fout,long time_slot)
{
 int i;
 if(send_index>g)
 {
  for(i=1;i<=g;i++)
   if(IN[i]==0) break;
   IN[i] = 1;//it means that the destination has received it's packet
   recv_ct++;
   //******trace*********//
   fout<<time_slot<<": S-->D packet ["<<i<<", "<<recv_ct<<"]"<<endl;
 }
 else if(send_index==g)
 {
  if(IN[send_index]==0)
  {
   IN[send_index]=1;
   recv_ct++;
   //******trace*********//
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
    //******trace*********//
    fout<<time_slot<<": S-->D packet ["<<i<<", "<<recv_ct<<"]"<<
     endl;
    //the packet P_h has been received
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
   //******trace*********//
   fout<<time_slot<<": S-->D packet ["<<send_index<<", "<<
    recv_ct<<"]"<<endl;
   send_index++;
   copy_index=1;
  }
  else
  {
   // correspond to case: k < j < g && IN&B[j]=0
   // find one fresh packet from the buffer of already-sent-queue
   // instead of the packet behind send_index
   if(send_index>recv_ct)
   {
    for(i=1;i<send_index;i++)
     if(IN[i]==0) break;
     IN[i]=1;
     recv_ct++;
     //******trace*********//
     fout<<time_slot<<": S-->D packet ["<<i<<", "<<recv_ct<<
      "]"<<endl;
     //the packet send_index has been received
     send_index++;
     copy_index=1;
   }
   // correspond to transitions of states
   // (2,k,k),(3,k,k),...,(f,k,k)
   else
   {
    IN[send_index+1]=1;
    recv_ct++;
    //******trace*********//
    fout<<time_slot<<": S-->D packet ["<<send_index+1<<", "
     <<recv_ct<<"]"<<endl;
    //move by two packets
    send_index=send_index+2;
    copy_index=1;
   }
  }
 }
}


///////////////////////////////////////////////////////////////////////////////
/***
Relay-->Destination Transmission
Relay node is K
***/
void RDTransmission(int *IN,int *carry,int &recv_ct,int K,ofstream &fout
     ,long time_slot)
{
 if(carry[K]==0) //K has no packet destined for node n
  return;
 if(IN[carry[K]]==1) //node n has gotten the packet carried by K
 {
  //carry[K]=0; //reset node K as an eligible relay candidate
  //cannot reset here, because this is different from Markov Model
  return;
 }
 IN[carry[K]] = 1;
 recv_ct++;
 //******trace*********//
 fout<<time_slot<<": R-->D node "<<K<<" packet ["<<carry[K]<<", "<<
  recv_ct<<"]"<<endl;
 carry[K] = 0;
}


///////////////////////////////////////////////////////////////////////////////
/**
Source-->Relay Transmission
Relay node is V
**/
void SRTransmission(int *carry,int &send_index,int &copy_index,int f,int
     g,int V, ofstream& fout,long time_slot)
{
 if(carry[V]) //node V already has some packet
  return;
 if(send_index>g) //source node has already finished the copy distribution process
  return;
 carry[V]=send_index;
 //*****trace********//
 fout<<time_slot<<": S-->R copy "<<copy_index<<" of packet "<<
  send_index<<" to node "<<V<<endl;
 copy_index++;
 if(copy_index>f)
 {
  send_index++;
  copy_index=1;
 }
}


///////////////////////////////////////////////////////////////////////////////
/**
Returns whether the dest node is among one-hop neighbors of the
source node
**/
///Here, 0=<dest, source<=m^3-1
int IsOneHopNeighbor(int dest,int source,int m)
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
 //considering the edge effects of network region
 //if(r_d>1)
 if(r_d>1 && r_d!=m-1)
  return 0;
 //if(c_d>1)
 if(c_d>1 && c_d!=m-1)
  return 0;
    if(h_d>1 && h_d!=m-1)
        return 0;
 return 1;
}


///////////////////////////////////////////////////////////////////////////////
/**
Check whether the cell with given cell_id is in one-hop neighbor of
some active cell
return the index of the active cell
**/
int IfOneHopOfActiveCell(int *cell_state,int cell_id,int m)
{
 //considering the edge effects of network region
 
 
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
   /*
   //without considering the edge effects of network region
   int R0=cell_id/m;
   int C0=cell_id%m;
   int i,j;
   int index;
   for(i=R0-1;i<=R0+1;i++)
   for(j=C0-1;j<=C0+1;j++)
   {
   if(i>=0 && i<=m-1 && j>=0 && j<=m-1)
   {
   index=i*m+j;
   if(cell_state[index])
   return index;
   }
   }
   return -1;
   */
}


///////////////////////////////////////////////////////////////////////////////
/************************************************************
1.Traffic Setting
1-->n, 2-->1, 3-->2,...,i-->i-1,...,n-->n-1
we focus on node pari 1-->n in this function
2.Basic Idea
determine the distribution case of node 1 and n
1 (active?) & n(one-hop neighbor?)
case 1: yes & yes S-->D or R-->D transmission
case 2: yes & no S-->R or R-->D transmission
case 3: no R-->D transmission
************************************************************/
void transmission_scheduling(int *pos,int *cell_state,int *carry,int *IN
       ,int &send_index,int &copy_index,int &recv_ct,int f,int g,int m,int n,
       ofstream& fout,long time_slot)
{
 int distribution = 0;
 if(cell_state[pos[1]]==0)
  distribution = 3;
 else
 {
  if(IsOneHopNeighbor(pos[n],pos[1],m))
   distribution = 1;
  else
   distribution = 2;
 }
 int K,V,index;
 switch(distribution)
 {
 case 1: /**check for S-->D **/
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
   /**check for R-->D **/
   if(IsOneHopNeighbor(pos[K-1],pos[K],m)) //a flow for K-->K-1
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
  index = IfOneHopOfActiveCell(cell_state,pos[n],m);
  if(index>=0)
  {
   K = RandomSelectTransmitter(index,pos,n);
   if(K==n)
   {;}
   else if(K==-1)
   {;}
   else
   {
    if(IsOneHopNeighbor(pos[K-1],pos[K],m))
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
  index = IfOneHopOfActiveCell(cell_state,pos[n],m);
  if(index>=0)
  {
   K = RandomSelectTransmitter(index,pos,n);
   if(K==n)
   {}
   else if(K==-1)
   {}
   else
   {
    if(IsOneHopNeighbor(pos[K-1],pos[K],m))
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

///////////////////////////////////////////////////////////////////////////////
/**
notice that here m=9*x and alpha=9
alternately activating cells inside a concurrent set
the period is alpha*alpha*alpha
**/
void initiate_cell_state(int *cell_state,long time_slot,int m)
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
void update_node_position(int *pos,int n,int m)
{
 int i;
 for(i=1;i<=n;i++)
  pos[i]=-1;
 double RAN=m*m*m;
 for(i=1;i<=n;i++)
 {
  //for each node i, randomly choose one cell from 0,1,2,...,m*m-1
  //output a double from [0,RAN-1]
  int sim=(int)(RAN*ran2(seed));
  pos[i]=sim;
 }
}


///////////////////////////////////////////////////////////////////////////////
int main()
{
 *seed = -time(0);//time(0):return system time(second) from 1.1. 1970  to now,
 ofstream fout;
 fout.open("for_standard variance.dat");
 ofstream fexp;
 fexp.open("for_mean.dat");
 ofstream frecd;
 frecd.open("for_record.dat");
 ofstream finstant;
 finstant.open("for_instant.dat");
 //define control parameters
 int f,  m, n, g;
 m =8;
 n = 100;
 f = 1;
 if(alpha>m)
  alpha = m;
 int *pos = NULL;
 int *carry = NULL;
 int *IN = NULL;
 int *cell_state = NULL;
 int i, j;
 //the destination has received recv_ct packet
 int recv_ct = 0;
 //the source is delivering the copy_index copy for the send_index packet
 int send_index = 1; // 1<=send_index<=g
 int copy_index = 1; // 1<=copy_index<=f
 long sim_round;
 long time_slot; //slot_0, slot_1, slot_2, ......
 double time_total = 0;
// double time_avg = 0;
 //The simulated expected delivery delay(SE)
 //is calculated as the average value of 1000000
 //random and independent simulations.
 int max_round = 1000000;
 //double *avg = new double[test_set+1];
 double *deliver_delay = new double[max_round+1];
 for(f=1; f<=10; f++)
 {
  g = 1;
  pos = new int[n+1]; //pos[1], pos[2], ..., pos[n]
  carry = new int[n+1]; //carry[1], carry[2], ..., carry[n]
  //IN[1], IN[2], ..., IN[g]; it is g-bit binary vector that records the
  //reception status of current requesting group at destination D
  //where the ith bit IN[i] is set as 1(resp. 0) if the ith packet of the current
  //requesting group has(resp. has not) been received.
  IN = new int[g+1];
  cell_state = new int[m*m*m]; // from cell_0 to cell_(m*m*m-1)
  int count = 0;
 
  //initialization for each max_round
  time_total = 0; //recording the total time for each max_round
 // time_avg = 0;   //recording the average time of each max_round
  for(sim_round=1; sim_round<=max_round; sim_round++)
  {
   count++;
   frecd<<"**********************************"<<endl;
   frecd<<" Round="<<sim_round<<endl;
   frecd<<"**********************************"<<endl;
   //initialization at the beginning of each simulation round
   for(j=1; j<=n; j++)
   {
    pos[j] = -1;
    carry[j] = 0;
   }
   //reset for the destination
   recv_ct = 0;
   for(j=1;j<=g;j++)
    IN[j] = 0;
   //reset for the source
   send_index = 1;
   copy_index = 1;
   //reset the state of all m*m*m cells
   for(j=0;j<m*m*m;j++)
    cell_state[j] = 0;
   time_slot = 0;
   while(recv_ct!=1)
   {
    time_slot++;
    initiate_cell_state(cell_state,time_slot,m);
    update_node_position(pos,n,m);
    transmission_scheduling(pos,cell_state,carry,IN,
     send_index,copy_index,recv_ct,f,g,m,n,frecd,time_slot);
   }
   deliver_delay[count]=time_slot;
   
   time_total = time_total+time_slot;
  }
  
  int sim_res; //expected delivery delay
  sim_res = time_total/max_round;
  
  cout<<"expected delay="<<sim_res<<endl;
  fexp<<sim_res<<endl;
  
  ///calculating the relative standard deviation
  double sum = 0;
  double ssd;
  for(i=1; i<=max_round; i++)
   sum = sum + (deliver_delay[i]-sim_res)*(deliver_delay[i]-sim_res);
  ssd = sqrt(sum/(max_round-1));///simulated relative standard deviation
  ssd = ssd/sim_res;
  cout<<"ssd="<<ssd<<endl;
  fout<<ssd<<endl;
  
  delete []cell_state;
  delete []IN;
  delete []pos;
  delete []carry;
  
 }
 
 fexp.close();
 fout.close();
 frecd.close();
 finstant.close();
 delete []deliver_delay;
 return 1;
}
