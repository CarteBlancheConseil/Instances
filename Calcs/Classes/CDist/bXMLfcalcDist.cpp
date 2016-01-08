//----------------------------------------------------------------------------
// File : bXMLfcalcDist.cpp
// Project : MacMap
// Purpose : C++ source file : Calc distance formula class. Return distance between an object and contrasts centroïds.
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

#include "bXMLfcalcDist.h"
#include <MacMapSuite/vx_lib.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcDistElement	::bfcalcDistElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
					: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalcdist");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcDistElement::~bfcalcDistElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcDistElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcDistElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcDistElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
ivertices*			vxs;
	o->getVertices(&vxs);

bGenericGeoElement*	co;
bArray*				arr=_gapp->cntMgr()->elements();
ivertices*			cvxs;
double				dmin=LONG_MAX,d;
	for(int i=1;i<=arr->count();i++){
		arr->get(i,&co);
		co->getVertices(&cvxs);
		d=vxs_dist(vxs,cvxs);
		if(dmin>d){
			dmin=d;
		}
	}
	_dbval->put(Measure_i2d(_gapp,dmin));
	return(ctx->add(_dbval));
}

