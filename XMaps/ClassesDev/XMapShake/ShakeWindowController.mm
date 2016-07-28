//----------------------------------------------------------------------------
// File : ShakeWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap Shake window controller
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
// 21/07/2016 creation.
//----------------------------------------------------------------------------

#import "ShakeWindowController.h"
#import "bXMapShake.h"
#import "CocoaStuff.h"

#import <mox_intf/bEventLog.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ShakeWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ShakeWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ShakeWindowController awakeFromNib]",true);
bXMapShake*   ext=(bXMapShake*)_ext;
shake_prm     prm=ext->get_data();
    
    [_dsttxt setDoubleValue:prm];

bGenericUnit*	u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char			val[256];
    u->short_name(val);
    [_dstunt setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[ShakeWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapShake*   ext=(bXMapShake*)_ext;
shake_prm     prm;

    prm=[_dsttxt doubleValue];
    ext->set_data(prm);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapShake* ext,
					  long* code){
ShakeWindowController	*controller;
NSAutoreleasePool       *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[ShakeWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
