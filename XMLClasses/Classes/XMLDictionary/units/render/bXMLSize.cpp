//----------------------------------------------------------------------------
// File : bXMLSize.cpp
// Project : MacMap
// Purpose : C++ source file : size (x&y) tag class, used in styles
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
// 02/04/2003 creation.
//----------------------------------------------------------------------------

#include "bXMLSize.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Size
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bSizeElement	::bSizeElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("size");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bSizeElement::create(bGenericXMLBaseElement* elt){
	return(new bSizeElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bSizeElement::~bSizeElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSizeElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
//_bTrace_("bSizeElement::actionval",true);
double x;
	elt->getvalue(geo,&x);
//_tm_(x);
	if(x>0){
		ctx->setSize(x);
		return(true);
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSizeElement::actionstd(bGenericGraphicContext* ctx){
//_bTrace_("bSizeElement::actionstd",true);
double	x;
	if(objectcompliant()){
//_tm_("objectcompliant");
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,&x);
	}
	else{
//_tm_("not objectcompliant");
char	val[_values_length_max_];
		getvalue(val);
		if(strlen(val)==0){
			return(false);
		}
		x=atof(val);
	}
//_tm_(x);
	if(x>0){
		ctx->setSize(x);
		return(true);
	}
	return(objectcompliant());
}
