//----------------------------------------------------------------------------
// File : bXMLStrokePattern.cpp
// Project : MacMap
// Purpose : C++ source file : stroke pattern tag class, used in styles
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
// 30/05/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLStrokePattern.h"

// ---------------------------------------------------------------------------
// StrokePattern
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bStrokePatternElement	::bStrokePatternElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
					: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("strokepattern");
	setclasscompliant(true);
	_data=NULL;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bStrokePatternElement::create(bGenericXMLBaseElement* elt){
	return(new bStrokePatternElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bStrokePatternElement::~bStrokePatternElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bStrokePatternElement::init(void *ctx){
	if(_data){
		free(_data);
		_data=NULL;
	}
	_sz=0;
	_last[0]=0;
	bStdXMLLowRenderElement::init(ctx);
	_tp=((bGenericStyle*)ctx)->gettype();
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bStrokePatternElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
char	val[_values_length_max_];
	elt->getvalue(geo,val);	
	if(strlen(val)==0){
		ctx->setStrokePattern(NULL,0,"");
		return(false);
	}
	if(!strcmp(_last,val)){
		ctx->setStrokePattern(_data,_sz,val);
		return(_data!=NULL);
	}
	if(_data){
		strcpy(_last,"");
		free(_data);
		_data=NULL;
		_sz=0;
	}
	if(!_tp->fields()->get_param("patterns",val,&_data,&_sz)){
		return(false);
	}
	strcpy(_last,val);
	ctx->setStrokePattern(_data,_sz,val);
	return(true);

}

// ---------------------------------------------------------------------------
// 
// -----------
bool bStrokePatternElement::actionstd(bGenericGraphicContext* ctx){
char	val[_values_length_max_];
	ctx->setColorLevel(_stroke);
	ctx->setAlpha(1);	
	if(objectcompliant()){
bStdXMLValueElement*	elt=find_value();
		if(elt==NULL){
			return(true);
		}
		elt->getvalue(NULL,val);
	}
	else{
		getvalue(val);
	}
	if(_data==NULL){
		if(strlen(val)==0){
			ctx->setStrokePattern(NULL,0,"");
			return(objectcompliant());
		}	
		if(!_tp->fields()->get_param("patterns",val,&_data,&_sz)){
			ctx->setStrokePattern(NULL,0,"");
			return(objectcompliant());
		}
		strcpy(_last,val);
	}
	ctx->setStrokePattern(_data,_sz,val);
	if(_data==NULL){
		return(objectcompliant());
	}
	return(true);
}

