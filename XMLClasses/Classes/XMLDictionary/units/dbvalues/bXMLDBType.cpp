//----------------------------------------------------------------------------
// File : bXMLDBType.cpp
// Project : MacMap
// Purpose : C++ source file : type tag class, used in selection solvers
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
// 09/03/2004 creation.
//----------------------------------------------------------------------------

#include "bXMLDBType.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bDBTypeElement	::bDBTypeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLFormulaElement(elt,gapp,bndl){
	setclassname("dbtype");
	_tp=NULL;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bDBTypeElement::~bDBTypeElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bDBTypeElement::create(bGenericXMLBaseElement* elt){
	return(new bDBTypeElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bDBTypeElement::init(void* ctx){
	//bStdXMLFormulaElement::init(ctx);
int idx=_gapp->typesMgr()->index(_cfvalue);
	_tp=_gapp->typesMgr()->get(idx);
	((bStdSolver*)ctx)->set_type(_tp);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bDBTypeElement::solve(bStdSolver* ctx){
	return(_tp!=NULL);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bDBTypeElement::reset(bStdSolver* ctx){
	//bStdXMLFormulaElement::reset(ctx);
	_tp=NULL;
}
