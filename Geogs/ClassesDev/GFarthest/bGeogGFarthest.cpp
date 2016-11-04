//----------------------------------------------------------------------------
// File : bGeogGFarthest.cpp
// Project : MacMap
// Purpose : C++ source file : Farthest Geog interface class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2008 Carte Blanche Conseil.
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
// 06/09/2016 cocoa intf.
// 01/11/2016 remove carbon call (edit(windowref,*rect), hide and show)
//----------------------------------------------------------------------------

#include "bGeogGFarthest.h"
#include "bXMLFarthest.h"
#include "CocoaStuff.h"
#include <mox_intf/xmldesc_utils.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGeogGFarthest::bGeogGFarthest(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			:bStdGeog(elt,gapp,bndl){
	setclassname("gfarthest");
	_val=0;
    _ctrlr=NULL;
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bGeogGFarthest::~bGeogGFarthest(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bGeogGFarthest::create(bGenericXMLBaseElement* elt){
	return(new bGeogGFarthest(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGFarthest::open(int* flags){
	bStdGeog::open(flags);
	_root=(bStdXMLFormulaElement*)new bFarthestElement(this,_gapp,getbundle());
    _ctrlr=NULL;
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGFarthest::close(){
	bStdGeog::close();
	if(_root){
		delete (bFarthestElement*)_root;
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
bool bGeogGFarthest::edit(void* nsview){
_bTrace_("bGeogGFarthest::edit",true);
    _ctrlr=allocViewController(nsview);
    if(_ctrlr){
        setDataToController(_ctrlr,_val);
    }
    return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGFarthest::end_edit(){
    if(_ctrlr){
        _val=getDataFromController(_ctrlr);
        releaseViewController(_ctrlr);
        _ctrlr=NULL;
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGFarthest::get_params(bArray* arr, int indent){
char	c[_names_length_max_];
	
	sprintf(c,"%d",_val);
	add_cdesc(*arr,indent,"farthest",c);
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGFarthest::put_params(bGenericXMLBaseElement* root){
char	c[_values_length_max_]="";
	root->getvalue(c);
	_val=atoi(c);
}
