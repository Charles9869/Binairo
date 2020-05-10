// Fichier: Grille.cpp //
// Charles Bertrand //
// Date de création: 3 Octobre 2018 //

#include "Grille.hpp"
#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

// Prototype: unsigned Power(unsigned Valeur, unsigned Puissance = 0 ) //
// Intrants: Valeur, Puissance //
// Extrants: Puissance //
// Type: Fonction //
// But: Calcule la puissance d'une valeur //
unsigned Power(unsigned Valeur, unsigned Puissance = 0) {
	if (Puissance <= 0)
	{
		return 1;
	}
	return Valeur * Power(Valeur, Puissance - 1);
}


// Constructeur //
CGrille::CGrille() {
	mGrid.SetNbLignes(GRIDSIZE);
	mGrid.SetNbColonnes(GRIDSIZE);
	mValeurDepart = 0;
	mValeurFin = 0;
}

// Prototype: void DemanderNomFichier(const string Phrase) //
// Intrants: Phrase //
// Extrants: Aucun //
// Type: Prototype //
// But: Permet de demander le nom des fichier à ouvrir //
void CGrille::DemanderNomFichier(const std::string Phrase) {
	string Nom;
	cout << Phrase;
	cin.ignore(cin.rdbuf()->in_avail());
	getline(cin, Nom);
	SetNomFichier(Nom + mExtension);
}

// Prototype: void SetNomFichier(const Nom) //
// Intrants: Nom //
// Extrants: Aucun //
// Type: Prototype //
// But: Set le nom du fichier assurer une bonne encapsulation //
void CGrille::SetNomFichier(const std::string nom) {
	mNomFichier = nom;
}

// Prototype: void LireFichier() //
// Intrants: Aucun //
// Extrants: Aucun //
// Type: Prototype //
// But: Permet la lecture du fichier //
void CGrille::LireFichier() {
	do {
		DemanderNomFichier("Entrez le nom du fichier: ");
		if (VerifieSiFichierExiste(mNomFichier)) {
			ifstream rIn(mNomFichier);
			mFichierExiste = true;
			ConvertirGrid(rIn);
		}
		else {
			mFichierExiste = false;
		}
	} while (!mFichierExiste);
}

// Prototype: void ConvertirGrid(ifstream& rIn) //
// Intrants: rIn //
// Extrants: Aucun //
// Type: Prototype //
// But: Permet de transfèrer les données du fichier dans une grille //
void CGrille::ConvertirGrid(ifstream &rIn) {
	const char ASTERIX = '*';
	int Ligne = 0;
	while (!rIn.eof()) {
		int Colonne = 0;
		string Phrase;

		getline(rIn, Phrase);

		for (char Index : Phrase) {
			if (Index != ASTERIX) SetGrid(Ligne, Colonne, Index - '0'); // Convertir le char et int //
			else SetGrid(Ligne, Colonne, MVALEURINCONNU);
			++Colonne;
		}
		++Ligne;
	}
	rIn.close();
}

// Prototype: VerifieSiFichierExiste(const string Nom) //
// Intrants: Nom //
// Extrants: Vrai ou Faux //
// Type: Fonction //
// But: Permet de vérifier si le fichier existe //
bool CGrille::VerifieSiFichierExiste(const std::string nom) {
	return !!(ifstream{ nom });
}

// Prototype: int GetValeursDecimalHorizontal(int Ligne) const //
// Intrants: Ligne //
// Extrants: La valeur de dicimal d'une ligne //
// Type: Fonction //
// But: Calcule la valeur decimal à partir d'une ligne binaire //
int CGrille::GetValeursDecimalHorizontal(int Ligne) const {
	int ValeurDecimal = 0;
	int i = 0;
	while (i < GRIDSIZE) {
		if (GetGrid(Ligne, i) == UN) {
			ValeurDecimal += Power(2, GRIDSIZE - i - UN);
		}
		++i;
	}
	return ValeurDecimal;
}

