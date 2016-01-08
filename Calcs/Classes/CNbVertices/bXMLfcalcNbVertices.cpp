//----------------------------------------------------------------------------
// File : bXMLfcalcNbVertices.cpp
// Project : MacMap
// Purpose : C++ source file : Calc nb vertices formula class. Return object's geometry vertices count.
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

#include "bXMLfcalcNbVertices.h"
#include <MacMapSuite/vx_lib.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bfcalcNbVerticesElement	::bfcalcNbVerticesElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl ) 
				: bStdXMLCalc(elt,gapp,bndl){
	setclassname("fcalcnbvertices");
	_dbval=new bIntDBValue;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bfcalcNbVerticesElement::~bfcalcNbVerticesElement(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bfcalcNbVerticesElement::create(bGenericXMLBaseElement* elt){
	return(new bfcalcNbVerticesElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bfcalcNbVerticesElement::solve(bStdSolver* ctx){
bGenericGeoElement*	o=ctx->get_object();
	if(!o){
		return(false);
	}
ivertices*			vxs;
	o->getVertices(&vxs);
	_dbval->put(vxs->nv);
	return(ctx->add(_dbval));
}

