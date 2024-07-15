#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct hand
{
    char h[100];
};

int readFromInput(struct hand *A)
{
    struct hand B;
    int n,i;
    scanf("%d ",&n);
    for (i=0;i<n;i++)
    {
        fgets(B.h,100,stdin);
        B.h[strcspn(B.h,"\n")]='\0';
        *A=B;
        *A++;
    }
    return n;
}

void printHand(struct hand a)
{
    int spades[13],hearts[13],diamonds[13],clubs[13];
    int i,counts=0,counth=0,countd=0,countc=0;
    for (i=0;i<13;i++)
    {
        if (a.h[3*i+1]=='S')
        {
            spades[counts]=a.h[3*i];
            counts++;
        }
        else if (a.h[3*i+1]=='H')
        {
            hearts[counth]=a.h[3*i];
            counth++;
        }
        else if (a.h[3*i+1]=='D')
        {
            diamonds[countd]=a.h[3*i];
            countd++;
        }
        else if (a.h[3*i+1]=='C')
        {
            clubs[countc]=a.h[3*i];
            countc++;
        }
    }
    printf("SPADES:   ");
    for (i=0;i<counts;i++)
        if (spades[i]>10)
            printf("%c ",spades[i]);
        else
            printf("%d ",spades[i]);
    printf("\nHEARTS:   ");
    for (i=0;i<counth;i++)
        if (hearts[i]>10)
            printf("%c ",hearts[i]);
        else
            printf("%d ",hearts[i]);
    printf("\nDIAMONDS: ");
    for (i=0;i<countd;i++)
        if (diamonds[i]>10)
            printf("%c ",diamonds[i]);
        else
            printf("%d ",diamonds[i]);
    printf("\nCLUBS:    ");
    for (i=0;i<countc;i++)
        if (clubs[i]>10)
            printf("%c ",clubs[i]);
        else
            printf("%d ",clubs[i]);
    printf("\n");
}

int balanced(struct hand a)
{
    int flag=1,counts=0,counth=0,countd=0,countc=0,i;
    for (i=0;i<13;i++)
    {
        if (a.h[3*i+1]=='S')
            counts++;
        if (a.h[3*i+1]=='H')
            counth++;
        if (a.h[3*i+1]=='D')
            countd++;
        if (a.h[3*i+1]=='C')
            countc++;
    }
    if (counts<2||counth<2||countd<2||countc<2)
            flag=0;
    if (counts==2)
        if(counth==2||countd==2||countc==2)
            flag=0;
    if (counth==2)
        if(counts==2||countd==2||countc==2)
            flag=0;
    if (countd==2)
        if(counth==2||counts==2||countc==2)
            flag=0;
    if (countc==2)
        if(counth==2||countd==2||counts==2)
            flag=0;
    return flag;
}

int hcp(struct hand a)
{
    int rs=0,i;
    for (i=0;i<strlen(a.h);i++)
    {
        if (a.h[i]=='A')
            rs+=4;
        else if (a.h[i]=='K')
            rs+=3;
        else if (a.h[i]=='Q')
            rs+=2;
        else if (a.h[i]=='J')
            rs+=1;
    }
    return rs;
}

int declarer(struct hand a)
{
    int rs=0,i,counts=0,counth=0,countd=0,countc=0;
    for (i=0;i<strlen(a.h);i++)
    {
        if (a.h[i]=='S')
            counts++;
        else if (a.h[i]=='H')
            counth++;
        else if (a.h[i]=='D')
            countd++;
        else if (a.h[i]=='C')
            countc++;
    }
    if (counts>4)
        rs+=(counts-4);
    if (counth>4)
        rs+=(counth-4);
    if (countd>4)
        rs+=(countd-4);
    if (countc>4)
        rs+=(countc-4);
    return rs;
}

void response(struct hand a)
{

    int i,counts=0,counth=0,countd=0,countc=0;
    for (i=0;i<strlen(a.h);i++)
    {
        if (a.h[i]=='S')
            counts++;
        else if (a.h[i]=='H')
            counth++;
        else if (a.h[i]=='D')
            countd++;
        else if (a.h[i]=='C')
            countc++;
    }
    if (hcp(a)<=17&&hcp(a)>=15&&balanced(a))
        printf("1NT\n");
    else if (hcp(a)<=21&&hcp(a)>=20&&balanced(a))
        printf("2NT\n");
    else if (hcp(a)>=22)
        printf("2 CLUBS\n");
    else if (hcp(a)<22&&(hcp(a)+declarer(a))>=13)
    {
        if (counts>=5&&counth<=5)
            printf("1 SPADES\n");
        else if (counth>=5&&counts<=5)
            printf("1 HEARTS\n");
        else if (countd>=4&&counts<5&&counth<5&&countc<5)
            printf("1 DIAMONDS\n");
        else if (countd<4&&counth<=5&&counts<=5)
            printf("1 CLUBS\n");
    }
    else if ((hcp(a)+declarer(a))<13)
        printf("PASS\n");
}

int readFromFile(struct hand *A)
{
    char s[100];
    scanf("%s",s);
    FILE *fp;
    fp=fopen(s,"r");
    struct hand B;
    int n,i;
    fscanf(fp,"%d ",&n);
    for (i=0;i<n;i++)
    {
        fgets(B.h,100,fp);
        B.h[strcspn(B.h,"\n")]='\0';
        *A=B;
        *A++;
    }
    fclose(fp);
    return n;
}

void saveData(struct hand *A,int n)
{
    int j;
    char s[100];
    scanf("%s",s);
    FILE *fp;
    fp=fopen(s,"w");
    for (j=0;j<n;j++)
    {
        int s[13],h[13],d[13],c[13];
        int ch=0,cs=0,cd=0,cc=0,i;
        for (i=0;i<39;i++)
        {
            if (A[j].h[i]=='S')
            {
                s[cs]=A[j].h[i-1];
                cs++;
            }
            if (A[j].h[i]=='H')
            {
                h[ch]=A[j].h[i-1];
                ch++;
            }
            if (A[j].h[i]=='D')
            {
                d[cd]=A[j].h[i-1];
                cd++;
            }
            if (A[j].h[i]=='C')
            {
                c[cc]=A[j].h[i-1];
                cc++;
            }
        }
        fprintf(fp,"SPADES:   ");
        for (i=0;i<cs;i++)
        {
            if (s[i]<10)
                fprintf(fp,"%d ",s[i]);
            else
                fprintf(fp,"%c ",s[i]);
        }
        fprintf(fp,"\nHEARTS:   ");
        for (i=0;i<ch;i++)
        {
            if (h[i]<10)
                fprintf(fp,"%d ",h[i]);
            else
                fprintf(fp,"%c ",h[i]);
        }
        fprintf(fp,"\nDIAMONDS: ");
        for (i=0;i<cd;i++)
        {
            if (d[i]<10)
                fprintf(fp,"%d ",d[i]);
            else
                fprintf(fp,"%c ",d[i]);
        }
        fprintf(fp,"\nCLUBS:    ");
        for (i=0;i<cc;i++)
        {
            if (c[i]<10)
                fprintf(fp,"%d ",c[i]);
            else
                fprintf(fp,"%c ",c[i]);
        }
        fprintf(fp,"\n\n");
    }
    fclose(fp);
}
