//----------------------------------------------------------------------------
// File : bXMLBgShiftX.cpp
// Project : MacMap
// Purpose : C++ source file : background x shift tag class, used in styles
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
// 22/10/2010 creation.
//----------------------------------------------------------------------------

#include "bXMLBgShiftX.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bBgShiftXElement::bBgShiftXElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("bgshiftx");
	setobjectcompliant(true);
	_val=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bBgShiftXElement::create(bGenericXMLBaseElement* elt){
	return(new bBgShiftXElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bBgShiftXElement::~bBgShiftXElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBgShiftXElement::actionval(	bGenericGraphicContext* ctx,
											bStdXMLValueElement* elt,
											bGenericGeoElement* geo){
	elt->getvalue(geo,&_val);
	if(_val!=SHRT_MIN){
		ctx->setBackgroundWidthDec(_val);
		return(true);
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBgShiftXElement::actionstd(bGenericGraphicContext* ctx){
	if(_elts.count()>0){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,&_val);
	}
	else{
char	val[_values_length_max_];
		getvalue(val);
		_val=atof(val);		
	}
	if(_val!=SHRT_MIN){
		ctx->setBackgroundWidthDec(_val);
		return(true);
	}
	return(true);
}


