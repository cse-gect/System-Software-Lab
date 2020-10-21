#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
    FILE *fi,*fopt,*fsymw,*fsymr,*fo;
    char lab[10],mn[10],op[10],tmps[10];
    int opi,sa,loc,tmp,flag,len;
    fi=fopen("input.txt","r");
    fo=fopen("output.txt","w");
    if(!fi){
        printf("input.txt failed to open");
        exit(0);
    }
    fsymw=fopen("symtab.txt","w");
    if(!fsymw){
        printf("symtab.txt failed to open");
        exit(0);
    }
    fscanf(fi,"%s %s %d",lab,mn,&opi);
    if(strcmp(mn,"START")==0){
        sa=opi;
        loc=sa;
        printf("\t%s\t%s\t%d\n",lab,mn,opi);
        fprintf(fo,"\t%s\t%s\t%d\n",lab,mn,opi);
    }
    else{
        loc=0;
    }
    fscanf(fi,"%s %s %s",lab,mn,op);
    while (!feof(fi))
    {
        printf("\t%d\t%s\t%s\t%s\n",loc,lab,mn,op);
        fprintf(fo,"\t%d\t%s\t%s\t%s\n",loc,lab,mn,op);
        if(strcmp(lab,"-")!=0)
        {   
            flag=0;
            fsymr=fopen("symtab.txt","r");
            fscanf(fsymr,"%d %s",&tmp,tmps);
            while(!feof(fsymr))
            {
                if(strcmp(lab,tmps)==0)
                {
                    printf("\nError: Duplicate Label\n");
                    fprintf(fo,"\nError: Duplicate Label\n");
                    flag=1;
                    break;
                }
                fscanf(fsymr,"%d %s",&tmp,tmps);
            }
            fclose(fsymr);
            if(!flag)
            {
                fprintf(fsymw,"%d %s\n",loc,lab);
            }     
        }
        fopt=fopen("optab.txt","r");
        fscanf(fopt,"%s %d",tmps,&tmp);
        while(!feof(fopt))
        {
            if(strcmp(mn,tmps)==0)
            {
                loc+=3;
                break;
            }
            fscanf(fopt,"%s %d",tmps,&tmp);
        }
        fclose(fopt);
        if(strcmp(mn,"WORD")==0)
        {
            loc+=3;
        }
        else if (strcmp(mn,"RESW")==0)
        {
            opi=atoi(op);
            loc+=(3*opi);
        }
        else if (strcmp(mn,"RESB")==0)
        {
            opi=atoi(op);
            loc+=opi;
        }
        else if(strcmp(mn,"BYTE")==0)
        {
            if(op[0]=='X'){
                loc=loc+1;
            }
            else{
                len=strlen(op)-3;
                loc+=len;
            }
        }
        fscanf(fi,"%s %s %s",lab,mn,op);      
    }
    printf("\nProgram length = %d",loc-sa);
    fprintf(fo,"\nProgram length = %d",loc-sa);
    fclose(fi);
    fclose(fsymw);
    fclose(fo);  
}
