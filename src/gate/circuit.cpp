#include <iostream>
#include "CirMgr.h"
using namespace std;

Circuit::Circuit()
{     
   const_list.push_back(new Const(0, "1'b0"));
   const_list.push_back(new Const(1, "1'b1"));
   const_list[1]->setValue(true);

   gate_list.push_back(const_list[0]);
   gate_list.push_back(const_list[1]);


   name_match.insert(pair<string, Gate*>("1'b0", const_list[0] ));
   name_match.insert(pair<string, Gate*>("1'b1", const_list[1] ));
}

Circuit::~Circuit()
{
   for(int i=0,size=gate_list.size();i<size;i++)
      delete gate_list[i];
}

Gate*
Circuit::getGate(unsigned int id)
{
   if( id < gate_list.size())
      return gate_list[id];
   else
      return 0;
}

void
Circuit::printDFS(Gate* g, int level)
{   
   for(int i=0;i<level;i++)
      cout<<"  ";
   cout<<'['<<g->getType()<<"] "<<g->getID();
   if(g->getName()!="")
      cout<<'('<<g->getName()<<')';

   vector<Gate*>& list=g->fanin_get();
   int size = list.size();
 
   for(int i=0;i<size;i++)
   {
      cout<<' '<<list[i]->getID();
      if(list[i]->getFlag())
         cout<<'*';
   }
   
   cout<<endl;

   for(int i=0;i<size;i++)
   {
      if(!list[i]->getFlag())
         printDFS(list[i], level+1);
   }

   g->setFlag(true);
}


void
Circuit::traceBack(Gate* g, vector<vector<pair<string, bool> > > & sequence, int & No, string OutputName, bool & x_existence)
{   
	cout<<"No: "<<No<<endl;
	/*
	for(int i = 0; i < sequence[No].size(); i++){		
			cout<<sequence[No][i].second;
	}
	*/
	cout<<'['<<g->getType()<<"] "<<g->getID();
	if(g->getName()!=""){
		cout<<'('<<g->getName()<<')';
	}
	cout<<endl<<endl;
	
	
	if(g->getType() == "Input"){
		for(int i = 0; i < sequence[No].size(); i++){
			sequence[No][i].first = g->getName();
		}
		
		return;
	}
	else if(g->getType() == "Output"){
				
		vector<Gate*>& list=g->fanin_get();
		vector<Gate*>& list2=g->fanout_get();
		int size = list2.size();
		if(size > 0){
			
			if(OutputName == g->getName()){
				vector<pair<string, bool> > branch;
				sequence.push_back(branch);
				traceBack(list[0], sequence, No, OutputName, x_existence);
			}
			else{
				traceBack(list[0], sequence, No, OutputName, x_existence);
			}
			
		}
		else{
			vector<pair<string, bool> > branch;
			sequence.push_back(branch);
			traceBack(list[0], sequence, No, OutputName, x_existence);
		}
		g->setFlag(true);
			
	}
	else{
		pair<string, bool> p0("", 0);
		pair<string, bool> p1("", 1);
		if(g->getType() == "AndGate"){
			
			sequence[No].push_back(p1);	
			
			vector<Gate*>& list=g->fanin_get();
			int size = list.size();
			int currentSize = sequence[No].size();
			for(int i=0;i<size;i++)
			{			
					if(i == 0){
						traceBack(list[i], sequence, No, OutputName, x_existence);
					}
					else{
						vector<pair<string, bool> > branch;
						for(int j = 0; j<currentSize; j++){
							pair<string, bool> temp(sequence[No][j]);
							branch.push_back(temp);
						}
						sequence.push_back(branch);
						No++;
						traceBack(list[i], sequence, No, OutputName, x_existence);						
					}					
			}			
		}
		else if(g->getType() == "NandGate"){
			if(sequence[No].size()!=0){
				if(!sequence[No][sequence[No].size()-1].second){
					sequence[No].pop_back();
					sequence[No].push_back(p1);
				}
				else{
					sequence[No].push_back(p0);
					sequence[No].push_back(p1);
				}
			}
			else{
				sequence[No].push_back(p0);
				sequence[No].push_back(p1);
			}
			
			
			vector<Gate*>& list=g->fanin_get();
			int size = list.size();
			int currentSize = sequence[No].size();
			for(int i=0;i<size;i++)
			{			
					if(i == 0){
						traceBack(list[i], sequence, No, OutputName, x_existence);
					}
					else{
						vector<pair<string, bool> > branch;
						for(int j = 0; j<currentSize; j++){
							pair<string, bool> temp(sequence[No][j]);
							branch.push_back(temp);
						}
						sequence.push_back(branch);
						No++;
						traceBack(list[i], sequence, No, OutputName, x_existence);						
					}					
			}
			
		}
		else if(g->getType() == "OrGate"){
			if(sequence[No].size()!=0){
				if(!sequence[No][sequence[No].size()-1].second){
					sequence[No].pop_back();
					sequence[No].push_back(p1);
					sequence[No].push_back(p0);
				}
				else{
					sequence[No].push_back(p0);
					sequence[No].push_back(p1);
					sequence[No].push_back(p0);
				}
			}
			else{
				sequence[No].push_back(p0);
				sequence[No].push_back(p1);
				sequence[No].push_back(p0);
			}
			
			vector<Gate*>& list=g->fanin_get();
			int size = list.size();
			int currentSize = sequence[No].size();
			for(int i=0;i<size;i++)
			{
				
					if(i == 0){
						traceBack(list[i], sequence, No, OutputName, x_existence);
						//cout<<"No: "<<No<<endl;
					}
					else{
						vector<pair<string, bool> > branch;
						for(int j = 0; j<currentSize; j++){
							pair<string, bool> temp(sequence[No][j]);
							branch.push_back(temp);
						}
						sequence.push_back(branch);
						No++;
						traceBack(list[i], sequence, No, OutputName, x_existence);
						//cout<<"No: "<<No<<endl;
					}
					
				
					
			}
			
		}
		else if(g->getType() == "NorGate"){
			sequence[No].push_back(p1);
			sequence[No].push_back(p0);
	
		}
		
		else if(g->getType() == "XorGate"){
			x_existence = 1;
			if(sequence[No].size()!=0){
				if(!sequence[No][sequence[No].size()-1].second){
					sequence[No].pop_back();
					sequence[No].push_back(p1);
					sequence[No].push_back(p0);
					sequence[No].push_back(p1);
				}
				else{
					sequence[No].push_back(p0);
					sequence[No].push_back(p1);
					sequence[No].push_back(p0);
					sequence[No].push_back(p1);
				}
			}
			else{
				sequence[No].push_back(p0);
				sequence[No].push_back(p1);
				sequence[No].push_back(p0);
				sequence[No].push_back(p1);
			}
			vector<Gate*>& list=g->fanin_get();
			int size = list.size();
			int currentSize = sequence[No].size();
			for(int i=0;i<size;i++)
			{
					if(i == 0){
						traceBack(list[i], sequence, No, OutputName, x_existence);
						
						vector<pair<string, bool> > branch;
						for(int j = 0; j<currentSize; j++){
							pair<string, bool> temp(sequence[No][j]);
							branch.push_back(temp);
						}
						branch.push_back(p0);
						sequence.push_back(branch);
						No++;
						traceBack(list[i], sequence, No, OutputName, x_existence);
					}
					else{
						vector<pair<string, bool> > branch;
						for(int j = 0; j<currentSize; j++){
							pair<string, bool> temp(sequence[No][j]);
							branch.push_back(temp);
						}
						sequence.push_back(branch);
						No++;
						traceBack(list[i], sequence, No, OutputName, x_existence);
						
						branch.push_back(p0);
						sequence.push_back(branch);
						No++;
						traceBack(list[i], sequence, No, OutputName, x_existence);
						//cout<<"No: "<<No<<endl;
					}
							
			}
			
		}
		else if(g->getType() == "XnorGate"){
			x_existence = 1;
			sequence[No].push_back(p1);
			sequence[No].push_back(p0);
			sequence[No].push_back(p1);
			
		}
			
		else if(g->getType() == "NotGate"){
			if(sequence[No].size()!=0){
				if(!sequence[No][sequence[No].size()-1].second){
					sequence[No].pop_back();
					
				}
				else{
					sequence[No].push_back(p0);
					
				}
			}
			else{
				sequence[No].push_back(p0);
				
			}
					
			vector<Gate*>& list=g->fanin_get();
			traceBack(list[0], sequence, No, OutputName, x_existence);
			
		
		}
		else{
			cout<<"error!!!"<<endl;
		}
	}
}
int 
Circuit::name2index(string s){
	for(int i = 0; i < in_list.size(); i++){
		if(in_list[i]->getName()== s){
			return i;
			break;
		}
	}
}
void
Circuit::clearFlag()
{
   for(int i=0,size=gate_list.size();i<size;i++)
      gate_list[i]->setFlag(false);
}

