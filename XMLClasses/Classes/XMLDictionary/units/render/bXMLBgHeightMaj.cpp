//----------------------------------------------------------------------------
// File : bXMLBgHeightMaj.cpp
// Project : MacMap
// Purpose : C++ source file : background height margin tag class, used in styles
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
// 05/10/2010 creation.
//----------------------------------------------------------------------------

#include "bXMLBgHeightMaj.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// BgHeightMaj
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bBgHeightMajElement	::bBgHeightMajElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("bgheightmaj");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bBgHeightMajElement::create(bGenericXMLBaseElement* elt){
	return(new bBgHeightMajElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bBgHeightMajElement::~bBgHeightMajElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBgHeightMajElement::actionval(bGenericGraphicContext* ctx,
									bStdXMLValueElement* elt,
									bGenericGeoElement* geo){
double x;
	elt->getvalue(geo,&x);
	if(x>=SHRT_MIN){
		ctx->setBackgroundHeightMaj(x);
		return(true);
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBgHeightMajElement::actionstd(bGenericGraphicContext* ctx){
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
	if(x>=SHRT_MIN){
		ctx->setBackgroundHeightMaj(x);
		return(true);
	}
	return(false);
}
