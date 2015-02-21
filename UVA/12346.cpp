#include <iostream>
#include <stdio.h>
using namespace std;
// flag 0 rightest 1 leftest
int query_segment(int *soldier, int left_survior, int right_survior, int left_node, int right_node, int iNode, bool flag){
	//cout << left_survior <<" " << right_survior << " " << left_node << " " << right_node << " " << iNode << endl; 
	if(left_survior > right_survior)
		return 0;
	if(left_node > right_survior)
		return 0;
	if(right_node < left_survior)
		return 0;
	if(left_survior == left_node && right_survior == right_node){
		if(soldier[iNode] == 0 )
			return 0;
		else{
			int i = iNode;
			while(left_node!=right_node){
				//cout << left_node << " "<< right_node << endl;
				int min_node = (left_node + right_node)/2;
				i *= 2;
				if(flag){
					if(soldier[i])
						right_node = min_node;
					else
						left_node = min_node + 1,i++;
				}else{
					if(soldier[i + 1])
						left_node = min_node + 1,i++;
					else
						right_node = min_node;
				}
			}
			return left_node;
		}
	}else{
		int min_node = (left_node + right_node)/2;
		if(flag){
			//if( min_node >= left_survior && soldier[iNode * 2] ){
				 int value = query_segment(soldier,left_survior,min(right_survior, min_node),left_node,min_node,iNode * 2, flag);
				 if(value)
				 	return value;
				 else
				 	return query_segment(soldier,max(left_survior, min_node + 1), right_survior, min_node + 1 , right_node, iNode * 2 + 1, flag);
			
		}else{
			//if( (min_node + 1) <= right_survior && soldier[iNode * 2 + 1] )
				int value =  query_segment(soldier,max(left_survior, min_node + 1), right_survior, min_node + 1 , right_node, iNode * 2 + 1, flag);
				 if(value)
				 	return value;
				 else
			
				return query_segment(soldier,left_survior,min(right_survior, min_node),left_node,min_node,iNode * 2, flag);
		}
	}
}
void del_segment(int *soldier, int left_dead, int right_dead, int left_node, int right_node, int iNode){
	//cout << left_dead <<" " << right_dead << " " << left_node << " " << right_node << " " << iNode << endl; 
	if(left_dead > right_dead)
		return;
	if(left_node > right_dead)
		return;
	if(right_node < left_dead)
		return;
	if(left_dead == left_node && right_dead == right_node)
		soldier[iNode] = 0 ;
	else{
		int min_node = (left_node + right_node)/2; 
		del_segment(soldier,left_dead,min(right_dead,min_node),left_node,min_node,iNode * 2);
		del_segment(soldier,max(left_dead, min_node + 1), right_dead, min_node + 1 , right_node, iNode * 2 + 1);
		soldier[iNode] = soldier[iNode * 2] + soldier[iNode * 2 + 1]; 
	}
}
int init_segment_tree(int *soldier, int left_node, int right_node, int iNode){

	if(left_node == right_node)
		soldier[iNode] = 1;
	else{
		int min_node = (left_node + right_node)/2; 
		soldier[iNode] = init_segment_tree(soldier, left_node, min_node, iNode * 2)
					 	+ init_segment_tree(soldier, min_node + 1, right_node, iNode * 2 + 1);
	}
	return soldier[iNode];
}
int main(){
	int num_soldier,num_report;
	while(cin >> num_soldier >> num_report){
		if(num_soldier+num_report == 0)
			break;
		int soldier[300000]={0};
		int left_killed,right_killed;
		init_segment_tree(soldier,1,num_soldier,1);
		for (int i = 1; i <= num_report; ++i)
		{
			scanf("%d %d", &left_killed,&right_killed);
			del_segment(soldier,left_killed,right_killed,1,num_soldier,1);
			int closed_left = query_segment(soldier,1 , left_killed - 1 , 1, num_soldier,1 , 0);
			int closed_right = query_segment(soldier,right_killed + 1, num_soldier, 1, num_soldier,1 , 1);
			if(closed_left)
				printf("%d ",closed_left);
			else
				printf("* ");
			if(closed_right)
				printf("%d\n",closed_right);
			else
				printf("*\n");
			// for (int j = 1; j < 25; ++j)
		 // 		cout << j<<" "<<soldier[j] << endl;
		 // 		cout << endl;

		}
		printf("-\n");
	}
}