#include <iostream>
#include <cassert>
#include "gate_def.h"
using namespace std;

//------------------------------------------------------------------------------
//    Input
//------------------------------------------------------------------------------

Input::Input(int id):Gate( "Input" , id  ) {}

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


Output::Output(int id):Gate( "Output" , id  ) {}

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

AndGate::AndGate(int id):Gate( "AndGate" , id  ) {}

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

NandGate::NandGate(int id):Gate( "NandGate" , id  ) {}

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

OrGate::OrGate(int id):Gate( "OrGate" , id  ) {}

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

NorGate::NorGate(int id):Gate( "NorGate" , id  ) {}

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

XorGate::XorGate(int id):Gate( "XorGate" , id  ) {}

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

XnorGate::XnorGate(int id):Gate( "XnorGate" , id  ) {}

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

NotGate::NotGate(int id):Gate( "NotGate" , id  ) {}

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

Wire::Wire(int id):Gate( "Wire" , id  ) {}

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

Buffer::Buffer(int id):Gate( "Buffer" , id  ) {}

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