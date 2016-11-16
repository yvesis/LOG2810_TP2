#pragma once
#ifndef AUTOMATE_H
#define AUTOMATE_H
#include <vector>
#include <map>
#include <string>
struct Entree;
struct Etat
{
	std::string nom;
	std::map<char,Entree> entrees;

};
struct Entree
{
	char valeur;
	std::vector<Etat> sorties;
};

class Automate
{
public:
	~Automate();
	static Automate* lireLexique(const char* fichier) ;
	static std::vector<Automate*> creerLexique(const char* repertoire);
	friend std::ostream& operator<<(std::ostream& os, const Automate& a);
private:
	Automate();
	std::map<std::string,Etat> etats_;
	std::string fichier_;
	int zoneIndex_;
};

#endif

