#include <iostream>
#include "CirMgr.h"
using namespace std;
/*
static int* state;
static int max_dig,size;
static bool add_dig(int dig=0);
*/
void
CirMgr::match()
{
// TODO...
/*   
   max_dig=2*c1.in_list.size()+2;
   size=c2.in_list.size();
   state=new int[size];
   for(int i=0;i<size;i++)  state[i]=0;
   module(state);
*/
   c2.in_list[0]->fanin_add(c1.const_list[0]);  // s
   c2.in_list[1]->fanin_add(c1.const_list[1]);  // t

   c2.in_list[2]->fanin_add(c1.in_list[2]);  // u
   c2.in_list[3]->fanin_add(c1.in_list[1]);  // v
   c2.in_list[4]->fanin_add(c1.in_list[0]);  // w


}
/*
bool add_dig(int dig)
{
   if(dig>=size)
      return false;
   else if(state[dig]!=max_dig-1)
      state[dig]++;
   else
   {
      state[dig]=0;
      return add_dig(dig+1);
   }
   return true;
}

void CirMgr::module(int* pat)
{
   for(int i=0;i<size;i++)
   {
      if(pat[i]%2==0)
      {
         if(pat[i]==0)
            c2.in_list[i]->fanin_add(c1.const_list[0]);
         else
            c2.in_list[i]->fanin_add(c1.in_list[pat[i]/2-1]);
      }
      else
      {
         if(pat[i]==1)
            c2.in_list[i]->fanin_add(c1.const_list[1]);
         else
         {
            Gate* g=new NotGate(0);            
            c2.in_list[i]->fanin_add(g);
            g->fanin_add(c1.in_list[pat[i]/2-1]);
         }
      }
   }
}

void
CirMgr::clear_module(int* pat)
{
   for(int i=0;i<size;i++)
   {
      vector<Gate*>& inlist = c2.in_list[i]->fanin_get();

      if(pat[i]%2==0 || pat[i]==1)
         inlist.erase(inlist.begin()+inlist.size()-1);
      else
      {
         delete inlist[inlist.size()-1];
         inlist.erase(inlist.begin()+inlist.size()-1);
      }
   }

}
*/