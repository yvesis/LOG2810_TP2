#include "Automate.h"
#include <fstream>
#include "dirent.h"

#ifndef WIN32
#include <sys/types.h>
#endif

using namespace std;

Automate::Automate()
{
}


Automate::~Automate()
{
}

/*
	Automate * Automate::lireLexique(const char * fichier)
	Lit un fichier donne et retourne l'automate correspondant
	fichier: le chemin du fichier
	Remarque : L'appelant de cette fonction doit liberer la
	ressource creee.
*/
Automate * Automate::lireLexique(const char * fichier)
{
	auto file = ifstream(fichier);

	if (!file.good())
	{
		printf("\nLe fichier n'existe pas!\n");
		return nullptr;
	}
	Automate* automate = new Automate(); // Liberer la ressource dans le main
	while (!ws(file).eof())
	{
		// On lit ligne par ligne
		string line;
		getline(file, line);

		// On cree le premier etat ou noeud
		auto nom = string(1,line[0]);
		automate->etats_[nom] = { nom };
		Etat* s0 = &automate->etats_[nom];

		// On lit chaque caractere
		std::string chaine;
		chaine = line[0];

		for (int i = 1; i < line.size(); i++)
		{
			if (line[i] != ' ') // Ne pas considerer les espaces comme entree, sinon commenter cette ligne
			{
				// Creation successif d'entree/sortie
				chaine += line[i];
				Entree e{ line[i] };
				Etat* s1; // la sortie ou etat suivant

				// Trouver si l'etat suivant existe deja sinon le creer
				auto query = automate->etats_.find(chaine);
				if (query == automate->etats_.end())
				{
					automate->etats_[chaine] = Etat{ chaine };
					s1 = &automate->etats_[chaine];
				}
				else
					s1 = &query->second;

				// On associe l'etat ou sortie a l'entree
				e.sorties.push_back(*s1); 
				s0->entrees[line[i]] = e;
				s0 = &automate->etats_[chaine]; // Pointer vers le nouvel etat
			}
			
		}
	}

	return automate;
}
/*
	std::vector<Automate*> Automate::creerLexique(const char * repertoire)
	Lit un repertoire donne et retourne les automates correspondants
	fichier: le chemin du repertoire contenant les fichiers d'automates compatibles
	Remarque : L'appelant de cette fonction doit liberer les
	ressources creees.
*/
std::vector<Automate*> Automate::creerLexique(const char * repertoire)
{
	auto automates = std::vector<Automate*>();
	DIR* dir = opendir(repertoire);
	if (dir)
	{
		dirent*  file = 0;
		while ((file = readdir(dir)) != NULL )
		{
			if (file->d_type == DT_REG)
			{
				std::string filename = repertoire;
				filename += '/';
				filename += +file->d_name;
				auto a = Automate::lireLexique(filename.c_str());
				if (a) automates.push_back(a);
			}
				
		}

		closedir(dir);
	}
	// retour par copie, mais ce sont des pointeurs d'automates
	return automates;
}
std::ostream & operator<<(std::ostream & os, const Automate & a)
{

	printf("\n\n Affichage automate\n");
	printf("\n_____________________\n");
	printf("\n\n Etat   \tEntree   \tSortie\n");
	int i = 0;
	for (auto it = a.etats_.begin(); it != a.etats_.end(); it++)
	{
		Etat s = it->second;
		printf("\n\n %-3d%-3s", i, s.nom.c_str());
		for (auto it2 = s.entrees.begin(); it2 != s.entrees.end(); it2++)
		{
			Entree e = it2->second;
			printf("%-3 %-3\t%-3c", e.valeur);

			for (auto it3 = e.sorties.begin(); it3 != e.sorties.end(); it3++)
			{
				Etat s1 = *it3;
				printf("%-3 %-3\t%-3\t%-3s\n", s1.nom.c_str());
			}
		}

	}

	return os;
}

