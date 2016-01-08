//----------------------------------------------------------------------------
// File : bXMLScreenGeometry.cpp
// Project : MacMap
// Purpose : C++ source file : screen geometry tag class, used in styles
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
// 26/06/2009 creation.
//----------------------------------------------------------------------------
// Type :	Container-Acteur
// Action :	Inscrit son instance dans le style passé en paramétre.
// 			Calcule la géométrie de l'écran et la place dans le contexte graphique passé en paramétre.
//----------------------------------------------------------------------------

#include "bXMLScreenGeometry.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Geometry
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bScreenGeometryElement	::bScreenGeometryElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
						: bGeometryElement(elt,gapp,bndl){
	setclassname("screengeometry");
	setobjectcompliant(false);
	setclasscompliant(true);
	setscalecompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bScreenGeometryElement::create(bGenericXMLBaseElement* elt){
	return(new bScreenGeometryElement(elt,(bGenericMacMapApp*)elt->getapp(),elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bScreenGeometryElement::~bScreenGeometryElement(){
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bScreenGeometryElement::applyforclass(bGenericGraphicContext *ctx){
ivx_rect		vr;
    
    switch(ctx->signature()){
        case kPDFGraphicContext:
            vr=*(_gapp->printMgr()->get_print_area());
            break;
        case kPrintGraphicContext:
            vr=*(_gapp->printMgr()->get_print_area());
            break;
        case kBitMapGraphicContext:
            vr=*(_gapp->printMgr()->get_print_area());
            break;
        case kKMLGraphicContext:
            vr=*(_gapp->printMgr()->get_print_area());
            break;
        case kCtxGraphicContext:
            _gapp->mapIntf()->screenBounds(&vr);
            break;
        default:
            _gapp->mapIntf()->screenBounds(&vr);
            break;
    }

ivertices*		vxs;
	ivr2ivs(&vr,&vxs);
	ctx->setGeography(vxs,true);
	ctx->convertGeography();

bGenericXMLRenderingElement*	elt;

	for(int i=1;i<=_elts.count();i++){
		if(_elts.get(i,&elt)){
			if(!elt->applyforclass(ctx)){
				return(false);
			}
		}
		else{
			return(false);
		}
	}

	return(true);

}

