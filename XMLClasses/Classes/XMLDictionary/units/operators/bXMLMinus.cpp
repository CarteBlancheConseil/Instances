//----------------------------------------------------------------------------
// File : bXMLMinus.cpp
// Project : MacMap
// Purpose : C++ source file : minus operator tag class, used in formulas
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
// 08/01/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLMinus.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bMinusElement	::bMinusElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
			: bStdXMLOperatorElement(elt,gapp,bndl){
	setclassname("minus");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bMinusElement::~bMinusElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bMinusElement::create(bGenericXMLBaseElement* elt){
	return(new bMinusElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bMinusElement::solve(bStdSolver* ctx){
	if(!bStdXMLOperatorElement::solve(ctx)){
		return(false);
	}
bStdDBValue*	v=(*_a)-(*_b);
double			d;
	v->get(&d);
	_dbval->put(d);
	return(ctx->add(_dbval));
}
