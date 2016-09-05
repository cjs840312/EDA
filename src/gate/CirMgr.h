#ifndef CIRMGR
#define CIRMGR

#include <string>
#include <map>
#include <fstream>
#include "gate_def.h"
using namespace std;

class Circuit
{
friend class CirMgr;

public:
   Circuit();
   ~Circuit();

   Gate* getGate(unsigned int);
   void printDFS(Gate*,int);
   void buildgate_list();
   void removeList(vector<Gate*>&);
   void clearFlag();
   void simulate();
   void his_push();
   void his_clear();
   void seq_trace();

private:
   vector<Gate*> gate_list; // all the gates are inside
   map< string, Gate* >   name_match;

   vector<Gate*>    in_list;
   vector<Gate*>   out_list;
   vector<Gate*> const_list;
   vector<Gate*>   And_list;
   vector<Gate*>  Nand_list;
   vector<Gate*>    Or_list;
   vector<Gate*>   Nor_list;
   vector<Gate*>   Xor_list;
   vector<Gate*>  Xnor_list;
   vector<Gate*>   Not_list;
   vector<Gate*>  Buff_list;
   vector<Gate*>  Wire_list;
};

class CirMgr
{   
public:
   CirMgr():best_score(0){}
   ~CirMgr()
   {
     delete [] matchlist;
     delete [] candidate_list1;
     delete [] candidate_list2;
   }
   bool parse( ifstream&, int );
   void printcircuit( int );
   void simulate();
   void match();
   void deep_match();
   void single_match();
   void FEC();
   bool satisfy(Gate*, Gate*, bool);
   int pairs();
   void GO();
   void set_output(string s){output_name = s;}

private:
   void gate_parse(vector<string>& , vector<Gate*>& , Gate* , Circuit&);
   void print_output();
   void trace();


   Circuit c1, c2;
   SatSolver satsolver;
   string output_name;

   map<Gate*,int > cir_num;
   
   int best_score;
   int* matchlist;
   int* best_match;
   bool* match_in_flag;
   bool* match_out_flag;

   vector< vector<Gate*> > final_pair_list;
   vector<int>* candidate_list1;
   vector<int>* candidate_list2;
};

#endif
