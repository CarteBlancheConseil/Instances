//----------------------------------------------------------------------------
// File : bXMLEndAngle.cpp
// Project : MacMap
// Purpose : C++ source file : end angle tag class, used in styles
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
// 30/06/2008 creation.
//----------------------------------------------------------------------------

#include "bXMLEndAngle.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Angle
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bEndAngleElement::bEndAngleElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("endangle");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bEndAngleElement::create(bGenericXMLBaseElement* elt){
	return(new bEndAngleElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bEndAngleElement::~bEndAngleElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bEndAngleElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
double	x;
	elt->getvalue(geo,&x);
	if((x>=0)&&(x<=360)){
		ctx->setEndAngle(x*M_PI/180.0);
		return(true);
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bEndAngleElement::actionstd(bGenericGraphicContext* ctx){
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
	if((x>=0)&&(x<=360)){
		ctx->setEndAngle(x*M_PI/180.0);
		return(true);
	}
	return(objectcompliant());
}

