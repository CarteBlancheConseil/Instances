//----------------------------------------------------------------------------
// File : SimplifyWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap Simplify window controller
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

#import "SimplifyWindowController.h"
#import "bXMapSimplify.h"
#import "CocoaStuff.h"

#import <mox_intf/bEventLog.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation SimplifyWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[SimplifyWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[SimplifyWindowController awakeFromNib]",true);
bXMapSimplify*  ext=(bXMapSimplify*)_ext;
double          prm=ext->get_data();
    
    [_angtxt setDoubleValue:prm];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[SimplifyWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapSimplify*  ext=(bXMapSimplify*)_ext;
double          prm;

    prm=[_angtxt doubleValue];
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
void runCocoaAppModal(bXMapSimplify* ext,
					  long* code){
SimplifyWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[SimplifyWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
