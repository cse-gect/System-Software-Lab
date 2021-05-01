#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *f1, *f2, *f3, *f4, *f5;
    int i, len;
    char mn[20], opnd[20], la[20];
    char name[20], mne1[20], opnd1[20], arg[20];
    f1 = fopen("minp2.txt", "r");
    f2 = fopen("ntab2.txt", "w+");
    f3 = fopen("dtab2.txt", "w+");
    f4 = fopen("atab2.txt", "w+");
    f5 = fopen("op2.txt", "w");
    if (!f1)
    {
        printf("Cannot open file minp2.txt\n");
        exit(1);
    }
    fscanf(f1, "%s%s%s", la, mn, opnd);
    while (!feof(f1))
    {
        if (strcmp(mn, "MACRO") == 0)
        {
            fprintf(f2, "%s\n", la);
            fprintf(f3, "%s\t%s\n", la, opnd);
            while (strcmp(mn, "MEND") != 0)
            {
                fscanf(f1, "%s%s%s", la, mn, opnd);
                fprintf(f3, "%s\t%s\n", mn, opnd);
            }
        }
        else

            fscanf(f1, "%s%s%s", la, mn, opnd);
    }

    fseek(f1, 0, SEEK_SET);
    fseek(f2, 0, SEEK_SET);
    fseek(f3, 0, SEEK_SET);
    fscanf(f1, "%s%s%s", la, mn, opnd);
    while (strcmp(mn, "END") != 0)
    {
        if (strcmp(mn, "MACRO") == 0)
        {
            fscanf(f1, "%s%s%s", la, mn, opnd);
            while (strcmp(mn, "MEND") != 0)
                fscanf(f1, "%s%s%s", la, mn, opnd);
        }
        else
        {
            fscanf(f2, "%s", name);
            if (strcmp(mn, name) == 0)
            {
                len = strlen(opnd);
                for (i = 0; i < len; i++)
                {
                    if (opnd[i] != ',')
                        fprintf(f4, "%c", opnd[i]);
                    else
                        fprintf(f4, "\n");
                }
                fseek(f2, SEEK_SET, 0);
                fseek(f4, SEEK_SET, 0);
                fscanf(f3, "%s%s", mne1, opnd1);
                printf(".\t%s\t%s\n", mne1, opnd);
                fprintf(f5, ".\t%s\t%s\n", mne1, opnd);
                fscanf(f3, "%s%s", mne1, opnd1);
                while (strcmp(mne1, "MEND") != 0)
                {
                    if ((opnd1[0] == '&'))
                    {
                        fscanf(f4, "%s", arg);
                        printf("-\t%s\t%s\n", mne1, arg);
                        fprintf(f5, "-\t%s\t%s\n", mne1, arg);
                    }
                    else
                    {
                        printf("-\t%s\t%s\n", mne1, opnd1);
                        fprintf(f5, "-\t%s\t%s\n", mne1, opnd1);
                    }
                    fscanf(f3, "%s%s", mne1, opnd1);
                }
            }
            else
                printf("%s\t%s\t%s\n", la, mn, opnd);
            fprintf(f5, "%s\t%s\t%s\n", la, mn, opnd);
        }
        fscanf(f1, "%s%s%s", la, mn, opnd);
    }
    printf("%s\t%s\t%s\n", la, mn, opnd);
    fprintf(f5, "%s\t%s\t%s\n", la, mn, opnd);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
}