//----------------------------------------------------------------------------
// File : bGeogGInside.cpp
// Project : MacMap
// Purpose : C++ source file : Inside Geog interface class
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
// Inside with this program.  If not, see <http://www.gnu.org/licenses/>.
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

#include "bGeogGInside.h"
#include "bXMLInside.h"
#include "CocoaStuff.h"
#include <mox_intf/xmldesc_utils.h>
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
	_full=false;
	_strict=false;
    _ctrlr=NULL;
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
    _ctrlr=NULL;
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
    if(_ctrlr){
        releaseViewController(_ctrlr);
        _ctrlr=NULL;
    }
}

// ---------------------------------------------------------------------------
//
// ------------
bool bGeogGInside::edit(void* nsview){
_bTrace_("bGeogGInside::edit",true);
    _ctrlr=allocViewController(nsview);
    if(_ctrlr){
        setDataToController(_ctrlr,_full,_strict);
    }
    return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGInside::end_edit(){
    if(_ctrlr){
        getDataFromController(_ctrlr,&_full,&_strict);
        releaseViewController(_ctrlr);
        _ctrlr=NULL;
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
