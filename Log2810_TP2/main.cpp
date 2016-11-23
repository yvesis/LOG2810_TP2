#include "Automate.h"
#include <iostream>
#include <vector>
using namespace std;

void creerZones(vector<Automate*>& zones);
void creerClients(vector<Client>& clients);
void creerVehicules(vector<Vehicule>& vehicules);

int main()
{
	vector<Client> clients;
	vector<Vehicule> vehicules;
	vector <Automate*> zones;
	char choix;
	do
	{
		printf("\n\nEntrer un choix:");
		cin >> choix;
		choix = tolower(choix);
		switch (choix)
		{
		case 'a':creerZones(zones);
			break;
		case 'b':break;
		
		default:
			break;
		}
	} while (choix != 'q');

	system("pause");

	for (auto it = zones.begin(); it != zones.end(); it++)
		delete (*it);

	return 0;

}

void creerZones(vector<Automate*>& zones)
{
	printf("\n\n 1) Lire repertoire "
		"\n\n 2) Lire fichier");

	char choix = '\0';
	do
	{
		printf("\n\nChoisir 1 ou 2: ");
		scanf_s(" %c", &choix);

	} while (choix != '1' && choix != '2');
	
	char chemin[255];
	printf("\n\n Entrer le chemin du");

	if (choix == '1')
	{
		printf(" repertoire: ");
		scanf_s(" %s", chemin);

		zones = Automate::creerLexique(chemin);
	}
	else
	{
		printf(" fichier: ");
		scanf_s(" %s", chemin);
		zones.push_back(Automate::lireLexique(chemin));

	}

	printf("\n\n Zones et lexiques créées!"
		   "\n\n Afficher le lexique? (o/n)?");
	scanf_s(" %c", &choix);

	if (tolower(choix) == 'o')
	{
		for (auto it = zones.begin(); it != zones.end(); it++)
		{
			cout << **it;
			system("pause");
		}
	}

}

void creerClients(vector<Client>& clients)
{
}

void creerVehicules(vector<Vehicule>& vehicules)
{
}
