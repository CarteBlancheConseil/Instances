//----------------------------------------------------------------------------
// File : bXMLStdGeometry.cpp
// Project : MacMap
// Purpose : C++ source file : standard object geometry tag class, used in styles
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
// 04/02/2004 creation.
//----------------------------------------------------------------------------
// Documentation
// Type :	Container-Acteur
// Action :	Inscrit son instance dans le style passé en paramétre.
// 			Calcule une géométrie par défaut et la place dans le contexte graphique passé en paramétre.
//----------------------------------------------------------------------------

#include "bXMLStdGeometry.h"

// ---------------------------------------------------------------------------
// Geometry
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bStdGeometryElement	::bStdGeometryElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bGeometryElement(elt,gapp,bndl){
	setclassname("stdgeometry");
	setobjectcompliant(true);
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bStdGeometryElement::create(bGenericXMLBaseElement* elt){
	return(new bStdGeometryElement(elt,(bGenericMacMapApp*)elt->getapp(),elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bStdGeometryElement::~bStdGeometryElement(){
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bStdGeometryElement::applyforobject(bGenericGraphicContext *ctx){
bGenericGeoElement* o=ctx->getCurElement();
	if(!o){
		return(false);
	}
ivertices*			vxs;
	
	o->getVertices(&vxs);
	ctx->setGeography(vxs,false);
	ctx->convertGeography();

bGenericXMLRenderingElement*	elt;
	
	for(int i=1;i<=_elts.count();i++){
		if(_elts.get(i,&elt)){
			if(!elt->applyforobject(ctx)){
				return(false);
			}
		}
		else{
			return(false);
		}
	}
	return(true);
}

// ---------------------------------------------------------------------------
// Action
// -----------
bool bStdGeometryElement::applyforclass(bGenericGraphicContext *ctx){
/*bGenericXMLRenderingElement*	elt;
	
	for(int i=1;i<=_elts.count();i++){
		if(_elts.get(i,&elt)){
			if(!elt->applyforclass(ctx)){
				return(false);
			}
		}
		else{
			return(false);
		}
	}*/
	return(bGeometryElement::applyforclass(ctx));
}

