//----------------------------------------------------------------------------
// File : bGeogGOutside.cpp
// Project : MacMap
// Purpose : C++ source file : Outside Geog interface class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2005 Carte Blanche Conseil.
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
// Outside with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 28/01/2005 creation.
// 06/09/2016 cocoa intf.
// 01/11/2016 remove carbon call (edit(windowref,*rect), hide and show)
//----------------------------------------------------------------------------

#include "bGeogGOutside.h"
#include "bXMLOutside.h"
#include "CocoaStuff.h"
#include <mox_intf/xmldesc_utils.h>
#include <MacMapSuite/bTrace.h>

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
	_full=false;
	_strict=false;
    _ctrlr=NULL;
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
    _ctrlr=NULL;
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
    if(_ctrlr){
        releaseViewController(_ctrlr);
        _ctrlr=NULL;
    }
}

// ---------------------------------------------------------------------------
//
// ------------
bool bGeogGOutside::edit(void* nsview){
_bTrace_("bGeogGOutside::edit",true);
    _ctrlr=allocViewController(nsview);
    if(_ctrlr){
        setDataToController(_ctrlr,_full,_strict);
    }
    return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGOutside::end_edit(){
    if(_ctrlr){
        getDataFromController(_ctrlr,&_full,&_strict);
        releaseViewController(_ctrlr);
        _ctrlr=NULL;
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
