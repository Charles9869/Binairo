// Fichier: Grille.hpp //
// Charles Bertrand //
// Date de création: 28 Septembre 2018 //

#ifndef Grille_hpp
#define Grille_hpp

#include "Matrice.h"
#include <fstream>
#include <iostream>
#include <cmath>

class CGrille
{
public:
	// Constructeur par défaut //
	CGrille();

	// Méthodes //
	void Resoudre();
private:
	// Attributs //
	Matrice<int> mGrid;
	static const int UN = 1;
	static const int ZERO = 0;
	bool mFichierExiste = false;
	string mNomFichier;
	const string mExtension = ".txt";
	const string DELIMITEUR = "\n--------------------------------------------\n";
	static const int GRIDSIZE = 10;
	const int MVALEURINCONNU = -1;
	int mValeurDepart = 0, mValeurFin = 0;
    
	// Accesseurs //
	int GetGrid(int PositionX, int PositionY) const { return mGrid[PositionX][PositionY]; }
	int GetValeursDecimalHorizontal(int Ligne) const;
	int GetValeursDecimalVertical(int Colonne) const;

	// Mutateurs //
	void SetGrid(int PositionX, int PositionY, int Nombre);
	void SetNomFichier(const string nom);

	// Méthodes //
	void ConvertirGrid(ifstream& rIn);
	void LireFichier();
	bool VerifieSiFichierExiste(const std::string nom);
	void CommencerResolution(int PositionX, int PositionY);
	bool VerifierSiPositionPeutBouger(int PositionX, int PositionY);
	bool VerifierPositionGrid(int &rPositionX, int &rPositionY);
	void TesterCombinaisons(int &rPositionX, int &rPositionY, int Nombre);
	void Afficher();
	void AfficherValeurDecimalColonne(ostream& rOut);
	void AfficherEntete(ostream& rOut) const;
	void DemanderNomFichier(const string Phrase);
	bool TesterAxeHorizontale(int PositionX, int PositionY, int Nombre);
	bool TesterAxeVerticale(int PositionX, int PositionY, int Nombre);
	bool VerifierSiPeutMettreDansCase(int PositionX, int PositionY, int Nombre);
	bool VerifierLigneRemplie(int Ligne) const;
	bool VerifierColonneRemplie(int Colonne) const;
};

#endif /* Grille_hpp */

