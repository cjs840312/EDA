#include <iostream>
#include "CirMgr.h"
using namespace std;

Gate*
Circuit::getGate(unsigned int id)
{
   if( id < gate_list.size())
      return gate_list[id];
   else
      return 0;
}


bool
CirMgr::parse( ifstream& fin, int num)
{
   Circuit& c = num==1? c1:c2;

   // TODO ...

   string s;
   getline(fin,s);

   return true;
}