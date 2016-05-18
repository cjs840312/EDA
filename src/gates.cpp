#include <iostream>
#include <vector>
#include<string>
using namespace std;

class Gate{
public:
	Gate(){
		ID = 0;
		Value = 0;
		fanin.clear();
		fanout.clear();	
	}
	void setType(string s){Type = s;}
	void setID(int i){ID = i;}
	void setValue(bool i){Value = i;}
	int getID() {return ID;}
	int getValue() {return Value;}
	void fanin_add(Gate* g){fanin.push_back(g);}
	void fanin_delete(int index){fanin.erase(fanin.begin()+index);}
	int fanin_size() {return fanin.size();}
	Gate* fanin_element(int index){
		if(index >= 0 && index < fanin.size()){
			return fanin.at(index);
		}
		else{
			return NULL;
			cout<<"index: "<<index<<" is not a valid index!"<<endl;
		}
	}
	void fanout_add(Gate* g){fanout.push_back(g);}
	void fanout_delete(int index){fanout.erase(fanout.begin()+index);}
	int fanout_size() {return fanout.size();}
	Gate* fanout_element(int index){
		if(index >= 0 && index < fanout.size()){
			return fanout.at(index);
		}
		else{
			return NULL;
			cout<<"index: "<<index<<" is not a valid index!"<<endl;
		}
	}
	void print_gate(){
		
		cout<<"Type: "<<Type<<endl<<"ID: "<<ID<<endl<<"Value: "<<Value<<endl;
		for(int i = 0; i<fanin.size(); i++){
			cout<<"fanin ID: "<<(*fanin.at(i)).getID()<<endl;
		}
		for(int i = 0; i<fanout.size(); i++){
			cout<<"fanout ID: "<<(*fanout.at(i)).getID()<<endl;
		}		
	}
	
protected:
	string Type;	//Type of a gate
	int ID;		//This inplies the fanout wire number
	bool Value;	//This suggests the value of the output.
	vector<Gate*> fanin;	//This suggests the fanin list providing pointers to gates.
	vector<Gate*> fanout;	//This suggests the fanout list providing pointers to gates.
};

class Input : public Gate{
public:
	Input(){
		Type = "Input";
	}
	void setValue(int i){Value = i;}
	void fanin_add(Gate* g){
		if(fanin.size()>=1){
			cout<<"There is no input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class Output : public Gate{
public:
	Output(){
		Type = "Output";
	}
	void setValue(){
		if(fanin.size()>=1){
			Value = (*fanin.at(0)).getValue();
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	};
	void fanin_add(Gate* g){
		if(fanin.size()>=1){
			cout<<"There is no input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class And2 : public Gate{
public:
	And2(){
		Type = "And2";
	}
	void setValue(){
		if(fanin.size()>=2){
			Value = (*fanin.at(0)).getValue()and(*fanin.at(1)).getValue();
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=2){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class Or2 : public Gate{
public:
	Or2(){
		Type = "Or2";
	}
	void setValue(){
		if(fanin.size()>=2){
			Value = (*fanin.at(0)).getValue()or(*fanin.at(1)).getValue();
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=2){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class And3 : public Gate{
public:
	And3(){
		Type = "And3";
	}
	void setValue(){
		if(fanin.size()>=3){
			Value = (*fanin.at(0)).getValue()and(*fanin.at(1)).getValue()and(*fanin.at(2)).getValue();
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=3){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class Xnor2 : public Gate{
public:
	Xnor2(){
		Type = "Xnor2";
	}
	void setValue(){
		if(fanin.size()>=2){
			Value = ~((*fanin.at(0)).getValue()xor(*fanin.at(1)).getValue());
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=2){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class Nor2 : public Gate{
public:
	Nor2(){
		Type = "Nor2";
	}
	void setValue(){
		if(fanin.size()>=2){
			Value = ~((*fanin.at(0)).getValue()or(*fanin.at(1)).getValue());
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=2){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class Buffer : public Gate{
public:
	Buffer(){
		Type = "Buffer";
	}
	void setValue(){
		if(fanin.size()>=1){
			Value = (*fanin.at(0)).getValue();
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=1){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class Not : public Gate{
public:
	Not(){
		Type = "Not";
	}
	void setValue(){
		if(fanin.size()>=1){
			Value = ~(*fanin.at(0)).getValue();
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=1){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};

class Xor2 : public Gate{
public:
	Xor2(){
		Type = "Xor2";
	}
	void setValue(){
		if(fanin.size()>=2){
			Value = (*fanin.at(0)).getValue()xor(*fanin.at(1)).getValue();
		}
		else{
			cout<<"No fanin to compute Value!!"<<endl;
		}
	}
	void fanin_add(Gate* g){
		if(fanin.size()>=2){
			cout<<"There is no more input port to add this fanin!"<<endl;
		}
		else{
		fanin.push_back(g);
		}
	}
	void fanout_add(Gate* g){
		if(fanout.size()>=1){
			cout<<"There is no more output port to add this fanout!"<<endl;
		}
		else{
			fanout.push_back(g);
		}		
	}
};