// Prototype: int GetValeursDecimalVertical(int Colonne) const //
// Intrants: Colonne //
// Extrants: La valeur de dicimal d'une Colonne //
// Type: Fonction //
// But: Calcule la valeur decimal à partir d'une Colonne binaire //
int CGrille::GetValeursDecimalVertical(int Colonne) const {
	int ValeurDecimal = 0;
	int i = 0;
	while (i < GRIDSIZE) {
		if (GetGrid(i, Colonne) == UN) {
			ValeurDecimal += Power(2, GRIDSIZE - i - UN);
		}
		++i;
	}
	return ValeurDecimal;
}

// Prototype: bool VerifierPositionGrid(int &PositionX, int &PositionY) //
// Intrants: PositionX, PositionY //
// Extrants: Vrai ou Faux //
// Type: Fonction //
// But: Vérifie si la position dans la grid est valide //
bool CGrille::VerifierPositionGrid(int &rPositionX, int &rPositionY) {
	if (rPositionY >= GRIDSIZE) { ++rPositionX; rPositionY = ZERO; }
	return (rPositionX < GRIDSIZE && rPositionY < GRIDSIZE) || (rPositionX < GRIDSIZE) ? true : false;
}

// Prototype: void Resoudre() //
// Intrants: Aucun //
// Extrants: Aucun //
// Type: Prototype //
// But: Utiliser dans la class Binairo qui appelle la fonction CommencerResolution() //
void CGrille::Resoudre()
{
	LireFichier();
	CommencerResolution(mValeurDepart, mValeurFin);
}

// Prototype: void CommencerResolution(int PositionX, int PositionY) //
// Intrants: PositionX, PositionY //
// Extrants: Aucun //
// Type: Prototype //
// But: Débuter la résolution de la grid //
void CGrille::CommencerResolution(int PositionX, int PositionY) {
	static const int MAXNUMBER = 2;
	if (VerifierPositionGrid(PositionX, PositionY))
		if (VerifierSiPositionPeutBouger(PositionX, PositionY)) TesterCombinaisons(PositionX, PositionY, MAXNUMBER);
		else CommencerResolution(PositionX, PositionY + UN);
	else Afficher();
}

// Prototype: bool VerifierSiPositionPeutBouger(int PositionX
bool CGrille::VerifierSiPositionPeutBouger(int PositionX, int PositionY) {
	return (GetGrid(PositionX, PositionY) == ZERO || GetGrid(PositionX, PositionY) == UN) ? false : true;
}

// Prototype: bool TesterAxeHorizontale(int x, int y, int Nombre) //
// Intrants: PositionX, PositionY, et Nombre //
// Extrants: Vrai ou Faux //
// Type: Fonction //
// But: Teste les conditions sur l'axe horizontale //
bool CGrille::TesterAxeHorizontale(int PositionX, int PositionY, int Nombre) {
	bool Correct = false;

	if ((PositionX >= ZERO && PositionX < GRIDSIZE && PositionY - UN >= ZERO && PositionY - UN < GRIDSIZE) && (PositionX >= ZERO && PositionX < GRIDSIZE && PositionY - 2 >= ZERO && PositionY - 2 < GRIDSIZE)) {
		if (GetGrid(PositionX, PositionY - UN) == Nombre && GetGrid(PositionX, PositionY - 2) == Nombre) {
			Correct = true;
		}
	}

	if ((PositionX >= ZERO && PositionX < GRIDSIZE && PositionY -  UN >= ZERO && PositionY - UN < GRIDSIZE) && (PositionX >= ZERO && PositionX < GRIDSIZE && PositionY + UN >= ZERO && PositionY + UN < GRIDSIZE)) {
		if (GetGrid(PositionX, PositionY - UN) == Nombre && GetGrid(PositionX, PositionY + UN) == Nombre) {
			Correct = true;
		}
	}

	if ((PositionX >= ZERO && PositionX < GRIDSIZE && PositionY + UN >= ZERO && PositionY + ZERO < GRIDSIZE) && (PositionX >= ZERO && PositionX < GRIDSIZE && PositionY + 2 >= ZERO && PositionY + 2 < GRIDSIZE)) {
		if (GetGrid(PositionX, PositionY + UN) == Nombre && GetGrid(PositionX, PositionY + 2) == Nombre) {
			Correct = true;
		}
	}
	return Correct;
}

