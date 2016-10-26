#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;



int main()
{
	fstream f,fo;
	f.open("text.txt",ios::in);
	fo.open("binary.txt");
	
	bool bin[8];
	char c;
	int freq[26];
	
	for(int i=0;i<26;++i)
		freq[i]=0;
	
	while(f.get(c))
	{
		if(c>=65&&c<=90)
		{
			for(int i=0;i<8;++i)
				bin[i]=0;
			freq[c-65]++;
			int count=7;
			while(c>0)
			{
				if(c%2==1)
					bin[count]++;
				
				c=c/2;
				count--;
			}	
			for(int j=0;j<8;++j)
				fo<<bin[j];
		}	
		else if(c>=97&&c<=122)
		{	
			for(int i=0;i<8;++i)
				bin[i]=0;
			freq[c-97]++;
			int count=7;
			while(c>0)
			{
				if(c%2==1)
					bin[count]++;
				
				c=c/2;
				count--;
			}
			for(int j=0;j<8;++j)
				fo<<bin[j];
		}
		else if(c==32)
			fo<<" ";
		else
			fo<<c;
		
		
		
	}
	
	for(int i=0;i<26;++i)
		cout<<char(65+i)<<" "<<freq[i]<<endl;
	
	
	f.close();
	fo.close();
	
	return 0;
}