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
   Circuit(){}

   Gate* getGate(unsigned int);
   void printCircuit();		// I have no idea how to print a circuit~~
   void buildgate_list();
   void removeWire();

private:
   int num;

   vector<Gate*> gate_list; // all the gates are inside
   map< string, Gate* >   name_match;

   vector<Gate*>   in_list;
   vector<Gate*>  out_list;
   vector<Gate*>  And_list;
   vector<Gate*> Nand_list;
   vector<Gate*>   Or_list;
   vector<Gate*>  Nor_list;
   vector<Gate*>  Xor_list;
   vector<Gate*> Xnor_list;
   vector<Gate*>  Not_list;
   vector<Gate*> Buff_list;
   vector<Gate*> Wire_list;
};

class CirMgr
{   
public:
   CirMgr(){}
   bool parse( ifstream&, int );
   void printcircuit(Circuit& cir);

protected:
   void Str2Vars(string& , vector<Gate*>& , Circuit& ); // parse input, output;
   void Str2Vars(string& , vector<Gate*>& , Gate* , Circuit&);  // parse gates;


private:
   Circuit c1, c2;   
};

#endif
