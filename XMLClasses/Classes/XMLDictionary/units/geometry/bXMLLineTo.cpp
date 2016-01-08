//----------------------------------------------------------------------------
// File : bXMLLineTo.cpp
// Project : MacMap
// Purpose : C++ source file : line to tag class, used in styles
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
// 27/06/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLLineTo.h"
#include <std_ext/bStdXMLValueElement.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bLineToElement	::bLineToElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLRenderingElement(elt,gapp,bndl){
	setclassname("lineto");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bLineToElement::create(bGenericXMLBaseElement* elt){
	return(new bLineToElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bLineToElement::~bLineToElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
void bLineToElement::init(void* ctx){
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
bool bLineToElement::action(bGenericGraphicContext* ctx){
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
	
int		n=npts*2;
int		no=npts+1;
int*	o=new int[no];
float*	x=new float[n];
float*	y=new float[n];
	
	for(int i=0;i<n;i+=2){
		x[i]=xpts[i/2];
		y[i]=ypts[i/2];
		x[i+1]=cgp.x;
		y[i+1]=cgp.y;
		o[i/2]=i;
	}
	o[no-1]=n;
	ctx->setGeometry(x,y,n,o,no);
	delete x;
	delete y;
	delete o;
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bLineToElement::applyforscale(bGenericGraphicContext *ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bLineToElement::applyforclass(bGenericGraphicContext *ctx){
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bLineToElement::applyforobject(bGenericGraphicContext *ctx){
	return(action(ctx));
}
