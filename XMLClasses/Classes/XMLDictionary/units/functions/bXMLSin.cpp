//----------------------------------------------------------------------------
// File : bXMLSin.cpp
// Project : MacMap
// Purpose : C++ source file : sinus function tag class, used in formulas
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
// 16/05/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLSin.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bSinElement	::bSinElement(	bGenericXMLBaseElement* elt, 
									bGenericMacMapApp* gapp, 
									CFBundleRef bndl ) 
				: bStdXMLFunctionElement(elt,gapp,bndl){
	setclassname("sin");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bSinElement::~bSinElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bSinElement::create(bGenericXMLBaseElement* elt){
	return(new bSinElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSinElement::solve(bStdSolver* ctx){
	if(!bStdXMLFunctionElement::solve(ctx)){
		return(false);
	}
	_a->get(&_v);
	_dbval->put(sin(_v));
	return(ctx->add(_dbval));
}
