#include <iostream>
#include "CirMgr.h"
using namespace std;

Circuit::Circuit()
{     
   const_list.push_back(new Const(0, "1'b0"));
   const_list.push_back(new Const(1, "1'b1"));
   const_list[1]->setValue(true);
   name_match.insert(pair<string, Gate*>("1'b0", const_list[0] ));
   name_match.insert(pair<string, Gate*>("1'b1", const_list[1] ));
}

Circuit::~Circuit()
{
   for(int i=0,size=gate_list.size();i<size;i++)
      delete gate_list[i];
}

Gate*
Circuit::getGate(unsigned int id)
{
   if( id < gate_list.size())
      return gate_list[id];
   else
      return 0;
}

void
Circuit::printDFS(Gate* g, int level)
{   
   for(int i=0;i<level;i++)
      cout<<"  ";
   cout<<'['<<g->getType()<<"] "<<g->getID();
   if(g->getName()!="")
      cout<<'('<<g->getName()<<')';

   vector<Gate*>& list=g->fanin_get();
   int size = list.size();
 
   for(int i=0;i<size;i++)
   {
      cout<<' '<<list[i]->getID();
      if(list[i]->getFlag())
         cout<<'*';
   }
   
   cout<<endl;

   for(int i=0;i<size;i++)
   {
      if(!list[i]->getFlag())
         printDFS(list[i], level+1);
   }

   g->setFlag(true);
}

void
Circuit::clearFlag()
{
   for(int i=0,size=gate_list.size();i<size;i++)
      gate_list[i]->setFlag(false);
}

void Circuit::removeList( vector<Gate*>& list)
{
   Gate* next_g,* prev_g,* this_g;
   for(size_t i = 0, sizel=list.size(); i<sizel; ++i)
   {
      this_g = list[i];      
      if(this_g->fanin_get().empty() || this_g->fanout_get().empty()) continue;

      vector<Gate*>& this_fanout = this_g->fanout_get();
      prev_g = this_g->fanin_get()[0];      
      vector<Gate*>& prev_fanout = prev_g->fanout_get();

      for(size_t j = 0; j<prev_fanout.size();)
      {
         if(prev_fanout[j]==this_g)
            prev_fanout.erase(prev_fanout.begin()+j);
         else j++;
      }
      for(size_t l = 0,sizeto=this_fanout.size();l<sizeto; ++l)
               prev_g->fanout_add(this_fanout[l]);

      for(size_t j = 0, sizeto=this_fanout.size();j<sizeto; ++j)
      {
         next_g = this_fanout[j];
         vector<Gate*>& next_fanin = next_g->fanin_get();
         for(size_t k = 0; k<next_fanin.size();)
         {
            if(this_g == next_fanin[k])
            {
               next_fanin.erase(next_fanin.begin()+k);
               next_g->fanin_add(prev_g);
            }
            else
               ++k;
         }
      }
   }
   for(size_t i = 0; i < list.size(); ++i)
      delete list[i];
   list.clear();
}