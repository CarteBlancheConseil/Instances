//----------------------------------------------------------------------------
// File : bGeogGOutside.cpp
// Project : MacMap
// Purpose : C++ source file : Outside Geog interface class
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

#include "bGeogGOutside.h"
#include "bXMLOutside.h"
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/mm_messages.h>

// ---------------------------------------------------------------------------
// 
// ------------
enum{
	kOutsideFully		=0x00000001,
	kOutsideStrictly	=0x00000002,
};

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGeogGOutside	::bGeogGOutside(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdGeog(elt,gapp,bndl){
	setclassname("goutside");
	_cfull=NULL;
	_cpart=NULL;
	_cstrict=NULL;
	_full=false;
	_strict=false;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bGeogGOutside::~bGeogGOutside(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bGeogGOutside::create(bGenericXMLBaseElement* elt){
	return(new bGeogGOutside(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGOutside::open(int* flags){
	bStdGeog::open(flags);
	_root=(bStdXMLFormulaElement*)new bOutsideElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGOutside::close(){
	bStdGeog::close();
	if(_root){
		delete (bOutsideElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bGeogGOutside::event(EventRef evt){
bool		b=true;
HICommand	cmd;
UInt32		clss;	
					
	clss=GetEventClass(evt);
	if(clss==kEventClassCommand){
		GetEventParameter(evt,kEventParamDirectObject,typeHICommand,NULL,sizeof(HICommand),NULL,&cmd);
		switch(cmd.commandID){
			case kGeogGOutsideFullyCmd:
				SetControl32BitValue(_cfull,true);
				SetControl32BitValue(_cpart,false);
				break;
			case kGeogGOutsidePartlyCmd:
				SetControl32BitValue(_cfull,false);
				SetControl32BitValue(_cpart,true);
				break;
			case kGeogGOutsideStrictlyCmd:
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
bool bGeogGOutside::edit(WindowRef wd, Rect* r){
OSStatus	status;
CFStringRef	cfs;
Rect		lr=(*r);
ControlID	cid;
	
	cid.signature=kGeogGOutsideSignature;
	
	lr.top+=5;
	lr.left+=5;
	lr.bottom=lr.top+16;
	lr.right=lr.left+100;
	
	b_message_cfstring(kGeogGOutsideMsgPartly,&cfs,getbundle());
	status=CreateRadioButtonControl(wd,&lr,cfs,!_full,true,&_cpart);
	cid.id=kGeogGOutsidePartlyID;
	SetControlID(_cpart,&cid);
	SetControlCommandID(_cpart,kGeogGOutsidePartlyCmd);
	CFRelease(cfs);
	
	lr.top=lr.bottom+5;
	lr.bottom=lr.top+16;
	
	b_message_cfstring(kGeogGOutsideMsgFully,&cfs,getbundle());
	status=CreateRadioButtonControl(wd,&lr,cfs,_full,true,&_cfull);
	cid.id=kGeogGOutsideFullyID;
	SetControlID(_cfull,&cid);
	SetControlCommandID(_cfull,kGeogGOutsideFullyCmd);
	CFRelease(cfs);
	
	lr.left+=5;
	lr.right+=5;
	lr.top=lr.bottom+5;
	lr.bottom=lr.top+16;

	b_message_cfstring(kGeogGOutsideMsgStrictly,&cfs,getbundle());
	status=CreateCheckBoxControl(wd,&lr,cfs,_strict,true,&_cstrict);
	cid.id=kGeogGOutsidePartlyID;
	SetControlID(_cstrict,&cid);
	SetControlCommandID(_cstrict,kGeogGOutsideStrictlyCmd);
	CFRelease(cfs);
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGOutside::end_edit(){
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
void bGeogGOutside::hide(){
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
void bGeogGOutside::show(){
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
void bGeogGOutside::get_params(bArray* arr, int indent){
char	c[_names_length_max_];
int		k=0;

	_root->getclassname(c);
	if(_full){
		k|=kOutsideFully;
	}
	if(_strict){
		k|=kOutsideStrictly;
	}
	add_idesc(*arr,indent,c,k);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGOutside::put_params(bGenericXMLBaseElement* root){
char	c[_values_length_max_]="";
	root->getvalue(c);
int		x=atoi(c);
	_full=(x&kOutsideFully);
	_strict=(x&kOutsideStrictly);
}
