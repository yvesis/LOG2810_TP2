#include "Automate.h"
#include <iostream>
using namespace std;
int main()
{

	auto automates = Automate::creerLexique("zones");
	for (auto it = automates.begin(); it != automates.end();it++)
		cout << **it;
	system("pause");
	return 0;

}