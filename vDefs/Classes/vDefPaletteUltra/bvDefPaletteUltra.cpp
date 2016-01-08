//----------------------------------------------------------------------------
// File : bvDefPaletteUltra.cpp
// Project : MacMap
// Purpose : C++ source file : Ultra vdef class (edits all styles in an XML mode)
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
// 12/08/2013 creation.
//----------------------------------------------------------------------------

#include "bvDefPaletteUltra.h"
#include "CocoaStuff.h"
#include <MacMapSuite/bTrace.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/endian.h>
#include <mox_intf/ext_utils.h>
#include <MacMapSuite/valconv.h>
#include <MacMapSuite/C_Utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bvDefPaletteUltra	::bvDefPaletteUltra(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
						: bStdNSPalettevDef(elt,gapp,bndl){
	setclassname("paletteultra");
	strcpy(_stylename,"circlestyle");
	_xml=NULL;
	_sz=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bvDefPaletteUltra::~bvDefPaletteUltra(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bvDefPaletteUltra::create(bGenericXMLBaseElement* elt){
	return(new bvDefPaletteUltra(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteUltra::test(bGenericType* tp){
	if(bStdNSPalettevDef::test(tp)==false){
		return(false);
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
char* bvDefPaletteUltra::txt_get(){	
	return(_xml);
}

// ---------------------------------------------------------------------------
// 
// -----------
long bvDefPaletteUltra::siz_get(){	
	return(_sz);
}

// ---------------------------------------------------------------------------
// 
// -----------
void bvDefPaletteUltra::txt_put(char* txt, long sz){
_bTrace_("bvDefPaletteUltra::txt_put",true);
	if(_xml){
		free(_xml);
	}
	_xml=txt;
	_sz=sz;
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bvDefPaletteUltra::ccinit(){
	return(initializeCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bvDefPaletteUltra::make(){
_bTrace_("bvDefPaletteUltra::make",true);
bArray	arr(sizeof(xmlelt));
char	val[256];
UInt32	sign=_sign;
int		i,n;
	
	_xml=NULL;
	_sz=0;

	if(_tp){
		n=_tp->fields()->count_constraints(kOBJ_SubType_);
	}
	else{
		n=0;
	}
	add_cdesc(arr,0,"circlestyle","");
	
	// Identification		
	add_cdesc(arr,1,"styleidentification","");
	add_cdesc(arr,2,"name",_name);
	sprintf(val,"%.4s",&sign);
	add_cdesc(arr,2,"sign",val);
	add_cdesc(arr,2,"version",_vers);
	
	// Globals
	add_cdesc(arr,1,"globals","");
	if(_tp){
		_tp->fields()->get_name(kOBJ_SubType_,val);
		add_cdesc(arr,2,"classfield",val);
	}
	add_ddesc(arr,2,"scaleref",0,0);
	add_ddesc(arr,2,"unitcoef",1,0);
	if(_tp){
		add_idesc(arr,2,"sort",2);
		add_idesc(arr,2,"passcount",1);
		add_cdesc(arr,2,"classboundsarray","");
		for(i=1;i<=n;i++){
			add_idesc(arr,3,"classbound",i);
			_tp->fields()->get_constraint(kOBJ_SubType_,i,val);
			add_cdesc(arr,3,"classname",val);
		}	
		add_idesc(arr,3,"classbound",i);
		add_cdesc(arr,3,"classname","");
	}
	else{
		add_idesc(arr,2,"sort",0);
		add_idesc(arr,2,"passcount",1);
	}
	// Condition	
	add_cdesc(arr,1,"condition","");
	// Nothing else, condition are optional.
	
	// StyleRun
	add_cdesc(arr,1,"stylerun","");
	add_cdesc(arr,2,"validity","");
	if(_tp){
		add_idesc(arr,3,"classmin",1);
		add_idesc(arr,3,"classmax",2);
	}
	add_ddesc(arr,3,"scalemin",1,0);
	add_ddesc(arr,3,"scalemax",LONG_MAX,0);
	add_idesc(arr,3,"pass",1);
	add_cdesc(arr,2,"render","");
	add_cdesc(arr,3,"stroke","");
	add_ddesc(arr,4,"red",0.5,2);
	add_ddesc(arr,4,"green",0.5,2);
	add_ddesc(arr,4,"blue",0,2);
	add_ddesc(arr,4,"alpha",1,2);
	add_cdesc(arr,3,"fill","");
	add_ddesc(arr,4,"red",0.5,2);
	add_ddesc(arr,4,"green",0.5,2);
	add_ddesc(arr,4,"blue",0.5,2);
	add_ddesc(arr,4,"alpha",1,2);
	if(_tp){
		add_cdesc(arr,2,"stdgeometry","");
	}
	else{
		add_cdesc(arr,2,"screengeometry","");
	}
	add_idesc(arr,3,"centroid",1);
	add_ddesc(arr,3,"size",3,2);
	add_ddesc(arr,3,"width",1,2);
	_root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	free_descs(arr);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteUltra::read(){
_bTrace_("bvDefPaletteUltra::read",true);
bool	made=false;
	if(!_root){
		make();
		made=true;
	}
	
	_xml=NULL;
	_sz=0;

bMemFile	f;
char*		bf;
int			sz;
	
	_root->encode(0,&f);
	if(f.status()){
		_gapp->classMgr()->ReleaseXMLInstance(_root);
		return(false);
	}
	f.mount(&bf,&sz);
	_xml=(char*)realloc(bf,sz+1);
	_xml[sz]=0;
	_sz=sz+1;
		
	if(made){
		_gapp->classMgr()->ReleaseXMLInstance(_root);
		_root=NULL;
	}
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bvDefPaletteUltra::write(){
_bTrace_("bvDefPaletteUltra::write",true);

char*		bf=(char*)malloc((_sz*3)+2);
	strcpy(bf,_xml);
//	strrep(bf,"&","\x26");
	
CFStringRef	cfs=CFStringCreateWithCString(kCFAllocatorDefault,bf,kCFStringEncodingUTF8);
	CFStringGetCString(cfs,bf,((_sz*3)+2),kCFStringEncodingUTF8);
	CFRelease(cfs);
	
//	fprintf(stderr,"%s\n",bf);// Pour Contrôle
	
//CFDataRef	data=CFDataCreateWithBytesNoCopy(kCFAllocatorDefault,(UInt8*)bf,strlen(bf),kCFAllocatorNull);
	_root=_gapp->classMgr()->ParseXMLData(bf,strlen(bf));

bGenericXMLBaseElement* chld;
bGenericXMLBaseElement* elt;
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
		elt->getvalue(val);
		if((strlen(val)==0)&&(strlen(_name)>0)){
_tm_("correction du nom");
			cfs=CFStringCreateWithCString(kCFAllocatorDefault,_name,kCFStringEncodingMacRoman);
			CFStringGetCString(cfs,val,_values_length_max_,kCFStringEncodingUTF8);
			CFRelease(cfs);
			elt->setvalue(val);
		}
		break;
	}		
	
//	CFRelease(data);
	free(bf);
	
	return(true);
}
