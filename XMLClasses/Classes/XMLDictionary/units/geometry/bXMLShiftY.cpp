//----------------------------------------------------------------------------
// File : bXMLShiftY.cpp
// Project : MacMap
// Purpose : C++ source file : y shift tag class, used in styles
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
// 04/07/2007 creation.
//----------------------------------------------------------------------------

#include "bXMLShiftY.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bShiftYElement	::bShiftYElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("shifty");
	setobjectcompliant(true);
	_val=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bShiftYElement::create(bGenericXMLBaseElement* elt){
	return(new bShiftYElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bShiftYElement::~bShiftYElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bShiftYElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
	elt->getvalue(geo,&_val);
	if(_val!=0){
		return(shift(ctx));
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bShiftYElement::actionstd(bGenericGraphicContext* ctx){
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
	if(_val!=0){
		return(shift(ctx));
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bShiftYElement::shift(bGenericGraphicContext *ctx){
double	v;
int		npts,*offsets,noffsets;
float	*xpts,*ypts;
	
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(npts<1){
		return(true);
	}
	v=_val*ctx->getUnitCoef()*ctx->getFixConv();
	for(int i=0;i<npts;i++){
		ypts[i]+=v;
	}
	return(true);
}

