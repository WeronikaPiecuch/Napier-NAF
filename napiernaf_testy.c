#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

#define N 1000

void pisz(int *a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%+d", a[i]);
    }
    putchar(';');
}

int wiecej(int n)
{
    assert(n<INT_MAX/3*2);
    return n*3/2+1;
}

void zwieksz(int **a, int *rozmiar)
{
    *rozmiar=wiecej(*rozmiar);
    *a=realloc(*a, (size_t) *rozmiar * sizeof (int));
    assert(*a!=NULL);
}

void dopisz(int i, int **a, int *n, int *rozmiar)
{
    if(*n==*rozmiar)
        zwieksz(a,rozmiar);
    (*a)[*n]=i;
    *n+=1;
}

int modulo(int a, int b)
{
    if(a>=0) return a%b;
    else
    {
        a=(-1)*a;
        int wynik=b-(a%b);
        if(wynik==b) wynik=0;
        return wynik;
    }
}

void iton(int x, int **a, int *n)
{
    int wn=0;
    int *wynik=NULL;
    int rozmiar=0, i=0;
    while(x!=0)
    {
        if(modulo(x,2)==1)
        {
            if(modulo(x,4)==1)
            {
                dopisz(i,&wynik,&wn,&rozmiar);
                x=(x-1)/2;
            }
            else
            {
                dopisz(-i-1,&wynik,&wn,&rozmiar);
                if(x==INT_MAX) x=x/2+1;
                else x=(x+1)/2;
            }
        }
        else x=x/2;
        i++;
    }
    *a=wynik;
    *n=wn;
}

int potega_2(int n)
{
    int potega=2;
    int wynik=-1;
    bool koniec=false;
    while(n>0 && !koniec)
    {
        if(n%2==1)
        {
            if(wynik<INT_MIN/potega) koniec=true;
            else wynik*=potega;
        }
        if(potega>INT_MAX/potega && n>1) koniec=true;
        else if(n>1) potega*=potega;
        n/=2;
    }
    if(koniec) return 0;
    else return wynik;
}

int pozycja(int i)
{
    if(i<0) i=-i-1;
    return i;
}

int cyfra(int *a, int i)
{
    if(a[i]>=0) return 1;
    else return -1;
}

int ntoi(int *a, int n)
{
    if(n>0)
    {
        int wynik=cyfra(a,n-1);
        int p=pozycja(a[n-1]);
        bool koniec=false;
        for(int i=n-2; i>=0 && !koniec; i--)
        {
             int pow=potega_2(p-pozycja(a[i]));
             if(pow!=0)
             {
                if(wynik>(INT_MAX+pow-cyfra(a,i))/pow*(-1)+1 || wynik<(INT_MIN-pow-cyfra(a,i))/pow*(-1)-1) koniec=true;
                else
                {
                    wynik=wynik*pow/(-2)-1;
                    wynik=wynik*2+cyfra(a,i)+2;
                }
                p=pozycja(a[i]);
            }
            else koniec=true;
        }
        if(potega_2(p)==0 || wynik>INT_MAX/potega_2(p)*(-1)) koniec=true;
        else
        {
            wynik=wynik*potega_2(p)*(-1);
        }
        if(koniec) return 0;
        else return wynik;
    }
    else return 0;
}

void nadpisz(int i, int **a, int n)
{
    (*a)[n-1]=i;
}

void usun(int *n)
{
    *n=*n-1;
}

void dodawanie(int *a, int i, int **wynik, int *n, int *rozmiar, int pozycja_a)
{
    if(*n>0)
    {
        int pozycja_p=pozycja((*wynik)[*n-1]);
        if(pozycja_a==pozycja_p)
        {
            if(a[i]>=0)
            {
                if((*wynik)[(*n)-1]>=0)
                    nadpisz(pozycja_a+1, wynik, *n);
                else
                    usun(n);
            }
            else
            {
                if((*wynik)[(*n)-1]<0)
                    nadpisz(-pozycja_a-2, wynik, *n);
                else
                    usun(n);
            }
        }
        else if(pozycja_a-pozycja_p==1)
        {
            if(a[i]>=0)
            {
                if((*wynik)[(*n)-1]>=0)
                {
                    nadpisz(-pozycja_p-1, wynik, *n);
                    dopisz(pozycja_a+1, wynik, n, rozmiar);
                }
                else
                    nadpisz(pozycja_p, wynik, *n);
            }
            else
            {
                if((*wynik)[(*n)-1]<0)
                {
                    nadpisz(pozycja_p, wynik, *n);
                    dopisz(-pozycja_a-2, wynik, n, rozmiar);
                }
                else
                    nadpisz(-pozycja_p-1, wynik, *n);
            }
        }
        else
        {
            if(a[i]>=0)
                dopisz(pozycja_a, wynik, n, rozmiar);
            else
                dopisz(-pozycja_a-1, wynik, n, rozmiar);
        }
    }
    else
    {
        dopisz(a[i], wynik, n, rozmiar);
    }
}

