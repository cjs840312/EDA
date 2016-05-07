#include<iostream>
#include"gate.cpp"
using namespace std;

int main(){
	Gate _primary_input1;
	Gate _primary_input2;
	Gate _and;
	Gate _primary_output;
	
	_primary_input1.setType("primary input");
	_primary_input1.setID(1);
	_primary_input1.setValue(0);
	_primary_input1.fanout_add(&_and);
	
	_primary_input2.setType("primary input");
	_primary_input2.setID(2);
	_primary_input2.setValue(0);
	_primary_input2.fanout_add(&_and);
	
	_and.setType("and");
	_and.setID(3);
	_and.setValue(0);
	_and.fanin_add(&_primary_input1);
	_and.fanin_add(&_primary_input2);
	_and.fanout_add(&_primary_output);
	
	_primary_output.setType("primary output");
	_primary_output.setID(0);
	_primary_output.setValue(0);
	_primary_output.fanin_add(&_and);
	
	_and.print_gate();
	
	
	return 0;
	
	
}
