#include <iostream>
#include <cstdlib>
#include "CirMgr.h"
#include <vector>
#include <fstream>
using namespace std;

static void randsort(int* A,int range1,int range2)
{
  vector<int> x1;
  int r;

  for(int i=0;i<range2;i++)
    x1.push_back(i);

  for(int i=0;i<range2;i++)
  {
    r=( rand() % x1.size());
    if(i<range1)
      A[x1[r]] = i;
    else
      A[x1[r]]=rand()%range1;

      x1.erase(x1.begin()+r);
  }
}

void
CirMgr::print_output()
{  
  vector<int> const0;
  vector< vector<int> > in_match;
  in_match.resize(c1.in_list.size());
  for(int i=0,sizei=c2.in_list.size();i<sizei;i++)
  {
    if(matchlist[i]<0)
      const0.push_back(i);
    else
      in_match[matchlist[i]/2].push_back(i);
  }

  fstream fout;
  fout.open(output_name.c_str(),ios::out);

  for (int i=0; i<final_pair_list.size(); ++i)
  {
    fout<<"OUTGROUP"<<endl;    
    for (int j=0; j<final_pair_list[i].size(); ++j)
      fout<< cir_num[final_pair_list[i][j]]
          << (final_pair_list[i][j]->getmatched() == final_pair_list[i][0]->getmatched() ?'+':'-')
          << final_pair_list[i][j]->getName()<<endl;
    fout<<"END"<<endl;
  }

  for(int i=0,sizei=c1.in_list.size();i<sizei;i++)
  {
    if(in_match[i].empty()) continue;
    fout<<"INGROUP"<<endl;
    fout<<"1+"<<c1.in_list[i]->getName()<<endl;
    
    for (int j=0; j<in_match[i].size(); ++j)
      fout<<'2'<< ( matchlist[in_match[i][j]]%2 ?'-':'+')<<c2.in_list[in_match[i][j]]->getName()<<endl;
    fout<<"END"<<endl;    
  }

  fout<<"CONST0GROUP"<<endl;
  for(int i=0,sizei=const0.size();i<sizei;i++)
    fout<<'2'<< ( matchlist[const0[i]]==-1 ?'-':'+')<<c2.in_list[const0[i]]->getName()<<endl;
  fout<<"END"<<endl;

  fout.close();
}

void
CirMgr::trace()
{
  c1.seq_trace();  c2.seq_trace();

  candidate_list1 = new vector<int>[c1.out_list.size()];
  candidate_list2 = new vector<int>[c2.out_list.size()];

  cout<<"c1 size : " <<c1.in_list.size()<<'/'<<c1.out_list.size()<<'/'<<c1.gate_list.size()<<endl;
  cout<<"c2 size : " <<c2.in_list.size()<<'/'<<c2.out_list.size()<<'/'<<c2.gate_list.size()<<endl;

  for(int i=0,sizei=c1.out_list.size();i<sizei;i++)
  {
    cir_num[c1.out_list[i]]=1;
    for(int j=0,sizej=c1.in_list.size();j<sizej;j++)
      if(c1.out_list[i]->in_flags[j])
        candidate_list1[i].push_back(j);
    cout<<candidate_list1[i].size()<<' ';
  }
  cout<<endl;
  
  for(int i=0,sizei=c2.out_list.size();i<sizei;i++)
  {
    cir_num[c2.out_list[i]]=2;
    for(int j=0,sizej=c2.in_list.size();j<sizej;j++)
      if(c2.out_list[i]->in_flags[j])
        candidate_list2[i].push_back(j);
    cout<<candidate_list2[i].size()<<' ';
  }
  cout<<endl<<endl;
}

void
CirMgr::match()
{  
  matchlist = new int[c2.in_list.size()]();
  best_match = new int[c2.in_list.size()]();
  match_in_flag = new bool[c2.in_list.size()]();
  match_out_flag = new bool[c2.out_list.size()]();

  int* randlist = new int[c2.out_list.size()];
  int* sortlist = new int[c2.out_list.size()];
  int temp_score;
  vector<Gate*> temp_not;

  for(int kk=0;kk<1000;kk++)  
  {
    randsort(randlist,c1.out_list.size(),c2.out_list.size());
    
    for(int i=0; i<1000;i++)
    {  
      c2.clearFlag();
      if(i%10==0)
        randsort(sortlist,c2.out_list.size(),c2.out_list.size());

      for( int k=0,sizek=c2.out_list.size();k<sizek;k++)
      {
        int l=sortlist[k];
        for( int j=0,sizej=candidate_list2[l].size();j<sizej;j++)   
        {
            if(!c2.in_list[candidate_list2[l][j]]->Flag)
            {
                int t = rand()%(candidate_list1[randlist[l]].size()+2)-2;
                if(t<0)
                    matchlist[ candidate_list2[l][j] ]= t ;
                else
                    matchlist[candidate_list2[l][j]] = candidate_list1[randlist[l]][t]; 
                c2.in_list[candidate_list2[l][j]]->Flag=true;
            }
        }
      }
      for(int k=0,sizek=c2.in_list.size();k<sizek;k++)
      {
        if (!c2.in_list[k]->Flag) continue;

        c2.in_list[k]->fanin.clear();
        if(matchlist[k] == -1)
          c2.in_list[k]->fanin_add(c2.const_list[1]);
        else if (matchlist[k] == -2 )
          c2.in_list[k]->fanin_add(c2.const_list[0]);
        else
        {
          if(rand()%3)
          {  
            c2.in_list[k]->fanin_add(c1.in_list[matchlist[k]]);
            matchlist[k]*=2;
          }
          else
          {
            Gate* temp = new NotGate(-1);
            temp_not.push_back(temp);
            c1.gate_list.push_back(temp);
            c2.in_list[k]->fanin_add(temp);
            temp->fanin_add(c1.in_list[matchlist[k]]);
            matchlist[k]=matchlist[k]*2+1;
          }
        }
      }

      simulate();
      FEC();
      temp_score = pairs();

      cout<< kk*1000+i<<'\r';
      if(temp_score>best_score)
      {
          best_score=temp_score;
          for(int k=0,sizek=c2.in_list.size();k<sizek;k++)
          {
            cout<<matchlist[k]<<' ';
            best_match[k]=matchlist[k];
            match_in_flag[k]=false;
          }
          cout<<"#"<<endl;
          for(int k=0,sizek=c2.out_list.size();k<sizek;k++)
          {
            if(c2.out_list[k]->matched)
            {
              match_out_flag[k] = true;
              for( int l=0,sizel=candidate_list2[k].size();l<sizel;l++)
                match_in_flag[candidate_list2[k][l]]=true;
            }
            else
              match_out_flag[k] = false;
            
            cout<<match_out_flag[k]<<' ';
          }
          cout<<"@"<<endl;
          for(int k=0,sizek=c2.in_list.size();k<sizek;k++)
            cout<<match_in_flag[k]<<' ';
          cout<<"!"<<endl;


          cout<< kk*1000+i << ' ' << best_score <<' '<<endl<<endl;
          print_output();
      }
      for(int k=0,sizek=temp_not.size();k<sizek;k++)
      {
          c1.gate_list.erase(c1.gate_list.end()-1);
          delete temp_not[k];
      }
      temp_not.clear();
    }
  }

  delete [] randlist;
  delete [] sortlist;
}

