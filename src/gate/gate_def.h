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

/*
   void fanin_delete( int index )   { fanin.erase(fanin.begin()+index); }
   int  fanin_size()                { return fanin.size();              }
   Gate* fanin_element(unsigned int index)
   {
      return index < fanin.size() ?  fanin[index] : 0 ;
   }
*/

/*
   void fanout_delete(unsigned int index){ fanout.erase(fanout.begin()+index);}
   int  fanout_size()                    { return fanout.size();              }
   Gate* fanout_element(unsigned int index)
   {
      return index < fanout.size() ?  fanout[index] : 0 ;
   }
*/