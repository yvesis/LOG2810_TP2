#include "Automate.h"
#include <fstream>
#include "dirent.h"
#include <iomanip>

#ifndef WIN32
#include <sys/types.h>
#endif

using namespace std;

Lexique::Lexique()
{
}


Lexique::~Lexique()
{
	for (auto it = etats_.begin(); it != etats_.end(); it++)
	{
		Etat* s = it->second;
		for (auto it2 = s->entrees.begin(); it2 != s->entrees.end(); it2++)
			delete it2->second;

		delete s;
	}
}

/*
	Automate * Automate::lireLexique(const char * fichier)
	Lit un fichier donne et retourne l'automate correspondant
	fichier: le chemin du fichier
	Remarque : L'appelant de cette fonction doit liberer la
	ressource creee.
*/
Lexique * Lexique::lireLexique(const char * fichier)
{
	auto file = ifstream(fichier);

	if (!file.good())
	{
		printf("\nLe fichier n'existe pas!\n");
		return nullptr;
	}
	Lexique* automate = new Lexique(); // Liberer la ressource dans le main
	while (!ws(file).eof())
	{
		// On lit ligne par ligne
		string line;
		getline(file, line);

		// On cree le premier etat ou noeud
		auto nom = string(1,line[0]);
		auto query = automate->arbre_.find(nom);
		if (query == automate->arbre_.end())
			automate->arbre_[nom] = new Etat { nom };

		Etat* s0 = automate->arbre_[nom];
		automate->etats_[nom] = s0;
		// On lit chaque caractere
		std::string chaine;
		chaine = line[0];
		Etat* s1;

		for (int i = 1; i < line.size(); i++)
		{
			if (line[i] != ' ') // Ne pas considerer les espaces comme entree, sinon commenter cette ligne
			{
				// Creation successif d'entree/sortie
				chaine += line[i];
				Entree* e;
				auto query = s0->entrees.find(line[i]);
				if (query == s0->entrees.end())
				{
					s0->entrees[line[i]] = new Entree { line[i] };
					e = s0->entrees[line[i]];
					auto query2 = automate->etats_.find(chaine);
					if (query2 == automate->etats_.end())
					{
						s1 = new Etat{ chaine };
						automate->etats_[chaine] = s1;
					}
					e->sorties.push_back(automate->etats_[ chaine ]);// la sortie ou etat suivant
					s0->entrees[line[i]] = e;
					s0 = e->sorties[e->sorties.size() - 1];
				}
				s0 = automate->etats_[chaine];
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
std::vector<Lexique*> Lexique::creerLexique(const char * repertoire)
{
	auto automates = std::vector<Lexique*>();
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
				auto a = Lexique::lireLexique(filename.c_str());
				if (a) automates.push_back(a);
			}
				
		}

		closedir(dir);
	}
	// retour par copie, mais ce sont des pointeurs d'automates
	return automates;
}
std::ostream & operator<<(std::ostream & os, const Lexique & a)
{

	os << "\n\n Affichage automate\n";
	os << "\n_____________________\n";
	os << "\n\n" << setw(10) << "Etat" << setw(20) << "Entree" << setw(30) << "Sortie\n";
	int i = 0;
	for (auto it = a.etats_.begin(); it != a.etats_.end(); it++)
	{
		if (i && !((i) % 50)) system("pause");

		Etat* s = it->second;

		os << endl << endl << ++i << setw(10) << s->nom.c_str();
		int j = 0;
		for (auto it2 = s->entrees.begin(); it2 != s->entrees.end(); it2++)
		{
			Entree* e = it2->second;
			os << setw(20 + 11 * j) << e->valeur;
			j = 1;
			int k = 0;
			for (auto it3 = e->sorties.begin(); it3 != e->sorties.end(); it3++)
			{
				Etat* s1 = *it3;
				os << setw(30  ) << s1->nom.c_str() << endl;
				//__debugbreak();
			}
		}
		os << endl;

	}

	return os;
}



