//----------------------------------------------------------------------------
// File : bXMLVertexGeometry.cpp
// Project : MacMap
// Purpose : C++ source file : vertex geometry tag class, used in styles
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
// 17/06/2016 creation.
//----------------------------------------------------------------------------
// Type :	Container-Acteur
// Action :	Inscrit son instance dans le style passé en paramétre.
// 			Calcule la géométrie d'une coordonnée passée en paramètre et la place dans le contexte graphique.
//----------------------------------------------------------------------------

#include "bXMLVertexGeometry.h"
#include <std_ext/bStdXMLValueElement.h>
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Geometry
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bVertexGeometryElement	::bVertexGeometryElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
						: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("vertexgeometry");
	setobjectcompliant(false);
	setclasscompliant(true);
	setscalecompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bVertexGeometryElement::create(bGenericXMLBaseElement* elt){
	return(new bVertexGeometryElement(elt,(bGenericMacMapApp*)elt->getapp(),elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bVertexGeometryElement::~bVertexGeometryElement(){
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bVertexGeometryElement::applyforclass(bGenericGraphicContext *ctx){
_bTrace_("bVertexGeometryElement::applyforclass",true);
d2dvertex   loc={0,0};
char        cval[256];
    
bStdXMLValueElement*    val=(bStdXMLValueElement*)(void*)getelement(1);
    if(val){
        val->getvalue(cval);
        loc.x=matof(cval);
    }
    val=(bStdXMLValueElement*)(void*)getelement(2);
    if(val){
        val->getvalue(cval);
        loc.y=matof(cval);
    }
ivertices*  vxs=ivs_new(_2D_VX,1,0);
    _gapp->locConverter()->convert(&(vxs->vx.vx2[0]),&loc);
	ctx->setGeography(vxs,true);
	ctx->convertGeography();
	return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bVertexGeometryElement::actionval(bGenericGraphicContext* ctx,
                                       bStdXMLValueElement* elt,
                                       bGenericGeoElement* geo){
_bTrace_("bVertexGeometryElement::actionval",true);
    return(true);
}

// ---------------------------------------------------------------------------
//
// -----------
bool bVertexGeometryElement::actionstd(bGenericGraphicContext* ctx){
_bTrace_("bVertexGeometryElement::actionstd",true);
   return(true);
}

