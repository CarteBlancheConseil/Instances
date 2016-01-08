//----------------------------------------------------------------------------
// File : bXMLArrow.cpp
// Project : MacMap
// Purpose : C++ source file : arrow tag class, used in styles
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
// A modidifer pour les multilines
//----------------------------------------------------------------------------
// 21/12/2005 creation.
//----------------------------------------------------------------------------

#include "bXMLArrow.h"
#include <mox_intf/CGUtils.h>
#include <MacMapSuite/C_Utils.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bArrowElement	::bArrowElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("arrow");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bArrowElement::create(bGenericXMLBaseElement* elt){
	return(new bArrowElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bArrowElement::~bArrowElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
void bArrowElement::init(void* ctx){
	bStdXMLLowRenderElement::init(ctx);
	_dr=0;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bArrowElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
	elt->getvalue(geo,&_dr);
	if(_dr==0){
int		o[2]={0,1};
float	x=0;
float	y=0;
		ctx->setGeometry(&x,&y,1,o,2);
		return(true);
	//	return(false);
	}
	return(make_arrow(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bArrowElement::actionstd(bGenericGraphicContext* ctx){
	if(_elts.count()>0){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,&_dr);
	}
	else{
char	val[_values_length_max_];
		getvalue(val);
		_dr=matof(val);		
	}
	if(_dr==0){
int		o[2]={0,1};
float	x=0;
float	y=0;
		ctx->setGeometry(&x,&y,1,o,2);
		return(true);
	//	return(false);
	}
	return(make_arrow(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bArrowElement::make_arrow(bGenericGraphicContext *ctx){
int		npts,*offsets,noffsets;
float	*xpts,*ypts;

	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);

	if(npts<2){
int		lo[2]={0,1};
float	lx=0;
float	ly=0;
		ctx->setGeometry(&lx,&ly,1,lo,2);
		return(true);
	}

long	npart=0;
	for(long i=0;i<noffsets-1;i++){
		if(offsets[i+1]-offsets[i]>1){
			npart++;
		}
	}
	if(npart==0){
int		lo[2]={0,1};
float	lx=0;
float	ly=0;
		ctx->setGeometry(&lx,&ly,1,lo,2);
		return(true);
	}
	
float	*x		=(float*)malloc((npart*5L)*sizeof(float));
float	*y		=(float*)malloc((npart*5L)*sizeof(float));
int		*poff	=(int*)malloc((npart+1L)*sizeof(int));
	
	poff[0]=0;
	for(long i=1;i<=npart;i++){
		poff[i]=poff[i-1]+5;
	}
	
float	sz=ctx->getHSize();
	npart=0;
	for(long i=0;i<noffsets-1;i++){
		if(offsets[i+1]-offsets[i]>1){
			make_arrow(&xpts[offsets[i]],&ypts[offsets[i]],offsets[i+1]-offsets[i],sz,&x[npart*5],&y[npart*5]);
			npart++;
		}
	}
	
	ctx->setGeometry(x,y,npart*5L,poff,npart+1);
	
	if(x){
		free(x);
	}
	if(y){
		free(y);
	}
	if(poff){
		free(poff);
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bArrowElement::make_arrow(float* xpts, float* ypts, int npts, float sz, float* xout, float* yout){
//_bTrace_("bArrowElement::make_arrow",true);
CGPoint	pa,pb;
long	i=0;
double	a,l=0,w,r,tl,pl;

	if(_dr>=1){
		pa=CGPointMake(xpts[npts-2],ypts[npts-2]);
		pb=CGPointMake(xpts[npts-1],ypts[npts-1]);
		a=CGPointVec2Angle(&pa,&pb);
	}
	else if(_dr<=-1){
		pa=CGPointMake(xpts[1],ypts[1]);
		pb=CGPointMake(xpts[0],ypts[0]);
		a=CGPointVec2Angle(&pa,&pb);
	}
	else if(_dr>=0){
		tl=length(xpts,ypts,npts);
		w=_dr*tl;
		for(i=1;i<npts;i++){
			pl=length(xpts[i-1],ypts[i-1],xpts[i],ypts[i]);
			l+=pl;
			if(l>=w){
				l-=pl;
				break;
			}
		}
		r=(w-l)/pl;//Résidu
		pa=CGPointMake(xpts[i-1],ypts[i-1]);
		pb=CGPointMake(xpts[i],ypts[i]);
		a=CGPointVec2Angle(&pa,&pb);// Calcul sur les points initiaux pour plus de précision
		pb.x=pa.x+(pb.x-pa.x)*r;// Calcul de l'accroche x
		pb.y=pa.y+(pb.y-pa.y)*r;// Calcul de l'accroche y
	}
	else{// <=0
		tl=length(xpts,ypts,npts);
		w=(1.0+_dr)*tl;
		for(i=1;i<npts;i++){// recherche de l'index du point après lequel le texte commence
			pl=length(xpts[i-1],ypts[i-1],xpts[i],ypts[i]);
			l+=pl;
			if(l>=w){
				l-=pl;
				break;
			}
		}
		r=(w-l)/pl;//Résidu
		pb=CGPointMake(xpts[i-1],ypts[i-1]);
		pa=CGPointMake(xpts[i],ypts[i]);
		a=CGPointVec2Angle(&pa,&pb);// Calcul sur les points initiaux pour plus de précision
		pb.x=pa.x+(pb.x-pa.x)*(1.0-r);// Calcul de l'accroche x
		pb.y=pa.y+(pb.y-pa.y)*(1.0-r);// Calcul de l'accroche y
	}
	
CGPoint	px;
	
	CGPointNewPos(&pb,sz/2.0,a+M_PI,&pa);
	
	CGPointNewPos(&pa,sz/2.0,a+M_PI,&px);
	CGPointNewPos(&pa,sz/3.0,a+M_PI,&pb);
	xout[0]=pb.x;yout[0]=pb.y;
	
	CGPointNewPos(&px,sz/3.0,a+(M_PI*1.5),&pb);
	xout[1]=pb.x;yout[1]=pb.y;
	
	CGPointNewPos(&pa,sz/2.0,a,&pb);
	xout[2]=pb.x;yout[2]=pb.y;
	
	CGPointNewPos(&px,sz/3.0,a+(M_PI*0.5),&pb);
	xout[3]=pb.x;yout[3]=pb.y;
	xout[4]=xout[0];yout[4]=yout[0];
		
	return(true);
}

