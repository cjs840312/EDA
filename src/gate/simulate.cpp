#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "CirMgr.h"
#include "../util/hash.h"
using namespace std;

#define history_unit sizeof(size_t)*8

static void generate_pattern(stringstream&, int) ;
static int decide_sim_time(int);

void
CirMgr::simulate()
{
   stringstream patterns;
   string pattern;

   generate_pattern(patterns,c1.in_list.size());

	while(getline(patterns,pattern))
   {
   	c1.clearFlag(); c2.clearFlag();

   	for(int i=0,size1=c1.in_list.size(); i<size1; ++i )
         c1.in_list[i]->setValue( (pattern[i] != '0') ); //setValue(bool x)

   	c1.simulate();
      c2.simulate();
   }
}

void
Circuit::simulate()
{
   int size=out_list.size();
   for(int i=0; i<size; ++i )
   {
      out_list[i]->compute_Value();
      out_list[i]->setHistory();
   }
}

void
CirMgr::FEC()
{
   HashMap<FEC_Key<Gate>,Gate*> FECgroup(16);


   






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