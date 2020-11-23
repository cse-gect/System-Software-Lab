#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 10

typedef struct sym
{
    char label[10];
    int address;
} symtab;

FILE *fi,*fout;
symtab s[15];

int hashFunc(char c1[5])
{
    int a, val = 0, i, c;
    for (i = 0; c1[i] != '\0'; i++)
    {
        val = val * 128;
        c = c1[i];
        a = (int)c;
        val += a;
    }
    return val % max;
}

void create()
{
    int v, add;
    char c[10],ch='y';
    while (ch=='y')
    {
        printf("\nEnter the address: ");
        fscanf(fi,"%d", &add);
        fprintf(fout,"\nEnter the address: %d",add);
        printf("\nEnter the label: ");
        fscanf(fi,"%s", c);
        fprintf(fout,"\nEnter the label: %s",c);
        v = hashFunc(c);
        while ((s[v].address != 0))
            v++;
        strcpy(s[v].label, c);
        s[v].address = add;
        printf("\nContinue (y/n)?");
        fscanf(fi," %c",&ch);
        fprintf(fout,"\nContinue (y/n)?%c",ch);
    }
}

void search()
{
    char c[10];
    int v, i;
    printf("\nEnter the label: ");
    fscanf(fi,"%s", c);
    fprintf(fout, "\nEnter the label: %s", c);
    v = hashFunc(c);
    i = v;
    while (1)
    {
        if (s[i].address == 0)
        {
            printf("\nSymbol not present");
            fprintf(fout, "\nSymbol not present");
            break;
        }
        if (strcmp(s[i].label, c) == 0)
        {
            printf("\nThe label %s is present at index %d\n", s[i].label, i);
            fprintf(fout, "\nThe label %s is present at index %d\n", s[i].label, i);
            break;
        }
        i++;
        i = i % max;
    }
}

void main()
{
    int choice;

    fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fi = fopen("input.txt", "r");
    if (fi == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        strcpy(s[i].label, "");
        s[i].address = 0;
    }
    while (1)
    {
        printf("\nEnter your choice\n1.Create a symbol table\n2.Search in the symbol table: ");
        fscanf(fi,"%d", &choice);
        fprintf(fout,"\nEnter your choice\n1.Create a symbol table\n2.Search in the symbol table: %d",choice);
        switch (choice)
        {
        case 1:
            create();
            break;
        case 2:
            search();
            break;
        default:
            exit(1);
        }
    }
    fclose(fi);
    fclose(fout);
}
