#include "Automate.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Client> clients;
vector<Vehicule> vehicules;

int main()
{

	auto zones = Automate::creerLexique("zones");
	for (auto it = zones.begin(); it != zones.end(); it++)
	{
		cout << **it;
		system("pause");
	}
	system("pause");

	for (auto it = zones.begin(); it != zones.end(); it++)
		delete (*it);

	return 0;

}