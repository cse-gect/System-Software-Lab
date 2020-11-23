#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main(){
    FILE *fi,*fsym,*fopt,*fo;
    int i,len,starti,temp;
    char lab[10],mn[10],op[10],addr[10],name[10],temps[10],start[10]="00";
    fi=fopen("input.txt","r");
    fsym=fopen("symtab.txt","r");
    fopt=fopen("optab.txt","r");
    fo=fopen("output.txt","w");
    if(!fi){
        printf("input.txt failed to open\n");
    }
    if(!fsym){
        printf("symtab.txt failed to open\n");
    }
    if(!fopt){
        printf("optab.txt failed to open/n");
    }
    fscanf(fi,"%d",&len);
    fscanf(fi,"%s %s %s %s",addr,lab,mn,op);
    if(strcmp(mn,"START")==0){
        strcpy(start,op);
        strcpy(name,lab);
        fscanf(fi,"%s %s %s %s",addr,lab,mn,op);
    }
    starti=atoi(start);
    printf("H^%s^%06d^%06d\nT^%06d^%d",name,starti,len,starti,len);
    fprintf(fo,"H^%s^%06d^%06d\nT^%06d^%d",name,starti,len,starti,len);
    while(strcmp(mn,"END")!=0){
        fseek(fopt,0,SEEK_SET);
        fscanf(fopt,"%s %d",temps,&temp);
        while(!feof(fopt))
        {
            if(strcmp(temps,mn)==0)
            {
                printf("^%02d",temp);
                fprintf(fo,"^%02d",temp);
                fseek(fsym,0,SEEK_SET);
                fscanf(fsym,"%d %s",&temp,temps);
                while(!feof(fsym))
                {
                    if(strcmp(temps,op)==0)
                    {
                        printf("%d",temp);
                        fprintf(fo,"%d",temp);
                        break;
                    }
                    fscanf(fsym,"%d %s",&temp,temps);
                }
                break;
            }
            fscanf(fopt,"%s %d",temps,&temp);
        }
        if(strcmp(mn,"WORD")==0)
        {
            printf("^%06d",atoi(op));
            fprintf(fo,"^%06d",atoi(op));
        }
        else if (strcmp(mn,"BYTE")==0)
        {
            printf("^");
            fprintf(fo,"^");
            for(i=2;i<strlen(op)-1;i++)
            {
                printf("%d",op[i]);
                fprintf(fo,"%d",op[i]);
            }
        }
        fscanf(fi,"%s %s %s %s",addr,lab,mn,op); 
    }
    printf("\nE^%06d",starti);
    fprintf(fo,"\nE^%06d",starti);
    fclose(fi);
    fclose(fo);
    fclose(fopt);
    fclose(fsym);
}
