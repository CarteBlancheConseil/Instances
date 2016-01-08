//----------------------------------------------------------------------------
// File : bXMLDBAddToContrast.cpp
// Project : MacMap
// Purpose : C++ source file : Add to contrasts tag class, used in selection solvers
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
// 25/05/2009 creation.
//----------------------------------------------------------------------------

#include "bXMLDBAddToContrast.h"
#include <mox_intf/bSelectSolver.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bDBAddToContrastElement	::bDBAddToContrastElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLFormulaElement(elt,gapp,bndl){
	setclassname("dbaddtocontrast");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bDBAddToContrastElement::~bDBAddToContrastElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bDBAddToContrastElement::create(bGenericXMLBaseElement* elt){
	return(new bDBAddToContrastElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bDBAddToContrastElement::init(void* ctx){
	((bSelectSolver*)ctx)->set_add2contrast((_cfvalue)?atoi(_cfvalue):0);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDBAddToContrastElement::solve(bStdSolver* ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bDBAddToContrastElement::reset(bStdSolver* ctx){
}
