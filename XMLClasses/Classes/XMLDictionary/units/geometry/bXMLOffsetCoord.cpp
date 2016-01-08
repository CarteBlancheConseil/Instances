//----------------------------------------------------------------------------
// File : bXMLOffsetCoord.cpp
// Project : MacMap
// Purpose : C++ source file : coordinates offset tag class, used in styles
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
// 10/06/2005 creation.
//----------------------------------------------------------------------------

#include "bXMLOffsetCoord.h"
#include <std_ext/bStdXMLValueElement.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bOffsetCoordElement	::bOffsetCoordElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLRenderingElement(elt,gapp,bndl){
	setclassname("offsetcoord");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bOffsetCoordElement::create(bGenericXMLBaseElement* elt){
	return(new bOffsetCoordElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bOffsetCoordElement::~bOffsetCoordElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
void bOffsetCoordElement::init(void* ctx){
bGenericType*	tp=((bGenericStyle*)ctx)->gettype();
	if(!tp){
		return;
	}
	if(_elts.count()>0){
		setobjectcompliant(true);
	}
bStdXMLValueElement*	elt;
	for(int i=1;i<=_elts.count();i++){
		if(_elts.get(i,&elt)){
			elt->init(tp);
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bOffsetCoordElement::action(bGenericGraphicContext *ctx){
	if(countelements()!=2){
		return(true);
	}
bGenericGeoElement*	geo=ctx->getCurElement();
	if(!geo){
		return(true);
	}
	
int		npts,*offsets,noffsets;
float	*xpts,*ypts;
	
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);

bStdXMLValueElement*	elt;
d2dvertex				vx;

	elt=(bStdXMLValueElement*)(void*)getelement(1);
	elt->getvalue(geo,&vx.x);
	elt=(bStdXMLValueElement*)(void*)getelement(2);
	elt->getvalue(geo,&vx.y);
	
	if((vx.x==0)&&(vx.y==0)){
		return(true);
	}
	
CGPoint		cgp;
	_gapp->locConverter()->convert(&cgp,&vx);
	
	cgp.x=(cgp.x-xpts[0]);
	cgp.y=(cgp.y-ypts[0]);
	
	for(int i=0;i<npts;i++){
		xpts[i]+=cgp.x;
		ypts[i]+=cgp.y;
	}

	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bOffsetCoordElement::applyforscale(bGenericGraphicContext *ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bOffsetCoordElement::applyforclass(bGenericGraphicContext *ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bOffsetCoordElement::applyforobject(bGenericGraphicContext *ctx){
	return(action(ctx));
}
