#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
// 2^14 = 16384
// N < 15
int node[16385];
int sum_node[16385];
int main(){
	int N_dimensional;
	while(cin >> N_dimensional){
		// N_dimensional cube has 2^N nodes.
		int num_node = pow(2,N_dimensional);
		for (int i = 0; i < num_node; ++i)
			cin >> node[i];
		// count all node potency
		int max_sum = 0;
		for (int i = 0; i < num_node; ++i)
		{
			int sum = 0;
			int current_node = i;
			for (int i = 0; i < N_dimensional; ++i)
			{
				int neighborhood_node = current_node ^ (1<<i);
				sum += node[neighborhood_node];
			}
			sum_node[i] = sum;
		}
		// find the maximum sum of two neighborhood nodes. 
		for (int i = 0; i < num_node; ++i)
		{
			int current_node = i;
			for (int i = 0; i < N_dimensional; ++i)
			{
				int neighborhood_node = current_node ^ (1<<i);
				max_sum = max(max_sum, sum_node[neighborhood_node] + sum_node[current_node]);
			}
		}
		cout << max_sum << endl;
	}
}