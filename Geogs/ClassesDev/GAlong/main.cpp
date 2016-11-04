//----------------------------------------------------------------------------
// File : main.cpp
// Project : MacMap
// Purpose : C++ source file : Plugin entry point
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2006 Carte Blanche Conseil.
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

#include "main.h"
#include <MacMapSuite/bTrace.h>
#include "bGeogGAlong.h"
#include "bXMLAlong.h"

// ---------------------------------------------------------------------------
// 
// ------------
void init(bGenericXMLBaseElement **elt,bGenericMacMapApp* gapp, CFBundleRef bndl){
//bTrace trc("lib::init",false);
	(*elt)=new bGeogGAlong(NULL,gapp,bndl);
//trc.msg("parent instance (%x) of %s created",(*elt),"bGeogGAlong");
bGenericXMLBaseElement*	chld=new bAlongElement(NULL,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
}

// ---------------------------------------------------------------------------
// 
// ------------
void destroy(bGenericXMLBaseElement *elt){
//bTrace trc("lib::destroy",false);
//trc.msg("parent instance (%x) of %s deleted",elt,"bGeogGAlong");
	delete (bGeogGAlong*)(void*)elt;
}
