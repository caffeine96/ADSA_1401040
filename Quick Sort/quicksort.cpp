#include <iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int partition(int arr[],int beg,int end)
{
	int pivot=arr[end];
	int i= beg -1;
	
	for(int j=beg;j<end;++j)
	{
		if(arr[j]<=pivot)
		{
			i++;
			int temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}	
	}
	
	int temp=arr[i+1];
	arr[i+1]=arr[end];
	arr[end]=temp;
	
	return i+1;
	
}

void quicksort(int arr[],int beg,int end)
{
	
	if(beg<end)
	{	
		int pivot =partition(arr,beg,end);
		quicksort(arr,beg, pivot-1);
		quicksort(arr,pivot+1,end);
	}	
}


int main()
{
	int n;
	cin>>n;
	int a[n];
	
	for(int i=0; i<n; i++)
	{	
		a[i] = (rand()%10)+1; 
		cout<<a[i]<<" ";
	}
	
	quicksort(a,0,n-1);

	for(int i=0; i<n; i++)
		cout<<a[i]<<" "; 
	
	return 0;
}