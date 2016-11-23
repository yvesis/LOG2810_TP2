#pragma once
#ifndef AUTOMATE_H
#define AUTOMATE_H
#include <vector>
#include <map>
#include <string>
class Automate;
struct Entree;
struct Etat
{
	std::string nom;
	std::map<char,Entree*> entrees;

};
struct Entree
{
	char valeur;
	std::vector<Etat*> sorties;
};

struct Vehicule
{
	int index;
	Automate* zoneDepart;
	unsigned int Occupation;
	Etat* positionActuelle;
};

struct Client
{
	int index;
	std::string pointDepart;
	std::string pointArrive;
	unsigned int groupe;
};
class Automate
{
public:
	~Automate();
	static Automate* lireLexique(const char* fichier) ;
	static std::vector<Automate*> creerLexique(const char* repertoire);
	friend std::ostream& operator<<(std::ostream& os, const Automate& a);
	unsigned int NbVehicules = 0;
private:
	Automate();

	// Utilisé pour parcourir l'automate
	std::map<std::string,Etat*> arbre_;	
	// Utilisé pour garder une trace sur tous les pointeurs d'etats
	std::map<std::string, Etat*> etats_;

	std::string fichier_;
	int zoneIndex_;
};

#endif

