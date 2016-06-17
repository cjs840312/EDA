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
   stringstream patterns;
   string pattern;

   int size1=c1.in_list.size();
   generate_pattern(patterns,size1);

   int count=0;
	while(getline(patterns,pattern))
   {
      pattern="000";
   	c1.clearFlag(); c2.clearFlag();
      cout<<"\rSimulating patterns : "<<count;
   	for(int i=0; i<size1; ++i )
         c1.in_list[i]->setValue( (pattern[i] != '0') ); 

   	c1.simulate();
      c2.simulate();
      if(++count%64 == 0)
      {
         c1.his_push();
         c2.his_push();
      }
   }
}

void
CirMgr::FEC()
{
   HashMap<FEC_Key<Gate>,Gate*> FEChash(16);
   Gate *temp;
   vector<Gate*> &o1 = c1.out_list;
   vector<Gate*> &o2 = c2.out_list;

   for(int i=0,size=o1.size();i<size;i++)
   {
      temp = o1[i];
//      cout<<o1[i]->getHistory();
      if( ! FEChash.check(FEC_Key<Gate>(temp),temp)  )
      {
         FEChash.insert(FEC_Key<Gate>(temp),temp);
      }
      else
      {
         // TODO...  sat
         cout<<satisfy(temp,o1[i],false);
      }
   }
/*
   for(int i=0,size=o2.size();i<size;i++)
   {
      temp = o2[i];
      if( ! FEChash.check(FEC_Key<Gate>(temp),temp)  )
      {
         FEChash.insert(FEC_Key<Gate>(temp),temp);
      }
      else
      {
         // TODO...  sat
      }
   }

*/

}

void generate_pattern(stringstream& ss, int n) 
{
   int times=decide_sim_time(n),x;

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
   int n=0;
   while(true)
   {
      if(n*n<=input_size) n++;
      else break;
   }
   n--;
   n=n*input_size;

   n=((n-1)/history_unit+1)*history_unit;

   return n;
}