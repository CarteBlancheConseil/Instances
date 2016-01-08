//----------------------------------------------------------------------------
// File : bXMLCentroid.cpp
// Project : MacMap
// Purpose : C++ source file : centroïd tag class, used in styles
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
// 09/06/2005 creation.
//----------------------------------------------------------------------------

#include "bXMLCentroid.h"
#include <mox_intf/CGUtils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bCentroidElement	::bCentroidElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("centroid");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bCentroidElement::create(bGenericXMLBaseElement* elt){
	return(new bCentroidElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bCentroidElement::~bCentroidElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
void bCentroidElement::init(void* ctx){
	bStdXMLLowRenderElement::init(ctx);
bGenericType* tp=((bGenericStyle*)ctx)->gettype();
	if(tp){
		_k=tp->kind();
	}
	else{
		_k=kBaseKindPolygon;
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bCentroidElement::actionval(	bGenericGraphicContext* ctx,
									bStdXMLValueElement* elt,
									bGenericGeoElement* geo){
bool	x;
	elt->getvalue(geo,&x);
	if(!x){
		return(false);
	}
	return(centroidize(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bCentroidElement::actionstd(bGenericGraphicContext* ctx){
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
	return(centroidize(ctx));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bCentroidElement::centroidize(bGenericGraphicContext *ctx){
int		npts,*offsets,noffsets;
float	*xpts,*ypts;

	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);

	if(npts==1){
		return(true);
	}
	
int*	newoff=(int*)malloc(2*sizeof(int));
	if(!newoff){
		return(true);
	}
	newoff[0]=0;
	newoff[1]=1;
	
float	x,y;
	
	switch(_k){
		case kBaseKindPolygon:
		case kBaseKindRaster:
			CentroidizeClosedPath(&x,&y,xpts,ypts,npts);
			break;
		case kBaseKindPolyline:
			CentroidizeLinePath(&x,&y,xpts,ypts,npts);
			break;
		default:
			Centroidize(&x,&y,xpts,ypts,npts);
			break;
	}
	
	ctx->setGeometry(&x,&y,1,newoff,2);
	
	return(true);
}

