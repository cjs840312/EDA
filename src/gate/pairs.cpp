#include <iostream>
#include "CirMgr.h"

using namespace std;

typedef vector<Gate*> one_pair;
typedef vector< vector<Gate*> > group_list;

int
CirMgr::pairs()
{
	map<int, group_list> group_map;  // real_fec as key
	final_pair_list.clear();

	vector<Gate*>::iterator it = c1.out_list.begin();
	for(; it!= c1.out_list.end(); ++it)
   {
		if ( group_map.find((*it)->real_fec) !=  group_map.end() )
      {
			one_pair tmp_pair;
			tmp_pair.push_back( *it );
			group_map.find((*it)->real_fec)->second.push_back( tmp_pair );
		}
      else
      {
			one_pair tmp_pair;
			tmp_pair.push_back( *it );
			group_list tmp_list;
			tmp_list.push_back( tmp_pair );
			group_map.insert(pair <int, group_list> ( (*it)->real_fec, tmp_list) );
		}
	}
	
	/*push matched c2 ouputs into pair, each time push in to the pair with min members*/
	it = c2.out_list.begin();
	map<int, group_list>::iterator it2 ;
	for(; it != c2.out_list.end(); ++it )  {
		if ( !( (*it)->matched ) ) continue;
		
		it2 = group_map.find( (*it)->real_fec );
		int min = 0;
		for( int i = 1; i < it2->second.size(); ++i) 
			if ( it2->second[i].size() < it2->second[min].size() )	min = i;
		it2->second[min].push_back( *it );
	}

	/* collect  pairs  into final_pair_list*/

	it2 = group_map.begin();
	for( ; it2 !=  group_map.end() ; ++it2) 
	{
		bool find=false;
		for(int i=0; i<it2->second.size(); ++i)
		{
			if( it2->second[i].size() > 1)
			{
				final_pair_list.push_back( it2->second[i] );
				find=true;
			}
			else if(i!=0 && find)
				(final_pair_list.end()-1)->push_back(it2->second[i][0]);
		}
	}

	int score=0;
	for (int i=0; i<final_pair_list.size(); ++i)
	{
		score+=11;
		for (int j=1; j<final_pair_list[i].size(); ++j)
			score+=1;
	}
	return score;
	
}
