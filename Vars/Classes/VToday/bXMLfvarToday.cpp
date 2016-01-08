//----------------------------------------------------------------------------
// File : bXMLfvarToday.cpp
// Project : MacMap
// Purpose : C++ source file : Var "Today" formula class. Returns current date (number).
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

#include "bXMLfvarToday.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfvarTodayElement	::bfvarTodayElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLConstant(elt,gapp,bndl){
	setclassname("fvartoday");
	_dbval=new bDateDBValue;
	_dbval->put(time(NULL));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfvarTodayElement::~bfvarTodayElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfvarTodayElement::create(bGenericXMLBaseElement* elt){
	return(new bfvarTodayElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfvarTodayElement::init(void* ctx){
	bStdXMLConstant::init(ctx);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfvarTodayElement::solve(bStdSolver* ctx){
	_dbval->put(time(NULL));
	return(ctx->add(_dbval));
}

