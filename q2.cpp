#include<pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
  #include <iostream>
using namespace std;
void mergeSorting(int[],int,int); 
void merging(int[],int,int,int);
int size;
struct siz{

int *a=new int;
};
void display(int arr[], int size)   //display function to display array values
{
    
    for(int i = 0; i < size; i++)
    {
        cout<<arr[i]<<"   ";
    }
    cout<<"\n";
}


void mergeSorting(int arr[], int start, int end)     //Divide,conqure and then combine
{
    int midel;
    if(start<end)
    {
        midel = (start+end)/2;
        
        mergeSorting(arr,start,midel);             //Dividing
        mergeSorting(arr,midel+1,end);            //Conquring
        merging(arr,start,midel,end);              //Combing
    }
}

void merging(int arr[], int start, int midel, int end)   //function for combining
{
    int i=start,j=midel+1,p,index = start;
    int temp[size];
    
    while(i<=midel && j<=end)
    {
        if(arr[i]<arr[j])
        {
            temp[index] = arr[i];
            i = i+1;
        }
        else
        {
            temp[index] = arr[j];
            j = j+1;
        }
        
        index++;
    }
    if(i>midel)
    {
        while(j<=end)
        {
            temp[index] = arr[j];
            index++;
            j++;
        }
    }
    else
    {
        while(i<=midel)
        {
            temp[index] = arr[i];
            index++;
            i++;
        }
    }
    p = start;
    while(p<index)
    {
        arr[p]=temp[p];
        p++;
    }
}

void *mergesort1(void* arg)         //thread 1 mergesort function
{
    int *data = (int *)arg;
    int k = 0, i = 0;
   mergeSorting(data,0,size/2-1);

    pthread_exit(NULL);                       
}

void *mergesort2(void* arg)        //thread 2 mergesort function
{
    int *data = (int *)arg;
    int k = 0, i = 0;
   mergeSorting(data,size/2,size-1);

   pthread_exit(NULL);                       
}


int main()
{

    int i; 

cout<<"Total system cores are 2 with 4 logical processors  but Ubuntu(VMWare) haave 2 processor so  : "<<endl;
system("grep -m 1 'cpu cores'  /proc/cpuinfo");
cout<<"MAC Address: "<<endl;
system("for x in `ls /sys/class/net |grep -v lo`; do cat /sys/class/net/$x/address; done");
cout<<"\n\nEnter Size of array : "<<endl;
cin>>size;

int a[size];
 cout<<"Input:"<<endl;
for(int i=0;i< size;i++)
cin>>a[i];


    cout<<"Before sorting array is: \n"; 
    display(a, size);                  //displaying  unsorted array.
    cout<<"After sorting array is: \n"; 
    
pthread_t threads[2];
       pthread_create(&threads[0], NULL, mergesort1,(void*)&a);
       pthread_create(&threads[1], NULL, mergesort2,(void*)&a);
  
    
   
       pthread_join(threads[0], NULL);
       pthread_join(threads[1], NULL);
 merging(a,0,size/2-1,size-1);         //Combining 
display(a, size);                    //displaying sorted array.



   
  

//wmic cpu get NumberOfCores, NumberOfLogicalProcessors/Format:List             //cmd
 cout<<"MergeSort Refrence Link :\nhttps://prepinsta.com/cpp-program/merge-sort/#:~:text=Merge%20Sort%20in%20C%2B%2B%201%20File%20of%20any,It%20requires%20more%20space%20and%20is%20less%20efficient"<<endl;

    return 0;
}

















