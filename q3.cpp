#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
 #include<iostream>
using namespace std;
void *multiply(void* arg)         //multiply function to calculate each value of resultant Matrix
{
    int *data = (int *)arg;
    int k = 0, i = 0;
      
    int x = data[0];
    for (i = 0; i < 3; i++)
          k += data[i]*data[i+3];


    pthread_exit((int*)k);                       //returning value
}
  
int main()
{
  
    int A[3][3]; 
    int B[3][3]; 
    int r1=3,c1=3,r2=3,c2=3,i,j,k;
   
    
  
    cout<<"Enter Values for Matrix A:\n"<<endl;

    for (i = 0; i < r1; i++)                     //Taking input for Matrix A
            for (j = 0; j < c1; j++) 
                  { 
		   cout<<"A["<<i<<"]["<<j<<"]: ";
                   cin>>A[i][j]; 
                   cout<<"\n";
		  }
        

cout<<"Enter Values for Matrix B:\n"<<endl;

    for (i = 0; i < r1; i++)                      //Taking input for Matrix B
            for (j = 0; j < c1; j++) 
                  { 
		   cout<<"B["<<i<<"]["<<j<<"]: ";
                   cin>>B[i][j]; 
                   cout<<"\n";
		  }
     
           
cout<<"Matrix A is: "<<endl;             //printing Matrix A

    for (i = 0; i < r1; i++)
	{
		for(j = 0; j < c1; j++)
			cout<<A[i][j]<<" ";
		cout<<"\n";
    	}
              
cout<<"Matrix B is: "<<endl;              //printing Matrix B
         
    for (i = 0; i < r2; i++)
	{
		for(j = 0; j < c2; j++)
		    cout<<B[i][j]<<" ";
	        cout<<"\n";   
    	}
          
    pthread_t threads[9];                            //threads ids
    int count = 0;
      
   
    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++)
               {
	     int *data=new int[6];
            for (k = 0; k < c1; k++)                //stroring   column values                
                data[k] = A[i][k];
            for (k = 0; k < r2; k++)                //storing row values
                data[k+3] = B[k][j];
               
                pthread_create(&threads[count], NULL, multiply, (void*)(data));    //creating threads
                 count++;
                }
      
   cout<<"Resultant Matrix is: "<<endl;
    for (i = 0; i < 9; i++) 
       {
         void *k;
         pthread_join(threads[i], &k);                      //joining and getting values       
         cout<<(int&)k<<" ";
         if ((i + 1) % c2 == 0)
         cout<<endl;  
       }
  
      
  
  return 0;
}
