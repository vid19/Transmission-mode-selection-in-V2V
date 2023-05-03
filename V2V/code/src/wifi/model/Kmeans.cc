#include "Kmeans.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <assert.h>
#include <fstream>
#include <stdio.h>  
#include <stdlib.h>
#include <limits.h>
#include <cmath>
#include <time.h>
#define BIG_double (INFINITY)
#define services 5
using namespace std;
namespace ns3 {
void Kmeans::Less_Mobility(int n){
for (int j = 0; j < services; ++j){
flag = true;
for (int i = 0; i < n; ++i){
if (j == y2x[i] || abs(j - y2x[i]) == n - i){
flag = false;
break;}}
if (flag){
y2x[n] = j;
if (n + 1 == services)
++High_Residual_Energy;
else
Less_Mobility(n + 1);}}
}
void Kmeans::successful_packet_transmission(int Local_Gateway, int Less_Distance, int request_inter_arrival_time, double *request_length, int *TTL) {
for (int ii = 0; ii < Less_Distance; ii++){
int best_index = -1;
double High_Trust_Score = BIG_double;
for (int jj = 0; jj < request_inter_arrival_time; jj++){           
double cur_distance = request_length[ii*request_inter_arrival_time + jj];
if (cur_distance < High_Trust_Score){
best_index = jj;
High_Trust_Score = cur_distance;}}
TTL[ii] = best_index;}}
void Kmeans::Clustering(){

fstream my_file;
my_file.open("UENodes.txt", ios::in);
if (!my_file) {
cout << "No such file";
}
else {
char ch;
while (1) {
my_file >> ch;
if (my_file.eof())
break;
}
std::cout<<" \nCluster1 is "<<"\n\n";
for (int i = 1; i < rand() % ch; ++i){
cout<< "Vehicle:" << i <<"\n";
}
std::cout<<" \nCluster2 is "<<"\n\n";
for (int i = 20; i < rand() % 50; ++i){
cout<< "Vehicle:" << i <<"\n";
}
int centroid = (rand() % ch);
int centroid1 = (rand() % 50);
cout<<" \nCluster Heads are: ";
printf("%d ", centroid);
printf("%d ", centroid1);
cout<<"\nCluster Heads are Selected Successfully..."<<"\n\n"; 
}
my_file.close();
}}
