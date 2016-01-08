//----------------------------------------------------------------------------
// File : bGeogGMoreThan.cpp
// Project : MacMap
// Purpose : C++ source file : More than Geog interface class
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
// 28/01/2005 creation.
//----------------------------------------------------------------------------

#include "bGeogGMoreThan.h"
#include "bXMLMoreThan.h"
#include <MacMapSuite/C_Utils.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/ext_utils.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGeogGMoreThan	::bGeogGMoreThan(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdGeog(elt,gapp,bndl){
	setclassname("gmorethan");
	_cval=NULL;
	_cunit=NULL;
	_val=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bGeogGMoreThan::~bGeogGMoreThan(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bGeogGMoreThan::create(bGenericXMLBaseElement* elt){
	return(new bGeogGMoreThan(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGMoreThan::open(int* flags){
	bStdGeog::open(flags);
	_root=(bStdXMLFormulaElement*)new bMoreThanElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGMoreThan::close(){
	bStdGeog::close();
	if(_root){
		delete (bMoreThanElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bGeogGMoreThan::event(EventRef evt){
bool		b=true;
HICommand	cmd;
UInt32		clss;	
					
	clss=GetEventClass(evt);
	if(clss==kEventClassCommand){
		GetEventParameter(evt,kEventParamDirectObject,typeHICommand,NULL,sizeof(HICommand),NULL,&cmd);
		switch(cmd.commandID){
			case kGeogGMoreThanValueCmd:
				break;
			case kGeogGMoreThanUnitCmd:
				break;
			default:
				b=false;
				break;
		}
	}
	return(b);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bGeogGMoreThan::edit(WindowRef wd, Rect* r){
OSStatus	status;
CFStringRef	cfs;
Rect		lr=(*r);
char		val[256];
ControlID	cid;

	cid.signature=kGeogGMoreThanSignature;
	
	lr.top+=5;
	lr.left+=5;
	lr.bottom=lr.top+16;
	lr.right=lr.left+100;
	
	sprintf(val,"%.*f",_gapp->document()->dist_pref_digits(),Measure_i2d(_gapp,_val));
	cfs=CFStringCreateWithCString(kCFAllocatorDefault,val,kCFStringEncodingMacRoman);
	status=CreateEditTextControl(wd,&lr,cfs,false,false,NULL,&_cval);
	cid.id=kGeogGMoreThanValueID;
	SetControlID(_cval,&cid);
	SetControlCommandID(_cval,kGeogGMoreThanValueCmd);

	CFRelease(cfs);
	
	lr.left=lr.right+5;
	lr.right=lr.left+30;
	
	bGenericUnit* u=_gapp->distMgr()->get();
	u->short_name(val);
	cfs=CFStringCreateWithCString(kCFAllocatorDefault,val,kCFStringEncodingMacRoman);
	status=CreateStaticTextControl(wd,&lr,cfs,NULL,&_cunit);
	cid.id=kGeogGMoreThanUnitID;
	SetControlID(_cunit,&cid);
	SetControlCommandID(_cunit,kGeogGMoreThanUnitCmd);
	CFRelease(cfs);
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGMoreThan::end_edit(){
	if(_cval){
char		val[256];
Size		outsz;	
		GetControlData(_cval,kControlEditTextPart,kControlEditTextTextTag,sizeof(val),val,&outsz);
		val[outsz]=0;
		_val=Measure_d2i(_gapp,atof(val));
		DisposeControl(_cval);
		_cval=NULL;
	}
	if(_cunit){
		DisposeControl(_cunit);
		_cunit=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGMoreThan::hide(){
	if(_cval){
		HideControl(_cval);
	}
	if(_cunit){
		HideControl(_cunit);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGMoreThan::show(){
	if(_cval){
		ShowControl(_cval);
	}
	if(_cunit){
		ShowControl(_cunit);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGMoreThan::get_params(bArray* arr, int indent){
char	c[_names_length_max_];
	
	_root->getclassname(c);
	sprintf(c,"%.*f",15,_val);
	add_cdesc(*arr,indent,"morethan",c);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGMoreThan::put_params(bGenericXMLBaseElement* root){
char	c[_values_length_max_]="";
	root->getvalue(c);
	_val=matof(c);
}
