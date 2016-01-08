//----------------------------------------------------------------------------
// File : bXMLSmooth.cpp
// Project : MacMap
// Purpose : C++ source file : smooth polyline tag class, used in styles
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
// 02/04/2003 creation.
//----------------------------------------------------------------------------
// Traiter les multi-segmentations
// Problèmes probables de double point
//----------------------------------------------------------------------------

#include "bXMLSmooth.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bSmoothElement	::bSmoothElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("smooth");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bSmoothElement::create(bGenericXMLBaseElement* elt){
	return(new bSmoothElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bSmoothElement::~bSmoothElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSmoothElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
bool	x;
	elt->getvalue(geo,&x);
	if(!x){
		return(false);
	}
	return(smooth(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSmoothElement::actionstd(bGenericGraphicContext* ctx){
bool x;
	if(_elts.count()>0){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,&x);
	}
	else{
char	val[_values_length_max_];
		getvalue(val);
		x=atoi(val);		
	}
	if(!x){
		return(true);
	}
	return(smooth(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSmoothElement::smooth(bGenericGraphicContext *ctx){
int		npts,*offsets,noffsets;
float	*xpts,*ypts;

	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(npts<3){
		return(true);
	}
	
//bool	closed;
int		nnewpts,*newoffsets,nnewoffsets,n;
float	*newxpts,*newypts;
	
	n=npts-1;
	
//	closed=((xpts[0]==xpts[npts-1])&&(ypts[0]==ypts[npts-1]));
	nnewpts=npts*16L+noffsets;
//	nnewpts+=(noffsets*((int)closed));
	
	newxpts=(float*)malloc(nnewpts*sizeof(float));
	if(!newxpts){
		return(true);
	}
	newypts=(float*)malloc(nnewpts*sizeof(float));
	if(!newypts){
		free(newxpts);
		return(true);
	}
	
	nnewoffsets=noffsets;
	newoffsets=(int*)malloc(nnewoffsets*sizeof(int));
	if(!newoffsets){
		free(newxpts);
		free(newypts);
		return(true);
	}
	newoffsets[0]=0;
	
int		curs;	
	curs=0;
	for(int i=0;i<nnewoffsets-1;i++){
		smooth_one(	&xpts[offsets[i]],
					&ypts[offsets[i]],
					&newxpts[curs],
					&newypts[curs],
					offsets[i+1]-offsets[i],
					&curs);
		newoffsets[i+1]=curs;
	}

	ctx->setGeometry(newxpts,newypts,curs,newoffsets,nnewoffsets);
	
	free(newxpts);
	free(newypts);
	free(newoffsets);
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bSmoothElement::smooth_one(float* xpts,
								float* ypts,
								float* newxpts,
								float* newypts,
								int npts,
								int* gcurs){
	if(npts<3){
		if(npts==2){
			newxpts[0]=xpts[0];
			newxpts[1]=xpts[1];
			newypts[0]=ypts[0];
			newypts[1]=ypts[1];
			gcurs+=2;
		}
		return(true);
	}
	
int		n=npts-1;	
bool	closed=((xpts[0]==xpts[npts-1])&&(ypts[0]==ypts[npts-1]));
int		curs,i,bkcurs,nnewpts=npts*16L+((int)closed);
float	x1,x2,x3,y1,y2,y3,lastx,lasty,firstx,firsty;
curve	crv;
	
	curs=0;
	for(i=1;i<=n-(int)(!closed);i++){
		x1=xpts[i-1];
		y1=ypts[i-1];
		x2=xpts[i];
		y2=ypts[i];
		if(i==n){
			x3=xpts[1];
			y3=ypts[1];
		}
		else{
			x3=xpts[i+1];
			y3=ypts[i+1];
		}
		
		if((!closed)&&(i==1)){
			newxpts[curs]=lastx=x1;
			newypts[curs]=lasty=y1;
			curs++;
			(*gcurs)++;
		}
		
		if((closed)||(i!=1)){
			mid(&x1,&y1,x1,y1,x2,y2);
		}
			
		if((closed)||(i!=n-1)){
			mid(&x3,&y3,x2,y2,x3,y3);
		}
		
		if((closed)&&(i==1)){			
			newxpts[curs]=firstx=lastx=x1;
			newypts[curs]=firsty=lasty=y1;
			curs++;
			(*gcurs)++;
		}
		
		if(((x1==x2)&&(y1==y2))||((x2==x3)&&(y2==y3))){
			continue;
		}
		
		crv.startx=x1;
		crv.starty=y1;
		
		crv.controlx=x2;
		crv.controly=y2;
		
		crv.endx=x3;
		crv.endy=y3;
		
		bkcurs=curs;
		makecurve(newxpts,newypts,nnewpts,&curs,&crv,4,&lastx,&lasty);
		(*gcurs)+=(curs-bkcurs);
	}
	
	if(closed){
		newxpts[curs]=newxpts[0];
		newypts[curs]=newypts[0];
		(*gcurs)++;
	}
		
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bSmoothElement::makecurve(	float *xpts, 
								float *ypts, 
								int npts, 
								int *cur, 
								curve *crv, 
								int level, 
								float *lastx, 
								float *lasty){
							
	curve	left,right;

	if(level>0){
		left.startx=crv->startx;
		left.starty=crv->starty;
		
		mid(&left.controlx,&left.controly,crv->startx,crv->starty,crv->controlx,crv->controly);
		mid(&right.controlx,&right.controly,crv->controlx,crv->controly,crv->endx,crv->endy);
		mid(&left.endx,&left.endy,left.controlx,left.controly,right.controlx,right.controly);
				
		right.startx=left.endx;
		right.starty=left.endy;
		
		right.endx=crv->endx;
		right.endy=crv->endy;
		
		makecurve(xpts,ypts,npts,cur,&left,level-1,lastx,lasty);
		makecurve(xpts,ypts,npts,cur,&right,level-1,lastx,lasty);
	}
	else{
		
		xpts[(*cur)]=crv->endx;
		ypts[(*cur)]=crv->endy;
		
		(*lastx)=crv->endx;
		(*lasty)=crv->endy;
		
		(*cur)++;
	}
}

/*// ---------------------------------------------------------------------------
// 
// -----------
bool bSmoothElement::smooth(bGenericGraphicContext *ctx){
int		npts,*offsets,noffsets;
float	*xpts,*ypts;

	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);

	if(npts<3){
		return(true);
	}
	
bool	closed;
int		nnewpts,*newoffsets,nnewoffsets,n;
float	*newxpts,*newypts;
	
	n=npts-1;
	
	closed=((xpts[0]==xpts[npts-1])&&(ypts[0]==ypts[npts-1]));
	nnewpts=npts*16L;
	nnewpts+=((int)closed);
	
	newxpts=(float*)malloc(nnewpts*sizeof(float));
	if(!newxpts){
		return(true);
	}
	newypts=(float*)malloc(nnewpts*sizeof(float));
	if(!newypts){
		free(newxpts);
		return(true);
	}
	
	//
	nnewoffsets=2;
	newoffsets=(int*)malloc(nnewoffsets*sizeof(int));
	if(!newoffsets){
		free(newxpts);
		free(newypts);
		return(true);
	}
	//
	
	int		curs,i;
	float	x1,x2,x3,y1,y2,y3,lastx,lasty,firstx,firsty;
	curve	crv;
	
	curs=0;
	for(i=1;i<=n-(int)(!closed);i++){
		x1=xpts[i-1];
		y1=ypts[i-1];
		x2=xpts[i];
		y2=ypts[i];
		if(i==n){
			x3=xpts[1];
			y3=ypts[1];
		}
		else{
			x3=xpts[i+1];
			y3=ypts[i+1];
		}
		
		if((!closed)&&(i==1)){
			newxpts[curs]=lastx=x1;
			newypts[curs]=lasty=y1;
			curs++;
		}
		
		if((closed)||(i!=1)){
			mid(&x1,&y1,x1,y1,x2,y2);
		}
			
		if((closed)||(i!=n-1)){
			mid(&x3,&y3,x2,y2,x3,y3);
		}
		
		if((closed)&&(i==1)){			
			newxpts[curs]=firstx=lastx=x1;
			newypts[curs]=firsty=lasty=y1;
			curs++;
		}
		
		if(((x1==x2)&&(y1==y2))||((x2==x3)&&(y2==y3))){
			continue;
		}
		
		crv.startx=x1;
		crv.starty=y1;
		
		crv.controlx=x2;
		crv.controly=y2;
		
		crv.endx=x3;
		crv.endy=y3;
		
		makecurve(newxpts,newypts,nnewpts,&curs,&crv,4,&lastx,&lasty);
	}
	nnewpts=curs;
	
	if(closed){
		newxpts[nnewpts-1]=newxpts[0];
		newypts[nnewpts-1]=newypts[0];
	}
	
	newoffsets[0]=0;
	newoffsets[1]=nnewpts;

	ctx->setGeometry(newxpts,newypts,nnewpts,newoffsets,nnewoffsets);
	
	free(newxpts);
	free(newypts);
	free(newoffsets);
	
	return(true);
}*/
