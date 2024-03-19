#include<stdio.h>
#include<malloc.h>

typedef struct Santier Santier;
typedef struct Nod Nod;

struct Santier
{
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct Nod
{
    Santier santier;
    Nod* next;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata)
{
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);///*sizeof(char),care e 1;
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;

    return santier; ///funtia care initializeaza informatia utila
}


Nod* inserareSantierInceput(Santier santier, Nod* lista)
{
    Nod* nod=(Nod*)malloc(sizeof(Nod));
    nod->santier = santier;
    nod->next = lista; 
    return nod;
}


int sumaMuncitori(Nod* lista)
{
    int suma = 0;
    while (lista != NULL)
    {
        suma = suma + lista->santier.nrMuncitori;
        lista = lista->next;

    }

    return suma;
}

void afisareSantier(Santier santier)
{
    printf("%s are %d muncitori si o suprafata de %5.2f mp\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}


void afisareLista(Nod* lista)
{
    while (lista != NULL)
    {
        ///procesare
        afisareSantier(lista->santier);
        lista = lista->next;
  
    }
}


void stergereLista(Nod** lista)
{
    while ((*lista) != NULL)
    {
        free((*lista)->santier.numeProiect);
        Nod* aux = (*lista)->next;
        free(*lista);
        (*lista) = aux;
    }

    (*lista) = NULL;
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

char* numeSantierDensitateMaxima(Nod* lista)
{
    float max = 0;
    char* aux=NULL;
    while (lista != NULL)
    {
        if (densitateMuncitori(lista->santier) > max)
        {
            max = densitateMuncitori(lista->santier);
            aux = lista->santier.numeProiect;
        }
        lista=lista->next;
    }
    if (aux != NULL)
    {
        char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
        strcpy(numeProiectDensitate, aux);

        return numeProiectDensitate;
    }
    else
    {
        return NULL;
    }
}


int main()
{
    Nod* lista=NULL;
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 16, 800);
    Santier s3 = initializareSantier("Santier 3", 14, 500);
    Santier s4 = initializareSantier("Santier 4", 12, 600);

    lista=inserareSantierInceput(s1, lista);
    lista=inserareSantierInceput(s2, lista);
    lista=inserareSantierInceput(s3, lista);
    lista=inserareSantierInceput(s4, lista);
    lista=inserareSantierInceput(initializareSantier("Santier 5", 10, 340), lista);
   /// afisareLista(lista);
   

    afisareLista(lista);
    int suma = 0;
    suma = sumaMuncitori(lista);
    printf("Pe santier sunt %d muncitori", suma);

    printf("\n%s\n", numeSantierDensitateMaxima(lista));

    stergereLista(&lista);
    afisareLista(lista);

}