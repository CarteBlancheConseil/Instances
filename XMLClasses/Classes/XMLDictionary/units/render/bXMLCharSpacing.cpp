//----------------------------------------------------------------------------
// File : bXMLCharSpacing.cpp
// Project : MacMap
// Purpose : C++ source file : char spacing tag class, used in styles
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
// 19/12/2003 creation.
//----------------------------------------------------------------------------

#include "bXMLCharSpacing.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// CharSpacing
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCharSpacingElement	::bCharSpacingElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("charspacing");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCharSpacingElement::create(bGenericXMLBaseElement* elt){
	return(new bCharSpacingElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bCharSpacingElement::~bCharSpacingElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bCharSpacingElement::actionval(	bGenericGraphicContext* ctx,
										bStdXMLValueElement* elt,
										bGenericGeoElement* geo){
//_bTrace_("bCharSpacingElement::actionval",true);
double	x;
	elt->getvalue(geo,&x);
	if(x!=SHRT_MIN){
		ctx->setCharSpacing(x);
		return(true);
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bCharSpacingElement::actionstd(bGenericGraphicContext* ctx){
//_bTrace_("bCharSpacingElement::actionstd",true);
double	x;
	if(objectcompliant()){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,&x);
	}
	else{
char	val[_values_length_max_];
		getvalue(val);
		if(strlen(val)==0){
			return(false);
		}
		x=atof(val);
	}
	if(x!=SHRT_MIN){
		ctx->setCharSpacing(x);
		return(true);
	}
	return(objectcompliant());
}

