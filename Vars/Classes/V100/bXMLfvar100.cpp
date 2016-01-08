//----------------------------------------------------------------------------
// File : bXMLfvar100.cpp
// Project : MacMap
// Purpose : C++ source file : Var "100" formula class. Returns 100.
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

#include "bXMLfvar100.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfvar100Element	::bfvar100Element(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLConstant(elt,gapp,bndl){
	setclassname("fvar100");
	_dbval=new bDoubleDBValue;
	_dbval->put(100.0);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfvar100Element::~bfvar100Element(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfvar100Element::create(bGenericXMLBaseElement* elt){
	return(new bfvar100Element(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfvar100Element::init(void* ctx){
	bStdXMLConstant::init(ctx);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfvar100Element::solve(bStdSolver* ctx){
	return(ctx->add(_dbval));
}

