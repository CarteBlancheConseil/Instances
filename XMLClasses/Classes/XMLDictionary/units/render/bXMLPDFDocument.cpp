//----------------------------------------------------------------------------
// File : bXMLPDFDocument.cpp
// Project : MacMap
// Purpose : C++ source file : pdf document tag class, used in styles
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
// 10/05/2004 creation.
//----------------------------------------------------------------------------

#include "bXMLPDFDocument.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// 
// ------------
// ---------------------------------------------------------------------------
// Constructeur
// ------------
bPDFDocumentElement	::bPDFDocumentElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
				: bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("pdfdocument");
	setclasscompliant(true);
	_data=NULL;
	_sz=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bPDFDocumentElement::create(bGenericXMLBaseElement* elt){
	return(new bPDFDocumentElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bPDFDocumentElement::~bPDFDocumentElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bPDFDocumentElement::init(void *ctx){
	if(_data){
		free(_data);
		_data=NULL;
	}
	_last[0]=0;
	_sz=0;
	_ispdf=true;
	bStdXMLLowRenderElement::init(ctx);
	_tp=((bGenericStyle*)ctx)->gettype();
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPDFDocumentElement::actionval(	bGenericGraphicContext* ctx,
										bStdXMLValueElement* elt,
										bGenericGeoElement* geo){
char	val[_values_length_max_];
	elt->getvalue(geo,val);	
	if(strlen(val)==0){
		if(_ispdf){
			ctx->setPDF(NULL,0,"");
		}
		else{
			ctx->setImage(NULL,0,"");
		}
		return(false);
	}
	if(!strcmp(_last,val)){
		if(_ispdf){
			ctx->setPDF(_data,_sz,val);
		}
		else{
			ctx->setImage(_data,_sz,val);
		}
		return(_data!=NULL);
	}
	if(_data){
		strcpy(_last,"");
		free(_data);
		_data=NULL;
		_sz=0;
	}
	if(_tp){
		if(!_tp->fields()->get_param("icons",val,&_data,&_sz)){
			return(false);
		}
		// on pourrait chercher ailleurs 
	}
	else{
        if(!_gapp->document()->readParam(&_data,&_sz,"icons",val)){
            if(_ispdf){
                ctx->setPDF(NULL,0,"");
            }
            else{
                ctx->setImage(NULL,0,"");
            }
            return(false);
        }
		// on pourrait chercher ailleurs
	}
    
//#warning COMMENTE
	_ispdf=(GetImageKind(val)==kFileTypePDF);
	strcpy(_last,val);
	if(_ispdf){
		ctx->setPDF(_data,_sz,val);
	}
	else{
		ctx->setImage(_data,_sz,val);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bPDFDocumentElement::actionstd(bGenericGraphicContext* ctx){
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
		if(strlen(val)==0){
			if(_ispdf){
				ctx->setPDF(NULL,0,"");
			}
			else{
				ctx->setImage(NULL,0,"");
			}
			return(objectcompliant());
		}	
		if(_tp){
			if(!_tp->fields()->get_param("icons",val,&_data,&_sz)){
				if(_ispdf){
					ctx->setPDF(NULL,0,"");
				}
				else{
					ctx->setImage(NULL,0,"");
				}
				return(false);
			}
			// on pourrait chercher ailleurs 
		}
		else{
            if(!_gapp->document()->readParam(&_data,&_sz,"icons",val)){
                if(_ispdf){
                    ctx->setPDF(NULL,0,"");
                }
                else{
                    ctx->setImage(NULL,0,"");
                }
                return(false);
            }
			// on pourrait chercher ailleurs
		}
		strcpy(_last,val);
	}
//#warning COMMENTE
	_ispdf=(GetImageKind(val)==kFileTypePDF);
	if(_ispdf){
		ctx->setPDF(_data,_sz,val);
	}
	else{
		ctx->setImage(_data,_sz,val);
	}
	if(_data==NULL){
		return(objectcompliant());
	}
	return(true);
}
