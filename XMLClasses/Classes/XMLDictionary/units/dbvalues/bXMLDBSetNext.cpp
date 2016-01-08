//----------------------------------------------------------------------------
// File : bXMLDBSetNext.cpp
// Project : MacMap
// Purpose : C++ source file : set next tag class, used in selection solvers
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

#include "bXMLDBSetNext.h"
#include <mox_intf/bSelectSolver.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bDBSetNextElement	::bDBSetNextElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLFormulaElement(elt,gapp,bndl){
	setclassname("dbsetnext");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bDBSetNextElement::~bDBSetNextElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bDBSetNextElement::create(bGenericXMLBaseElement* elt){
	return(new bDBSetNextElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bDBSetNextElement::init(void* ctx){
	((bSelectSolver*)ctx)->set_next((_cfvalue)?(*(UInt32*)_cfvalue):0);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDBSetNextElement::solve(bStdSolver* ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bDBSetNextElement::reset(bStdSolver* ctx){
}
