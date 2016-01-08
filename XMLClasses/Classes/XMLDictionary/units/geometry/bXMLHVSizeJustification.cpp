//----------------------------------------------------------------------------
// File : bXMLHVSizeJustification.cpp
// Project : MacMap
// Purpose : C++ source file : x&y size justification tag class, used in styles
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
// 22/06/2011 creation.
//----------------------------------------------------------------------------

#include "bXMLHVSizeJustification.h"
#include <MacMapSuite/bTrace.h>

#pragma mark ->hvsizejustification
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bHVSizeJustificationElement	::bHVSizeJustificationElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
							: bStdXMLLowRenderElement(elt,gapp,bndl){
	setobjectcompliant(true);
	_val=-1;
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bHVSizeJustificationElement::~bHVSizeJustificationElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bHVSizeJustificationElement::actionval(bGenericGraphicContext* ctx,
											bStdXMLValueElement* elt,
											bGenericGeoElement* geo){
	elt->getvalue(geo,&_val);
	if((_val>=0)&&(_val<=1)){
		return(align(ctx));
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bHVSizeJustificationElement::actionstd(bGenericGraphicContext* ctx){
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
	if((_val>=0)&&(_val<=1)){
		return(align(ctx));
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bHVSizeJustificationElement::align(bGenericGraphicContext *ctx){
	return(false);
}

#pragma mark ->hsizejustification
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bHSizeJustificationElement	::bHSizeJustificationElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
							: bHVSizeJustificationElement(elt,gapp,bndl){
	setclassname("hsizejustification");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bHSizeJustificationElement::create(bGenericXMLBaseElement* elt){
	return(new bHSizeJustificationElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bHSizeJustificationElement::~bHSizeJustificationElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bHSizeJustificationElement::align(bGenericGraphicContext *ctx){
_bTrace_("bHSizeJustificationElement::align",false);
int		npts,*offsets,noffsets;
float	*xpts,*ypts;
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(npts<=0){
		return(true);
	}
	
double	m=ctx->getHSize();
double	d=(m*0.5)-(m*_val);
	for(int i=0;i<npts;i++){
		xpts[i]=xpts[i]-d;
	}	
	return(true);
}

#pragma mark ->vsizejustification
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVSizeJustificationElement	::bVSizeJustificationElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
							: bHVSizeJustificationElement(elt,gapp,bndl){
	setclassname("vsizejustification");
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVSizeJustificationElement::create(bGenericXMLBaseElement* elt){
	return(new bVSizeJustificationElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bVSizeJustificationElement::~bVSizeJustificationElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bVSizeJustificationElement::align(bGenericGraphicContext *ctx){
_bTrace_("bVSizeJustificationElement::align",false);
int		npts,*offsets,noffsets;
float	*xpts,*ypts;
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(npts<=0){
		return(true);
	}
	
double	m=ctx->getVSize();
double	d=(m*0.5)-(m*_val);
	for(int i=0;i<npts;i++){
		ypts[i]=ypts[i]-d;
	}	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
/*double	m=ctx->getHSize();
double	a=ctx->getAngle();
double	d=(m*0.5)-(m*_val);
_tm_("m="+m);
_tm_("d="+d);
_tm_("a="+a);
for(int i=0;i<npts;i++){
	xpts[i]=xpts[i]-d*cos(a);
	//ypts[i]=ypts[i]-d*sin(a);
}	
return(true);
*/
