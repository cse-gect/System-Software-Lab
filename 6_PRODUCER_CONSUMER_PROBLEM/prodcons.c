#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

int n,bufferSize = 20,buffer=0;
int prate[10],crate[10];
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
void *producer(void *vargp){
    for(int i=0;i<n;){
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if (buffer+prate[i]<bufferSize)
        {         
            printf("\nBuffer spaces filled: %d\n", buffer);
            printf("Producer produced successfully\n",prate[i]);
            buffer+=prate[i];
            i+=1;
        }
        else
        {
            printf("\nProducer cannot produce");
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *vargp){
    for(int i=0;i<n;)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if (buffer-crate[i]>=0)
        {         
            printf("\nBuffer spaces filled: %d\n", buffer);
            printf("Consumer consumed successfully\n",crate[i]);
            buffer-=crate[i];
            i+=1;
        }
        else
        {
            printf("\nConsumer cannot consume");
        }
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}
void main(){
    int i;
    FILE *fp;
    fp=fopen("input.txt","r");
    if(fp==NULL){
	printf("\nCannot open input.txt");
	exit(0);
    }
    pthread_t prod,cons;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,bufferSize);
    sem_init(&full,0,0);
    printf("\nEnter the Buffer size: ");
    fscanf(fp,"%d",&bufferSize);
    printf("\nEnter the number of productions/consumptions:");
    fscanf(fp,"%d",&n);
    printf("\nEnter Production rates : ");
    for(i=0;i<n;++i)
        fscanf(fp,"%d",&prate[i]);
    printf("\nEnter Consumption rates : ");
    for(i=0;i<n;++i)
        fscanf(fp,"%d",&crate[i]);
    pthread_create(&prod,NULL,producer,NULL);   
    pthread_create(&cons,NULL,consumer,NULL);
    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    printf("Buffer spaces filled: %d\n", buffer);
    pthread_mutex_destroy(&mutex);
    fclose(fp);
    sem_destroy(&empty);
    sem_destroy(&full);    
}
