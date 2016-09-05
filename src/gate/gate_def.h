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
   : Type(type), ID(id), Name(name), Value(-1), Flag(false),history(0),matched(0),vari(0),dominate_0(false),dominate_1(false){}
   virtual ~Gate(){}

   void setValue(unsigned x)  { Value =  x; }
   void setFlag (bool x)  { Flag  =  x; }
   void setHistory() { history = Value;}
   void setHistorys(){ historys.push_back(history);}

   string            getType()      const {   return Type;    }
   int               getID()        const {   return ID;      }
   string            getName()      const {   return Name;    }
   unsigned          getValue()     const {   return Value;   }
   bool              getFlag()      const {   return Flag;    }
   unsigned          getHistory()   const {   return history; }
   Var               getVar()       const {   return vari;    }
   vector<unsigned>& getHistorys()        {   return historys; }
   int               getmatched()   const {     return matched;}
 
   vector<Gate*>& fanin_get() { return fanin ;}  // Please don't use push_back()
   vector<Gate*>& fanout_get(){ return fanout;}  // Use fanxx_add instead

   virtual unsigned compute_Value()  = 0;
   virtual bool fanin_add (Gate* g)  = 0;
   virtual void sat_mod(SatSolver&)  = 0;
   //virtual bool pass_dominate(bool ) = 0;
   void back_flag(int);
   void fanout_add(Gate* g) { fanout.push_back(g); }

   void print_gate();
   void relate_merge(int* ,int );
   
protected:
   string Type;            //Type of a gate
   int ID;                 //This inplies the fanout wire number
   string Name;
   unsigned Value;             //This suggests the value of the output.
   bool Flag;
   unsigned history;
   vector<unsigned> historys;
   vector<Gate*> fanin;    //This suggests the fanin  list providing pointers to gates.
   vector<Gate*> fanout;   //This suggests the fanout list providing pointers to gates.
   Var vari;
   int real_fec,fake_fec;
   int matched;
   bool* in_flags;
   bool dominate_0,dominate_1;
};


#define GateClass(T)             \
class T: public Gate             \
{                                \
public:                          \
   T(int,string="");             \
   ~T() {}                       \
   unsigned compute_Value();     \
   bool fanin_add(Gate*);        \
   void sat_mod(SatSolver&);     \
}                                \

//   bool pass_dominate(bool );

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
