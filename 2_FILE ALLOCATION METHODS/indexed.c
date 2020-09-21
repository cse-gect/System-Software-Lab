#include <stdio.h>
void main()
{

    int nb,nf,nd,i,j,ind,k=0,fr=1,index[10][10]={0};
    char content[10];
    int len[10],disp[10],p[10],f[10]={0},req[10]={0};
    char s[10];
    printf("\nEnter No of blocks:");
    scanf("%d",&nb);
    printf("Enter No of files:");
    scanf("%d",&nf);
    for(i=0;i<nf;i++)
    {
        printf("Enter Length,index node and contents of file :");
        scanf("%d%d%s",&len[i],&ind,s);
        req[i]= ind;
        if(!f[ind])
        {
            f[ind]=1;
            p[i]=0;
            for(j=0;j<len[i];j++)
            {
                if(!f[fr])
                {
                index[ind][j] = fr;
                content[fr]=s[j];
                f[fr]=1;
                fr++;
                }
                else{
                    fr++;
                }
            }
        }
        else{
            p[i]=1;

        }
    }
    printf("\n\n");
    printf("Enter No of files to be displayed :");
    scanf("%d",&nd);
    printf("Enter index of the files :");
    for(i=0;i<nd;i++){
      scanf("%d",&disp[i]);
    }
    printf("\n\n");
    for(i=0;i<nf;i++)
    {
        printf("P%d \t",i+1);
        if(!p[i])
        {
                if(req[i])
                {
                    printf("%d\t",req[i]);
                    j=0;
                    while(index[req[i]][j]!=0)
                    {
                        if(j==0)
                            printf("%d",index[req[i]][j]);
                        else
                            printf(",%d",index[req[i]][j]);
                        j++;
                    }

                }
            printf("\tAllocated\n");
        }
        else
            printf("%d\t\tNot Allocated\n",req[i]);

    }
    printf("Index \t Allocated block \t Content \n");
    for(i=0;i<nd;i++)
    {
        for(k=0;k<nf;k++){
            if(disp[i]==req[k]){
                j=0;
                int l=req[k];
                while(index[l][j]!=0)
                {
                    printf("%d \t",l);
                    printf("\t%d \t ",index[l][j]);
                    printf("\t%c \n",content[index[l][j]]);
                    j++;
                }
                break;
            }
        }

    }
}
