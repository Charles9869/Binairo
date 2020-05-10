//  Classe permettant de généraliser la création 
//  d'une matrice sans égard au type
//
//  par Pierre Prud'homme, septembre 2009
//--------------------------------------------------
#pragma once
#include <vector>
#include <exception>
using namespace std;

template <class T>
class Matrice
{
public:
	//--- Constructeurs
	Matrice( ) { }
	Matrice( int iNbLignes, int iNbColonnes ) : vecteur_( iNbLignes )
	{
		for( int i = 0; i < iNbLignes; i++ )
			vecteur_[ i ].resize( iNbColonnes );
	}
	Matrice( const Matrice & oDroite ) : vecteur_( oDroite.vecteur_ ) { }

	//--- Accesseurs et Mutateurs
	int GetNbLignes( ) const
	{ return static_cast<int>(vecteur_.size( )); }

	int GetNbColonnes( ) const
	{ return GetNbLignes( ) > 0 ? static_cast<int>(vecteur_[ 0 ].size( )) : 0; }

	void SetNbLignes( int iNbLignes )
	{ vecteur_.resize(iNbLignes); }

	void SetNbColonnes ( int iNbColonnes )
	{  for( int i = 0; i < static_cast<int>(vecteur_.size()); i++ )
    	vecteur_[ i ].resize( iNbColonnes );
	}

	//--- Surcharge de l'opérateur [ ] 
	//    pour lecture et écriture dans la matrice 
	const vector<T> & operator[]( int iLigne ) const
	{ return vecteur_[ iLigne ]; }
	vector<T> & operator[]( int iLigne )
	{ return vecteur_[ iLigne ]; }

	const vector<T> & at (int iLigne) const
	{	return vecteur_.at( iLigne );	}
	vector<T> & at (int iLigne) 
	{	return vecteur_.at( iLigne );	}

private:
	vector< vector<T> > vecteur_;
};
