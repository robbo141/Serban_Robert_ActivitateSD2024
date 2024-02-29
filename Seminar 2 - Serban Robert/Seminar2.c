#include<stdio.h>
#include<malloc.h>


struct Farmacie
{
	int id;
	char* nume;
	float suprafata; 
};

struct Farmacie initializareFarmacie(int id, const char* nume, float suprafata)
{
	struct Farmacie f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char*) * (strlen(nume) + 1));
	strcpy(f.nume, nume);
	f.suprafata = suprafata;

	return f;
}

void afisareFarmacie(struct Farmacie farmacie)
{
	printf("%d. %s are o suprafata de %5.2f\n", farmacie.id, farmacie.nume, farmacie.suprafata);
}




void afisareVector(struct Farmacie* farmacii, int nrFarmacii)
{
	for (int i = 0; i < nrFarmacii; i++)
	{
		afisareFarmacie(farmacii[i]);
	}
}

struct Farmacie* copiazaNelemente(struct Farmacie* vector, int nrFarmacii, int nrObiecteCopiate)
{
	if (nrObiecteCopiate <= nrFarmacii && nrObiecteCopiate > 0)
	{
		struct Farmacie* copiat = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrObiecteCopiate);
		for (int i = 0; i < nrObiecteCopiate; i++)
		{
			copiat[i] = initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}

		return copiat;
	}
	else
	{
		return NULL;
	}
}

struct Farmacie* copiazaFarmaciiMici(struct Farmacie* farmacii, int nrFarmacii, float pragSuprafata, int* nrFarmaciiMici) ///folosim prin pointer pentru ca il vom modifica
{
	*nrFarmaciiMici = 0;
	for (int i = 0; i < nrFarmacii; i++)
	{
		if (farmacii[i].suprafata < pragSuprafata)
		{
			(*nrFarmaciiMici)++;
		}
	}

	struct Farmacie* vector = (struct Farmacie*)malloc(sizeof(struct Farmacie) * (*nrFarmaciiMici));


	int k = 0;   ///
	for (int i = 0; i < nrFarmacii; i++)
	{
		if (farmacii[i].suprafata < pragSuprafata)
		{
			vector[k++] = initializareFarmacie(farmacii[i].id, farmacii[i].nume, farmacii[i].suprafata);
		}
	}

	return vector;
}


void dezalocareVectorFarmacii(struct Farmacie** vector, int* nrFarmacii) ///fara ** ramane dangling pointer
{
	for (int i = 0; i < *nrFarmacii; i++)
	{
		free((*vector)[i].nume);
	}

	free(*vector);
	*nrFarmacii = 0;
	*vector = NULL;
}

struct Farmacie getFarmacieById(struct Farmacie* vector, int nrFarmacii, int idCautat)
{
	for (int i = 0; i < nrFarmacii; i++)
	{
		if (vector[i].id == idCautat)
		{
			return initializareFarmacie(vector[i].id, vector[i].nume, vector[i].suprafata);
		}
	}

	return initializareFarmacie(0, "N/A", 0);
}

int main()
{

	///int v[40];
	///int *v2
	///vectorul este o structura de date cu accesare directa,omogena.liniara
	///pe stack-ul functiei main vom avea acest vector
	/// 
	/// //cream un vector de farmacii

	int nrFarmacii = 4;
	struct Farmacie* farmacii = (struct Farmacie*)malloc(sizeof(struct Farmacie) * nrFarmacii);

	for (int i = 0; i < nrFarmacii; i++)
	{
		farmacii[i] = initializareFarmacie(i + 1, "Farmacie", 30 * i + 10);
	}

	afisareVector(farmacii, nrFarmacii);
	int nrFarmaciiCopiate = 2;
	struct Farmacie* farmaciiCopiate = copiazaNelemente(farmacii, nrFarmacii, nrFarmaciiCopiate);
	printf("\n\nVectorul in care copiem n elemente:\n");
	afisareVector(farmaciiCopiate, nrFarmaciiCopiate);


	int nrFarmaciiMici = 0;

	farmacii[3].suprafata = 20; ///modificam suprafata farmaciei de pe pozitia 3
	struct Farmacie* farmaciiMici = copiazaFarmaciiMici(farmacii, nrFarmacii, 50, &nrFarmaciiMici);
	printf("\n\n Vectorul de farmacii cu suprafata strict mai mare de 50:\n");
	afisareVector(farmaciiMici, nrFarmaciiMici);
	printf("\n\nFarmacie cautata:\n");
	struct Farmacie	farmacieCautata = getFarmacieById(farmacii, nrFarmacii, 7);
	afisareFarmacie(farmacieCautata);
	free(farmacieCautata.nume);

	dezalocareVectorFarmacii(&farmacii, &nrFarmacii);

	dezalocareVectorFarmacii(&farmaciiCopiate, &nrFarmaciiCopiate);
	dezalocareVectorFarmacii(&farmaciiMici, &nrFarmaciiMici);

}