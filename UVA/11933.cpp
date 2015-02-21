#include <iostream>
using namespace std;
int main(){
	int number;
	while(cin >> number){
		if(number == 0)
			break;
		int a = 0, b = 0, i = 1;
		int cnt = 0;
		while(number){
			if(i & number){
				cnt ++;
				number -=i;
				if(cnt % 2)
					a += i;
				else
					b += i;
			}
			i <<= 1;
		}
		cout << a << " " << b << endl;
	}
}