//----------------------------------------------------------------------------
// File : bXMLfcalcCrtDate.cpp
// Project : MacMap
// Purpose : C++ source file : Calc creation date formula class. Return object's creation date.
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
// 01/03/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLfcalcCrtDate.h"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcCrtDateElement	::bfcalcCrtDateElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalccrtdate");
	_dbval=new bDateDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcCrtDateElement::~bfcalcCrtDateElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcCrtDateElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcCrtDateElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcCrtDateElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
double	val;
	o->getValue(kOBJ_CrDate_,&val);
	_dbval->put(val);
	return(ctx->add(_dbval));
}

