#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "CirMgr.h"
#include "../util/hash.h"
using namespace std;

#define history_unit (sizeof(size_t)*8)

static void generate_pattern(stringstream&, int) ;
static int decide_sim_time(int);

void
CirMgr::simulate()
{
   int size1=c1.in_list.size();   

   c1.his_clear();  c2.his_clear();

  	c1.clearFlag();  c2.clearFlag();
      
	for(int i=0; i<size1; ++i )
      c1.in_list[i]->setValue( rand() ); 

	c1.simulate();   c2.simulate();
   c1.his_push();   c2.his_push();
}

void
CirMgr::FEC()
{  
 
   HashMap<FEC_Key<Gate>,Gate*> FEChash(16);
   Gate *temp;
   vector<Gate*> &o1 = c1.out_list;
   vector<Gate*> &o2 = c2.out_list;
   int n=0,m=0;
   vector<vector<Gate*> > FECgroups;
   vector<int> FECsizes;

   for(int i=0,size=o1.size();i<size;i++)
   {
      temp = o1[i];
      temp->matched=0;
      if( ! FEChash.check(FEC_Key<Gate>(temp),temp)  )
      {
         vector<Gate*> v;
         v.push_back(temp);
         FEChash.insert(FEC_Key<Gate>(temp),temp);
         FECgroups.push_back(v);
         FECsizes.push_back(1);
         temp->fake_fec=n++;
         temp->real_fec=m++;
         temp->matched=1;
      }
      else
      {
         bool find=false;
         for(int j=0,fs=FECsizes[temp->fake_fec];j<fs;j++)
         {
            temp=FECgroups[temp->fake_fec][j];
            if(!satisfy(temp,o1[i],(o1[i]->history ^ temp->history)))
            {
               o1[i]->fake_fec=temp->fake_fec;
               o1[i]->real_fec=temp->real_fec;
               o1[i]->matched = (o1[i]->history ^ temp->history)? -1 : 1;
               find=true;
               break;              
            }
         }
         if(!find)
         {
           FECgroups[temp->fake_fec].push_back(o1[i]);
           FECsizes[temp->fake_fec]=FECsizes[temp->fake_fec]+1;           
           o1[i]->fake_fec=temp->fake_fec;
           o1[i]->real_fec=m++;
           o1[i]->matched=1;
         }
         
      }
   } 
   for(int i=0,size=o2.size();i<size;i++)
   {
      temp = o2[i];
      temp->matched=0;
      if(FEChash.check(FEC_Key<Gate>(temp),temp)  )
      {
         for(int j=0,fs=FECsizes[temp->fake_fec];j<fs;j++)
         {
            temp=FECgroups[temp->fake_fec][j];
            if(!satisfy(temp,o2[i],(o2[i]->history ^ temp->history)))
            {
               o2[i]->real_fec=temp->real_fec;
               o2[i]->matched = ((o2[i]->history ^ temp->history) ? -1 : 1);
               break;              
            }
         }       
      }      
   } 

}

void generate_pattern(stringstream& ss, int n) 
{
   int times=decide_sim_time(n),x;

   //cout<<"Total "<<n<<" inputs"<<endl;
   //cout<<"Attempt to simulate "<<times<<" times"<<endl;


   for(int t=0;t<times;t++)      // sould be 32*n  TODO...
   {
      for(int i=0,loop=n/30;i<loop;i++)
      {
         x=rand();
         for(int j=0;j<30;j++)
            ss<<((x>>j)%2);
      }
      x=rand();
      for(int i=0,loop=n%30;i<loop;i++)
         ss<<((x>>i)%2);
      ss<<'\n';
   }
}

int decide_sim_time(int input_size)
{
	/*
   int n=0;
   while(true)
   {
      if(n*n<=input_size) n++;
      else break;
   }
   n--;
   n=n*input_size;
   */
   //int n=input_size*10;
   int n=1;
   n=((n-1)/history_unit+1)*history_unit;

   return n;
}