// Prototype: bool TesterAxeVerticale(int x, int y, int Nombre) //
// Intrants: PositionX, PositionY et Nombre //
// Extrants: Vrai ou Faux //
// Type: Fonction //
// But: Teste les conditions sur l'axe verticale //
bool CGrille::TesterAxeVerticale(int PositionX, int PositionY, int Nombre) {
	bool Correct = false;

	if ((PositionX - UN >= 0 && PositionX - UN < GRIDSIZE && PositionY >= ZERO && PositionY < GRIDSIZE) && (PositionX - 2 >= ZERO && PositionX - 2 < GRIDSIZE && PositionY >= ZERO && PositionY < GRIDSIZE)) {
		if (GetGrid(PositionX - UN, PositionY) == Nombre && GetGrid(PositionX - 2, PositionY) == Nombre) {
			Correct = true;
		}
	}

	if ((PositionX - UN >= ZERO && PositionX - UN < GRIDSIZE && PositionY >= ZERO && PositionY < GRIDSIZE) && (PositionX + UN >= ZERO && PositionX + UN < GRIDSIZE && PositionY >= ZERO && PositionY < GRIDSIZE)) {
		if (GetGrid(PositionX - UN, PositionY) == Nombre && GetGrid(PositionX + UN, PositionY) == Nombre) {
			Correct = true;
		}
	}

	if ((PositionX + UN >= ZERO && PositionX + UN < GRIDSIZE && PositionY >= ZERO && PositionY < GRIDSIZE) && (PositionX + 2 >= ZERO && PositionX + 2 < GRIDSIZE && PositionY >= ZERO && PositionY < GRIDSIZE)) {
		if (GetGrid(PositionX + UN, PositionY) == Nombre && GetGrid(PositionX + 2, PositionY) == Nombre) {
			Correct = true;
		}
	}

	return Correct;
}

// Prototype: bool VerifierSiPeutMettreDansCase //
// Intrants: PositionX, PositionY et Nombre //
// Extrants: Vrai ou Faux //
// Type: Fonction //
// But: Permet de verifier s'il est possible de mettre une soit un 0 ou 1 dans la case passé en paramètre //
bool CGrille::VerifierSiPeutMettreDansCase(int PositionX, int PositionY, int Nombre) {
	int NombreLigne = 0;
	int NombreColonne = 0;
	bool LigneUnique = true;
	const int NBCOLONNE = 5, NBLIGNE = 5;
	int i = 0;

	while (i < GRIDSIZE)
	{
		if (GetGrid(PositionX, i) == Nombre) NombreLigne++;
		if (GetGrid(i, PositionY) == Nombre) NombreColonne++;
		++i;
	}

	return (!TesterAxeHorizontale(PositionX, PositionY, Nombre) && !TesterAxeVerticale(PositionX, PositionY, Nombre) && NombreLigne != NBLIGNE && NombreColonne != NBCOLONNE && LigneUnique) ? true : false;
}

