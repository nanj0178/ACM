#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    float total_salary = 0;
    float salary = 0;
    for(int i = 0;i<12;i++){
      cin >> salary;
      total_salary +=salary; 
    }
    printf("$%.2f\n",total_salary/12);
}
