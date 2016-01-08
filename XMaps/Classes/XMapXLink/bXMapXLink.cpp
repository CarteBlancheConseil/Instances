//----------------------------------------------------------------------------
// File : bXMapXLink.cpp
// Project : MacMap
// Purpose : C++ source file : XMap link (i.e. url) class
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

#include "bXMapXLink.h"
#include "CocoaStuff.h"
#include <mox_intf/Type_Utils.h>
#include <mox_intf/NSOpenSavePanelWrappers.h>
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapXLink	::bXMapXLink(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
			:bStdNSXMap(elt,gapp,bndl){
	setclassname("xlink");
	set_flags(kXMapNeedEvents+kXMapNeedIdle);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapXLink::~bXMapXLink(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapXLink::create(bGenericXMLBaseElement* elt){
	return(new bXMapXLink(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapXLink::open(int* flags){
    bStdNSXMap::open(flags);
    _wd_open=false;
}

// ---------------------------------------------------------------------------
// 
// -----------
void* bXMapXLink::ccinit(){
	return(initializeCocoa(getapp(),this));
}

