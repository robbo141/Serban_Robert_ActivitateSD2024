#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct Masina
{
	int id;
	char* producator;
	int nrUsi;
	float pret;
};

struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini)
{
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini)+1));
	for (int i = 0; i < *nrMasini; i++)
	{
		aux[i] = masini[i];
	}
	aux[*nrMasini] = m; 
	(*nrMasini)++;   //dereferentiere
	if (masini != NULL)
	{
		free(masini);
	}
	return aux;

}


struct Masina* citireFisier(const char* numeFisier, int* nrMasini)
{
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
    char separator[] = ",\n";
	struct Masina* masini=NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, file) != NULL)
	{
		char* element = strtok(buffer, separator);
		struct Masina m;
		m.id = atoi(element);
		element=strtok(NULL, separator);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, separator);
		m.nrUsi = atoi(element);
		element = strtok(NULL, separator);
		m.pret = atof(element);

		masini = adaugareInVector(masini, m, nrMasini);
	}
	
	return masini;
}

int main()
{
	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt",&nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		printf("Masina nr. %d\n", i);
		printf("Id:%d\n", masini[i].id);
		printf("Producator: %s\n", masini[i].producator);
		printf("Nr usi: %d\n", masini[i].nrUsi);
		printf("Pret: % 5.2f\n", masini[i].pret);
		printf("\n");
	}
	printf("%d");
}