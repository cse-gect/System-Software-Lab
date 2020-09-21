#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap(int *xp,int *yp){
  int temp=*xp;
  *xp=*yp;
  *yp=temp;
}
void asort(int a[],int n){
  int i,j,min;
  for(i=0;i<n-1;i++){
    min=i;
    for(j=i+1;j<n;j++){
      if(a[j]<a[min])
        min=j;
    }
    swap(&a[min],&a[i]);
  }
}
void dsort(int a[],int n)
{
  int i,j,max;
  for (i = 0; i < n-1; i++) {
    max=i;
    for (j = 0; j < n; j++) {
      if(a[j]>a[max])
        j=max;
    }
    swap(&a[max],&a[i]);
  }
}
void fcfs(int n,int cur,int req[]){
  int i,seek=0,temp=cur;
  for(i=0;i<n;i++){
    seek+=abs(req[i]-temp);
    temp=req[i];
  }
  printf("\nFCFS Total head movement : %d\n",seek);
}
void scan(int n,int cur,int req[],int max){
  int q1[50],q2[50];
  int i,j,nq1=0,nq2=0,seek=0,temp=cur;
  for(i=0;i<n;i++){
    if(req[i]>=cur){
      q1[nq1++]=req[i];
    }
    else{
      q2[nq2++]=req[i];
    }
  }
  asort(q1,nq1);
  dsort(q2,nq2);
  q1[nq1++]=max;
  for (i = 0; i < nq1; i++) {
    seek+=abs(q1[i]-temp);
    temp=q1[i];
  }
  for (i = 0; i < nq2; i++) {
    seek+=abs(q2[i]-temp);
    temp=q2[i];
  }
  printf("\nSCAN Total head movement : %d\n",seek);
}
void cscan(int n,int cur,int req[],int max){
  int q1[50],q2[50];
  int i,j,nq1=0,nq2=0,seek=0,temp=cur;
  for(i=0;i<n;i++){
    if(req[i]>=cur){
      q1[nq1++]=req[i];
    }
    else{
      q2[nq2++]=req[i];
    }
  }
  asort(q1,nq1);
  asort(q2,nq2);
  q1[nq1++]=max;
  for ( i = 0; i < nq1; i++) {
    seek+=abs(q1[i]-temp);
    temp=q1[i];
  }
  seek+=max;
  temp=0;
  for ( i = 0; i < nq2; i++) {
    seek+=abs(q2[i]-temp);
    temp=q2[i];
  }
  printf("\nC-SCAN Total head movement : %d\n",seek);
}
void main(){
  FILE *fp;
  fp=fopen("input.txt","r");
  if(fp==NULL){
    printf("input.txt failed to open\n" );
    exit(0);
  }
  int n,i,temp,cur,max,req[50],seek=0;
  printf("\nEnter current head position :");
  fscanf(fp,"%d",&cur);
  printf("\nEnter maximum range :");
  fscanf(fp,"%d",&max);
  printf("\nEnter no. of requests :");
  fscanf(fp,"%d",&n );
  printf("\nEnter requests array :\n");
  for(i=0;i<n;i++){
    fscanf(fp,"%d",&req[i] );
  }
  fclose(fp);
  fcfs(n,cur,req);
  scan(n,cur,req,max);
  cscan(n,cur,req,max);
}
