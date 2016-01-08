//----------------------------------------------------------------------------
// File : bXMLNthChar.cpp
// Project : MacMap
// Purpose : C++ source file : nth char operator tag class, used in formulas
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
// 06/07/2011 creation.
//----------------------------------------------------------------------------

#include "bXMLNthChar.h"
#include <MacMapSuite/C_Utils.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bNthCharElement	::bNthCharElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLOperatorElement(elt,gapp,bndl){
	setclassname("nthchar");
	_dbval=new bCharDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bNthCharElement::~bNthCharElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bNthCharElement::create(bGenericXMLBaseElement* elt){
	return(new bNthCharElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bNthCharElement::solve(bStdSolver* ctx){
	if(!bStdXMLOperatorElement::solve(ctx)){
		return(false);
	}
char	va[_values_length_max_];
int		vb;
char	bf[8];
	bf[1]=0;
	
	_a->get(va);
	_b->get(&vb);
	if(strlen(va)<vb){
		_dbval->put(0);
	}
	else{
		bf[0]=va[vb-1];
		_dbval->put(bf);
	}
	return(ctx->add(_dbval));
}
