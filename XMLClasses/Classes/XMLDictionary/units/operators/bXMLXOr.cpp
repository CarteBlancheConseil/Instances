//----------------------------------------------------------------------------
// File : bXMLXOr.cpp
// Project : MacMap
// Purpose : C++ source file : xor operator tag class, used in formulas
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
// 21/05/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLXOr.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXOrElement	::bXOrElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
			: bStdXMLOperatorElement(elt,gapp,bndl){
	setclassname("xor");
	_dbval=new bBoolDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXOrElement::~bXOrElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXOrElement::create(bGenericXMLBaseElement* elt){
	return(new bXOrElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXOrElement::solve(bStdSolver* ctx){
	if(!bStdXMLOperatorElement::solve(ctx)){
		return(false);
	}
bool	a,b;
	_a->get(&a);
	_b->get(&b);
	if(a&&b){
		_dbval->put(false);
	}
	else{
		_dbval->put(a||b);
	}
	return(ctx->add(_dbval));
}
