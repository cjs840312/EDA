#include<iostream>
#include"gate.cpp"
using namespace std;

int main(){
	
	
	Input _primary_input1;
	Input _primary_input2;
	Xor2 _xor;
	Output _primary_output;
	
	
	_primary_input1.setID(1);
	_primary_input1.setValue(0);
	_primary_input1.fanout_add(&_xor);
	
	
	_primary_input2.setID(2);
	_primary_input2.setValue(1);
	_primary_input2.fanout_add(&_xor);
	
	
	_xor.setID(3);
	_xor.fanin_add(&_primary_input1);
	_xor.fanin_add(&_primary_input2);
	_xor.setValue();
	_xor.fanout_add(&_primary_output);
	
	
	_primary_output.setID(0);	
	_primary_output.fanin_add(&_xor);
	_primary_output.setValue();
	
	_xor.print_gate();
	_primary_output.print_gate();
	
	
	return 0;
	
	
}
