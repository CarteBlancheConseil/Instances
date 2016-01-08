//----------------------------------------------------------------------------
// File : bXMapStatUni.cpp
// Project : MacMap
// Purpose : C++ source file : XMap univariate statistics class
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
// 18/04/2014 creation.
//----------------------------------------------------------------------------

#include "bXMapStatUni.h"
#include "CocoaStuff.h"
#include <mox_intf/Type_Utils.h>
#include <mox_intf/NSOpenSavePanelWrappers.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapStatUni::bXMapStatUni(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			: bStdNSXMap(elt,gapp,bndl){
	setclassname("statuni");
	set_flags(kXMapNeedEvents+kXMapNeedIdle);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapStatUni::~bXMapStatUni(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapStatUni::create(bGenericXMLBaseElement* elt){
	return(new bXMapStatUni(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bXMapStatUni::ccinit(){
	return(initializeStatCocoa(getapp(),this));
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapStatUni::test(void* prm){
	return true;
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapStatUni::edit(void* prm){
_bTrace_("bXMapStatUni::edit",true);
	if(_controller){
		closeStatCocoa(_controller);
		disposeStatCocoa(_controller);
		_controller=NULL;
		_wd_open=false;
	}
	if(SelectionIsMonoType(_gapp)==0){
char path[PATH_MAX];
const char*	ft="uni";
		if(NSGetFilePath(&ft,1,cNSUTF8StringEncoding,false,NULL,path)==cNSOKButton){
_tm_(path);			
			_controller=initializeStatCocoaAtPath(getapp(),this,path);
			if(_controller==NULL){
_te_("LOAD FAILED for "+path);
			}
			else{
				_wd_open=true;
			}
		}
	}
	else{
		_controller=ccinit();
		if(_controller){
			_wd_open=true;
		}
	}
	return(true);
}
