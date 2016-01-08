//----------------------------------------------------------------------------
// File : bXMLfvarNow.cpp
// Project : MacMap
// Purpose : C++ source file : Var "Now" formula class. Returns current time (number).
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
// 06/10/2008 creation.
//----------------------------------------------------------------------------

#include "bXMLfvarNow.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfvarNowElement	::bfvarNowElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLConstant(elt,gapp,bndl){
	setclassname("fvarnow");
	_dbval=new bTimeDBValue;
	_dbval->put(time(NULL));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfvarNowElement::~bfvarNowElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfvarNowElement::create(bGenericXMLBaseElement* elt){
	return(new bfvarNowElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfvarNowElement::init(void* ctx){
	bStdXMLConstant::init(ctx);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfvarNowElement::solve(bStdSolver* ctx){
	_dbval->put(time(NULL));
	return(ctx->add(_dbval));
}

