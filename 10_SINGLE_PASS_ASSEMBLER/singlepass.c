#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *f1, *f2, *f3, *f4, *f5,*f6;
    int loc, sa, i = 0, j = 0, m[10], pgmlen, len, k, len1, l = 0;
    char name[10], opnd[10], la[10], mn[10], s1[10], mn1[10], opnd1[10];
    char locs[10], ms[10];
    char sym[10], symaddr[10], obj1[10], obj2[10], s2[10], q[10], s3[10];
    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");
    f3 = fopen("symtab.txt", "w+");
    f4 = fopen("symtab1.txt", "w+");
    f5 = fopen("output.txt", "w+");
    f6 = fopen("result.txt", "w+");
    fscanf(f1, "%s%s%s", la, mn, opnd);
    if (strcmp(mn, "START") == 0)
    {
        sa = atoi(opnd);
        strcpy(name, la);
        loc = sa;
    }
    strcpy(s1, "*");
    fscanf(f1, "%s%s%s", la, mn, opnd);
    while (strcmp(mn, "END") != 0)
    {
        if (strcmp(la, "-") == 0)
        {
            fscanf(f2, "%s%s", mn1, opnd1);
            while (!feof(f2))
            {
                if (strcmp(mn1, mn) == 0)
                {
                    m[i] = loc + 1;
                    fprintf(f3, "%s\t%s\n", opnd, s1);
                    fprintf(f5, "%s\t0000\n", opnd1);
                    loc = loc + 3;
                    i = i + 1;
                    break;
                }
                else
                    fscanf(f2, "%s%s", mn1, opnd1);
            }
        }

        else
        {
            fseek(f3, SEEK_SET, 0);
            fscanf(f3, "%s%s", sym, symaddr);
            while (!feof(f3))
            {
                if (strcmp(sym, la) == 0)
                {
                    sprintf(locs,"%d",loc);
                    fprintf(f4, "%s\t%s\n", la, locs);
                    sprintf(ms,"%d",m[j]);
                    j = j + 1;
                    fprintf(f5, "%s\t%s\n", ms, locs);
                    i = i + 1;
                    break;
                }
                else
                    fscanf(f3, "%s%s", sym, symaddr);
            } 
            if (strcmp(mn, "RESW") == 0)
                loc = loc + 3 * atoi(opnd);
            else if (strcmp(mn, "BYTE") == 0)
            {
                strcpy(s2, "-");
                len = strlen(opnd);
                loc = loc + len - 2;
                for (k = 2; k < len; k++)
                {
                    q[l] = opnd[k];
                    l = l + 1;
                }
                fprintf(f5, "%s\t%s\n", q, s2);
                break;
            }
            else if (strcmp(mn, "RESB") == 0)
                loc = loc + atoi(opnd);
            else if (strcmp(mn, "WORD") == 0)
            {
                strcpy(s3, "#");
                loc = loc + 3;
                fprintf(f5, "%s\t%s\n", opnd, s3);
                break;
            }
        }

        fseek(f2, SEEK_SET, 0);
        fscanf(f1, "%s%s%s", la, mn, opnd);
    }
    fseek(f5, SEEK_SET, 0);
    pgmlen = loc - sa;
    printf("H^%s^%d^0%x\n", name, sa, pgmlen);
    fprintf(f6,"H^%s^%d^0%x\n", name, sa, pgmlen);
    printf("T^");
    fprintf(f6,"T^");
    printf("00%d^0%x", sa, pgmlen);
    fprintf(f6,"00%d^0%x", sa, pgmlen);
    fscanf(f5, "%s%s", obj1, obj2);
    while (!feof(f5))
    {
        if (strcmp(obj2, "0000") == 0) {
            printf("^%s%s", obj1, obj2);
            fprintf(f6,"^%s%s", obj1, obj2); }
        else if (strcmp(obj2, "-") == 0)
        {
            printf("^");
            fprintf(f6,"^");
            len1 = strlen(obj1);
            for (k = 0; k < len1; k++)
                printf("%d", obj1[k]);
                fprintf(f6,"%d", obj1[k]);
        }
        else if (strcmp(obj2, "#") == 0)
        {
            printf("^");
            fprintf(f6,"^");
            printf("%s", obj1);
            fprintf(f6,"%s", obj1);
        }
        fscanf(f5, "%s%s", obj1, obj2);
    }
    fseek(f5, SEEK_SET, 0);
    fscanf(f5, "%s%s", obj1, obj2);
    while (!feof(f5))
    {
        if (strcmp(obj2, "0000") != 0)
        {
            if (strcmp(obj2, "-") != 0)
            {
                if (strcmp(obj2, "#") != 0)
                {
                    printf("\n");
                    fprintf(f6,"\n");
                    printf("T^%s^02^%s", obj1, obj2);
                    fprintf(f6,"T^%s^02^%s", obj1, obj2);
                }
            }
        }
        fscanf(f5, "%s%s", obj1, obj2);
    }
    printf("\nE^00%d", sa);
    fprintf(f6,"\nE^00%d", sa);
    printf("\n");
}
