//----------------------------------------------------------------------------
// File : bXMLPath.cpp
// Project : MacMap
// Purpose : C++ source file : simple path tag class, used in params
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
// 12/01/2004 creation.
//----------------------------------------------------------------------------

#include "bXMLPath.h"
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Path
// ------------
#define _DOCUMENT_NAME_ "$DOCUMENT_NAME"

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPathElement	::bPathElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLBaseElement(elt,gapp,bndl){
	setclassname("path");
	_docrel=false;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPathElement::create(bGenericXMLBaseElement* elt){
	return(new bPathElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPathElement::~bPathElement(){
}

// ---------------------------------------------------------------------------
// Accès à la valeur
// -----------
void bPathElement::getvalue(char* value){
	bStdXMLBaseElement::getvalue(value);
	if(strstr(value,_DOCUMENT_NAME_)==value){
char	name[_values_length_max_];
		_gapp->document()->name(name);
		strrep(value,_DOCUMENT_NAME_,name);
		_docrel=true;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
void bPathElement::setvalue(char* value){
	if(_docrel){
char*	val=(char*)malloc(strlen(value)+strlen(_DOCUMENT_NAME_)+1);
		if(val){
char	name[_values_length_max_];
			_gapp->document()->name(name);
			strrep(val,name,_DOCUMENT_NAME_);
			bStdXMLBaseElement::setvalue(val);
			free(val);
			return;
		}
	}
	bStdXMLBaseElement::setvalue(value);
}