void nadd(int *a, int an, int *b, int bn, int **c, int *cn)
{
    int *wynik=NULL;
    int rozmiar=0;
    int n=0;
    int i=0, j=0;
    int pozycja_a, pozycja_b;
    while(i<an && j<bn)
    {
        pozycja_a=pozycja(a[i]);
        pozycja_b=pozycja(b[j]);
        if(pozycja_a==pozycja_b)
        {
            if(a[i]>=0)
            {
                if(b[j]>=0)
                    dopisz(pozycja_a+1, &wynik, &n, &rozmiar);
            }
            else
            {
                if(b[j]<0)
                    dopisz(-pozycja_a-2, &wynik, &n, &rozmiar);
            }
            i++;
            j++;
        }
        else if(pozycja_a<pozycja_b)
        {
            dodawanie(a,i,&wynik,&n,&rozmiar,pozycja_a);
            i++;
        }
        else
        {
            dodawanie(b,j,&wynik,&n,&rozmiar,pozycja_b);
            j++;
        }
    }
    while(i<an)
    {
        pozycja_a=pozycja(a[i]);
        dodawanie(a,i,&wynik,&n,&rozmiar,pozycja_a);
        i++;
    }
    while(j<bn)
    {
        pozycja_b=pozycja(b[j]);
        dodawanie(b,j,&wynik,&n,&rozmiar,pozycja_b);
        j++;
    }
    *c=wynik;
    *cn=n;
}

int *przeciwna(int *a, int n)
{
    int *wynik=malloc((size_t) n*sizeof(int));
    assert(wynik!=NULL);
    for(int i=0; i<n; i++)
    {
        wynik[i]=-a[i]-1;
    }
    return wynik;
}

void nsub(int *a, int an, int *b, int bn, int **c, int *cn)
{
    int *b_przeciwna=przeciwna(b,bn);
    int *wynik=NULL;
    int n=0;
    nadd(a, an, b_przeciwna, bn, &wynik, &n);
    *c=wynik;
    *cn=n;
    free(b_przeciwna);
}

int *przesun(int *a, int n, int p)
{
    int *wynik=NULL;
    wynik=malloc((size_t) n*sizeof(int));
    for(int i=0; i<n; i++)
    {
        if(a[i]>=0) wynik[i]=a[i]+p;
        else wynik[i]=a[i]-p;
    }
    return wynik;
}

void nmul(int *a, int an, int *b, int bn, int **c, int *cn)
{
    int *wynik=NULL, *suma=NULL;
    int n=0, sn=0;
    int i=0;
    while(i<bn)
    {
        int *skladnik=przesun(a,an,pozycja(b[i]));
        if(b[i]<0)
        {
            int *pom=przeciwna(skladnik,an);
            free(skladnik);
            skladnik=pom;
        }
        nadd(wynik, n, skladnik, an, &suma, &sn);
        free(skladnik);
        free(wynik);
        wynik=suma;
        n=sn;
        i++;
    }
    *c=wynik;
    *cn=n;
}

void jeden(int **a)
{
    int *wynik;
    wynik=malloc((size_t) sizeof(int));
    wynik[0]=0;
    free(*a);
    *a=wynik;
}

void binarna(int *a, int an, int **b, int *bn)
{
    int *wynik=NULL;
    int n=0, rozmiar=0;
    int przeniesienie=0;
    int poz=0;
    for(int i=0; i<an; i++)
    {
        int poz_a=pozycja(a[i]);
        if(przeniesienie==0)
        {
            for(int j=poz; j<poz_a; j++)
                dopisz(0,&wynik,&n,&rozmiar);
            dopisz(1,&wynik,&n,&rozmiar);
            if(a[i]<0) przeniesienie=-1;
        }
        else
        {
            for(int j=poz; j<poz_a; j++)
                dopisz(1,&wynik,&n,&rozmiar);
            dopisz(0,&wynik,&n,&rozmiar);
            if(a[i]>=0) przeniesienie=0;
        }
        poz=poz_a+1;
    }
    if(wynik[n-1]==0) usun(&n);
    *b=wynik;
    *bn=n;
}

void nexp(int *a, int an, int *b, int bn, int **c, int *cn)
{
    int *wykladnik=NULL;
    int wn=0;
    int *pom=NULL;
    int pomn=0;
    binarna(b,bn,&wykladnik,&wn);
    int *wynik=NULL;
    int n=1;
    jeden(&wynik);
    int *potega;
    potega=a;
    int pn=an;
    for(int i=0;i<wn;i++)
    {
        if(wykladnik[i]==1)
        {
            nmul(wynik, n, potega, pn, &pom, &pomn);
            free(wynik);
            wynik=pom;
            n=pomn;
        }
        nmul(potega, pn, potega, pn, &pom, &pomn);
        if(potega!=a)free(potega);
        potega=pom;
        pn=pomn;
    }
    free(wykladnik);
    free(potega);
    *c=wynik;
    *cn=n;

}

