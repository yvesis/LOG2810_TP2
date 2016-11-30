#pragma once
#ifndef AUTOMATE_H
#define AUTOMATE_H
#include <vector>
#include <map>
#include <string>
class Lexique;
struct Entree;
class Lexique;

/*
	Represente une chaine de caractere reconnue mais pas forcement acceptee
*/
struct Etat
{
	// Chaine des caracteres definissant l'etat
	std::string nom;
	// Les entrees reconnues
	std::map<char,Entree*> entrees;
	// Etat final?
	bool final;

};
/*
	Represente un caractere du zip code. Fait le lien avec un etat donne
*/
struct Entree
{
	char valeur;
	// Les etats suivants
	std::vector<Etat*> sorties;
};

/*
	Structure vehicule
*/
struct Vehicule
{
	int index;
	Lexique* zoneDepart;
	unsigned int Occupation;
	Etat* positionActuelle;
};

/*
	Structure client
*/
struct Client
{
	int index;
	std::string pointDepart;
	std::string pointArrive;
	unsigned int groupe;
};

/*
	Represente un automate pouvant reconnaitre un Zip code
*/
class Lexique
{
public:
	~Lexique();
	static Lexique* lireLexique(const char* fichier) ;
	static std::vector<Lexique*> creerLexique(const char* repertoire);
	friend std::ostream& operator<<(std::ostream& os, const Lexique& a);
	unsigned int NbVehicules = 0;
private:
	Lexique();

	// Utilisé pour parcourir l'automate
	std::map<std::string,Etat*> arbre_;	
	// Utilisé pour garder une trace sur tous les pointeurs d'etats
	std::map<std::string, Etat*> etats_;

	std::string fichier_;
	int zoneIndex_;
};

#endif

