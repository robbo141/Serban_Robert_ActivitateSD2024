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
	struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
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
	struct Masina* masini = NULL;
	(*nrMasini) = 0;

	while (fgets(buffer, 100, file) != NULL)
	{
		char* element = strtok(buffer, separator);
		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, separator);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, separator);
		m.nrUsi = atoi(element);
		element = strtok(NULL, separator);
		m.pret = atof(element);

		masini = adaugareInVector(masini, m, &nrMasini);
	}

	fclose(file);
	return masini;
}

void afisareMatrice(struct Masina** matrice,int nrLinii, int *nrColoane)
{
	for(int i=0;i<nrLinii;i++)
		for (int j = 0; j < *(nrColoane); j++)
		{
			printf(" Masina %d marca %s cu %d usi costa %5.2f lei\t ", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
			printf("\n");
		}

}


void  citireMatrice(const char* numeFisier, struct Masina** matrice, int* nrLinii, int* nrColoane)
{
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char separator[] = ",\n";
	
	while (fgets(buffer, 100, file) != NULL)
	{
		char* element = strtok(buffer, separator);
		struct Masina m;
		m.id = atoi(element);
		element = strtok(NULL, separator);
		m.producator = malloc(strlen(element) + 1);
		strcpy(m.producator, element);
		element = strtok(NULL, separator);
		m.nrUsi = atoi(element);
		element = strtok(NULL, separator);
		m.pret = atof(element);

		matrice[m.nrUsi-2] = adaugareInVector(matrice[m.nrUsi-2], m, &(nrColoane[m.nrUsi-2]));
	}

	fclose(file);
	
}

//pretul mediu al masinilor cu nr de usi dat ca parametru

float pretMediu(struct Masina** matrice, int NrLinii, int* nrColoane, int nrUsi)
{
	if (nrUsi <= 1 || nrUsi > 4)
	{
		return 0;
	}

	float pretTotal = 0;
	int index = nrUsi - 2;
	if (nrColoane[index] == 0)
	{
		return 0;
	}
	for (int i = 0; i < nrColoane[index]; i++)
	{
		pretTotal = pretTotal + matrice[index][i].pret;
	}

	return pretTotal / nrColoane[index];
}


struct Masina cautaMasinaID(struct Masina** matrice, int nrLinii, int* nrCol, int id)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			if (matrice[i][j].id == id)
				return matrice[i][j];
		}
	}

	struct Masina m;
	m.id = -1;
	m.producator = NULL;
	m.nrUsi = -1;
	m.pret = -1;
	return m;
}


void dezalocareMarice(struct Masina*** matrice, int* nrLinii,int ** nrCol )
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrCol[i]; j++)
		{
			if ((*matrice)[i][j].producator!=NULL)
				free((*matrice)[i][j].producator);
		}
		free((*matrice[i]));
	}

	free((*nrCol));
	(*nrCol) = NULL;
	free((*matrice));
	(*matrice) = NULL;
}


int main()
{
	struct Masina** matrice;
	int nrLinii = 3;
	int* nrCol;
	float pret=0;
	nrCol = (int*)malloc(sizeof(int) * nrLinii); //vectorul de lungimi
	matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);

	for (int i = 0; i < nrLinii; i++)
	{
		nrCol[i] = 0;
		matrice[i] = NULL;
	}

	struct Masina masina_cautata;

	citireMatrice("masini.txt", matrice, nrLinii, nrCol);
	afisareMatrice(matrice, nrLinii, nrCol);
	pret=pretMediu(matrice, nrLinii, nrCol, 4);
	printf("\n Pretul mediu este %5.2f\n",pret);
	masina_cautata=cautaMasinaID(matrice, nrLinii, nrCol, 20);

	printf(" Masina cu id-ul cautat : %d  %s  %d  %5.2f \t ", masina_cautata.id, masina_cautata.producator, masina_cautata.nrUsi, masina_cautata.pret);
     
	dezalocareMatrice(&matrice, nrLinii, &nrCol);
	
}
