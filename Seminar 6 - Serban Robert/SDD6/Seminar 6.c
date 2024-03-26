#include<stdio.h>
#include<malloc.h>

typedef struct Santier Santier;


struct Santier
{
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};


typedef struct NodLdi NodLdi;
struct NodLdi
{
    NodLdi* prev;
    NodLdi* next;
    Santier info;
};

typedef struct ListaDubla ListaDubla;

struct ListaDubla
{
    NodLdi* prim;
    NodLdi* ultim;
};


void inserareInceput(ListaDubla* lista, Santier s)
{
    NodLdi* aux = malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;
    if (lista->prim != NULL)
    {
        lista->prim->prev = aux;
        lista->prim = aux;
    }
    else
    {
        lista->prim = aux;
    }
    lista->ultim = aux;
}


Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata)
{
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);///*sizeof(char),care e 1;
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;

    return santier; ///funtia care initializeaza informatia utila
}



void afisareSantier(Santier santier)
{
    printf("%s are %d muncitori si o suprafata de %5.2f mp\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}


///numele santierului cu densitatea cea mai mare de muncitori pe mp


float densitateMuncitori(Santier santier)
{
    if (santier.suprafata != 0)
    {
        return santier.nrMuncitori / santier.suprafata;
    }
    else
    {
        return 0;
    }
}


void afisareLdiDeLaInceput(ListaDubla lista)
{
    for (NodLdi* nod = lista.prim; nod != NULL; nod = nod->next)
    {
        afisareSantier(nod->info);
    }
}

void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier)
{
    NodLdi* nod = lista->prim;
    while (nod != NULL)
    {
        if (strcmp(nod->info.numeProiect, numeSantier) == 0)
        {
            if (nod->prev == NULL)//daca este primul nod
            {
                if (nod->next == NULL)
                {
                    lista->prim = NULL;
                    lista->ultim = NULL;
                }
                else
                {
                    nod->next->prev = NULL;
                    lista->prim = nod->next;
                }
            }
            else
            {
                if (nod->next == NULL)// daca este ultimul
                {
                    nod->prev->next = NULL;
                    lista->ultim = nod->prev;
                }
                else //daca e in mijloc
                {
                    nod->prev->next = nod->next;
                    nod->next->prev = nod->prev;
                }
            }

            free(nod->info.numeProiect);
            free(nod);
            nod = NULL;

        }
        else {
            nod = nod->next;
        }
    }
}


void stergereCompleta(ListaDubla* lista)
{
    if (lista != NULL)
    {
        NodLdi* aux = lista->prim;
        while (aux != NULL)
        {

            free(aux->info.numeProiect);
            NodLdi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}

//numarul de muncitori total de pe toate santierele


int calculNumarTotalDeMuncitori(ListaDubla lista)
{
    int suma = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
    {
        suma += i->info.nrMuncitori;
    }

    return suma;
}

int calculNumarTotalDeMuncitoriInFunctieDeSuprafata(ListaDubla lista,float suprafataMax)
{
    int suma = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next)
    {   if(i->info.suprafata<suprafataMax)
        suma += i->info.nrMuncitori;
    }

    return suma;
}


int main()
{
   
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 16, 800);
    Santier s3 = initializareSantier("Santier 3", 14, 500);
    Santier s4 = initializareSantier("Santier 4", 12, 600);

    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;
    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);
    inserareInceput(&lista, s4);
    afisareLdiDeLaInceput(lista);
    /*
    printf("\nStergere mijloc:\n");
    stergereSantierDupaNume(&lista, "Santier 2");
    afisareLdiDeLaInceput(lista);
    printf("\nStergere inceput:\n");
    stergereSantierDupaNume(&lista, "Santier 1");
    afisareLdiDeLaInceput(lista);
    printf("\nStergere final:\n");
    stergereSantierDupaNume(&lista, "Santier 3");
    afisareLdiDeLaInceput(lista);
    */

    int nrMuncitori = calculNumarTotalDeMuncitori(lista);
    printf("Numar muncitori: %d\n", nrMuncitori);

    int nrMuncitori2 = calculNumarTotalDeMuncitoriInFunctieDeSuprafata(lista,500);
    printf("Numar muncitori la santierele cu suprafata mai mica de 600: %d\n",nrMuncitori2);

    //inserareinceput,insearesfarsit;

    printf("\nStergere completa:\n");
    stergereCompleta(&lista);
    afisareLdiDeLaInceput(lista);

}