void
CirMgr::deep_match()
{

   //matchlist = new int[c2.in_list.size()]();
   best_match = new int[c2.in_list.size()]();
   match_in_flag = new bool[c2.in_list.size()]();
   match_out_flag = new bool[c2.out_list.size()]();

   best_match[0]=-2;
   best_match[1]=8;
   best_match[2]=-1;
   best_match[3]=6;
   best_match[4]=15;
   best_match[5]=0;
   best_match[6]=11;
   best_match[7]=12;

   match_out_flag[0]=1;
   match_out_flag[1]=1;
   match_out_flag[2]=1;
   match_out_flag[3]=1;
   match_out_flag[4]=1;
   match_out_flag[5]=0;
   match_out_flag[6]=1;
   match_out_flag[7]=1;

   match_in_flag[0]=1;
   match_in_flag[1]=1;
   match_in_flag[2]=1;
   match_in_flag[3]=1;
   match_in_flag[4]=1;
   match_in_flag[5]=1;
   match_in_flag[6]=1;
   match_in_flag[7]=1;


  for(int i=0,sizei=c2.out_list.size();i<sizei;i++)
  {
    if(match_out_flag[i])
      cout<<'o';
    else
      cout<<'x';
  }
  cout<<endl;







}

void
CirMgr::single_match()
{
    int g1=0;
    int g2=5;

    matchlist = new int[c2.in_list.size()]();

    vector<Gate*> temp_not;

    bool xxx=false;
    int count=0;
    while(true)
    {

        c2.clearFlag();
        for( int i=0,sizei=candidate_list2[g2].size();i<sizei;i++)   
        {
            int t = rand()%(candidate_list1[g1].size()+2)-2;
            if(t<0)
                matchlist[ candidate_list2[g2][i] ]= t ;
            else
                matchlist[candidate_list2[g2][i]] = candidate_list1[g1][t];
            c2.in_list[candidate_list2[g2][i]]->Flag=true;
        }

        for(int l=0,sizel=c2.in_list.size();l<sizel;l++)
        {
            if (!c2.in_list[l]->Flag) continue;

            c2.in_list[l]->fanin.clear();
            if(matchlist[l] == -1)
              c2.in_list[l]->fanin_add(c1.const_list[1]);
            else if (matchlist[l] == -2 )
              c2.in_list[l]->fanin_add(c1.const_list[0]);
            else
            {
              //if(true)
              if(rand()%3)
              {  
                c2.in_list[l]->fanin_add(c1.in_list[matchlist[l]]);
                matchlist[l]*=2;
              }
              else
              {
                Gate* temp = new NotGate(-1);
                temp_not.push_back(temp);
                c1.gate_list.push_back(temp);
                c2.in_list[l]->fanin_add(temp);
                temp->fanin_add(c1.in_list[matchlist[l]]);
                matchlist[l]=matchlist[l]*2+1;
              }
            }
        }
        c1.his_clear();
        c2.his_clear();
        c1.clearFlag();
        c2.clearFlag();

        for(int i=0; i<c1.in_list.size(); ++i )
            c1.in_list[i]->setValue( rand() ); 

        c1.out_list[g1]->compute_Value();
        c2.out_list[g2]->compute_Value();
        c1.out_list[g1]->setHistory();
        c2.out_list[g2]->setHistory();
        c1.out_list[g1]->setHistorys();
        c2.out_list[g2]->setHistorys();

   

        if(c1.out_list[g1]->history != c2.out_list[g2]->history && ((c1.out_list[g1]->history ^ c2.out_list[g2]->history) != -1))
            xxx=false;
        else 
            xxx= !satisfy(c1.out_list[g1],c2.out_list[g2],(c1.out_list[g1]->history ^ c2.out_list[g2]->history));

        for(int l=0,sizel=temp_not.size();l<sizel;l++)
        {
          c1.gate_list.erase(c1.gate_list.end()-1);
          delete temp_not[l];
        }
        temp_not.clear();

        cout<<"\r"<<count++<<' '<<xxx;
        if(xxx)
            cout<<endl;
    }
    delete [] candidate_list1;
    delete [] candidate_list2;
    delete [] matchlist;
}
