#include "Automate.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Client> clients;
vector<Vehicule> vehicules;
void afficherMenu();

char choix;
bool choixA = false;
bool choixB = false;

int main()
{
	do
	{
		afficherMenu();

		switch (choix)
		{
		case 'a':
		{
			auto zones = Automate::creerLexique("zones");
			for (auto it = zones.begin(); it != zones.end(); it++)
			{
				cout << **it;
				//system("pause");
			}
			//system("pause");

			//for (auto it = zones.begin(); it != zones.end(); it++)
			//	delete (*it);
			afficherMenu();
			break;
		}

		case 'b':
			if (!choixA)
				std::cout << "Il faut choisir l'option A avant de choisir l'option B." << std::endl;
			else
			{
				//equilibrerFlotte()
				choixA = true;
			}
			break;

		case 'c':
			if (!choixB)
				std::cout << "Il faut choisir l'option B avant de choisir l'option C." << std::endl;
			else
			{
				// lancerSimulation()
				choixB = true;
			}
			break;

		case 'd': break;

		default:
			std::cout << std::endl << "Veuillez choisir une lettre entre a et d." << std::endl;
		}
		std::cout << std::endl;
	} while (choix != 'd');


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