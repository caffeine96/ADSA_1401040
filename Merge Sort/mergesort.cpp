#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;


void merge(int arr[],int x,int mid,int y)
{
	int size1,size2,i;
	size1=mid-x+1;
	size2=y-mid;
	
	int a1[size1],a2[size2];
	
	for(i=0;i<=size1-1;++i)
		a1[i]=arr[x+i];
	
	for(i=1;i<=size2;++i)
		a2[i]=arr[mid+i+1];
	
	i=0;
	int j=0;
	int k=0;
	while(i<size1&&j<size2)
	{
		if(a1[i]<=a2[j])
		{
			arr[k]=a1[i];
			i++;
		}	
		else
		{
			arr[k]=a2[j];
			j++;
		}	
		k++;
	}	
	
	while(i<size1)
	{
		arr[k]=a1[i];
		i++;
		k++;
	}
	
	while(j<size2)
	{
		arr[k]=a2[j];
		j++;
		k++;
	}	
}

void mergesort(int arr[],int x,int y)
{
	if(y>x)
	{
		int mid=x+(y-1)/2;
		mergesort(arr,x,mid);
		mergesort(arr,mid+1,y);
		merge(arr,x,mid,y);
	}	
	
}

int main()
{
	int n;
	cin>>n;
	int a[n];
	
	for(int i=0; i<n; i++)
		a[i] = (rand()%10)+1;
	
	mergesort(a,0,n-1);
	
	for(int i=0; i<n; i++)
		cout<<a[i];
	
	return 0;
}