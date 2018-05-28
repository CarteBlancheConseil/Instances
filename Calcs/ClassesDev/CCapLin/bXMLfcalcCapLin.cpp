//----------------------------------------------------------------------------
// File : bXMLfcalcCapLin.cpp
// Project : MacMap
// Purpose : C++ source file : Calc CapLin formula class. Return angle between start and end point of a line.
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 28/04/2017 creation.
//----------------------------------------------------------------------------

#include "bXMLfcalcCapLin.h"
#include <MacMapSuite/vx_lib.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcCapLinElement	::bfcalcCapLinElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalccaplin");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcCapLinElement::~bfcalcCapLinElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcCapLinElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcCapLinElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void  bfcalcCapLinElement::init(void* ctx){
	bStdXMLCalc::init(ctx);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcCapLinElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
ivertices*  vxs;
	o->getVertices(&vxs);
    
double	a;
    if(o->getDirection()<0){
        a=rad2deg(hv_vx_angle(&vxs->vx.vx2[vxs->nv-1],&vxs->vx.vx2[0]));
    }
    else{
        a=rad2deg(hv_vx_angle(&vxs->vx.vx2[0],&vxs->vx.vx2[vxs->nv-1]));
    }
    a+=90.0;
    if(a>=360.0){
        a-=360.0;
    }
	_dbval->put(a);
	return(ctx->add(_dbval));
}

