//----------------------------------------------------------------------------
// File : bXMLfvar0.cpp
// Project : MacMap
// Purpose : C++ source file : Var "0" formula class. Returns 0.
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
// 30/07/2010 creation.
//----------------------------------------------------------------------------

#include "bXMLfvar0.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfvar0Element	::bfvar0Element(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLConstant(elt,gapp,bndl){
	setclassname("fvar0");
	_dbval=new bDoubleDBValue;
	_dbval->put(0.0);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfvar0Element::~bfvar0Element(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfvar0Element::create(bGenericXMLBaseElement* elt){
	return(new bfvar0Element(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfvar0Element::init(void* ctx){
	bStdXMLConstant::init(ctx);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfvar0Element::solve(bStdSolver* ctx){
	return(ctx->add(_dbval));
}

