#include <iostream>
#include "CirMgr.h"
using namespace std;
//#define REMOVEWIRE_TEST
//#define BUILD_TEST
//#define DEBUG
//#define DEBUG_STR2VAR


Gate*
Circuit::getGate(unsigned int id)
{
   if( id < gate_list.size())
      return gate_list[id];
   else
      return 0;
}


void
Circuit::buildgate_list()
{
//   vector<Gate*> gate_list;
   int gatecount = 0;
   Gate* g;
   gate_list.clear();
   if(in_list.size() != 0){
   	for(size_t i = 0; i < in_list.size(); ++i){
		g = in_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(out_list.size() != 0){
   	for(size_t i = 0; i < out_list.size(); ++i){
		g = out_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(And_list.size() != 0){
   	for(size_t i = 0; i < And_list.size(); ++i){
		g = And_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Nand_list.size() != 0){
   	for(size_t i = 0; i < Nand_list.size(); ++i){
		g = Nand_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Or_list.size() != 0){
   	for(size_t i = 0; i < Or_list.size(); ++i){
		g = Or_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Nor_list.size() != 0){
   	for(size_t i = 0; i < Nor_list.size(); ++i){
		g = Nor_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Xor_list.size() != 0){
   	for(size_t i = 0; i < Xor_list.size(); ++i){
		g = Xor_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Xnor_list.size() != 0){
   	for(size_t i = 0; i < Xnor_list.size(); ++i){
		g = Xnor_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Not_list.size() != 0){
   	for(size_t i = 0; i < Not_list.size(); ++i){
		g = Not_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Buff_list.size() != 0){
   	for(size_t i = 0; i < Buff_list.size(); ++i){
		g = Buff_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
   if(Wire_list.size() != 0){
   	for(size_t i = 0; i < Wire_list.size(); ++i){
		g = Wire_list[i];
		g->setID(gatecount++);
		gate_list.push_back(g);
	}
   }
#ifdef BUILD_TEST
	cout << "buildgate_list()..." << endl;
	cout << "gatecount: " << gatecount << "\tgate_list.size(): " << gate_list.size() << endl;
	for(size_t i = 0; i < gate_list.size(); ++i){
		gate_list[i]->print_gate();
	}
	cout << endl;

#endif


}

void Circuit::removeWire() 		// there are some bugs, but I don't know where (eric~~ help)
{
#ifdef REMOVEWIRE_TEST
	cout << "before removeWire()..." << endl;
	for(size_t i = 0; i < Wire_list.size(); ++i){
		Wire_list[i]->print_gate();
	}
	cout << endl;

#endif
	if(Wire_list.size() == 0)return;
	Gate* next_g,* prev_g,* this_g;
	vector<Gate*> this_fanin, this_fanout;
	vector<Gate*> next_fanin, prev_fanout;
	for(size_t i = 0; i < Wire_list.size(); ++i){
		this_g = Wire_list[i];
		this_fanin = this_g->fanin_get();
		this_fanout = this_g->fanout_get();
		for(size_t j = 0; j < this_fanin.size(); ++j){
			prev_g = this_fanin[j];
			prev_fanout = prev_g->fanout_get();
			for(size_t k = 0; k < prev_fanout.size(); ++k){
				if(this_g == prev_fanout[k]){
					prev_fanout.erase(prev_fanout.begin()+k);
					for(size_t l = 0; l < this_fanout.size(); ++l){
						prev_g->fanout_add(this_fanout[l]);
					}
				}
			}
		}
		for(size_t j = 0; j < this_fanout.size(); ++j){
			next_g = this_fanout[j];
			next_fanin = next_g->fanin_get();
			for(size_t k = 0; k < next_fanin.size(); ++k){
				if(this_g == next_fanin[k]){
					next_fanin.erase(next_fanin.begin()+k);
					for(size_t l = 0; l < this_fanin.size(); ++l){
						next_g->fanin_add(this_fanin[l]);
					}
				}
			}
		}


	}
	for(size_t i = 0; i < Wire_list.size(); ++i){		// is this right??? (eric)
		delete Wire_list[i];
	}
	gate_list.resize(gate_list.size()-Wire_list.size());
	
	Wire_list.clear();

#ifdef REMOVEWIRE_TEST
	cout << "after removeWire()..." << endl;
	for(size_t i = 0; i < Wire_list.size(); ++i){
		Wire_list[i]->print_gate();
	}
	cout << endl;

#endif


}


bool
CirMgr::parse( ifstream& cirfile, int num)
{
   Circuit& cir = num==1? c1:c2;

   // TODO ...
 	// parse module
	enum {Module, Input, Output, Wires, Gates, Endmodule} state = Module;
	string buff;
	// get module
	while(cirfile.good()){
#ifdef DEBUG
	cout << "getline" << endl;
#endif		
		getline(cirfile, buff);
		switch(state){
			case Module:
#ifdef DEBUG
	cout << "parsing module" << endl;
#endif		
				if(buff.substr(0,6) != "module") {
					//cerr << "parsing error!!" << endl;
				}
				else{
					while(buff[buff.length()-1] != ';'){
						string buff1;
						getline(cirfile, buff1);
						buff += buff1;
					}
					state = Input;
				}
#ifdef DEBUG
	cout << "parsing module success" << endl;
#endif
			break;
			
			case Input:
#ifdef DEBUG
	cout << "parsing input" << endl;
#endif		
				if(buff.substr(0,5) != "input"){
					cerr << "parsing input error!!" << endl;
					return false;
				}else {
					while(buff[buff.length()-1] != ';'){
						string buff1;
						getline(cirfile, buff1);
						buff += buff1;
					}
					Str2Vars(buff, cir.in_list, cir);
					state = Output;
				}
#ifdef DEBUG
	cout << "parsing input success" << endl;
#endif
			break;

			case Output:
#ifdef DEBUG
	cout << "parsing output" << endl;
#endif
				if(buff.substr(0,6) != "output"){
					cerr << "parsing output error!!" << endl;
					return false;
				}else{
					while(buff[buff.length()-1] != ';'){
						string buff1;
						getline(cirfile, buff1);
						buff += buff1;
					}
					Str2Vars(buff, cir.out_list, cir);
					state = Wires;
				}
#ifdef DEBUG
	cout << "parsing output success" << endl;
#endif
			break;

			case Wires:
#ifdef DEBUG
	cout << "parsing wire" << endl;
#endif
				if(    buff.substr(0,3) == "buf"  || buff.substr(0,3) == "not" || buff.substr(0,3) == "and"
					|| buff.substr(0,4) == "nand" || buff.substr(0,2) == "or"  || buff.substr(0,3) == "nor"
					|| buff.substr(0,3) == "xor"  || buff.substr(0,4) == "xnor"){
					state = Gates;
				}else{
					while(buff[buff.length()-1] != ';'){
						string buff1;
						getline(cirfile, buff1);
						buff += buff1;
					}
					Str2Vars( buff, cir.Wire_list, cir);
					state = Gates;
#ifdef DEBUG
	cout << "parsing wire success" << endl;
#endif
					break;
				}
#ifdef DEBUG
	cout << "parsing gates" << endl;
#endif
			case Gates:
				if(buff.substr(0,4) == "wire"){
					state = Wires; 
					break;
				}else if(buff.substr(0,9) == "endmodule"){
					state = Endmodule;
					break;
				}else{
					if(buff.substr(0,3) == "buf"){
						Gate* gate = new Buffer(0, "");
						Str2Vars(buff, cir.Buff_list, gate, cir);
					}else if(buff.substr(0,3) == "not"){
						Gate* gate = new NotGate(0, "");
						Str2Vars(buff, cir.Not_list, gate, cir);
					}else if(buff.substr(0,3) == "and"){
						Gate* gate = new AndGate(0, "");
						Str2Vars(buff, cir.And_list, gate, cir);
					}else if(buff.substr(0,4) == "nand"){
						Gate* gate = new NandGate(0, "");
						Str2Vars(buff, cir.Nand_list, gate, cir);
					}else if(buff.substr(0,2) == "or"){
						Gate* gate = new OrGate(0, "");
						Str2Vars(buff, cir.Or_list, gate, cir);
					}else if(buff.substr(0,3) == "nor"){
						Gate* gate = new NorGate(0, "");
						Str2Vars(buff, cir.Nor_list, gate, cir);
					}else if(buff.substr(0,3) == "xor"){
						Gate* gate = new XorGate(0, "");
						Str2Vars(buff, cir.Xor_list, gate, cir);
					}else if(buff.substr(0,4) == "xnor"){
						Gate* gate = new XnorGate(0, "");
						Str2Vars(buff, cir.Xnor_list, gate, cir);
					}else{
						cerr << "parssing gates error!!" << endl;
						cout << buff << endl;
					}
				}
			break;

			case Endmodule:
			break;
			
			default:
				cerr << "should not have happened!!" << endl;
			break;



		}


	}
	cirfile.close();

	cir.buildgate_list();
//	cir.removeWire();



   return true;
}



void CirMgr::Str2Vars(string& buff, vector<Gate*>& gate_list, Circuit& cir){
	bool iswire = true, isinput = true;
	if(buff.substr(0,4) == "wire"){buff = buff.substr(4);}
	else if(buff.substr(0,5) == "input"){buff = buff.substr(5); iswire= false;}
	else if(buff.substr(0,6) == "output"){buff = buff.substr(6); iswire = false; isinput = false;}
	else {cerr<< "Str2Vars parsing error!!" << endl; return;}
	Gate* inout_gate;
	size_t varbegin, varlen;
	string var;
	inout_gate = new Input(0, "1'b0");
	cir.name_match.insert(pair<string, Gate*>("1'b0", inout_gate));
	inout_gate = new Input(1, "1'b1");
	cir.name_match.insert(pair<string, Gate*>("1'b1", inout_gate));

	while(buff.length()!=0){
		// get 1 variable
#ifdef DEBUG_STR2VAR
	cout << "parsing buff: " << buff << "\nbuff.length()= " << buff.length()<< endl;
#endif
		
		varbegin = 0; varlen = 0;
		var = "";
		varbegin = buff.find_first_not_of(" ,;");
		varlen = buff.find_first_of(" ,;", varbegin) - varbegin;
		if(varlen == 0) break;
		else{
			var = buff.substr(varbegin, varlen) ;
			if(iswire) inout_gate = new Wire(0, var);
			else if(isinput) inout_gate = new Input(0, var);
			else inout_gate = new Output(0, var);
			gate_list.push_back(inout_gate);
			cir.name_match.insert(pair<string, Gate*>(var, inout_gate));
			buff = buff.substr(varbegin+varlen);
		}
	}
	return;
}
/*
void CirMgr::Str2Vars(string& buff, vector<Gate*>& gate_list){
	if(buff.substr(0,4) == "wire"){buff = buff.substr(4);}
	else {cerr<< "Str2Vars parsing wire error!!" << endl; return;}
	Gate* wire_gate;
	size_t varbegin, varlen;
	string var;

	while(buff.length()!=0){
		// get 1 variable
#ifdef DEBUG
	cout << "parsing buff: " << buff << "\nbuff.length()= " << buff.length()<< endl;
#endif
		varbegin = 0; varlen = 0;
		var = "";
		varbegin = buff.find_first_not_of(" ,;");
		varlen = buff.find_first_of(" ,;", varbegin) - varbegin;
		if(varlen == 0) break;
		else{
			var = buff.substr(varbegin, varlen) ;
			wire_gate = new Wire(0, var);
			gate_list.push_back(wire_gate);
			cir.name_match.insert(pair<string, Gate*>(var, wire_gate));
			buff = buff.substr(varbegin+varlen);
		}
	}
	return;
	
}
*/

void CirMgr::Str2Vars(string& buff, vector<Gate*>& gate_list,  Gate* gate, Circuit& cir){
	//get gate
	Gate* link_gate;
	map<string, Gate*>::iterator it;
	size_t buffbegin = 0, bufflen = 0;
	buffbegin = buff.find_first_of("(") + 1;
	bufflen = buff.find_first_of(")") - buffbegin;
	if(bufflen == 0){
		cerr << "parsing error: " << buff << endl;
		return;
	}else{
		buff = buff.substr(buffbegin, bufflen)+' ';
	}
	// get fanout(wire)
	size_t varbegin = 0, varlen = 0;
	string var = "";
	varbegin = buff.find_first_not_of(" ,;");
	varlen = buff.find_first_of(" ,;", varbegin) - varbegin;
	if(varlen == 0){
		cerr << "parsing error: " << buff << endl;
		return;
	}else{
		var = buff.substr(varbegin, varlen) ;
		link_gate = cir.name_match.find(var)->second;
		link_gate->fanin_add(gate);
		gate->fanout_add(link_gate);
		buff = buff.substr(varbegin+varlen);
	}

	// get fanins(wire)
	while(buff.length()!=0){
		// get 1 variable
#ifdef DEBUG_STR2VAR
	cout << "parsing buff: " << buff << "\nbuff.length()= " << buff.length()<< endl;
#endif
		varbegin = 0; varlen = 0;
		var = "";
		varbegin = buff.find_first_not_of(" ,;");
		varlen = buff.find_first_of(" ,;", varbegin) - varbegin;
		if(varlen == 0) break;
		else{
			var = buff.substr(varbegin, varlen);
			link_gate = cir.name_match.find(var)->second;
			link_gate->fanout_add(gate);
			gate->fanin_add(link_gate);
			buff = buff.substr(varbegin+varlen);
		}
	}
	gate_list.push_back(gate);

}
