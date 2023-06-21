//----------------------------------------------------------------------------
// File : bvDefPaletteVirtualWMS.cpp
// Project : MacMap
// Purpose : C++ source file : WMS vdef class (connects to WMS services)
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
// 13/07/2013 creation.
//----------------------------------------------------------------------------

#include "bvDefPaletteVirtualWMS.h"
#include "bvDefVirtualWMSStyle.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/mmurl.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/endian.h>
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/valconv.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPaletteVirtualWMS	::bvDefPaletteVirtualWMS(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
						: bStdNSPalettevDef(elt,gapp,bndl)
						,_layers(sizeof(wmslayerdesc)){
	setclassname("palettevirtualwms");
	strcpy(_stylename,"rasterstyle");
	_sort=0;
    _https=false;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPaletteVirtualWMS::~bvDefPaletteVirtualWMS(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bvDefPaletteVirtualWMS::create(bGenericXMLBaseElement* elt){
	return(new bvDefPaletteVirtualWMS(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteVirtualWMS::test(bGenericType* tp){
	if(bStdNSPalettevDef::test(tp)==false){
		return(false);
	}
	return(tp==NULL);
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bvDefPaletteVirtualWMS::ccinit(){	
	return(initializeCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteVirtualWMS::stl_alloc(){
_bTrace_("bvDefPaletteVirtualWMS::stl_alloc()",true);
bvDefVirtualWMSStyle	*stl=new bvDefVirtualWMSStyle(_gapp);
	_styles.add(&stl);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bvDefPaletteVirtualWMS::stl_free(){
_bTrace_("bvDefPaletteVirtualWMS::stl_free()",true);
bvDefVirtualWMSStyle* stl;
	for(int i=1;i<=_styles.count();i++){
		_styles.get(i,&stl);
		delete stl;
	}
	_styles.reset();
	WMSCapabilitiesFreeDescs(_layers);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bvDefPaletteVirtualWMS::make(){
bArray	arr(sizeof(xmlelt));
char	val[256];
UInt32	sign=_sign;
	
	add_cdesc(arr,0,_stylename,"");
	
// Identification		
	add_cdesc(arr,1,"styleidentification","");
	add_cdesc(arr,2,"name",_name);
	sprintf(val,"%.4s",&sign);
	add_cdesc(arr,2,"sign",val);
	add_cdesc(arr,2,"version",_vers);
	
// Globals
	add_cdesc(arr,1,"globals","");
	add_ddesc(arr,2,"scaleref",0,0);
	add_ddesc(arr,2,"unitcoef",1,0);
	add_idesc(arr,2,"sort",_sort);
	add_idesc(arr,2,"passcount",_pssmax);
	
// Condition	
	add_cdesc(arr,1,"condition","");

// Nothing else, condition are optional.
	
	_root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	free_descs(arr);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteVirtualWMS::read(){
_bTrace_("bvDefPaletteVirtualWMSc::read",true);
bool	made=false,b=false;

	if(!_root){
		make();
		made=true;
	}
	
bGenericXMLBaseElement* chld;
bGenericXMLBaseElement* elt;
bvDefVirtualWMSStyle*	stl;
char					val[_values_length_max_];
	
	for(;;){
// Identification		
		chld=_gapp->classMgr()->NthElement(_root,1,"styleidentification");
		if(!chld){
			break;
		}
		elt=_gapp->classMgr()->NthElement(chld,1,"name");
		if(!elt){
			break;
		}
		elt->getvalue(_name);
		elt=_gapp->classMgr()->NthElement(chld,1,"version");
		if(!elt){
			break;
		}
		elt->getvalue(_vers);
		if(strlen(_vers)==0){
			strcpy(_vers,"3.0.0");
		}
// Globals
		chld=_gapp->classMgr()->NthElement(_root,1,"globals");
		if(!chld){
			break;
		}
				
		elt=_gapp->classMgr()->NthElement(chld,1,"scaleref");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_sref=matof(val);
		elt=_gapp->classMgr()->NthElement(chld,1,"unitcoef");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_coef=matof(val);
		elt=_gapp->classMgr()->NthElement(chld,1,"sort");
		if(!elt){
			break;
		}
		elt->getvalue(val);
		_sort=atoi(val);
				
// StyleRuns
		for(int i=1;i<=_styles.count();i++){
			_styles.get(i,&stl);
			stl->load(_root);
            strcpy(_url,stl->_url);
            strcpy(_usr,stl->_usr);
            strcpy(_pwd,stl->_pwd);
            
            stl->_srs=_gapp->document()->srid();
		}
		
		b=true;
		break;
	}

	if(made){
		_gapp->classMgr()->ReleaseXMLInstance(_root);
		_root=NULL;
	}
	
	if(strlen(_url)>0){
char    url[2048],fullurl[2048];
char    service[256]="WMS";
char    version[256]="1.1.1";

        /*if(strstr(_url,"wmts")){
            strcpy(service,"WMTS");
            strcpy(version,"1.0.0");
        }*/
            
        _https=(strstr(_url,"https://")==_url);
        
		sprintf(url,_url);
		strrep(url,"http://","");
        strrep(url,"https://","");
        strrep(url,"?","");
		
		sprintf(fullurl,"http%s://%s?SERVICE=%s&VERSION=%s&REQUEST=GetCapabilities",(_https?"s":""),url,service,version);
_tm_("trying to connect to :"+fullurl);
		
void*	buffer=NULL;
size_t	sz;
		
		WMSCapabilitiesFreeDescs(_layers);
		
		if(mmurl_get(fullurl,NULL,NULL,&buffer,&sz)!=0){
_te_("mmurl_get failed");
		}
		else{
			if(WMSCapabilitiesParser(buffer,sz,_layers)){
_te_("WMSCapabilitiesParser failed");
			}
		}
		if(buffer){
			free(buffer);
		}
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteVirtualWMS::write(){
_bTrace_("bvDefPaletteVirtualWMSc::write",true);
bArray					arr(sizeof(xmlelt));
char					val[_values_length_max_];
bvDefVirtualWMSStyle	*stl;
UInt32					sign=_sign;
		
	add_cdesc(arr,0,_stylename,"");
	
// Identification			
	add_cdesc(arr,1,"styleidentification","");
	add_cdesc(arr,2,"name",_name);
	sprintf(val,"%.4s",&sign);
	add_cdesc(arr,2,"sign",val);
	add_cdesc(arr,2,"version",_vers);
	
// Globals		
	add_cdesc(arr,1,"globals","");
	add_ddesc(arr,2,"scaleref",_sref,0);
	add_ddesc(arr,2,"unitcoef",_coef,6);
	add_idesc(arr,2,"sort",_sort);
	add_idesc(arr,2,"passcount",_pssmax);
	
// Conditions	
	add_cdesc(arr,1,"condition","");
	
	// StyleRuns
	for(int i=1;i<=_styles.count();i++){
_tm_("dump style "+i);
		_styles.get(i,&stl);
		stl->dump(arr,0);
	}
	
	_root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	
	free_descs(arr);
	
	return(true);
}
