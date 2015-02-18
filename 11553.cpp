#include <iostream>
#include <algorithm>
using namespace std;
int g_grid[8][8];
int main(){
	int num_case;
	cin >> num_case;
	for (int test_case = 0; test_case < num_case; ++test_case)
	{
		int num_dimension;
		cin >> num_dimension;
		for (int i = 0; i < num_dimension; ++i)
		{
			for (int j = 0; j < num_dimension; ++j)
			{
				cin >> g_grid[i][j];

			}
		}
		int set[8] = {0,1,2,3,4,5,6,7};
		int min_score = 1000 * num_dimension * num_dimension + 1;
		do{
			int score = 0;
			for (int i = 0; i < num_dimension; ++i)
			{
				score += g_grid[i][set[i]];
			}
			min_score = min(min_score,score);
		}while(next_permutation(set,set+num_dimension));
		cout << min_score << endl;
	}
}