#define _CRT_SECURE_NO_WARNINGS
#include "Automate.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Client> clients;
vector<Vehicule> vehicules;
void afficherMenu();
void creerZones(vector<Lexique*>& zones);
void creerClients(vector<Client>& clients);
void creerVehicules(vector<Vehicule>& vehicules);
void lireFichierClientsVehicules(const string& fichier, vector<Client>& clients);
void demarrerSimulation(vector<Vehicule>& vehicules, vector<Client>& clients);
void equilibrerFlotte(vector<Vehicule>& vehicules, vector<Client>& clients);
void parseZone(const string& zone, Lexique* out, Etat* out2);

char choix;
bool choixA = false;
bool choixB = false;

int main()
{
	vector<Client> clients;
	vector<Vehicule> vehicules;
	vector <Lexique*> zones;

	do
	{
		afficherMenu();

		switch (choix)
		{
		case 'a':
		{
			creerZones(zones);
			choixA = true;
			break;
		}

		case 'b':
			/*if (!choixA)
				std::cout << "Il faut choisir l'option A avant de choisir l'option B." << std::endl;
			else*/
			{
				clients.clear();
				vehicules.clear();
				creerClients(clients);
				if (!vehicules.empty()) creerVehicules(vehicules);
				choixB = true;
			}
			break;

		case 'c':
			if (!choixB)
				std::cout << "Il faut choisir l'option B avant de choisir l'option C." << std::endl;
			else
			{
				// lancerSimulation()
			
			}
			break;

		case 'd': break;

		default:
			std::cout << std::endl << "Veuillez choisir une lettre entre a et d." << std::endl;
		}
		std::cout << std::endl;
	} while (choix != 'd');

	for (auto it = zones.begin(); it != zones.end(); it++)
		delete (*it);

	system("pause");


	return 0;
}

void afficherMenu() 
{
	std::cout << "-------------------Menu principal-------------------" << std::endl;
	std::cout << "****************************************************" << std::endl;
	std::cout << "(a) Creer les zones." << std::endl;
	std::cout << "(b) Entrer les clients et les vehicules." << std::endl;
	std::cout << "(c) Demarrer la simulation." << std::endl;
	std::cout << "(d) Quitter." << std::endl;
	std::cout << "****************************************************" << std::endl;
	std::cout << "Votre choix:\0";

	cin >> choix;
}

/*
	Cree les zones
*/
void creerZones(vector<Lexique*>& zones)
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

		zones = Lexique::creerLexique(chemin);
	}
	else
	{
		printf(" fichier: ");
		scanf_s(" %s", chemin);
		zones.push_back(Lexique::lireLexique(chemin));

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
	printf("\n\n 1) Lire a partir d'un fichier (o/n)?: ");

	char choix = '\0';
	scanf_s(" %c", &choix);

	if (tolower(choix) != 'o')
	{
		int i = 0;
		choix = 'o';
		while (tolower(choix) == 'o')
		{
			Client c;
			c.index = i++;
			
			printf("\n\n Entrer les informations du client %d\n:", i);
			printf("\n***************************************\n\n");
			printf(" Point de depart :\t ");
			string depart;
			cin.ignore();
			getline(cin , depart);

			printf("\n Point d'arrive :\t ");
			string arrive;
			getline(cin , arrive);

			c.pointDepart = depart;
			c.pointArrive = arrive;
			clients.push_back(c);

			printf("\n Continuer? (o/n)? : ");
			scanf_s(" %c", &choix);


		}

		
	}
	else
	{
		printf("\n\n Chemin du fichier contenant les informations des clients et vehicules\n");
		printf("  :");
		string fichier;
		getline(cin, fichier);
		printf("\n");
		lireFichierClientsVehicules(fichier, clients);
	}
}

void creerVehicules(vector<Vehicule>& vehicules)
{
	printf("\n\n 1) Lire a partir d'un fichier (o/n)?: ");

	char choix = '\0';
	scanf_s(" %c", &choix);

	if (tolower(choix) != 'o')
	{
		int i = 0;
		choix = 'o';
		while (tolower(choix) == 'o')
		{
			Vehicule v;
			v.index = i++;
			v.Occupation = 0;
			
			printf("\n\n Entrer les informations du vehicule %d\n:", i);
			printf("\n***************************************\n\n");
			printf(" Zone de depart :\t ");
			string depart;
			cin.ignore();
			getline(cin, depart);

			//printf("\n Occupation:\t ");
			string arrive;
			getline(cin, arrive);

			parseZone(depart, v.zoneDepart, v.positionActuelle);
			
			vehicules.push_back(v);

			printf("\n Continuer? (o/n)? : ");
			scanf_s(" %c", &choix);


		}


	}
	else
	{
		printf("\n\n Chemin du fichier contenant les informations des clients et vehicules\n");
		printf("  :");
		string fichier;
		getline(cin, fichier);
		printf("\n");
		lireFichierClientsVehicules(fichier, clients);
	}
}

void lireFichierClientsVehicules(const string& fichier, vector<Client>& clients)
{
}

void demarrerSimulation(vector<Vehicule>& vehicules, vector<Client>& clients)
{
}

void equilibrerFlotte(vector<Vehicule>& vehicules, vector<Client>& clients)
{
}

void parseZone(const string & zone, Lexique * autoOut, Etat* etatOut)
{
}
