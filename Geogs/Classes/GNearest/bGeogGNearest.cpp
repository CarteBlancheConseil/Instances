//----------------------------------------------------------------------------
// File : bGeogGNearest.cpp
// Project : MacMap
// Purpose : C++ source file : Nearest Geog interface class
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
// 03/12/2008 creation.
//----------------------------------------------------------------------------

#include "bGeogGNearest.h"
#include "bXMLNearest.h"
#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/C_Utils.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/Carb_Utils.h>
#include <mox_intf/mm_messages.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGeogGNearest::bGeogGNearest(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			:bStdGeog(elt,gapp,bndl){
	setclassname("gnearest");
	_cval=NULL;
	_cunit=NULL;
	_val=0;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bGeogGNearest::~bGeogGNearest(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bGeogGNearest::create(bGenericXMLBaseElement* elt){
	return(new bGeogGNearest(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGNearest::open(int* flags){
	bStdGeog::open(flags);
	_root=(bStdXMLFormulaElement*)new bNearestElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGNearest::close(){
	bStdGeog::close();
	if(_root){
		delete (bNearestElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bGeogGNearest::event(EventRef evt){
bool		b=true;
HICommand	cmd;
UInt32		clss;	
					
	clss=GetEventClass(evt);
	if(clss==kEventClassCommand){
		GetEventParameter(evt,kEventParamDirectObject,typeHICommand,NULL,sizeof(HICommand),NULL,&cmd);
		switch(cmd.commandID){
			case kGeogGNearestValueCmd:
				break;
			case kGeogGNearestUnitCmd:
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
bool bGeogGNearest::edit(WindowRef wd, Rect* r){
OSStatus	status;
CFStringRef	cfs;
Rect		lr=(*r);
char		val[256];
ControlID	cid;

	cid.signature=kGeogGNearestSignature;
	
	lr.top+=5;
	lr.left+=5;
	lr.bottom=lr.top+16;
	lr.right=lr.left+100;

	b_message_string("retain",val,getbundle(),0);
	cfs=CFStringCreateWithCString(kCFAllocatorDefault,val,kCFStringEncodingMacRoman);
	status=CreateStaticTextControl(wd,&lr,cfs,NULL,&_cunit);
	cid.id=kGeogGNearestUnitID;
	SetControlID(_cunit,&cid);
	SetControlCommandID(_cunit,kGeogGNearestUnitCmd);
	CFRelease(cfs);

	lr.left=lr.right+5;
	lr.right=lr.left+100;
	
	sprintf(val,"%d",_val);
	cfs=CFStringCreateWithCString(kCFAllocatorDefault,val,kCFStringEncodingMacRoman);
	status=CreateEditUnicodeTextControl(wd,&lr,cfs,false,NULL,&_cval);
	cid.id=kGeogGNearestValueID;
	SetControlID(_cval,&cid);
	SetControlCommandID(_cval,kGeogGNearestValueCmd);

	CFRelease(cfs);
		
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGNearest::end_edit(){
	if(_cval){
char	val[256];

		GetTextControlValue(_cval,val,sizeof(val)-1);
		_val=atoi(val);
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
void bGeogGNearest::hide(){
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
void bGeogGNearest::show(){
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
void bGeogGNearest::get_params(bArray* arr, int indent){
char	c[_names_length_max_];
	
	sprintf(c,"%d",_val);
	add_cdesc(*arr,indent,"nearest",c);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGNearest::put_params(bGenericXMLBaseElement* root){
char	c[_values_length_max_]="";
	root->getvalue(c);
	_val=atoi(c);
}
