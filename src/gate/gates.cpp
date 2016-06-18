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

Input::Input(int id, string name):Gate( "Input" , id, name ) {}

bool Input::fanin_add(Gate* g)
{
	if(fanin.size()>=1)
	  		return false;
   else
      fanin.push_back(g);
  	
  	return true;
}

bool Input::compute_Value()
{
	if( !Flag && !fanin.empty())
	{
		Value = fanin[0]->compute_Value();
		Flag = true;
	}
	return Value ; 
}

void Input::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;
   if(!fanin.empty())
   {
      fanin[0]->sat_mod(satsolver);
      vari=fanin[0]->getVar();
   }
   else
   {
      vari=satsolver.newVar();
   }

   Flag=true;
}
//------------------------------------------------------------------------------
//    Const
//------------------------------------------------------------------------------

Const::Const(int id, string name):Gate( "Const" , id, name ) {}

bool Const::fanin_add(Gate* g) { return false; }

bool Const::compute_Value() { return Value ; }

void Const::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   vari=satsolver.newVar();
   if(Value)
      satsolver.addConst1CNF(vari);
   else
      satsolver.addConst0CNF(vari);
   Flag=true;
}

//------------------------------------------------------------------------------
//    Output
//------------------------------------------------------------------------------


Output::Output(int id, string name):Gate( "Output" , id, name ) {}

bool
Output::fanin_add(Gate* g)
{
	if(fanin.size()>=1)
	  		return false;
  else
      fanin.push_back(g);
  	
  	return true;
}

bool
Output::compute_Value()
{
	assert(!fanin.empty()) ;

	if(!Flag)	
	{
		Value = fanin[0]->compute_Value();
		Flag = true;
	}

	return Value;
}

void Output::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   fanin[0]->sat_mod(satsolver);
   vari=fanin[0]->getVar();
   Flag=true;
}

//------------------------------------------------------------------------------
//    AndGate
//------------------------------------------------------------------------------

AndGate::AndGate(int id, string name):Gate( "AndGate" , id, name ) {}

bool
AndGate::fanin_add(Gate* g)
{
	fanin.push_back(g);
	return true;
}

bool
AndGate::compute_Value()
{ 
	int size=fanin.size();
	assert(size >= 2);


	if(Flag)
		return Value;

	Value =true;
	for(int i=0 ; i < size ; i++)
	{
		Value = Value && fanin[i]->compute_Value();
	}

	Flag = true;
    return Value;
}

void AndGate::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;
   vari=satsolver.newVar();
   vector<Var> vi;

   for(int i=0,size=fanin.size();i<size;i++)
   {
      fanin[i]->sat_mod(satsolver);
      vi.push_back(fanin[i]->getVar());
   }

   satsolver.addAndCNF(vari,vi);
   
   Flag=true;
}

//------------------------------------------------------------------------------
//    NandGate
//------------------------------------------------------------------------------

NandGate::NandGate(int id, string name):Gate( "NandGate" , id, name ) {}

bool
NandGate::fanin_add(Gate* g)
{
	fanin.push_back(g);
	return true;
}

bool
NandGate::compute_Value()
{
	int size=fanin.size();
	assert(size >= 2);

	if(Flag)
		return Value;

	Value = true;
	for(int i=0 ; i < size ; i++)
		Value = Value && fanin[i]->compute_Value();
	Value = !Value;

	Flag = true;
    return Value;
}

void NandGate::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   vari=satsolver.newVar();
   vector<Var> vi;
   for(int i=0,size=fanin.size();i<size;i++)
   {
      fanin[i]->sat_mod(satsolver);
      vi.push_back(fanin[i]->getVar());
   }
   satsolver.addNandCNF(vari,vi);
   Flag=true;
}
//------------------------------------------------------------------------------
//    OrGate
//------------------------------------------------------------------------------

OrGate::OrGate(int id, string name):Gate( "OrGate" , id, name ) {}

bool
OrGate::fanin_add(Gate* g)
{
   fanin.push_back(g);
	return true;
}

bool
OrGate::compute_Value()
{
	int size=fanin.size();
	assert(size >= 2 );

	if(Flag)
		return Value;

	Value = false;
	for(int i=0 ; i < size ; i++)
		Value = Value || fanin[i]->compute_Value();
	
	Flag = true;
    return Value;
}

void OrGate::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   vari=satsolver.newVar();
   vector<Var> vi;
   for(int i=0,size=fanin.size();i<size;i++)
   {
      fanin[i]->sat_mod(satsolver);
      vi.push_back(fanin[i]->getVar());
   }
   satsolver.addOrCNF(vari,vi);
   Flag=true;
}

