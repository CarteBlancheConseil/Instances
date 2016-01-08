//----------------------------------------------------------------------------
// File : bXMLValue.cpp
// Project : MacMap
// Purpose : C++ source file : value tag class, used in styles
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
// Classe de base pour lecture de paramétrages au format XML
//----------------------------------------------------------------------------
// 22/10/2003 creation.
//----------------------------------------------------------------------------

#include "bXMLValue.h"

// ---------------------------------------------------------------------------
// Value
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bValueElement	::bValueElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLValueElement(elt,gapp,bndl){
	setclassname("value");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bValueElement::create(bGenericXMLBaseElement* elt){
	return(new bValueElement(elt,(bGenericMacMapApp*)elt->getapp(),elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bValueElement::~bValueElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
void bValueElement::getvalue(bGenericGeoElement* geo, char* value){
	bStdXMLValueElement::getvalue(value);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bValueElement::getvalue(bGenericGeoElement* geo, bool* value){
char	val[_values_length_max_];
	bStdXMLValueElement::getvalue(val);
	(*value)=atoi(val);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bValueElement::getvalue(bGenericGeoElement* geo, int* value){
char	val[_values_length_max_];
	bStdXMLValueElement::getvalue(val);
	(*value)=atoi(val);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bValueElement::getvalue(bGenericGeoElement* geo, double* value){
char	val[_values_length_max_];
	bStdXMLValueElement::getvalue(val);
	(*value)=atof(val);
}
