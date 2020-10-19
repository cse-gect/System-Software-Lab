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
            printf("Buffer spaces filled: %d\n", buffer);
            printf("Producer produced %d items\n\n",prate[i]);
            store+=prate[i];
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
            printf("Buffer spaces filled: %d\n", buffer);
            printf("Consumer consumed %d items\n\n",crate[i]);
            store-=crate[i];
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
    pthread_t prod,cons;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);
    printf("Enter the Buffer size: ");
    scanf("%d",&bufferSize);
    printf("Enter the number of productions/consumptions");
    scanf("%d",&n);
    printf("\nEnter Production rates : ");
    for(i=0;i<n;++i)
        scanf("%d",&prate[i]);
    printf("\nEnter Consumption rates : ");
    for(i=0;i<n;++i)
        scanf("%d",&crate[i]);
    pthread_create(&prod,NULL,producer,NULL);   
    pthread_create(&cons,NULL,consumer,NULL);
    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full); 
    printf("Buffer spaces filled: %d\n", buffer);
}
