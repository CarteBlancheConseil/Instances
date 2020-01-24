//----------------------------------------------------------------------------
// File : bXMLBoxPos.cpp
// Project : MacMap
// Purpose : C++ source file : box from geometry tag class, used in styles
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
// 09/07/2009 creation.
//----------------------------------------------------------------------------

#include "bXMLBoxPos.h"
#include <std_ext/bStdXMLValueElement.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bBoxPosElement	::bBoxPosElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLRenderingElement(elt,gapp,bndl){
	setclassname("boxpos");
	setobjectcompliant(true);
	setclasscompliant(true);
	_xval=0;
	_yval=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bBoxPosElement::create(bGenericXMLBaseElement* elt){
	return(new bBoxPosElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bBoxPosElement::~bBoxPosElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
void bBoxPosElement::init(void* ctx){
bGenericType*	tp=((bGenericStyle*)ctx)->gettype();
	if(tp==NULL){
		setobjectcompliant(false);
	}
	else{
		setclasscompliant(false);
	}
bStdXMLValueElement*	elt;
	for(int i=1;i<=_elts.count();i++){
		if(_elts.get(i,&elt)){
			elt->init(tp);
		}
	}
	_xval=0;
	_yval=0;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBoxPosElement::action(bGenericGraphicContext *ctx){
	if(countelements()>=2){
bGenericGeoElement*		geo=ctx->getCurElement();
bStdXMLValueElement*	elt;

		elt=(bStdXMLValueElement*)(void*)getelement(1);
		elt->getvalue(geo,&_xval);
		elt=(bStdXMLValueElement*)(void*)getelement(2);
		elt->getvalue(geo,&_yval);
	}

int		npts,*offsets,noffsets;
float	*xpts,*ypts;
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(npts<=0){
		return(true);
	}
CGPoint	min,max;
CGPoint	res;
	min.x=max.x=xpts[0];
	min.y=max.y=ypts[0];
	for(int i=1;i<npts;i++){
		if(min.x>xpts[i]){
			min.x=xpts[i];
		}
		else if(max.x<xpts[i]){
			max.x=xpts[i];
		}
		if(min.y>ypts[i]){
			min.y=ypts[i];
		}
		else if(max.y<ypts[i]){
			max.y=ypts[i];
		}
	}
	res.x=min.x+(max.x-min.x)*_xval;
	res.y=min.y+(max.y-min.y)*_yval;
#warning CAST
	ctx->setGeometry((float*)&res.x,(float*)&res.y,1,NULL,0);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBoxPosElement::applyforscale(bGenericGraphicContext *ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBoxPosElement::applyforclass(bGenericGraphicContext *ctx){
	return(action(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bBoxPosElement::applyforobject(bGenericGraphicContext *ctx){
	return(action(ctx));
}
