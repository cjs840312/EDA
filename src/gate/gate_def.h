#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Gate
{
public:
   Gate(string type,int id) : Type(type), ID(id), Value(false){}
   virtual ~Gate(){}
  
   void setType(string s) { Type  =  s; }
   void setID(int id)     { ID    = id; }
   void setValue(bool x)  { Value =  x; }

   int getID()    const { return ID;    }
   int getValue() const { return Value; }

   virtual bool compute_Value() = 0;
 
   virtual bool fanin_add( Gate* g ){ fanin.push_back(g);               }
   void fanin_delete( int index )   { fanin.erase(fanin.begin()+index); }
   int  fanin_size()                { return fanin.size();              }
   Gate* fanin_element(int index)
   {
      if(index >= 0 && index < fanin.size())
         return fanin.at(index);
      else
         return 0;      
   }

   virtual bool fanout_add(Gate* g){ fanout.push_back(g);                }
   void fanout_delete(int index)   { fanout.erase(fanout.begin()+index); }
   int  fanout_size()              { return fanout.size();               }
   Gate* fanout_element(int index)
   {
      if(index >= 0 && index < fanout.size())
         return fanout.at(index);
      else
         return 0;
   }

   void print_gate()
   {     
      cout <<"Type:  " << Type  << endl
           <<"ID:    " << ID    << endl
           <<"Value: " << Value << endl;
      if(!fanin.empty())
      {
         cout<<"fanin ID :";
         for(int i = 0; i<fanin.size(); i++)
            cout<< fanin[i]->getID()<<' ';
         cout<<endl;
      }      
      if(!fanout.empty())
      {
         cout<<"fanout ID :";
         for(int i = 0; i<fanout.size(); i++)
            cout<< fanout[i]->getID()<<' ';
         cout<<endl;
      }
   }
   
protected:

   string Type;            //Type of a gate
   int ID;                 //This inplies the fanout wire number
   bool Value;             //This suggests the value of the output.   
   vector<Gate*> fanin;    //This suggests the fanin  list providing pointers to gates.
   vector<Gate*> fanout;   //This suggests the fanout list providing pointers to gates.
};


#define GateClass(T)             \
class T: public Gate             \
{                                \
public:                          \
   T(int);                       \
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