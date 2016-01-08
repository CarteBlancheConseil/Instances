//----------------------------------------------------------------------------
// File : bCalcCLastX.cpp
// Project : MacMap
// Purpose : C++ source file : Calc last x coordinate interface class
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
// 30/05/2008 creation.
//----------------------------------------------------------------------------

#include "bCalcCLastX.h"
#include "bXMLfcalcLastX.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCalcCLastX	::bCalcCLastX(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				: bStdCalc(elt,gapp,bndl){
	setclassname("clastx");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bCalcCLastX::~bCalcCLastX(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCalcCLastX::create(bGenericXMLBaseElement* elt){
	return(new bCalcCLastX(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCLastX::open(int* flags){
	bStdCalc::open(flags);
	_root=(bStdXMLFormulaElement*)new bfcalcLastXElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCalcCLastX::close(){
	bStdCalc::close();
	if(_root){
		delete (bfcalcLastXElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
int bCalcCLastX::kind(){
	return(_double);
}
