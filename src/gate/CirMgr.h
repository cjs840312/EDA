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
   int name2index(string);
   void traceBack(Gate*, vector<vector<pair<string, bool> > > & , int &, string,  bool &);
   void buildgate_list();
   void removeList(vector<Gate*>&);
   void clearFlag();
   void simulate();
   void his_push();

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
   CirMgr(){}
   bool parse( ifstream&, int );
   void printcircuit( int );
   void optimize( int );
   void simulate();
   void match();
   void FEC();
   bool satisfy(Gate*, Gate*, bool);
   void pairs();

private:
   void gate_parse(vector<string>& , vector<Gate*>& , Gate* , Circuit&);
   Circuit c1, c2;
   SatSolver satsolver;
};

#endif
