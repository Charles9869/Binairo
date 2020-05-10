// Fichier: Binairo.cpp //
// Charles Bertrand //
// Date de création: 3 Octobre 2018 //

#include "Binairo.hpp"
#include <exception>
#include <iostream>
#include <string>
using namespace std;

// Prototype: Binairo() //
// Intrants: Aucun //
// Extrants: Aucun //
// Type: Constructeur //
Binairo::Binairo() {

}

// Prototype: void Run() //
// Intrants: Aucun //
// Extrants: Aucun //
// Type: Prototype //
// But: Permet de démarrer la résolution de la grille //s
void Binairo::Run() {
	try {
		do {
			mGrid.Resoudre();
		} while (true);
	}
	catch (const std::exception& ex) {
		cout << ex.what();
	}
}

