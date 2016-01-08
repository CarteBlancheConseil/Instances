//----------------------------------------------------------------------------
// File : bXMLfcalcAngle.cpp
// Project : MacMap
// Purpose : C++ source file : Calc angle formula class. Return angle between an object and contrasts centroïds.
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
// 09/12/2005 creation.
//----------------------------------------------------------------------------

#include "bXMLfcalcAngle.h"
#include <MacMapSuite/vx_lib.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcAngleElement	::bfcalcAngleElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalcangle");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcAngleElement::~bfcalcAngleElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcAngleElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcAngleElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfcalcAngleElement::init(void* ctx){
	bStdXMLCalc::init(ctx);
	centroidize();
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcAngleElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
ivertices*			vxs;
i2dvertex			vx;
	o->getVertices(&vxs);
	switch(_gapp->typesMgr()->get(o->getType())->kind()){
		case kBaseKindPolygon:
			ivs_centro_surf(vxs,&vx);
			break;
		case kBaseKindPolyline:
			ivs_centro_line(vxs,&vx);
			break;
		case kBaseKindText:
		case kBaseKindPoint:
			ivs_centro(vxs,&vx);
			break;
	}
double	a=vx_angle(&_vx,&vx);
	_dbval->put(rad2deg(a));
	return(ctx->add(_dbval));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bfcalcAngleElement::centroidize(){
bGenericGeoElement*	co;
bArray*		arr=_gapp->cntMgr()->elements();
ivertices*			cvxs;
ivx_rect			vxr,bounds={0,0,0,0};

	for(int i=1;i<=arr->count();i++){
		arr->get(i,&co);
		co->getVertices(&cvxs);
		ivs_bounds(cvxs,&vxr);
		ivr_union(&vxr,&bounds,&bounds);
	}
	ivr_mid(&vxr,&_vx);
}