bool wieksza_rowna(int *a, int an, int *b, int bn)
{
    if(an==0) return false;
    int i=1;
    while(i>an && i>bn && a[an-i]==b[bn-i]) i++;
    return a[an-i]>=b[bn-i];
}

bool wieksza(int *a, int an, int *b, int bn)
{
    if(an==0) return false;
    int i=1;
    while(a[an-i]==b[bn-i]) i++;
    return a[an-i]>b[bn-i];
}

int *bezwzgledna(int *a, int n)
{
    int *wynik=NULL;
    wynik=malloc((size_t) n*sizeof(int));
    if(n==0 || a[n-1]>=0) wynik=a;
    else wynik=przeciwna(a,n);
    return wynik;
}

int *granica(int k)
{
    int *wynik=NULL;
    int n=0, rozmiar=0;
    for(int i=k%2;i<=k;i=i+2)
        dopisz(i,&wynik,&n,&rozmiar);
    return wynik;
}

void dopisz_dzielenie(int znak, int i, int **a, int *n, int *rozmiar)
{
    if(znak>=0)
        dopisz(i,a,n,rozmiar);
    else
        dopisz(-i-1,a,n,rozmiar);
}

void ndivmod(int *a, int an, int *b, int bn, int **q, int *qn, int **r, int *rn)
{
    int *iloraz=NULL;
    int in=0;
    int *reszta=NULL;
    int ren=0;
    int rozmiar=0;
    int *dzielna=bezwzgledna(a,an);
    int dn=an;
    int *dzielnik=bezwzgledna(b,bn);
    if(an>0)
    {
        int *dzielna_abs=bezwzgledna(dzielna,dn);
        while(wieksza_rowna(dzielna_abs, dn, dzielnik, bn))
        {
            int p=pozycja(dzielna[dn-1])-pozycja(dzielnik[bn-1]);
            int *odjemnik=przesun(dzielnik,bn,p);
            int odn=p/2+1;
            if(wieksza_rowna(dzielna_abs,dn,odjemnik,odn))
            {
                int *graniczna=NULL;
                int gn=0;
                nmul(dzielnik,bn,granica(p),p/2+1,&graniczna,&gn);
                if(wieksza(dzielna_abs,an,graniczna,gn))
                {
                    free(odjemnik);
                    odjemnik=przesun(dzielnik,bn,p+1);
                    odn=(p+1)/2+1;
                    dopisz_dzielenie(dzielna[dn-1],p+1,&iloraz,&in,&rozmiar);
                }
                else
                    dopisz_dzielenie(dzielna[dn-1],p,&iloraz,&in,&rozmiar);
                free(graniczna);
            }
            else
            {
                int *graniczna=NULL;
                int gn=0;
                nmul(dzielnik,bn,granica(p-1),(p-1)/2+1,&graniczna,&gn);
                if(!wieksza(dzielna_abs,an,graniczna,gn))
                {
                    free(odjemnik);
                    odjemnik=przesun(dzielnik,bn,p-1);
                    odn=(p-1)/2+1;
                    dopisz_dzielenie(dzielna[dn-1],p-1,&iloraz,&in,&rozmiar);
                }
                else
                    dopisz_dzielenie(dzielna[dn-1],p,&iloraz,&in,&rozmiar);
                free(graniczna);
            }
            if(dzielna_abs!=dzielna)
            {
                free(dzielna);
                dn=0;
            }
            nsub(dzielna_abs,dn,odjemnik,odn,&dzielna,&dn);
            if(dzielna_abs!=a) free(dzielna_abs);
            if(odjemnik!=b) free(odjemnik);
            dzielna_abs=bezwzgledna(dzielna,dn);
        }
        if(dn>0)
        {
            int *jedynka=NULL;
            int jn=1;
            jeden(&jedynka);
            if(dzielna[dn-1]<0)
            {
                nadd(iloraz,in,jedynka,jn,&iloraz,&jn);
                nadd(dzielnik,bn,dzielna,dn,&dzielna,&dn);
            }
            if(a[an-1]<0)
            {
                nadd(iloraz,in,jedynka,jn,&iloraz,&jn);
                nsub(dzielnik,bn,dzielna,dn,&reszta,&ren);
            }
            else
            {
                reszta=dzielna;
                ren=dn;
            }
            free(jedynka);
        }
        if(a[an-1]*b[bn-1]<0)
        {
            int *pom;
            pom=przeciwna(iloraz,in);
            free(iloraz);
            iloraz=pom;
        }
    }
    if(dzielnik!=b) free(dzielnik);
    if(dzielna!=reszta && dzielna!=a) free(dzielna);
    free(q);
    free(r);
    *q=iloraz;
    *qn=in;
    *r=reszta;
    *rn=ren;
}


int main(void) {
    int *d, dn;
    int n;
    scanf("%d",&n);
    iton(n, &d, &dn);
    pisz(d, dn);
    printf(" (%d)\n", ntoi(d, dn));
    free(d);
    return 0;
}