// Prototype: void Afficher() //
// Intrants: Aucun //
// Extrants: Aucun //
// Type: Prototype //
// But: Affiche la grid à l'écran et dans un fichier //
void CGrille::Afficher() {
	string NomFichierSolution = "Charles-Bertrand-Solution-" + mNomFichier;
	const string DELIMITEUR_SANS_END_DEBUT = "--------------------------------------------\n";
	ofstream Out(NomFichierSolution);
    
	AfficherEntete(Out);
	cout << DELIMITEUR_SANS_END_DEBUT;
	Out << DELIMITEUR_SANS_END_DEBUT;
	for (int Ligne = 0; Ligne < GRIDSIZE; ++Ligne) {
		cout << " " << Ligne << " | ";
		Out << " " << Ligne << " | ";
		for (int Colonne = 0; Colonne < GRIDSIZE; ++Colonne) {
			cout << GetGrid(Ligne, Colonne) << " | ";
			Out << GetGrid(Ligne, Colonne) << " | ";
		}

		cout << GetValeursDecimalHorizontal(Ligne);
		Out << GetValeursDecimalHorizontal(Ligne);
		cout << DELIMITEUR;
		Out << DELIMITEUR;
	}
	cout << "   ";
	Out << "   ";
	AfficherValeurDecimalColonne(Out);
	cout << endl;
	Out << endl;

	Out.close();
}

// Prototype: void AfficherValeurDecimalColonne() //
// Intrants: Aucuns //
// Extrants: Aucun //
// Type: Prototype //
// But: Affiche les valeurs des colonnes converti //
void CGrille::AfficherValeurDecimalColonne(ostream& rOut) {
	for (int Colonne = 0; Colonne < GRIDSIZE; ++Colonne) {
		cout << " " << GetValeursDecimalVertical(Colonne);
		rOut << " " << GetValeursDecimalVertical(Colonne);
	}
}

// Prototype: bool VerifierLigneRemplie(int Ligne) const //
// Intrants: Ligne //
// Extrants: Vrai ou Faux //
// Type: Fonction //
// But: Vérifie si les lignes sont remplies //
bool CGrille::VerifierLigneRemplie(int Ligne) const {
	int i = 0;
	bool Reste = true;
	while (i < GRIDSIZE) {
		if (GetGrid(Ligne, i) == MVALEURINCONNU)
			Reste = false;
		++i;
	}
	return Reste;
}

// Prototype: bool VerifierColonneRemplie(int Colonne) const //
// Intrants: Colonne //
// Extrants: Vrai ou Faux //
// Type: Fonction //
// But: Vérifie si les colonnes sont remplies //
bool CGrille::VerifierColonneRemplie(int Colonne) const {
	int i = 0;
	bool Reste = false;
	while (i < GRIDSIZE) {
		if (GetGrid(i, Colonne) == MVALEURINCONNU)
			Reste = true;
	}
	return Reste;
}

// Prototype: void TesterCombinaisons(int &PositionX, int &PositionY) //
// Intrants: PositionX et PositionY //
// Extrants: Aucun //
// Type: Prototype //
// But: Après avoir vérifier certaines conditions, tester les nombres 0 et 1 //
void CGrille::TesterCombinaisons(int &rPositionX, int &rPositionY, int Nombre) {
	int i = 0;
	while (i < Nombre) {
		if (VerifierSiPeutMettreDansCase(rPositionX, rPositionY, i)) {
			SetGrid(rPositionX, rPositionY, i);
			CommencerResolution(rPositionX, rPositionY + UN);
			SetGrid(rPositionX, rPositionY, MVALEURINCONNU);
		}
		++i;
	}
}

// Prototype: void SetGrid(int PositionX, int PositionY, int Nombre) //
// Intrants: PositionX, PositionY, Nombre //
// Extrants: Aucun //
// Type: Prototype //
// But: Permet d'assigner une une valeur dans la Grid à l'aide de la PositionX et PositionY //
void CGrille::SetGrid(int PositionX, int PositionY, int Nombre) {
	mGrid[PositionX][PositionY] = Nombre;
}

void CGrille::AfficherEntete(ostream& rOut) const {
	cout << DELIMITEUR;
	rOut << DELIMITEUR;
	cout << "   | ";
	rOut << "   | ";

	int Colonne = 0;

	while (Colonne < GRIDSIZE) {
		cout << Colonne << " | ";
		rOut << Colonne << " | ";
		++Colonne;
	}

	cout << endl;
	rOut << endl;
}
