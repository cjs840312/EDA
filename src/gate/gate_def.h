#ifndef GATE
#define GATE

#include <vector>
#include <string>
#include "../sat/sat.h"
using namespace std;

class Gate
{

friend class CirMgr;
friend class Circuit;

public:
   Gate(string type, int id, string name="")
   : Type(type), ID(id), Name(name), Value(false), Flag(false),history(0),matched(false),vari(0){}
   virtual ~Gate(){}

   void setValue(bool x)  { Value =  x; }
   void setFlag (bool x)  { Flag  =  x; }
   void setHistory() { history = history*2 + Value;}
   void setHistorys(){ historys.push_back(history);}

   string getType()  const { return Type;  }
   int    getID()    const { return ID;    }
   string getName()  const { return Name;  }
   int    getValue() const { return Value; }
   bool   getFlag()  const { return Flag;  }
   size_t getHistory() const{ return history; }
   Var    getVar()   const { return vari;   }
   vector<size_t>& getHistorys(){ return historys; }

 
   vector<Gate*>& fanin_get() { return fanin ;}  // Please don't use push_back()
   vector<Gate*>& fanout_get(){ return fanout;}  // Use fanxx_add instead

   virtual bool compute_Value()      = 0;
   virtual bool fanin_add (Gate* g)  = 0;
   virtual void sat_mod(SatSolver&)  = 0;
   void fanout_add(Gate* g) { fanout.push_back(g); }

   void print_gate();
   
protected:

   string Type;            //Type of a gate
   int ID;                 //This inplies the fanout wire number
   string Name;
   bool Value;             //This suggests the value of the output.
   bool Flag;
   size_t history;
   vector<size_t> historys;
   vector<Gate*> fanin;    //This suggests the fanin  list providing pointers to gates.
   vector<Gate*> fanout;   //This suggests the fanout list providing pointers to gates.
   Var vari;
   int real_fec,fake_fec;
   bool matched;
};


#define GateClass(T)             \
class T: public Gate             \
{                                \
public:                          \
   T(int,string="");             \
   ~T() {}                       \
   bool compute_Value();         \
   bool fanin_add(Gate*);        \
   void sat_mod(SatSolver&);     \
}                                \


GateClass(   Input   );
GateClass(  Output   );
GateClass(  AndGate  );
GateClass( NandGate  );
GateClass(   OrGate  );
GateClass(  NorGate  ); 
GateClass(  XorGate  );
GateClass( XnorGate  );
GateClass(  NotGate  );
GateClass(   Wire    );
GateClass(  Buffer   );
GateClass(  Const    );

#endif
