//----------------------------------------------------------------------------
// File : bXMLfcalcRotation.cpp
// Project : MacMap
// Purpose : C++ source file : Calc rotation formula class. Return rotation direction of a polygon ([1;-1]).
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
// 30/10/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLfcalcRotation.h"
#include <MacMapSuite/vx_lib.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcRotationElement	::bfcalcRotationElement(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl ) 
						: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalcrotation");
	_dbval=new bIntDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcRotationElement::~bfcalcRotationElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcRotationElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcRotationElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcRotationElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
ivertices*			vxs;
	o->getVertices(&vxs);

i2dvertex*		vx;
int				nv;
	vx=ivs2_part(vxs,0,&nv);
int				r=ivx2_clockwise(vx,nv);
	if(r==0){
		r=-1;
	}
	_dbval->put(r);
	return(ctx->add(_dbval));
}

