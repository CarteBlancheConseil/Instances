//----------------------------------------------------------------------------
// File : bGeogGAtStart.cpp
// Project : MacMap
// Purpose : C++ source file : At start Geog interface class
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

#include "bGeogGAtStart.h"
#include "bXMLAtStart.h"
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/mm_messages.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGeogGAtStart	::bGeogGAtStart(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl) 
				:bStdGeog(elt,gapp,bndl){
	setclassname("gatstart");
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bGeogGAtStart::~bGeogGAtStart(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bGeogGAtStart::create(bGenericXMLBaseElement* elt){
	return(new bGeogGAtStart(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGAtStart::open(int* flags){
	bStdGeog::open(flags);
	_root=(bStdXMLFormulaElement*)new bAtStartElement(this,_gapp,getbundle());
}

// ---------------------------------------------------------------------------
// 
// -----------
void bGeogGAtStart::close(){
	bStdGeog::close();
	if(_root){
		delete (bAtStartElement*)_root;
		_root=NULL;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
void bGeogGAtStart::get_params(bArray* arr, int indent){
char	c[_names_length_max_];

	_root->getclassname(c);
	add_cdesc(*arr,indent,c,"");
}
