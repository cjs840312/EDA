#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Gate
{
public:
   Gate(string type, int id, string name="")
   : Type(type), ID(id), Name(name), Value(false), Falg(false) {}
   virtual ~Gate(){}

   void setValue(bool x)  { Value =  x; }
   void setFlag (bool x)  { flag  =  x; }


   string getType()  const { return Type;  }
   int    getID()    const { return ID;    }
   string getName()  const { return Name;  }
   int    getValue() const { return Value; }
   bool   getFlag()  const { return Flag;  }
 
   vector<Gate*>& fanin_get() { return fanin ;}  // Please don't use push_back()
   vector<Gate*>& fanout_get(){ return fanout;}  // Use fanxx_add instead

   virtual bool compute_Value()      = 0;
   virtual bool fanin_add (Gate* g)  = 0;
   virtual bool fanout_add(Gate* g)  = 0;
   
   void print_gate();
   
protected:

   string Type;            //Type of a gate
   int ID;                 //This inplies the fanout wire number
   string Name;
   bool Value;             //This suggests the value of the output.
   vector<Gate*> fanin;    //This suggests the fanin  list providing pointers to gates.
   vector<Gate*> fanout;   //This suggests the fanout list providing pointers to gates.
   bool Flag;
};


#define GateClass(T)             \
class T: public Gate             \
{                                \
public:                          \
   T(int,string);                       \
   ~T() {}                       \
   bool compute_Value();         \
   bool fanin_add(Gate* g);      \
   bool fanout_add(Gate* g);     \
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

class Circuit {
	friend class CirMgr;
	public:
		Circuit();
	private:
		vector<Gate*> internalGate;
		vector<Gate*> input;
		vector<Gate*> output;	
};

class CirMgr{
	
	public:
		CirMgr();
		parse(string);	
	private:
		Circuit c1, c2;	
};
