//----------------------------------------------------------------------------
// File : bXMLWMSRaster.cpp
// Project : MacMap
// Purpose : C++ source file : WMS service tag class, used in styles
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

#include "bXMLWMSRaster.h"
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/bStdFile.h>
#include <MacMapSuite/bStdDirectory.h>
#include <MacMapSuite/mmurl.h>
#include <MacMapSuite/bString.h>
#include <MacMapSuite/vx_measure.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bWMSRasterElement	::bWMSRasterElement(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl )
                    : bStdXMLLowRenderElement(elt,gapp,bndl){
	setclassname("wmsraster");
	setobjectcompliant(false);
	setclasscompliant(true);
	_data=NULL;
	_sz=0;
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bWMSRasterElement::create(bGenericXMLBaseElement* elt){
	return(new bWMSRasterElement(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// Destructeur
// ------------
bWMSRasterElement::~bWMSRasterElement(){
}

// ---------------------------------------------------------------------------
// Init
// -----------
void bWMSRasterElement::init(void *ctx){
	if(_data){
		free(_data);
		_data=NULL;
	}
	_last[0]=0;
	_sz=0;
	bStdXMLLowRenderElement::init(ctx);
    setobjectcompliant(false);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bWMSRasterElement::actionstd(bGenericGraphicContext* ctx){
_bTrace_("bWMSRasterElement::actionstd",false);
char	req[_values_length_max_];
char	usr[_values_length_max_]="";

	if(_data){
		free(_data);
		_data=NULL;
	}
	_sz=0;
	
    if(countelements()==0){
        getvalue(req);
    }
    else{
bStdXMLValueElement*	elt;
        if(_elts.get(1,&elt)){
            elt->getvalue(NULL,usr);
        }
        else{
_te_("NULL user:pwd");
            return(true);
        }
        if(_elts.get(2,&elt)){
            elt->getvalue(NULL,req);
        }
        else{
_te_("NULL request");
            return(true);
        }
    }

ivx_rect	ivr;
dvx_rect	vr;

CGRect	box=ctx->get_box();

    switch(ctx->signature()){
        case kCtxGraphicContext:
            _gapp->mapIntf()->screenBounds(&ivr);
            break;
        default:
            ivr=*(_gapp->printMgr()->get_print_area());
            break;
    }

    if(!ivr_ok(&ivr)){
_te_("NULL area");
        return(true);
    }

i2dvertex   ivx;
d2dvertex   vx;
    ivx.h=ivr.left;
    ivx.v=ivr.bottom;
    _gapp->locConverter()->convert(&vx,&ivx);
    vr.xmin=vx.x;
    vr.ymin=vx.y;
    ivx.h=ivr.right;
    ivx.v=ivr.top;
    _gapp->locConverter()->convert(&vx,&ivx);
    vr.xmax=vx.x;
    vr.ymax=vx.y;
    
bString	str(req);
	str+"&Request=GetMap&BBox="+(int)vr.xmin+","+(int)vr.ymin+","+(int)vr.xmax+","+(int)vr.ymax;
	str+"&Width="+(int)round(box.size.width)+"&Height="+(int)round(box.size.height);
	
_tm_(usr);
__trc__.msg(str);

    if(countelements()==0){
        if(mmurl_get((char*)(str.string()),NULL,NULL,&_data,&_sz)!=0){
_te_("mmurl_get failed");
            ctx->setImage(NULL,0,"");
            return(objectcompliant());
        }
    }
    else{       
        if(mmurl_userGet(usr,(char*)(str.string()),NULL,NULL,&_data,&_sz)!=0){
//        if(mmurl_userGet(usr,(char*)(str.string()),NULL,"/Users/benoit/Desktop/test",&_data,&_sz)!=0){
_te_("mmurl_userGet failed");
            ctx->setImage(NULL,0,"");
            return(objectcompliant());
        }
    }
	if(_data==NULL){
_te_("NULL data");
		ctx->setImage(NULL,0,"");
		return(objectcompliant());
	}

//_tm_("data size ="+(int)_sz);
	ctx->setImage(_data,_sz,"raster.png");
	return(true);
}
