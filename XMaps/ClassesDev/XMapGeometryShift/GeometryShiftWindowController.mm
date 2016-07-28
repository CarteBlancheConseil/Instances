//----------------------------------------------------------------------------
// File : GeometryShiftWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap GeometryShift window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 01/07/2016 creation.
//----------------------------------------------------------------------------

#import "GeometryShiftWindowController.h"
#import "bXMapGeometryShift.h"
#import "CocoaStuff.h"

#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation GeometryShiftWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[GeometryShiftWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[GeometryShiftWindowController awakeFromNib]",true);
bXMapGeometryShift* ext=(bXMapGeometryShift*)_ext;
double              d=ext->get_data();
    
    [_dsttxt setDoubleValue:d];

bGenericUnit*	u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char			val[256];
    u->short_name(val);
    [_dstlbl setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[GeometryShiftWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapGeometryShift* ext=(bXMapGeometryShift*)_ext;
double              d;

    d=[_dsttxt doubleValue];
    ext->set_data(d);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapGeometryShift* ext,
					  long* code){
GeometryShiftWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[GeometryShiftWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
