#include <iostream>
#include "CirMgr.h"
#include "../util/help_function.h"
using namespace std;

enum PARSE_STATE
{
	MODULE,
	INPUT,
	OUTPUT,
	WIRE,
	AND,
	NAND,
	OR,
	NOR,
	XOR,
	XNOR,
	BUFF,
	NOT,
	END,
	ERROR
};

static void check_comment(string&);
static PARSE_STATE state_parse(string&);
static string get_1_tok(string);
static int gatecount=2;

void
CirMgr::printcircuit( int num)
{
	Circuit& cir = num==1? c1:c2;
	cout<<"Circuit "<<num<<" :"<<endl<<endl;
	
	int size = cir.out_list.size();
   for(int i=0;i<size;i++)
   	cir.printDFS(cir.out_list[i],0);
   cir.clearFlag();
}

bool
CirMgr::parse( ifstream& cirfile, int num)
{
   Circuit& cir = num==1? c1:c2;

	string buff;
 	PARSE_STATE state = MODULE;
	while(getline(cirfile, buff,';'))
	{
		check_comment(buff);
		vector<string> tokens;	
		myStr2Tok( buff,tokens," ,\n\t()");
		switch(state_parse(tokens[0]))
		{
			case MODULE: /* skip error handling */	break;			
			case INPUT:
				for(int n=1,size=tokens.size() ; n<size; n++)
				{
					cir.name_match.insert(pair<string, Gate*>(tokens[n], new Input(gatecount++,tokens[n])));
			 		cir.in_list.push_back(cir.name_match[tokens[n]]);
			 		cir.gate_list.push_back(cir.name_match[tokens[n]]);
				}
				break;
			case OUTPUT:
				for(int n=1,size=tokens.size() ; n<size; n++)
				{
					cir.name_match.insert(pair<string, Gate*>(tokens[n], new Output(gatecount++,tokens[n])));
			 		cir.out_list.push_back(cir.name_match[tokens[n]]);			 		
			 		cir.gate_list.push_back(cir.name_match[tokens[n]]);
				}
				break;	
			case WIRE:
				for(int n=1,size=tokens.size() ; n<size; n++)
				{
					cir.name_match.insert(pair<string, Gate*>(tokens[n], new Wire(-1,tokens[n])));
			 		cir.Wire_list.push_back(cir.name_match[tokens[n]]);			 		
				}
				break;
			case BUFF:	 gate_parse(tokens, cir.Buff_list, new Buffer  (gatecount++), cir); break;
			case NOT:	 gate_parse(tokens, cir.Not_list,  new NotGate (gatecount++), cir); break;
			case AND:	 gate_parse(tokens, cir.And_list,  new AndGate (gatecount++), cir); break;
			case NAND:	 gate_parse(tokens, cir.Nand_list, new NandGate(gatecount++), cir); break;
			case OR:		 gate_parse(tokens, cir.Or_list,   new OrGate  (gatecount++), cir); break;
			case NOR:	 gate_parse(tokens, cir.Nor_list,  new NorGate (gatecount++), cir); break;
			case XOR:	 gate_parse(tokens, cir.Xor_list,  new XorGate (gatecount++), cir); break;
			case XNOR: 	 gate_parse(tokens, cir.Xnor_list, new XnorGate(gatecount++), cir); break;
			case END: /*skip*/ break;			
			case ERROR:  return false;
		}
	}

	cirfile.close();	
	cir.removeList(cir.Wire_list);
	cir.removeList(cir.Buff_list);

   return true;
}

void CirMgr::gate_parse(vector<string>& tokens, vector<Gate*>& gate_list,  Gate* gate, Circuit& cir)
{

	Gate* link_gate;
	if(tokens.size()==1)
	{
		cerr << "Missing parameter after \"" << tokens[0] <<"\" !!"<< endl;
		return;
	}

	// get fanout(wire)
	link_gate = cir.name_match.find(tokens[1])->second;
	link_gate->fanin_add(gate);
	gate->fanout_add(link_gate);

	// get fanins(wire)
	for(int i=2,size=tokens.size();i<size;i++)
	{
		link_gate = cir.name_match.find(tokens[i])->second;
		link_gate->fanout_add(gate);
		gate->fanin_add(link_gate);
	}
	gate_list.push_back(gate);
	if(gate->getType()!="Buffer")
		cir.gate_list.push_back(gate);
}

static void check_comment(string& s)
{
   int size=s.size() , start=0;
   string temp="";
   for(int i=0;i<size-1;)
   {
      if(s[i]=='/' && s[i+1]=='/')
      {
         temp += s.substr(start,i-start);
         i+=2;
         while( s[i] !='\n' && s[i] !='\0')
            i++;
         start = i+1 ;
      }
      i++;
   }
   if(start<size)
      temp += s.substr(start,size-start);
   s=temp;
}

static PARSE_STATE state_parse(string& state)
{
	if( state=="module")
		return MODULE;
	else if( state == "input")
		return INPUT;
	else if( state == "output")
		return OUTPUT;
	else if( state == "wire")
		return WIRE;
	else if( state == "buf"  )
		return BUFF;
	else if( state == "not"  )
		return NOT;
	else if( state == "and"  )
		return AND;
	else if( state == "nand" )
		return NAND;
	else if( state == "or"   )
		return OR;
	else if( state == "nor"  )
		return NOR;
	else if( state == "xor"  )
		return XOR;
	else if( state == "xnor" )
		return XNOR;
	else if( state == "endmodule" )
		return END;
	else
	{
		cerr<<"Illigal argument \""<<state<<"\" !!"<<endl;	
		return ERROR;
	}
}