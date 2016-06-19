#include <iostream>
#include <algorithm> 
#include "CirMgr.h"
#include <ctime>
using namespace std;
/*
static int* state;
static int max_dig,size;
static bool add_dig(int dig=0);
*/

struct Node{
	int cir_Number;
	int output_Number;
	vector<vector<vector<pair<int,bool> > > > sequence;
};

struct Node* newNode(int cir_No, int output_No){
	struct Node* temp = new Node;
	
	temp->cir_Number = cir_No;
	temp->output_Number = output_No;
	return temp;
};
bool compare(const pair<string, int>&i, const pair<string, int>&j)
{
    return i.second > j.second;
}

void
CirMgr::match()
{
	srand (static_cast <unsigned> (time(0)));
	cout<<"//////////////////////// CIRCUIT 1 ////////////////////////"<<endl;
	c1.clearFlag();
	vector<vector<vector<pair<string, bool> > > >sequence;
	vector<bool>x_exist_cir1;
	for(int i = 0; i<c1.out_list.size(); i++){
		
		cout<<"///////////////////////////"<<endl;
		int zero = 0;
		
		vector<vector<pair<string, bool> > >branch;
		sequence.push_back(branch);
		bool checkx = 0;
		c1.traceBack(c1.out_list[i], sequence[i], zero, c1.out_list[i]->getName(), checkx);
		x_exist_cir1.push_back(checkx);
		cout<<"///////////////////////////"<<endl;
	}
	//cout<<c1.out_list[0]->getType()<<"!!!!";
	
	//c1.traceBack(c1.out_list[0], sequence, No1);
	cout<<"traceback done!"<<endl;
	vector<vector<vector<pair<string,int> > > >index;
	for(int i = 0; i<c1.out_list.size(); i++){
		
		vector<vector<pair<string, int> > >branch;
		index.push_back(branch);
		
	}
	for(int i = 0; i < sequence.size(); i++){
		//output
		cout<<"i: "<<i<<endl;
		for(int j = 0; j < sequence[i].size(); j++){
			//input
			bool foundSameInput = 0;
			for(int k = 0; k < index[i].size(); k++){

				if(index[i][k][0].first == sequence[i][j][0].first){
					pair<string, int> temp(sequence[i][j][0].first,j);
					index[i][k].push_back(temp);
					foundSameInput = 1;
					break;
				}
			}
			if(!foundSameInput){
				vector<pair<string, int> > branch;
				pair<string, int> temp(sequence[i][j][0].first,j);
				branch.push_back(temp);
				index[i].push_back(branch);
			}
		}
		
	}
	cout<<"////////////////////////"<<endl;
	cout<<"sequence: "<<endl;
	for(int i = 0; i < sequence.size(); i++){
		cout<<"output: "<<i<<endl;
		for(int j = 0; j < sequence[i].size(); j++){
			cout<<sequence[i][j][sequence[i][j].size()-1].first<<endl;
			for(int k = 0; k < sequence[i][j].size();k++){
				cout<<sequence[i][j][k].second;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<"////////////////////////"<<endl;
	cout<<"index: "<<endl;
	for(int i = 0; i < index.size(); i++){
		cout<<"output: "<<i<<endl;
		for(int j = 0; j < index[i].size(); j++){
			cout<<index[i][j][0].first<<endl;
			for(int k = 0; k < index[i][j].size();k++){
				cout<<index[i][j][k].second<<"\t";;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	cout<<"////////////////////////"<<endl;
	cout<<"x_exist_cir1: "<<endl;
	for(int i = 0; i < x_exist_cir1.size(); i++){
		cout<<"output: "<<i<<endl;
		cout<<x_exist_cir1[i]<<endl;
		cout<<endl;
	}
	cout<<"//////////////////////// CIRCUIT 2 ////////////////////////"<<endl;
	c2.clearFlag();
	vector<vector<vector<pair<string, bool> > > >sequence2;
	vector<bool>x_exist_cir2;
	for(int i = 0; i<c2.out_list.size(); i++){
		cout<<"///////////////////////////"<<endl;
		int zero = 0;
		vector<vector<pair<string, bool> > >branch;
		sequence2.push_back(branch);
		
		bool checkx = 0;
		c2.traceBack(c2.out_list[i], sequence2[i], zero, c2.out_list[i]->getName(), checkx);
		x_exist_cir2.push_back(checkx);
		cout<<"///////////////////////////"<<endl;
	}
	//cout<<c1.out_list[0]->getType()<<"!!!!";
	
	//c1.traceBack(c1.out_list[0], sequence2, No1);
	cout<<"traceback done!"<<endl;
	vector<vector<vector<pair<string,int> > > >index2;
	for(int i = 0; i<c2.out_list.size(); i++){
		
		vector<vector<pair<string, int> > >branch;
		index2.push_back(branch);
		
	}
	for(int i = 0; i < sequence2.size(); i++){
		//output
		cout<<"i: "<<i<<endl;
		for(int j = 0; j < sequence2[i].size(); j++){
			//input
			bool foundSameInput = 0;
			for(int k = 0; k < index2[i].size(); k++){

				if(index2[i][k][0].first == sequence2[i][j][0].first){
					pair<string, int> temp(sequence2[i][j][0].first,j);
					index2[i][k].push_back(temp);
					foundSameInput = 1;
					break;
				}
			}
			if(!foundSameInput){
				vector<pair<string, int> > branch;
				pair<string, int> temp(sequence2[i][j][0].first,j);
				branch.push_back(temp);
				index2[i].push_back(branch);
			}
		}
		
	}
	cout<<"////////////////////////"<<endl;
	cout<<"sequence2: "<<endl;
	for(int i = 0; i < sequence2.size(); i++){
		cout<<"output: "<<i<<endl;
		for(int j = 0; j < sequence2[i].size(); j++){
			cout<<sequence2[i][j][sequence2[i][j].size()-1].first<<endl;
			for(int k = 0; k < sequence2[i][j].size();k++){
				cout<<sequence2[i][j][k].second;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<"////////////////////////"<<endl;
	cout<<"index2: "<<endl;
	for(int i = 0; i < index2.size(); i++){
		cout<<"output: "<<i<<endl;
		for(int j = 0; j < index2[i].size(); j++){
			cout<<index2[i][j][0].first<<endl;
			for(int k = 0; k < index2[i][j].size();k++){
				cout<<index2[i][j][k].second<<"\t";;
			}
			cout<<endl;
		}
		cout<<endl;
	}
	cout<<"////////////////////////"<<endl;
	cout<<"x_exist_cir2: "<<endl;
	for(int i = 0; i < x_exist_cir2.size(); i++){
		cout<<"output: "<<i<<endl;
		cout<<x_exist_cir2[i]<<endl;
		cout<<endl;
	}
	cout<<"//////////////////////// START MATCHING ////////////////////////"<<endl;
	
	/*vector<string, bool> C2_already_match;
	for(int i = 0; i< c2.in_list.size(); i++){
		C2_already_match.push_back(c2.in_list[i]->getName(),0);
	}
	*/
	vector<string> final_matching_check;
	
	for(int i = 0; i < c2.out_list.size(); i++){
		cout<<"**********************************************"<<endl;
		cout<<i<<" matching inputs in "<<c2.out_list[i]->getName()<<endl;
		vector<int>weight;
		weight.resize(c1.out_list.size());
		int numOfZero2 = 0;
		int numOfOne2 = 0;
		for(int j = 0; j < sequence2[i].size(); j++){
			
			for(int k = 0; k < sequence2[i][j].size();k++){
				if(sequence2[i][j][k].second){
					numOfOne2++;
				}
				else{
					numOfZero2++;
				}
			}
		}
		cout<<"numOfZero2: "<<numOfZero2<<endl;
		cout<<"numOfOne2: "<<numOfOne2<<endl;
		cout<<"/////////////////////////////"<<endl;
		vector<int>additionMatch;
		for(int j = 0; j < c1.out_list.size(); j++){
			cout<<j<<" scanning inputs in "<<c1.out_list[j]->getName()<<endl;
			int addtional_matching = abs(int(index2[i].size() - index[j].size()));
			additionMatch.push_back(addtional_matching);
			cout<<"addtional_matching: "<<addtional_matching<<endl;
			int numOfZero = 0;
			int numOfOne = 0;
			for(int k = 0; k < sequence[j].size(); k++){
				for(int h = 0; h < sequence[j][k].size();h++){
					if(sequence[j][k][h].second){
						numOfOne++;
					}
					else{
						numOfZero++;
					}	
				}
			}
			cout<<"numOfZero2: "<<numOfZero2<<endl;
			cout<<"numOfOne2: "<<numOfOne2<<endl;
			weight[j] = 50*addtional_matching + 1*abs(numOfZero - numOfZero2) + 5*abs(numOfOne - numOfOne2);
			cout<<"weight: "<<weight[j]<<endl;
		}
		int min_weight = weight[0];
		int indexOfChosenCir1Output = 0;
		for(int j = 0; j < weight.size(); j++){
			if(weight[j]<min_weight){
				min_weight = weight[j];
				indexOfChosenCir1Output = j; //the index in out_list of cir1
			}
		}
		//match x to f first
		vector<pair<string, int> >outputRelatedNumber2;
		for(int j = 0; j < index2[i].size(); j++){
			pair<string, int> temp(index2[i][j][0].first,0);
			outputRelatedNumber2.push_back(temp);
		}
		for(int j = 0; j < index2.size(); j++){
			for(int k = 0; k<index2[j].size(); k++){
				for(int h = 0 ; h < outputRelatedNumber2.size(); h++){
					if(index2[j][k][0].first == outputRelatedNumber2[h].first){
						outputRelatedNumber2[h].second++;
						break;
					}
				}
			}
		}
		vector<pair<string, int> >outputRelatedNumber;
		for(int j = 0; j < index[indexOfChosenCir1Output].size(); j++){
			pair<string, int> temp(index[indexOfChosenCir1Output][j][0].first,0);
			outputRelatedNumber.push_back(temp);
		}
		for(int j = 0; j < index.size(); j++){
			for(int k = 0; k<index[j].size(); k++){
				for(int h = 0 ; h < outputRelatedNumber.size(); h++){
					if(index[j][k][0].first == outputRelatedNumber[h].first){
						outputRelatedNumber[h].second++;
						break;
					}
				}
			}
		}
		sort(outputRelatedNumber2.begin(), outputRelatedNumber2.end(), compare);
		
		for(int j = 0; j < outputRelatedNumber2.size(); j++){
			cout<<outputRelatedNumber2[j].first<<": "<<outputRelatedNumber2[j].second<<endl;
		}
		cout<<"////////////////////////"<<endl;
		sort(outputRelatedNumber.begin(), outputRelatedNumber.end(), compare);
		
		for(int j = 0; j < outputRelatedNumber.size(); j++){
			cout<<outputRelatedNumber[j].first<<": "<<outputRelatedNumber[j].second<<endl;
		}
		cout<<"*************************"<<endl;
		
		int NumOfInputs1 = outputRelatedNumber.size();
		int NumOfInputs2 = outputRelatedNumber2.size();
		int additional_match = 0;
		if(NumOfInputs2 > NumOfInputs1){
			additional_match = NumOfInputs2 - NumOfInputs1;
		}
		//////match every input of this output
		//first matching input
		/*
		for(int k = 0; k < outputRelatedNumber2.size(); j++){
			bool found = 0;
			for(int k = 0; k<final_matching_check.size();k++){
				if(outputRelatedNumber2[j].first == final_matching_check[k]){
					found = 1;
					break;
				}
			}
			if(!found){
				final_matching_check.push_back(outputRelatedNumber2[j].first);
			}
			
		}
		*/
		for(int j = 0; j < outputRelatedNumber2.size(); j++){
			bool found = 0;
			for(int k = 0; k<final_matching_check.size();k++){
				if(outputRelatedNumber2[j].first == final_matching_check[k]){
					found = 1;
					break;
				}
			}
			if(found){
				cout<<endl<<outputRelatedNumber2[j].first<<" is already matched!"<<endl;
				
			}
			else{
			cout<<"input in cir2: "<<outputRelatedNumber2[j].first<<" is on the match! "<<endl;//the target in cir2
			
			int cir2_input_index = 0;
			bool check = 0;
			for(int k = 0; k < index2[i].size(); k++){
				if(index2[i][k][0].first == outputRelatedNumber2[j].first){
					cir2_input_index = k;
					check = 1;
					break;
				}
			}
			if(!check){
				cout<<"error"<<endl;
			}
			vector<vector<bool> >match;
			//cout<<"input in cir2: "<<index2[i][cir2_input_index][0].first<<" is on the match! "<<endl;//check the target in cir2
			for(int h = 0; h < index2[i][cir2_input_index].size(); h++){
				//cout<<index2[i][cir2_input_index][j].second<<endl;
				int differentSequenceIndex = index2[i][cir2_input_index][h].second;
				vector<bool> branch;
				match.push_back(branch);
				cout<<"sequence of "<<index2[i][cir2_input_index][0].first<<" : ";
				for(int k = 0; k < sequence2[i][differentSequenceIndex].size();k++){
					cout<<sequence2[i][differentSequenceIndex][k].second;
					match[h].push_back(sequence2[i][differentSequenceIndex][k].second);
				}	
				cout<<endl;
			}
			
			//cout<<"input in cir1: "<<outputRelatedNumber[0].first<<endl; //target in cir1
			vector<pair<string, bool> > candidateOfCir1; //the name of candidate in Cir1
			for(int m = 0; m < index[indexOfChosenCir1Output].size(); m++){
				for(int k = 0; k < index[indexOfChosenCir1Output][m].size(); k++){
					cout<<"input in cir1: "<<index[indexOfChosenCir1Output][m][0].first<<endl;
					int differentSequenceIndex = index[indexOfChosenCir1Output][m][k].second;
					cout<<"sequence of "<<index[indexOfChosenCir1Output][m][0].first<<" : ";
					for(int g = 0; g < sequence[indexOfChosenCir1Output][differentSequenceIndex].size();g++){
						cout<<sequence[indexOfChosenCir1Output][differentSequenceIndex][g].second;
					}
					cout<<endl;
					for(int n = 0; n<match.size(); n++){
						if(sequence[indexOfChosenCir1Output][differentSequenceIndex].size() == match[n].size()){
							bool reject = 0;
							for(int h = 0; h < sequence[indexOfChosenCir1Output][differentSequenceIndex].size();h++){
								//cout<<sequence[indexOfChosenCir1Output][differentSequenceIndex][h].second;
								if((match[n][h])xor(sequence[indexOfChosenCir1Output][differentSequenceIndex][h].second)){
									reject = 1;
									break;
								}
							}
							///////////////additional
							if(!reject){
								pair<string, bool> temp(index[indexOfChosenCir1Output][m][0].first, 0);
								candidateOfCir1.push_back(temp);
								break;
							}
							//cout<<endl;
						}
						else if(sequence[indexOfChosenCir1Output][differentSequenceIndex].size() == match[n].size()-1 && !match[n][match[n].size()-1]){
							bool reject = 0;
							for(int h = 0; h < sequence[indexOfChosenCir1Output][differentSequenceIndex].size();h++){
								//cout<<sequence[indexOfChosenCir1Output][differentSequenceIndex][h].second<<endl;
								if((match[n][h])xor(sequence[indexOfChosenCir1Output][differentSequenceIndex][h].second)){
									reject = 1;
									break;
								}
							}
							if(!reject){
								pair<string, bool> temp(index[indexOfChosenCir1Output][m][0].first, 1);
								candidateOfCir1.push_back(temp);
								break;
							}
							//cout<<endl;						
						}	
					}
					
				}
			}			
			if(candidateOfCir1.size() > 0){
				cout<<"candidate: ";
				int numOfRelatedOutput = c1.out_list.size();
				int min_output_related = 0;
				bool set = 0;
				for(int k = 0; k < candidateOfCir1.size(); k++){
					cout<<candidateOfCir1[k].first<<"\t";
					int candidate_related_output = 0;
					for(int h = 0; h < outputRelatedNumber.size(); h++){
						if(candidateOfCir1[k].first == outputRelatedNumber[h].first){
							candidate_related_output = outputRelatedNumber[h].second;
						}
					}
					if(candidate_related_output == 0){
						cout<<"error"<<endl;
					}
					if(outputRelatedNumber2[j].second == candidate_related_output){
						if(candidateOfCir1[k].second){
							cout<<endl<<"final : ~"<<outputRelatedNumber2[j].first<<" to "<<candidateOfCir1[k].first<<endl;
							final_matching_check.push_back(outputRelatedNumber2[j].first);
							
							////////////////////////////////////////////////////////Please check here
							//c2.in_list[2]->fanin_add(c1.in_list[2]);
							int OutputOfCir2 = c2.name2index(outputRelatedNumber2[j].first);
							int OutputOfCir1 = c1.name2index(candidateOfCir1[k].first);
							Gate* temp = new NotGate(10000,"invert");
							c1.gate_list.push_back(temp);
							c2.gate_list.push_back(temp);
							c1.Not_list.push_back(temp);
							c2.Not_list.push_back(temp);
							
							temp->fanout_add(c2.in_list[OutputOfCir2]);
							temp->fanin_add(c1.in_list[OutputOfCir1]);
							c1.in_list[OutputOfCir1]->fanout_add(temp);
							c2.in_list[OutputOfCir2]->fanin_add(temp);
							cout<<endl<<"final : ~"<<c2.in_list[OutputOfCir2]->getName()<<" to "<<c1.in_list[OutputOfCir1]->getName()<<endl;
							
						}
						else{
							cout<<endl<<"final : "<<outputRelatedNumber2[j].first<<" to "<<candidateOfCir1[k].first<<endl;
							final_matching_check.push_back(outputRelatedNumber2[j].first);
							
							//c2.in_list[2]->fanin_add(c1.in_list[2]);
							int OutputOfCir2 = c2.name2index(outputRelatedNumber2[j].first);
							int OutputOfCir1 = c1.name2index(candidateOfCir1[k].first);
							c2.in_list[OutputOfCir2]->fanin_add(c1.in_list[OutputOfCir1]);
							cout<<endl<<"final : "<<c2.in_list[OutputOfCir2]->getName()<<" to "<<c1.in_list[OutputOfCir1]->getName()<<endl;
							
						}
						set = 1;						
						break;
						
					}
					if(candidate_related_output < numOfRelatedOutput){
						numOfRelatedOutput = candidate_related_output;
						min_output_related = k;
					}
					
				}
				if(!set){
					if(candidateOfCir1[min_output_related].second){
						cout<<endl<<"final : ~"<<outputRelatedNumber2[j].first<<" to "<<candidateOfCir1[min_output_related].first<<endl;
						final_matching_check.push_back(outputRelatedNumber2[j].first);
						//c2.in_list[2]->fanin_add(c1.in_list[2]);
						int OutputOfCir2 = c2.name2index(outputRelatedNumber2[j].first);
						int OutputOfCir1 = c1.name2index(candidateOfCir1[min_output_related].first);
						//c2.in_list[OutputOfCir2]->fanin_add(c1.in_list[OutputOfCir1]);
						Gate* temp = new NotGate(10000,"invert");
						temp->fanout_add(c2.in_list[OutputOfCir2]);
						temp->fanin_add(c1.in_list[OutputOfCir1]);
						c1.in_list[OutputOfCir1]->fanout_add(temp);
						c2.in_list[OutputOfCir2]->fanin_add(temp);
						
						c1.gate_list.push_back(temp);
						c2.gate_list.push_back(temp);
						c1.Not_list.push_back(temp);
						c2.Not_list.push_back(temp);
											
						////////////////////////////////////////////////////////Please check here
						cout<<endl<<"final : ~"<<c2.in_list[OutputOfCir2]->getName()<<" to "<<c1.in_list[OutputOfCir1]->getName()<<endl;
					}
					else{
						cout<<endl<<"final : "<<outputRelatedNumber2[j].first<<" to "<<candidateOfCir1[min_output_related].first<<endl;
						final_matching_check.push_back(outputRelatedNumber2[j].first);
						//c2.in_list[2]->fanin_add(c1.in_list[2]);
						int OutputOfCir2 = c2.name2index(outputRelatedNumber2[j].first);
						int OutputOfCir1 = c1.name2index(candidateOfCir1[min_output_related].first);
						c2.in_list[OutputOfCir2]->fanin_add(c1.in_list[OutputOfCir1]);
						cout<<endl<<"final : "<<c2.in_list[OutputOfCir2]->getName()<<" to "<<c1.in_list[OutputOfCir1]->getName()<<endl;
					}
				}
				
			}
			else{
				float random1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				cout<<"no candidate!"<<endl;
				if(random1 > 0.5){
					cout<<endl<<"final : "<<outputRelatedNumber2[j].first<<" to "<<"0"<<endl;
					final_matching_check.push_back(outputRelatedNumber2[j].first);
					//c2.in_list[2]->fanin_add(c1.in_list[2]);
					int OutputOfCir2 = c2.name2index(outputRelatedNumber2[j].first);
					//int OutputOfCir1 = c1.name2index(candidateOfCir1[min_output_related].first);
					//c2.in_list[OutputOfCir2]->fanin_add(c1.in_list[OutputOfCir1]);
					c2.in_list[OutputOfCir2]->fanin_add(c1.const_list[0]); 
					cout<<endl<<"final : "<<c2.in_list[OutputOfCir2]->getName()<<" to "<<"0"<<endl;
				}
				else{
					cout<<endl<<"final : "<<outputRelatedNumber2[j].first<<" to "<<"1"<<endl;
					final_matching_check.push_back(outputRelatedNumber2[j].first);
					//c2.in_list[2]->fanin_add(c1.in_list[2]);
					int OutputOfCir2 = c2.name2index(outputRelatedNumber2[j].first);
					//int OutputOfCir1 = c1.name2index(candidateOfCir1[min_output_related].first);
					//c2.in_list[OutputOfCir2]->fanin_add(c1.in_list[OutputOfCir1]);
					c2.in_list[OutputOfCir2]->fanin_add(c1.const_list[1]); 
					cout<<endl<<"final : "<<c2.in_list[OutputOfCir2]->getName()<<" to "<<"1"<<endl;
				}
				
			}
			}
			
		}		
	}
	cout<<"fanin of "<<c2.in_list[0]->getName()<<endl;
	for(int i = 0; i < c2.in_list[0]->fanin_get().size(); i++){
		cout<<c2.in_list[0]->fanin_get()[i]->getName()<<endl;
	}
	cout<<"fanin of "<<c2.in_list[1]->getName()<<endl;
	for(int i = 0; i < c2.in_list[1]->fanin_get().size(); i++){
		cout<<c2.in_list[1]->fanin_get()[i]->getName()<<endl;
	}
	cout<<"fanin of "<<c2.in_list[2]->getName()<<endl;
	for(int i = 0; i < c2.in_list[2]->fanin_get().size(); i++){
		cout<<c2.in_list[2]->fanin_get()[i]->getName()<<endl;
	}
	cout<<"fanin of "<<c2.in_list[3]->getName()<<endl;
	for(int i = 0; i < c2.in_list[3]->fanin_get().size(); i++){
		cout<<c2.in_list[3]->fanin_get()[i]->getName()<<endl;
	}
	cout<<"fanin of "<<c2.in_list[4]->getName()<<endl;
	for(int i = 0; i < c2.in_list[4]->fanin_get().size(); i++){
		cout<<c2.in_list[4]->fanin_get()[i]->getName()<<endl;
	}
	/*
   c2.in_list[0]->fanin_add(c1.const_list[0]);  // s
   c2.in_list[1]->fanin_add(c1.const_list[1]);  // t

   c2.in_list[2]->fanin_add(c1.in_list[2]);  // u
   c2.in_list[3]->fanin_add(c1.in_list[1]);  // v
   c2.in_list[4]->fanin_add(c1.in_list[0]);  // w
	*/

}
