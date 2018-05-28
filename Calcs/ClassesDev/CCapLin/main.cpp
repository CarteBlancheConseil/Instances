//----------------------------------------------------------------------------
// File : main.cpp
// Project : MacMap
// Purpose : C++ source file : Plugin entry point
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 28/04/2017 creation.
//----------------------------------------------------------------------------

#include "main.h"
#include <MacMapSuite/bTrace.h>
#include "bCalcCCapLin.h"
#include "bXMLfcalcCapLin.h"

// ---------------------------------------------------------------------------
// 
// ------------
void init(bGenericXMLBaseElement **elt,bGenericMacMapApp* gapp, CFBundleRef bndl){
//bTrace trc("lib::init",false);
	(*elt)=new bCalcCCapLin(NULL,gapp,bndl);
//trc.msg("parent instance (%x) of %s created",(*elt),"bCalcCCapLin");

bGenericXMLBaseElement*	chld;
	
	chld=new bfcalcCapLinElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
}

// ---------------------------------------------------------------------------
// 
// ------------
void destroy(bGenericXMLBaseElement *elt){
//bTrace trc("lib::destroy",false);
//trc.msg("parent instance (%x) of %s deleted",elt,"bCalcCCapLin");
	delete (bCalcCCapLin*)(void*)elt;
}
