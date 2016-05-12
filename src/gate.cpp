#include <iostream>
#include <vector>
#include <string>
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
	void setValue(int i){Value = i;};
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
	int Value;	//This suggests the flag which indicates that whether the path to primary inputs of a gate have been traced.
	vector<Gate*> fanin;	//This suggests the fanin list providing pointers to gates.
	vector<Gate*> fanout;	//This suggests the fanout list providing pointers to gates.
};

