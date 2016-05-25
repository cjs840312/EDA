#include <iostream>
#include <cassert>
#include "gate_def.h"
using namespace std;

//------------------------------------------------------------------------------
//    Gate
//------------------------------------------------------------------------------

void
Gate::print_gate()
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


//------------------------------------------------------------------------------
//    Input
//------------------------------------------------------------------------------

Input::Input(int id = 0, string name = ""):Gate( "Input" , id, name ) {}

bool Input::fanin_add(Gate* g) { return false; }

bool 
Input::fanout_add(Gate* g)
{
	fanout.push_back(g);
	return true;
}

bool Input::compute_Value() { return Value ; }

//------------------------------------------------------------------------------
//    Output
//------------------------------------------------------------------------------


Output::Output(int id = 0, string name = ""):Gate( "Output" , id, name ) {}

bool
Output::fanin_add(Gate* g)
{
	if(fanin.size()>=1)
	  		return false;
   else
      fanin.push_back(g);
  	
  	return true;
}

bool Output::fanout_add(Gate* g) { return false; }

bool
Output::compute_Value()
{
	assert(!fanin.empty()) ;

	Value = fanin[0]->getValue();
	return Value;
}

//------------------------------------------------------------------------------
//    AndGate
//------------------------------------------------------------------------------

AndGate::AndGate(int id = 0, string name = ""):Gate( "AndGate" , id, name ) {}

bool
AndGate::fanin_add(Gate* g)
{
	fanin.push_back(g);
	return true;
}

bool
AndGate::fanout_add(Gate* g)
{
   fanout.push_back(g);
   return true;
}

bool
AndGate::compute_Value()
{ 
	int size=fanin.size();
	assert(size >= 2);

	Value =true;
	for(int i=0 ; i < size ; i++)
		Value = Value && fanin[i]->getValue();

   return Value;
}

//------------------------------------------------------------------------------
//    NandGate
//------------------------------------------------------------------------------

NandGate::NandGate(int id = 0, string name = ""):Gate( "NandGate" , id, name ) {}

bool
NandGate::fanin_add(Gate* g)
{
	fanin.push_back(g);
	return true;
}

bool
NandGate::fanout_add(Gate* g)
{
	fanout.push_back(g);
   return true;
}

bool
NandGate::compute_Value()
{
	int size=fanin.size();
	assert(size >= 2);

	Value = true;
	for(int i=0 ; i < size ; i++)
		Value = Value && fanin[i]->getValue();
	Value = !Value;

   return Value;
}

//------------------------------------------------------------------------------
//    OrGate
//------------------------------------------------------------------------------

OrGate::OrGate(int id = 0, string name = ""):Gate( "OrGate" , id, name ) {}

bool
OrGate::fanin_add(Gate* g)
{
   fanin.push_back(g);
	return true;
}

bool
OrGate::fanout_add(Gate* g)
{
	fanout.push_back(g);
   return true;
}

bool
OrGate::compute_Value()
{
	int size=fanin.size();
	assert(size >= 2 );

	for(int i=0 ; i < size ; i++)
		Value = Value || fanin[i]->getValue();

   return Value;
}

//------------------------------------------------------------------------------
//    NorGate
//------------------------------------------------------------------------------

NorGate::NorGate(int id = 0, string name = ""):Gate( "NorGate" , id, name ) {}

bool
NorGate::fanin_add(Gate* g)
{
   fanin.push_back(g);
	return true;
}

bool
NorGate::fanout_add(Gate* g)
{
	fanout.push_back(g);
   return true;
}

bool
NorGate::compute_Value()
{
	int size=fanin.size();
	assert(size >=2);

	Value = false;
	for(int i=0 ; i < size ; i++)
		Value = Value || fanin[i]->getValue();

	Value = !Value;
   return Value;
}

//------------------------------------------------------------------------------
//    XorGate
//------------------------------------------------------------------------------

XorGate::XorGate(int id = 0, string name = ""):Gate( "XorGate" , id, name ) {}

bool
XorGate::fanin_add(Gate* g)
{
	if(fanin.size() >= 2)
 		return false;
	else
      fanin.push_back(g);

    return true;
}

bool
XorGate::fanout_add(Gate* g)
{
	fanout.push_back(g);
   return true;
}

bool
XorGate::compute_Value()
{
	int size=fanin.size();
	assert (size == 2);

	Value = fanin[0]->getValue() ^ fanin[1]->getValue();

   return Value;
}

//------------------------------------------------------------------------------
//    XnorGate
//------------------------------------------------------------------------------

XnorGate::XnorGate(int id = 0, string name = ""):Gate( "XnorGate" , id, name ) {}

bool
XnorGate::fanin_add(Gate* g)
{
	if(fanin.size() >= 2)
 		return false;
	else
      fanin.push_back(g);

   return true;
}

bool
XnorGate::fanout_add(Gate* g)
{
	fanout.push_back(g);
   return true;
}

bool
XnorGate::compute_Value()
{
	int size=fanin.size();
	assert(size == 2);

	Value = fanin[0]->getValue() ^ fanin[1]->getValue();

	Value = !Value;
   return Value;
}

//------------------------------------------------------------------------------
//    NotGate
//------------------------------------------------------------------------------

NotGate::NotGate(int id = 0, string name = ""):Gate( "NotGate" , id, name ) {}

bool
NotGate::fanin_add(Gate* g)
{
	if(fanin.size() >=1)
 		return false;
	else
      fanin.push_back(g);

   return true;
}

bool
NotGate::fanout_add(Gate* g)
{
 	fanout.push_back(g);
   return true;
}

bool
NotGate::compute_Value()
{ 
	int size=fanin.size();
	assert(size == 1);

	Value = !fanin[0]->getValue();

   return Value;
}

//------------------------------------------------------------------------------
//    Wire
//------------------------------------------------------------------------------

Wire::Wire(int id = 0, string name = ""):Gate( "Wire" , id, name ) {}

bool
Wire::fanin_add(Gate* g) 
{
	if(fanin.size()>=1)
		return false;

   fanin.push_back(g);
   return true;
}

bool 
Wire::fanout_add(Gate* g)
{
	fanout.push_back(g);
	return true;
}

bool 
Wire::compute_Value()
{
	assert(fanin.size()==1);
  	return  fanin[0]->getValue();
}

//------------------------------------------------------------------------------
//    Buffer
//------------------------------------------------------------------------------

Buffer::Buffer(int id = 0, string name = ""):Gate( "Buffer" , id, name ) {}

bool
Buffer::fanin_add(Gate* g) 
{
	if(fanin.size()>=1)
		return false;
	
   fanin.push_back(g);
   return true;
}

bool 
Buffer::fanout_add(Gate* g)
{
	fanout.push_back(g);
	return true;
}

bool
Buffer::compute_Value()
{
	assert(fanin.size()==1);
  	return  fanin[0]->getValue();
}