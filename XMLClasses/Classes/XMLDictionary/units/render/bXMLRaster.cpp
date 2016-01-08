//----------------------------------------------------------------------------
// File : bXMLRaster.cpp
// Project : MacMap
// Purpose : C++ source file : raster image tag class, used in styles
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
// 13/12/2006 creation.
//----------------------------------------------------------------------------

#include "bXMLRaster.h"
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/bStdFile.h>
#include <MacMapSuite/bStdDirectory.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bRasterElement	::bRasterElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("raster");
	setobjectcompliant(true);
	_data=NULL;
	_sz=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bRasterElement::create(bGenericXMLBaseElement* elt){
	return(new bRasterElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bRasterElement::~bRasterElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bRasterElement::init(void *ctx){
	if(_data){
		free(_data);
		_data=NULL;
	}
	_last[0]=0;
	_sz=0;
	bStdXMLLowRenderElement::init(ctx);
	_tp=((bGenericStyle*)ctx)->gettype();
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bRasterElement::actionval(	bGenericGraphicContext* ctx,
								bStdXMLValueElement* elt,
								bGenericGeoElement* geo){
//_bTrace_("bRasterElement::actionval",true);
char	val[_values_length_max_];
	elt->getvalue(geo,val);	
	if(strlen(val)==0){
		ctx->setImage(NULL,0,"");
		return(false);
	}
	if(!strcmp(_last,val)){
//_tm_("same raster");
		ctx->setImage(_data,_sz,val);
		return(_data!=NULL);
	}
	if(_data){
//_tm_("free previous raster");
		strcpy(_last,"");
		free(_data);
		_data=NULL;
		_sz=0;
	}
	if(val[0]=='/'){
bStdFile	f(val,"rb");
		if(f.status()){
			ctx->setImage(NULL,0,"");
			return(false);
		}
		f.mount((char**)&_data,&_sz);
		if(f.status()){
			ctx->setImage(NULL,0,"");
			return(false);
		}
	}
	else if(!_tp->fields()->get_param("rasters",val,&_data,&_sz)){
		ctx->setImage(NULL,0,"");
		return(false);
	}
	strcpy(_last,val);
	ctx->setImage(_data,_sz,val);
//_tm_("new raster ready to be drawn");
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bRasterElement::actionstd(bGenericGraphicContext* ctx){
//_bTrace_("bRasterElement::actionstd",true);
char	val[_values_length_max_];
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
		if(val[0]=='/'){
bStdFile	f(val,"rb");
			if(f.status()){
				ctx->setImage(NULL,0,"");
				return(objectcompliant());
			}
			f.mount((char**)&_data,&_sz);
			if(f.status()){
				ctx->setImage(NULL,0,"");
				return(objectcompliant());
			}
		}
		else if(!_tp->fields()->get_param("rasters",val,&_data,&_sz)){
			ctx->setImage(NULL,0,"");
			return(objectcompliant());
		}
	}
	ctx->setImage(_data,_sz,val);
	if(_data==NULL){
		return(objectcompliant());
	}
	return(true);
}
