//----------------------------------------------------------------------------
// File : bXMLLegible.cpp
// Project : MacMap
// Purpose : C++ source file : text legibility tag class, used in styles
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
// 11/12/2008 creation.
//----------------------------------------------------------------------------

#include "bXMLLegible.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/CGUtils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bLegibleElement	::bLegibleElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("legible");
	setobjectcompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bLegibleElement::create(bGenericXMLBaseElement* elt){
	return(new bLegibleElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bLegibleElement::~bLegibleElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bLegibleElement::actionval(	bGenericGraphicContext* ctx,
									bStdXMLValueElement* elt,
									bGenericGeoElement* geo){
bool	x;
	elt->getvalue(geo,&x);
	if(!x){
		return(false);
	}
	make_legible(ctx);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bLegibleElement::actionstd(bGenericGraphicContext* ctx){
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
	make_legible(ctx);
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bLegibleElement::make_legible(bGenericGraphicContext* ctx){
int		npts,*offsets,noffsets,i,j,np;
float	*xpts,*ypts,bf;
	
	ctx->getGeometry(&xpts,&ypts,&npts,&offsets,&noffsets);
	if(!XYLegible(xpts,ypts,npts)){
		for(i=0;i<noffsets-1;i++){
			np=(offsets[i+1]-offsets[i]);
			for(j=0;j<np/2;j++){
				bf=xpts[offsets[i]+j];
				xpts[offsets[i]+j]=xpts[offsets[i]+(np-1)-j];
				xpts[offsets[i]+(np-1)-j]=bf;
				
				bf=ypts[offsets[i]+j];
				ypts[offsets[i]+j]=ypts[offsets[i]+(np-1)-j];
				ypts[offsets[i]+(np-1)-j]=bf;
			}
		}
	}
}

