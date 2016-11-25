#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#define dim 2
using namespace std;


/*Function to calcyulate cofactors*/
void getCofactor(float cov[dim][dim], float temp[dim][dim], int p, int q, int n)
{
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < dim; row++)
    {
        for (int col = 0; col < dim; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = cov[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/*Function to calculate the determinant*/
float determinant(float A[dim][dim], int n)
{
    float D = 0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];
 
    float temp[dim][dim]; // To store cofactors
 
    int sign = 1;  // To store sign multiplier
 
     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}


/*Function to calculate the adjoint matrix*/
void adjoint(float cov[dim][dim],float covadj[dim][dim])
{
    if (dim == 1)
    {
        covadj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    int sign = 1;
	float temp[dim][dim];
 
    for (int i=0; i<dim; i++)
    {
        for (int j=0; j<dim; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(cov, temp, i, j, dim);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            covadj[j][i] = (sign)*(determinant(temp, dim-1));
        }
    }
}


/*Function to calculate the inverse matrix*/
bool inverse(float cov[dim][dim], float covinv[dim][dim])
{
    // Find determinant of A[][]
    float det = determinant(cov, dim);
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }
 
    // Find adjoint
    float adj[dim][dim];
    adjoint(cov, adj);
 
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (int i=0; i<dim; i++)
        for (int j=0; j<dim; j++)
            covinv[i][j] = adj[i][j]/det;
 
    return true;
}

/*Function that calculates the Mahalanobis distance between a given point to classify and a 
data point already labelled in the data set*/
float Mahalanobis(float ptoclassify[dim],float covinv[dim][dim],float points[dim+1])
{
	float xtrans[1][dim];
	float x[dim][1];
	float transition[1][dim];
	float dist,temp;
	
	for(int i=0;i<dim;++i)
	{
		xtrans[0][i]=ptoclassify[i]-points[i];
		x[i][0]=ptoclassify[i]-points[i];
	}	
	
	for(int i=0;i<dim;++i)
	{
		temp=0;
		for(int j=0;j<dim;++j)
			temp+=xtrans[0][j]*covinv[j][i];
		transition[0][i]=temp;
	}	
	
	dist=0;
	for(int i=0;i<dim;++i)
		dist+=transition[0][i]*x[i][0];
	
	return dist;
	
}




int main()
{
	int cluster,K,noofpoints,countc=0,counti=0;
	float temp;
	cout<<"Enter the number of clusters: "<<endl;
	cin>>cluster;
	cout<<"Enter K: "<<endl;
	cin>>K;
	float cov[cluster][dim][dim];			 //Covariance matrix
	float covadj[cluster][dim][dim];		
	float covinv[cluster][dim][dim];		//Covariance Inverse matrix
	float mean[cluster][dim];        //holds mean value of each dimension of a cluster
	float sum[cluster][dim];
	float variance[cluster][dim];           //Holds the variance of each dimension of each cluster
	float covar[cluster];
	int label[cluster];
	
	for(int i=0;i<cluster;++i)
		covar[i]=label[i]=0;
	
	for(int i=0;i<cluster;++i)
		for(int j=0;j<dim;++j)
			variance[i][j]=0;
	
	
	for(int i=0;i<cluster;++i)
		for(int j=0;j<dim;++j)
			sum[i][j]=0;
		
	int pincluster[cluster];		 //counts points in a cluster;
	for(int i=0;i<cluster;++i)
		pincluster[i]=0;
	
	float ptoclassify[dim];
	cout<<"Enter the coordiantes of the point to be classified:"<<endl;
	for(int i=0;i<dim;++i)
		cin>>ptoclassify[i];
	
	/*A matrix of float values where each row contains information about a
	data point. Every column except the last holds the value across each 
	dimension and the last column contains the label value.*/
	float points[5000][dim+1];
	
	ifstream source;                    
    source.open("data.txt", ios_base::in); 
	ofstream file;                    
    file.open("data.txt",ios::app);
	std::string line;
	
	/*data taken from the file and stored into the matrix*/
	while(std::getline(source, line))
	{
		
		countc=0;	
		
		std::stringstream ss(line);

        while (ss >> temp)
        {
            points[counti][countc] = temp;
            ++countc;
        }
		
		counti++;
	}	
	noofpoints=counti;
	/*Array that holds  Mahalabonis distance measure between
	each point and the new point*/
	float mlbsdist[noofpoints][2];
	
	/*Counting mean of each cluster*/
	for(int i=0;i<noofpoints;++i)
	{
		int clusterno=points[i][dim];
		pincluster[clusterno]++;
		for(int j=0;j<dim;++j)
			sum[clusterno][j]+=points[i][j];
	}	
	
	for(int i=0;i<cluster;++i)
	{	
		for(int j=0;j<dim;++j)
			mean[i][j]=sum[i][j]/pincluster[i];
	}
	
	/*Calculation of variance for each cluster and dimension*/
	for(int i=0;i<noofpoints;++i)
	{
		int clusterno=points[i][dim];
		for(int j=0;j<dim;++j)
			variance[clusterno][j]+=pow(ptoclassify[j]-mean[clusterno][j],2);
	}
	
	
	for(int i=0;i<cluster;++i)
	{	
		for(int j=0;j<dim;++j)
			variance[i][j]/=pincluster[i];
	}
	
	
	/*Covariance matrix formed*/
	for(int i=0;i<cluster;++i)
	{	
		for(int j=0;j<dim;++j)
			cov[i][j][j]=variance[i][j];
	}
	
	for(int i=0;i<noofpoints-1;++i)
	{
		int clusterno=points[i][dim];
		for(int j=i+1;j<noofpoints;++j)
		{	
			if(points[j][dim]==clusterno)
				covar[clusterno]+=(points[i][0]-points[j][0])*(points[i][1]-points[j][1]);
		}
	}	
	
	for(int i=0;i<cluster;++i)
	{	
		cov[i][1][0]=cov[i][0][1]=covar[i]/pincluster[i];
	}
	
	
	/*Displaying covariance matrices*/
	for(int i=0;i<cluster;++i)
	{	
		cout<<"Cluster "<<i<<endl;
		for(int j=0;j<dim;++j)
		{	
			for(int k=0;k<dim;++k)
				cout<<cov[i][j][k]<<" ";
			cout<<endl;
		}	
		cout<<endl;
	}
	
	/*Inverse of the covariance matrix calculated*/
	for(int i=0;i<cluster;++i)
	{
		inverse(cov[i],covinv[i]);
	}	
	
	/*Displaying inverse matrix*/
	for(int i=0;i<cluster;++i)
	{	
		cout<<"Cluster "<<i<<endl;
		for(int j=0;j<dim;++j)
		{	
			for(int k=0;k<dim;++k)
				cout<<covinv[i][j][k]<<" ";
			cout<<endl;
		}	
		cout<<endl;
	}
	
	
	/*Loop to calculate Mahalabonis distance*/
	for(int i=0;i<noofpoints;++i)
	{
		int clusterno=points[i][dim];
		mlbsdist[i][1]=clusterno;
		mlbsdist[i][0]=Mahalanobis(ptoclassify,covinv[clusterno],points[i]);
		
	}
	
	/*Points sorted according to the Mahalanobis distance*/
	for(int i=0;i<noofpoints-1;i++)
    {
        float min=mlbsdist[i][0];
        int loc=i;
        for(int j=i+1;j<noofpoints;j++)
        {
            if(min>mlbsdist[j][0])
            {
                min=mlbsdist[j][0];
                loc=j;
            }
        }
 
        temp=mlbsdist[i][0];
		float templab=mlbsdist[i][1];
        mlbsdist[i][0]=mlbsdist[loc][0];
		mlbsdist[i][1]=mlbsdist[loc][1];
		mlbsdist[loc][0]=temp;
        mlbsdist[loc][1]=templab;
    }
	
	
	cout<<"The sorted distances(Mahalanobis) and its respective labels: "<<endl;
	for(int i=0;i<noofpoints;++i)
	{
		cout<<mlbsdist[i][0]<<" "<<mlbsdist[i][1]<<endl;
	}
	
	
	/*The count of labels in K nearest points is calculated*/
	for(int i=0;i<K;++i)
	{
		int clusterno=mlbsdist[i][1];
		label[clusterno]++;
	}	
	
	
	/*Final Label is decided by the label associated with majority of points in first
	K nearest neighbours*/
	int max=label[0];
	int finallabel=0;
	for(int i=1;i<cluster;++i)
	{
		if(max<label[i])
		{
			max=label[i];
			finallabel=i;
		}	
	}	
	
	cout<<"The point is labelled: "<<finallabel;
	
	file<<"\n";
	for(int i=0;i<dim;++i)
		file<<ptoclassify[i]<<" ";
	
	file<<finallabel;
	source.close();
	
	/* Value Checker
	for(int i=0;i<cluster;++i)
		cout<<"Cluster "<<i<<":"<<pincluster[i]<<endl;	
	
	for(int i=0;i<cluster;++i)
	{	
		cout<<"Cluster "<<i<<endl;
		for(int j=0;j<dim;++j)
			cout<<variance[i][j]<<" ";
		cout<<endl;
	}*/
	return 0;
}