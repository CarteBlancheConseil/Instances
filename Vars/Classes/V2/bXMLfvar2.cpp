//----------------------------------------------------------------------------
// File : bXMLfvar2.cpp
// Project : MacMap
// Purpose : C++ source file : Var "2" formula class. Returns 2.
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
// 09/12/2005 creation.
//----------------------------------------------------------------------------

#include "bXMLfvar2.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfvar2Element	::bfvar2Element(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLConstant(elt,gapp,bndl){
	setclassname("fvar2");
	_dbval=new bDoubleDBValue;
	_dbval->put(2.0);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfvar2Element::~bfvar2Element(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfvar2Element::create(bGenericXMLBaseElement* elt){
	return(new bfvar2Element(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfvar2Element::init(void* ctx){
	bStdXMLConstant::init(ctx);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfvar2Element::solve(bStdSolver* ctx){
	return(ctx->add(_dbval));
}

