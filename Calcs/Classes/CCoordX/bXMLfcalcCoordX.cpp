//----------------------------------------------------------------------------
// File : bXMLfcalcCoordX.cpp
// Project : MacMap
// Purpose : C++ source file : Calc x coordinate formula class. Return object's x first coordinate.
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
// 01/12/2005 creation.
//----------------------------------------------------------------------------

#include "bXMLfcalcCoordX.h"
#include <MacMapSuite/vx_lib.h>
#include <MacMapSuite/bStdProj.h>
#include <MacMapSuite/wgs84.h>
#include <MacMapSuite/lambert93.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcCoordXElement	::bfcalcCoordXElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalccoordx");
	_dbval=new bDoubleDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur_gapp
// -----------
bfcalcCoordXElement::~bfcalcCoordXElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcCoordXElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcCoordXElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcCoordXElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
ivertices*			vxs;
	o->getVertices(&vxs);
d2dvertex			dvx;
	_gapp->locConverter()->convert(&dvx,&vxs->vx.vx2[0]);
/*
bool		init=false;
//bStdProj	fp(_gapp->document()->srid(),&init);
wgs84		wgs;
lambert93	lmb;
dvertices*	dvxs=dvs_new(_2D_VX,1,0);
	dvxs->vx.vx2[0]=dvx;
	wgs.transform(lmb,dvxs);
	dvx=dvxs->vx.vx2[0];
*/
	_dbval->put(dvx.x);
	return(ctx->add(_dbval));
}

