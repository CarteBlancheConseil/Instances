//----------------------------------------------------------------------------
// File : bXMLPointJustification.cpp
// Project : MacMap
// Purpose : C++ source file : justify on coordinate tag class, used in styles
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
// 12/06/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLPointJustification.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPointJustificationElement	::bPointJustificationElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
							: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("pointjustification");
	setobjectcompliant(true);
	_val=-1;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPointJustificationElement::create(bGenericXMLBaseElement* elt){
	return(new bPointJustificationElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPointJustificationElement::~bPointJustificationElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPointJustificationElement::actionval(	bGenericGraphicContext* ctx,
											bStdXMLValueElement* elt,
											bGenericGeoElement* geo){
	elt->getvalue(geo,&_val);
	if((_val>0)&&(_val<=1)){
		ctx->setJustification(_val);
		return(align(ctx));
	}
	else if(_val==0){
		ctx->setJustification(_val);
		return(true);
	}
	else if(_val==2){
		ctx->setJustification(_val);
		return(justify(ctx));
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPointJustificationElement::actionstd(bGenericGraphicContext* ctx){
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
	if((_val>0)&&(_val<=1)){
		ctx->setJustification(_val);
		return(align(ctx));
	}
	else if(_val==0){
		ctx->setJustification(_val);
		return(true);
	}
	else if(_val==2){
		ctx->setJustification(_val);
		return(justify(ctx));
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPointJustificationElement::align(bGenericGraphicContext *ctx){
int		npts,*offsets,noffsets;
float	*xpts,*ypts;
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(npts<=0){
		return(true);
	}
bCoreTextInfo* txt=ctx->getText();
	if(!txt){
		return(true);
	}
	if(txt->nGlyphs()==0){
		return(true);
	}
	txt->setAlign(_val);

double	w=txt->textWidth();
double	a=ctx->getAngle();
double	d=((_val==2.0)?0.0:_val)*w;
	for(int i=0;i<npts;i++){
		xpts[i]=xpts[i]-d*cos(a);
		ypts[i]=ypts[i]-d*sin(a);
	}	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPointJustificationElement::justify(bGenericGraphicContext *ctx){
int		npts,*offsets,noffsets;
float	*xpts,*ypts;
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(npts!=1){
		return(true);
	}
bCoreTextInfo* txt=ctx->getText();
	if(!txt){
		return(true);
	}
int	ng=txt->nGlyphs();
	if(ng==0){
		return(true);
	}
	txt->setAlign(_val);
	
float*	x=new float[ng];
float*	y=new float[ng];
float*	a=new float[ng];
double	alpha=ctx->getAngle();
double	dx,dy,gx,gy;
int		i,j,g,sz;
int		o[2]={0,ng};

	txt->setAngle(alpha);
	dx=xpts[0];
	dy=ypts[0];

	for(i=0;i<txt->nLines();i++){
		g=txt->lineStart(i,&sz);
		txt->setFirst(g);
		txt->setOrigin(dx,dy);
		for(j=g;j<g+sz;j++){
			txt->absoluteGlyphPos(&gx,&gy,j,1);
			x[j]=gx;
			y[j]=gy;
			a[j]=alpha;
		}
		dy-=txt->ascent();
		if(g!=0){
			x[g-1]=x[g];
			y[g-1]=y[g];
			a[g-1]=0;
		}
	}
	ctx->setGeometry(x,y,a,ng,o,2);
	delete x;
	delete y;
	delete a;
	return(true);
}


