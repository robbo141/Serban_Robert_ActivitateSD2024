#include<stdio.h>
#include<malloc.h>
#define CRT_SECURE_NO_WARNINGS_

typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Autobuz
{
	int linie;
	char* capatLinie;
};

struct NodPrincipal
{
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar
{
	NodPrincipal* nod;
	NodSecundar* next;
};

Autobuz initializareAutobuz(int linie, const char* capat)
{
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(sizeof(char) * (strlen(capat) + 1));
	strcpy_s(a.capatLinie, strlen(capat)+1,capat);
	return a;

}


//functie de inserare la sf in lista principala
//functie e cautare dupa linie

void inserarePrincipala(NodPrincipal** graf,Autobuz a)
{ 
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = a;
	nou->next = NULL;
	nou->vecini = NULL;
	if ((*graf) != NULL)
	{
		NodPrincipal* temp = *graf;
		while (temp->next)
		{
			temp = temp->next;
		}

		temp->next = nou;
    }
	else
	{
		*graf = nou;
	}
}

NodPrincipal* cautaLinie(NodPrincipal* graf, int linie)
{
	while (graf && graf->info.linie != linie)
	{
		graf = graf->next;
	}

	return graf;
}

NodSecundar* inserareSecundara(NodSecundar* cap, NodPrincipal* info)
{
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap)
	{
		NodSecundar* p = cap;
		while (p = p->next)
		{
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else
	{
		return nou;
	}
}

void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop)
{
	NodPrincipal* nodStart=cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareSecundara(nodStop->vecini, nodStart);
}

//functie de inserare in lista secundara
//functie de inserare muchie


void main()
{
	NodPrincipal * graf=NULL;
	inserarePrincipala(&graf, initializareAutobuz(1, "Romana"));
	inserarePrincipala(&graf, initializareAutobuz(2, "Universitate"));
	inserarePrincipala(&graf, initializareAutobuz(3, "Baicului"));
	inserarePrincipala(&graf, initializareAutobuz(4, "Pantelimon"));
	inserarePrincipala(&graf, initializareAutobuz(5, "Militari"));
	inserarePrincipala(&graf, initializareAutobuz(6, "Ferentari"));

	inserareMuchie(graf,0, 1);
	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 3, 4);

}