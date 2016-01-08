//----------------------------------------------------------------------------
// File : bXMLBgWidthMaj.cpp
// Project : MacMap
// Purpose : C++ source file : background width margin tag class, used in styles
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

#include "bXMLBgWidthMaj.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// BgWidthMaj
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bBgWidthMajElement	::bBgWidthMajElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("bgwidthmaj");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bBgWidthMajElement::create(bGenericXMLBaseElement* elt){
	return(new bBgWidthMajElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bBgWidthMajElement::~bBgWidthMajElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBgWidthMajElement::actionval(bGenericGraphicContext* ctx,
								   bStdXMLValueElement* elt,
								   bGenericGeoElement* geo){
double x;
	elt->getvalue(geo,&x);
	if(x>=0){
		ctx->setBackgroundWidthMaj(x);
		return(true);
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBgWidthMajElement::actionstd(bGenericGraphicContext* ctx){
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
	if(x>=0){
		ctx->setBackgroundWidthMaj(x);
		return(true);
	}
	return(false);
}
