#include<stdio.h>

struct process{
  int pid;
  int bt;
  int at;
  int pt;
};

int main(){
  // Initializing Variables
  struct process prt[10], tempProc;
  int n, twt[10], tat[10], sm, wtTot, taTot;
  float awt, atat;
  // Printing Welcome Note
  printf("\e[1;1H\e[2J");
  printf("\nCPU Scheduling Algorithms\n-----------------------\n\n");
  // Reading Input Values
  printf("Enter Number of Processes : ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    printf("\n\nEnter Process Id of Process %d : ", i+1);
    scanf("%d", &prt[i].pid);
    printf("\nEnter Arrival time of Process %d : ", i+1);
    scanf("%d", &prt[i].at);
    printf("\nEnter Burst time of Process %d : ", i+1);
    scanf("%d", &prt[i].bt);
    printf("\nEnter Priority of Process %d : ", i+1);
    scanf("%d", &prt[i].pt);
  }
  // Sorting Processes on Arrival Order
  for (int i = 0; i < n-1; i++){
    sm = i;
    for (int j = i+1; j < n; j++){
      if (prt[j].at < prt[sm].at) {
        sm = j;
      }
    }
    if (sm != i) {
      tempProc = prt[i];
      prt[i] = prt[sm];
      prt[sm] = tempProc;
    }
  }



struct process pr[100];
//FCFS-------------------------------------------------------------------------------



  for (int i = 0; i < n; i++){
    pr[i] = prt[i];
  }
  // Calculating Waiting time and Turnaround time of each process
  twt[0] = 0;
  tat[0] = pr[0].bt;
  for (int i = 1; i < n; i++){
    twt[i] = 0;
    for (int j = i-1; j >= 0; j--) {
      twt[i] += pr[j].bt;
    }
    twt[i] -= pr[i].at;
    tat[i] = twt[i] + pr[i].bt;
  }
  // Calculating Average Waiting time and Average Turnaround time
  wtTot = 0;
  taTot = 0;
  for (int i = 0; i < n; i++){
    wtTot+=twt[i];
    taTot+=tat[i];
  }

  awt = (float)wtTot/n;
  atat = (float)taTot/n;
  // Displaying Output
  printf("\n\n\nFCFS\n------");
  printf("\n\nAverage Waiting Time : %.2f\n", awt);
  printf("\nAverage Turn Around Time : %.2f\n\n\n", atat);



//SJF------------------------------------------------------------------------------



  for (int i = 0; i < n; i++){
    pr[i] = prt[i];
  }
  int st, top=-1, gtop=-1, done[10], tInd;
  struct process gnattChart[10], tempChart[10];
  for(int i = 0; i < n; i++){
    done[i] = 0;
  }

  // Preparing Gnatt Chart on SJF
  st = pr[0].at;
  for (int k = 0; k < n; k++){
    for (int i = 0; i < n; i++){
      if (pr[i].at <= st && done[i] != 1) {
        tempChart[++top] = pr[i];
      }
    }

    for (int i = 0; i < top; i++) {
      sm = i;
      for (int j = i+1; j <= top; j++){
        if (tempChart[j].bt < tempChart[sm].bt) {
          sm = j;
        }
      }
      if (sm != i) {
        tempProc = tempChart[i];
        tempChart[i] = tempChart[sm];
        tempChart[sm] = tempProc;
      }
    }

    tInd = tempChart[0].pid;
    for (int m = 0; m < n; m++){
      if (pr[m].pid == tInd) {
        tInd = m;
        break;
      }
    }

    done[tInd] = 1;
    gnattChart[++gtop]=tempChart[0];
    st += tempChart[0].bt;
    top=-1;
  }

  // Calculating Waiting time and Turnaround time of each process
  twt[0] = 0;
  tat[0] = pr[0].bt;
  for (int i = 1; i < n; i++){
    twt[i] = 0;
    for (int j = i-1; j >= 0; j--) {
      twt[i] += gnattChart[j].bt;
    }
    twt[i] -= gnattChart[i].at;
    tat[i] = twt[i] + gnattChart[i].bt;
  }
  // Calculating Average Waiting time and Average Turnaround time
  wtTot = 0;
  taTot = 0;
  for (int i = 0; i < n; i++){
    wtTot+=twt[i];
    taTot+=tat[i];
  }

  awt = (float)wtTot/n;
  atat = (float)taTot/n;
  // Displaying Output
  printf("\n\n\nSJF\n------");
  printf("\n\nAverage Waiting Time : %.2f\n", awt);
  printf("\nAverage Turn Around Time : %.2f\n\n\n", atat);



//Round Robin----------------------------------------------------------



  int qTime, rear = n-1, arBt[10], tempWt, tempTat, ind;
  printf("\n\nEnter the Time Quantum for Round Robin : ");
  scanf("%d", &qTime);
  for (int i = 0; i < n; i++){
    pr[i] = prt[i];
    arBt[i] = pr[i].bt;
  }
  st = pr[0].at;
  wtTot = 0;
  taTot = 0;
  for (int i = 0; i <= rear; i++){
    if (pr[i].at <= st && pr[i].bt > 0){
      if (pr[i].bt >= qTime){
        pr[i].bt -= qTime;
        st += qTime;
      }else{
        st += pr[i].bt;
        pr[i].bt = 0;
      }
    }
    if (pr[i].bt > 0){
      pr[++rear] = pr[i];
    }else {
      ind = pr[i].pid;
      for (int j = 0; j < n; j++){
        if (prt[j].pid == ind) {
          ind = j;
          break;
        }
      }
      tempWt = st - pr[ind].at - arBt[ind];
      wtTot += tempWt;
      tempTat = st - pr[ind].at;
      taTot += tempTat;
    }
  }
  awt = (float)wtTot/n;
  atat = (float)taTot/n;
  // Displaying Output
  printf("\n\n\nRound Robin\n------");
  printf("\n\nAverage Waiting Time : %.2f\n", awt);
  printf("\nAverage Turn Around Time : %.2f\n\n\n", atat);



//Priority-----------------------------------------------------------------------------



  for (int i = 0; i < n; i++){
    pr[i] = prt[i];
  }
  top=-1;
  gtop=-1;
  for(int i = 0; i < n; i++){
    done[i] = 0;
  }

  // Preparing Gnatt Chart on Priority
  st = pr[0].at;
  for (int k = 0; k < n; k++){
    for (int i = 0; i < n; i++){
      if (pr[i].at <= st && done[i] != 1) {
        tempChart[++top] = pr[i];
        // done[i] = 1;
      }
    }
    for (int i = 0; i < top; i++) {
      sm = i;
      for (int j = i+1; j <= top; j++){
        if (tempChart[j].pt < tempChart[sm].pt) {
          sm = j;
        }
      }
      if (sm != i) {
        tempProc = tempChart[i];
        tempChart[i] = tempChart[sm];
        tempChart[sm] = tempProc;
      }
    }

    tInd = tempChart[0].pid;
    for (int m = 0; m < n; m++){
      if (pr[m].pid == tInd) {
        tInd = m;
        break;
      }
    }

    done[tInd] = 1;
    gnattChart[++gtop]=tempChart[0];
    st += tempChart[0].bt;
    top=-1;
  }

  // Calculating Waiting time and Turnaround time of each process
  twt[0] = 0;
  tat[0] = pr[0].bt;
  for (int i = 1; i < n; i++){
    twt[i] = 0;
    for (int j = i-1; j >= 0; j--) {
      twt[i] += gnattChart[j].bt;
    }
    twt[i] -= gnattChart[i].at;
    tat[i] = twt[i] + gnattChart[i].bt;
  }
  // Calculating Average Waiting time and Average Turnaround time
  wtTot = 0;
  taTot = 0;
  for (int i = 0; i < n; i++){
    wtTot+=twt[i];
    taTot+=tat[i];
  }

  awt = (float)wtTot/n;
  atat = (float)taTot/n;
  // Displaying Output
  printf("\n\n\nPriority\n------");
  printf("\n\nAverage Waiting Time : %.2f\n", awt);
  printf("\nAverage Turn Around Time : %.2f\n\n\n", atat);



  return 0;
}
