#include <iostream>
#include "CirMgr.h"
#include "../sat/sat.h"
using namespace std;

bool
CirMgr::satisfy(Gate* g1, Gate* g2, bool inv)
{
   satsolver.initialize();

   c1.clearFlag(); c2.clearFlag();
   
   
   g1->sat_mod(satsolver);
   g2->sat_mod(satsolver);
   Var temp = satsolver.newVar();
   if(!inv)
      satsolver.addXorCNF(temp,g1->vari,g2->vari);
   else
      satsolver.addXnorCNF(temp,g1->vari,g2->vari);


   satsolver.assertProperty(temp,true);
   

   return satsolver.solve();

}

void
CirMgr::GO()
{
   trace();
   match();
   //deep_match();
   //single_match(output_name);
}
