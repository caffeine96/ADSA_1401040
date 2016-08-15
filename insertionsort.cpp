#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;

int main()
{
	ofstream MyExcelFile;
	MyExcelFile.open("test.csv",ios::out|ios::app);
	clock_t stop,start;
	int n;
	cin>>n;
	int a[n]; 
     
	for(int i=0; i<n; i++)
        	a[i] = (rand()%10)+1; 
         
	start=clock();
	
	for(int i=1;i<n-1;++i)
	{
		int temp=a[i];
		int j=i-1; 
		while(j>=0&&a[j]>a[i])
		{
			a[j+1]=a[j];
			j--;
			
		}
		a[j+1]=temp;
	}
	
	stop=clock();
	double msecs=(stop-start)/(double)CLOCKS_PER_SEC;
	cout<<msecs;
	
	MyExcelFile<<n<<"\""<<msecs<<endl;	
	return 0;
}
