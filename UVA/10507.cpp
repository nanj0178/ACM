#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
class LifeTime{
public:
	void clear_all(){
		memset(area_connection_,0,sizeof(area_connection_));
		memset(state_area_,0,sizeof(state_area_));
	}
	void set_area_connection(int from,int to){
		//cout << from << " " << to << endl;
		area_connection_[from][to] = 1;
		area_connection_[to][from] = 1;
	}
	void set_need_awake(int num_area){
		num_need_awake_ =	num_area;
	}
	int get_awake_time(int initA, int initB, int initC){
		//copy state
		int state_area[26]={0};
		for (int i = 0; i < 26; ++i)
			state_area[i] = state_area_[i];
		//init
		state_area[initA] = state_area[initB] = state_area[initC] = 1;
		bool check_continue = true;
		int awake_year = 0;
		int awake_count = 0;
		// a round
		while(check_continue && awake_count != num_need_awake_-3){
			awake_year++;
			int next_state_area[26]={0};
			// check awake up by rules.
			for (int i = 0; i < 26; ++i){
				if(!state_area[i]){
					int count_neighbor_awake = 0;
					for (int j = 0; j < 26; ++j)
						if(area_connection_[i][j] && state_area[j]){
							count_neighbor_awake++;
						}
					if (count_neighbor_awake >= 3){
						next_state_area[i] = 1;
						awake_count++;
					}
					else
						next_state_area[i] = 0;
				}else{
					next_state_area[i] = state_area[i];
				}
			}
			//  Is there anyone awake in this round.
			// 	Yes, copy next_state array to state array,
			//  No, stop. 
			int same_state = 0;		
			for (int i = 0; i < 26; ++i)
			{
				if(state_area[i] == next_state_area[i])
					same_state++;
				state_area[i] = next_state_area[i];
			}
			if(same_state == 26)
				   check_continue = false;
		}
		// return -1 (fail). 
		// return the number year of awake up.
		if (awake_count == num_need_awake_-3)
			return awake_year;
		else
			return -1;
	}

private:
	int area_connection_[26][26];
	int state_area_[26];
	int num_need_awake_;
};
vector< pair<int,int> > parser(int num_connect){
	vector< pair<int,int> > result;
	string connection;
	for(int i = 1;i <= num_connect; i++){
		cin >> connection;
		result.push_back(pair<int,int>(connection[0]-'A',connection[1]-'A'));
	}
	return result;

}
int main(){
	int num_area,num_connect;
	string first_awake_area;
	while(cin >> num_area >> num_connect >> first_awake_area){
		 vector< pair<int,int> > connect_info = parser(num_connect);
		 LifeTime lifetime;
		 lifetime.clear_all();
		 lifetime.set_need_awake(num_area);
		 for (vector< pair<int,int> >::iterator it = connect_info.begin(); it!=connect_info.end(); it++)
		 {
		 	lifetime.set_area_connection(it->first,it->second);
		 }
		// cout << "parser over" << endl;
		 int ans = lifetime.get_awake_time(first_awake_area[0]-'A',first_awake_area[1]-'A',first_awake_area[2]-'A');
		 if(ans == -1)
		 	cout << "THIS BRAIN NEVER WAKES UP" << endl;
		 else
		 	cout << "WAKE UP IN, "<< ans <<", YEARS"<< endl;
	}	
}
