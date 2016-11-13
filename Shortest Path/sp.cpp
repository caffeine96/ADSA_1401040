#include <iostream>
#include <stdlib.h>
#include <limits.h>
#define noofnodes 5

using namespace std;


int mat[5][5]= {{0,5,2,100000,100000},{5,0,100000,3,3},{2,100000,0,7,100000},{100000,3,7,0,100000},{100000,3,100000,100000,0}};
int sourcenode;
int trav[5][5];

int shortestpath(int temp,int target, int prev)
{
	int temp1,min1=100000;
	temp1=mat[prev][temp];
	trav[prev][temp]=1;
	trav[temp][prev]=1;	

	for(int i=0;i<noofnodes;++i)
	{
		
		temp1=mat[prev][temp];
		if(mat[temp][i]!=100000&&i!=prev&&i!=temp)
		{
			if(i==target)
				temp1+=mat[temp][target];
			else if(trav[temp][i]==0)				
				temp1+=shortestpath(i,target,temp);
			else
				temp1+=100000;

			if(temp1<min1)
				min1=temp1;
		}

	}

	return min1;

}


int main()
{
	
	int min[noofnodes],temp;
	cout<<"Enter Source Node: ";
	cin>>sourcenode;

	for(int j=0;j<noofnodes;++j)
	{
		if(j!=sourcenode-1)
		{
			for(int k1=0;k1<5;++k1)
				for(int k2=0;k2<5;++k2)
					trav[k1][k2]=0;

			min[j]=mat[sourcenode-1][j];
			for(int i=0;i<noofnodes;++i)
			{
				temp=mat[sourcenode-1][j];
				if(mat[sourcenode-1][i]!=100000 && i!=j && i!=sourcenode-1)
					temp=shortestpath(i,j,sourcenode-1);
			
				if(temp<min[j])
					min[j]=temp;
			}

			cout<<min[j]<<endl;
		}
	}
	return 0;
}
