//----------------------------------------------------------------------------
// File : bCalcCCoordX.cpp
// Project : MacMap
// Purpose : C++ source file : Calc x coordinate interface class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 1997-2015 Carte Blanche Conseil.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 01/12/2005 creation.
//----------------------------------------------------------------------------

#include "bCalcCCoordX.h"
#include "bXMLfcalcCoordX.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCCoordX	::bCalcCCoordX(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("ccoordx");
//	_sign='cCrx';
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCCoordX::~bCalcCCoordX(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCCoordX::create(bGenericXMLBaseElement* elt){
	return(new bCalcCCoordX(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCCoordX::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcCoordXElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCCoordX::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcCoordXElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCCoordX::kind(){
	return(_double);
}
