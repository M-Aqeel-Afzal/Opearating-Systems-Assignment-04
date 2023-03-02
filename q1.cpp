#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include <pthread.h>

using namespace std;
string abc="abcdefghijklmnopqrstuvwxyz";
int j=0;
struct file{
char* s1=new char[20];
	
};

void* thread_count(void* arg){                             //thread count function to count
	file *f=(file* )arg;
	char *buf=new char[20000];
	int stream = open(f->s1, O_RDONLY);
	 read(stream, buf,20000);
int count=0;
int i=0;
while(buf[i]!='\0')
{
if(buf[i]==abc[j]||buf[i]==abc[j])
count++;
i++;
}
    cout<<"\nthread: "<<j+1<<" is counting the character\" "<<abc[j]<<"\"  -->> "<<count<<endl;  //printing count of each character
j++;
pthread_exit((char*)count);
}




int  main(int argc,char *argv[])               //run time arguments
{
int total=0;
void* result; 
file obj;
	pthread_t id[26];
	
obj.s1=argv[1];

	
    for(int i=0;i<26;i++)                                         //creating 26 threads for counting
	{pthread_create(&id[i],NULL,thread_count,(void*)&obj);
	pthread_join(id[i],&result);                      //joining and getting returned count value
        total=total+(int&)result;                             //total sum
               
	}
	
	cout<<"final sum: "<<total<<endl;               //printing total sum
    pthread_exit(NULL);
return 0;
}



