//----------------------------------------------------------------------------
// File : bXMLText.cpp
// Project : MacMap
// Purpose : C++ source file : text tag class, used in styles
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
// 23/12/2003 creation.
//----------------------------------------------------------------------------
// Documentation
// Type :	Acteur
// Action :	Inscrit le texte dans le contexte graphique passé en paramètre
//----------------------------------------------------------------------------

#include "bXMLText.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Text
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bTextElement	::bTextElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("text");
	setclasscompliant(true);
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bTextElement::create(bGenericXMLBaseElement* elt){
	return(new bTextElement(elt,(bGenericMacMapApp*)elt->getapp(),elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bTextElement::~bTextElement(){
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bTextElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
//_bTrace_("bTextElement::actionval",true);
char	val[_values_length_max_];
	elt->getvalue(geo,val);
//_tm_(val);
	if(strlen(val)>0){
		ctx->setText(val);
		return(true);
	}
	return(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bTextElement::actionstd(bGenericGraphicContext* ctx){
//_bTrace_("bTextElement::actionstd",true);
char	val[_values_length_max_];
	if(objectcompliant()){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
//_te_("elt==NULL");
			ctx->setText("");
			return(true);
		}
		elt->getvalue(NULL,val);
	}
	else{
		getvalue(val);
	}
//_tm_(val);
	ctx->setText(val);
	if(strlen(val)==0){
		return(objectcompliant());
	}
	return(true);
}