void Circuit::removeList( vector<Gate*>& list)
{
   Gate* next_g,* prev_g,* this_g;
   for(size_t i = 0, sizel=list.size(); i<sizel; ++i)
   {
      this_g = list[i];      
      if(this_g->fanin_get().empty() || this_g->fanout_get().empty()) continue;

      vector<Gate*>& this_fanout = this_g->fanout_get();
      prev_g = this_g->fanin_get()[0];      
      vector<Gate*>& prev_fanout = prev_g->fanout_get();

      for(size_t j = 0; j<prev_fanout.size();)
      {
         if(prev_fanout[j]==this_g)
            prev_fanout.erase(prev_fanout.begin()+j);
         else j++;
      }
      for(size_t l = 0,sizeto=this_fanout.size();l<sizeto; ++l)
               prev_g->fanout_add(this_fanout[l]);

      for(size_t j = 0, sizeto=this_fanout.size();j<sizeto; ++j)
      {
         next_g = this_fanout[j];
         vector<Gate*>& next_fanin = next_g->fanin_get();
         for(size_t k = 0; k<next_fanin.size();)
         {
            if(this_g == next_fanin[k])
            {
               next_fanin.erase(next_fanin.begin()+k);
               next_g->fanin_add(prev_g);
            }
            else
               ++k;
         }
      }
   }
   for(size_t i = 0; i < list.size(); ++i)
      delete list[i];
   list.clear();
}

void
Circuit::simulate()
{
   int size=out_list.size();
   for(int i=0; i<size; ++i )
   {
      out_list[i]->compute_Value();
      out_list[i]->setHistory();
   }
}

void
Circuit::his_push()
{
   int size=out_list.size();
   for(int i=0; i<size; ++i )
      out_list[i]->setHistorys();
}