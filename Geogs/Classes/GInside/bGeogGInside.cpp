//----------------------------------------------------------------------------
// File : bGeogGInside.cpp
// Project : MacMap
// Purpose : C++ source file : Inside Geog interface class
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

#include "bGeogGInside.h"
#include "bXMLInside.h"
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/mm_messages.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
enum{
	kInsideFully		=0x00000001,
	kInsideStrictly		=0x00000002,
};

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGeogGInside::bGeogGInside(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			:bStdGeog(elt,gapp,bndl){
	setclassname("ginside");
	_cfull=NULL;
	_cpart=NULL;
	_cstrict=NULL;
	_full=false;
	_strict=false;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bGeogGInside::~bGeogGInside(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bGeogGInside::create(bGenericXMLBaseElement* elt){
	return(new bGeogGInside(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGInside::open(int* flags){
	bStdGeog::open(flags);
	_root=(bStdXMLFormulaElement*)new bInsideElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGInside::close(){
	bStdGeog::close();
	if(_root){
		delete (bInsideElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bGeogGInside::event(EventRef evt){
bool		b=true;
HICommand	cmd;
UInt32		clss;	
					
	clss=GetEventClass(evt);
	if(clss==kEventClassCommand){
		GetEventParameter(evt,kEventParamDirectObject,typeHICommand,NULL,sizeof(HICommand),NULL,&cmd);
		switch(cmd.commandID){
			case kGeogGInsideFullyCmd:
				SetControl32BitValue(_cfull,true);
				SetControl32BitValue(_cpart,false);
				break;
			case kGeogGInsidePartlyCmd:
				SetControl32BitValue(_cfull,false);
				SetControl32BitValue(_cpart,true);
				break;
			case kGeogGInsideStrictlyCmd:
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
bool bGeogGInside::edit(WindowRef wd, Rect* r){
OSStatus	status;
CFStringRef	cfs;
Rect		lr=(*r);
ControlID	cid;
	
	cid.signature=kGeogGInsideSignature;
	
	lr.top+=5;
	lr.left+=5;
	lr.bottom=lr.top+16;
	lr.right=lr.left+100;
	
	b_message_cfstring(kGeogGInsideMsgPartly,&cfs,getbundle());
	status=CreateRadioButtonControl(wd,&lr,cfs,!_full,true,&_cpart);
	cid.id=kGeogGInsidePartlyID;
	SetControlID(_cpart,&cid);
	SetControlCommandID(_cpart,kGeogGInsidePartlyCmd);
	CFRelease(cfs);
	
	lr.top=lr.bottom+5;
	lr.bottom=lr.top+16;
	
	b_message_cfstring(kGeogGInsideMsgFully,&cfs,getbundle());
	status=CreateRadioButtonControl(wd,&lr,cfs,_full,true,&_cfull);
	cid.id=kGeogGInsideFullyID;
	SetControlID(_cfull,&cid);
	SetControlCommandID(_cfull,kGeogGInsideFullyCmd);
	CFRelease(cfs);
	
	lr.left+=5;
	lr.right+=5;
	lr.top=lr.bottom+5;
	lr.bottom=lr.top+16;

	b_message_cfstring(kGeogGInsideMsgStrictly,&cfs,getbundle());
	status=CreateCheckBoxControl(wd,&lr,cfs,_strict,true,&_cstrict);
	cid.id=kGeogGInsidePartlyID;
	SetControlID(_cstrict,&cid);
	SetControlCommandID(_cstrict,kGeogGInsideStrictlyCmd);
	CFRelease(cfs);
	
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGInside::end_edit(){
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
void bGeogGInside::hide(){
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
void bGeogGInside::show(){
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
void bGeogGInside::get_params(bArray* arr, int indent){
char	c[_names_length_max_];
int		k=0;

	_root->getclassname(c);
	if(_full){
		k|=kInsideFully;
	}
	if(_strict){
		k|=kInsideStrictly;
	}
	add_idesc(*arr,indent,c,k);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGInside::put_params(bGenericXMLBaseElement* root){
char	c[_values_length_max_]="";
	root->getvalue(c);
int		x=atoi(c);
	_full=(x&kInsideFully);
	_strict=(x&kInsideStrictly);
}
