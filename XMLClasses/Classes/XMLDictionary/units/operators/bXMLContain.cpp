//----------------------------------------------------------------------------
// File : bXMLContain.cpp
// Project : MacMap
// Purpose : C++ source file : contains with operator tag class, used in formulas
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
// 12/03/2004 creation.
//----------------------------------------------------------------------------

#include "bXMLContain.h"
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bContainElement	::bContainElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLOperatorElement(elt,gapp,bndl){
	setclassname("contain");
	_dbval=new bBoolDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bContainElement::~bContainElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bContainElement::create(bGenericXMLBaseElement* elt){
	return(new bContainElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bContainElement::solve(bStdSolver* ctx){
	if(!bStdXMLOperatorElement::solve(ctx)){
		return(false);
	}
char	va[_values_length_max_];
char	vb[_values_length_max_];
	
	_a->get(va);
	_b->get(vb);
	
	strupper(va);
	strupper(vb);
	
	if(strlen(vb)==0){
		_dbval->put(false);
	}
	else{
		_dbval->put(strstr(va,vb)!=NULL);
	}
	return(ctx->add(_dbval));
}
