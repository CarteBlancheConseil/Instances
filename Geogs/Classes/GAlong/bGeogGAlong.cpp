//----------------------------------------------------------------------------
// File : bGeogGAlong.cpp
// Project : MacMap
// Purpose : C++ source file : Along Geog interface class
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
// 07/11/2006 creation.
//----------------------------------------------------------------------------

#include "bGeogGAlong.h"
#include "bXMLAlong.h"
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/mm_messages.h>

// ---------------------------------------------------------------------------
// 
// ------------
enum{
	kAlongFully		=0x00000001,
	kAlongStrictly	=0x00000002,
};

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGeogGAlong	::bGeogGAlong(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdGeog(elt,gapp,bndl){
	setclassname("galong");
	_cfull=NULL;
	_cpart=NULL;
	_cstrict=NULL;
	_full=false;
	_strict=false;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bGeogGAlong::~bGeogGAlong(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bGeogGAlong::create(bGenericXMLBaseElement* elt){
	return(new bGeogGAlong(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGAlong::open(int* flags){
	bStdGeog::open(flags);
	_root=(bStdXMLFormulaElement*)new bAlongElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGAlong::close(){
	bStdGeog::close();
	if(_root){
		delete (bAlongElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bGeogGAlong::event(EventRef evt){
bool		b=true;
HICommand	cmd;
UInt32		clss;	
					
	clss=GetEventClass(evt);
	if(clss==kEventClassCommand){
		GetEventParameter(evt,kEventParamDirectObject,typeHICommand,NULL,sizeof(HICommand),NULL,&cmd);
		switch(cmd.commandID){
			case kGeogGAlongFullyCmd:
				SetControl32BitValue(_cfull,true);
				SetControl32BitValue(_cpart,false);
				break;
			case kGeogGAlongPartlyCmd:
				SetControl32BitValue(_cfull,false);
				SetControl32BitValue(_cpart,true);
				break;
			case kGeogGAlongStrictlyCmd:
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
bool bGeogGAlong::edit(WindowRef wd, Rect* r){
OSStatus	status;
CFStringRef	cfs;
Rect		lr=(*r);
ControlID	cid;
	
	cid.signature=kGeogGAlongSignature;
	
	lr.top+=5;
	lr.left+=5;
	lr.bottom=lr.top+16;
	lr.right=lr.left+100;
	
	b_message_cfstring(kGeogGAlongMsgPartly,&cfs,getbundle());
	status=CreateRadioButtonControl(wd,&lr,cfs,!_full,true,&_cpart);
	cid.id=kGeogGAlongPartlyID;
	SetControlID(_cpart,&cid);
	SetControlCommandID(_cpart,kGeogGAlongPartlyCmd);
	CFRelease(cfs);
	
	lr.top=lr.bottom+5;
	lr.bottom=lr.top+16;
	
	b_message_cfstring(kGeogGAlongMsgFully,&cfs,getbundle());
	status=CreateRadioButtonControl(wd,&lr,cfs,_full,true,&_cfull);
	cid.id=kGeogGAlongFullyID;
	SetControlID(_cfull,&cid);
	SetControlCommandID(_cfull,kGeogGAlongFullyCmd);
	CFRelease(cfs);
	
	lr.left+=5;
	lr.right+=5;
	lr.top=lr.bottom+5;
	lr.bottom=lr.top+16;

	b_message_cfstring(kGeogGAlongMsgStrictly,&cfs,getbundle());
	status=CreateCheckBoxControl(wd,&lr,cfs,_strict,true,&_cstrict);
	cid.id=kGeogGAlongPartlyID;
	SetControlID(_cstrict,&cid);
	SetControlCommandID(_cstrict,kGeogGAlongStrictlyCmd);
	CFRelease(cfs);
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGAlong::end_edit(){
	if(_cfull){
		_full=GetControl32BitValue(_cfull);
		DisposeControl(_cfull);
		_cfull=NULL;
	}
	if(_cpart){
		DisposeControl(_cpart);
		_cpart=NULL;
	}
	if(_cstrict){
		_strict=GetControl32BitValue(_cstrict);
		DisposeControl(_cstrict);
		_cstrict=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGAlong::hide(){
	if(_cfull){
		HideControl(_cfull);
	}
	if(_cpart){
		HideControl(_cpart);
	}
	if(_cstrict){
		HideControl(_cstrict);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGAlong::show(){
	if(_cfull){
		ShowControl(_cfull);
	}
	if(_cpart){
		ShowControl(_cpart);
	}
	if(_cstrict){
		ShowControl(_cstrict);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGAlong::get_params(bArray* arr, int indent){
char	c[_names_length_max_];
int		k=0;

	_root->getclassname(c);
	if(_full){
		k|=kAlongFully;
	}
	if(_strict){
		k|=kAlongStrictly;
	}
	add_idesc(*arr,indent,c,k);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGAlong::put_params(bGenericXMLBaseElement* root){
char	c[_values_length_max_]="";
	root->getvalue(c);
int		x=atoi(c);
	_full=(x&kAlongFully);
	_strict=(x&kAlongStrictly);
}