//------------------------------------------------------------------------------
//    NorGate
//------------------------------------------------------------------------------

NorGate::NorGate(int id, string name):Gate( "NorGate" , id, name ) {}

bool
NorGate::fanin_add(Gate* g)
{
   fanin.push_back(g);
	return true;
}

bool
NorGate::compute_Value()
{
	int size=fanin.size();
	assert(size >=2);

	if(Flag)
		return Value;

	Value = false;
	for(int i=0 ; i < size ; i++)
		Value = Value || fanin[i]->compute_Value();

	Value = !Value;

	Flag = true;
   	return Value;
}

void NorGate::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   vari=satsolver.newVar();
   vector<Var> vi;
   for(int i=0,size=fanin.size();i<size;i++)
   {
      fanin[i]->sat_mod(satsolver);
      vi.push_back(fanin[i]->getVar());
   }
   satsolver.addNorCNF(vari,vi);
   Flag=true;
}

//------------------------------------------------------------------------------
//    XorGate
//------------------------------------------------------------------------------

XorGate::XorGate(int id, string name):Gate( "XorGate" , id, name ) {}

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
XorGate::compute_Value()
{
	int size=fanin.size();
	assert (size == 2);

	if(Flag)
		return Value;

	Value = fanin[0]->compute_Value() ^ fanin[1]->compute_Value();

   
	Flag = true;
   return Value;
}

void XorGate::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   vari=satsolver.newVar();
   
   fanin[0]->sat_mod(satsolver);
   fanin[1]->sat_mod(satsolver);

   satsolver.addXorCNF(vari,fanin[0]->getVar(),fanin[1]->getVar());
   Flag=true;
}

//------------------------------------------------------------------------------
//    XnorGate
//------------------------------------------------------------------------------

XnorGate::XnorGate(int id, string name):Gate( "XnorGate" , id, name ) {}

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
XnorGate::compute_Value()
{
	int size=fanin.size();
	assert(size == 2);

	if(Flag)
		return Value;

	Value = fanin[0]->compute_Value() ^ fanin[1]->compute_Value();

	Value = !Value;
	Flag = true;
    return Value;
}

void XnorGate::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   vari=satsolver.newVar();
   
   fanin[0]->sat_mod(satsolver);
   fanin[1]->sat_mod(satsolver);

   satsolver.addXnorCNF(vari,fanin[0]->getVar(),fanin[1]->getVar());
   Flag=true;
}

//------------------------------------------------------------------------------
//    NotGate
//------------------------------------------------------------------------------

NotGate::NotGate(int id, string name):Gate( "NotGate" , id, name ) {}

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
NotGate::compute_Value()
{ 
	int size=fanin.size();
	assert(size == 1);

	if(Flag)
		return Value;

	Value = !(fanin[0]->compute_Value());

	Flag = true;
    return Value;
}

void NotGate::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   vari=satsolver.newVar();
   
   fanin[0]->sat_mod(satsolver);

   satsolver.addNotCNF(vari,fanin[0]->getVar());
   Flag=true;
}

//------------------------------------------------------------------------------
//    Wire
//------------------------------------------------------------------------------

Wire::Wire(int id, string name):Gate( "Wire" , id, name ) {}

bool
Wire::fanin_add(Gate* g) 
{
	if(fanin.size()>=1)
		return false;

   fanin.push_back(g);
   return true;
}

bool 
Wire::compute_Value()
{
	assert(fanin.size()==1);

	if(Flag)
		return Value;

  	Value = fanin[0]->compute_Value();

  	Flag = true;
    return Value;
}

void Wire::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   fanin[0]->sat_mod(satsolver);

   vari=fanin[0]->getVar();
   Flag=true;
}

//------------------------------------------------------------------------------
//    Buffer
//------------------------------------------------------------------------------

Buffer::Buffer(int id, string name):Gate( "Buffer" , id, name ) {}

bool
Buffer::fanin_add(Gate* g) 
{
	if(fanin.size()>=1)
		return false;
	
   fanin.push_back(g);
   return true;
}

bool

Buffer::compute_Value()
{
	assert(fanin.size()==1);
 
	if(Flag)
		return Value;

  	Value = fanin[0]->compute_Value();

  	Flag = true;
    return Value;
}

void Buffer::sat_mod(SatSolver& satsolver)
{
   if(Flag)  return;

   fanin[0]->sat_mod(satsolver);

   vari=fanin[0]->getVar();
   Flag=true;
}