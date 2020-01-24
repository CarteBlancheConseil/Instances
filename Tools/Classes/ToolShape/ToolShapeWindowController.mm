//----------------------------------------------------------------------------
// File : ToolShapeWindowController.h
// Project : MacMap
// Purpose : Header file : Tool Shape window controller
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
// 24/03/2017 creation.
//----------------------------------------------------------------------------

#import "ToolShapeWindowController.h"
#import "bToolShape.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolShapeWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolShapeWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolShapeWindowController awakeFromNib]",true);
    [super awakeFromNib];
bToolShape* ext=(bToolShape*)_ext;
    
    [_cip_chk setIntValue:ext->get_ctr()];
    [_opf_chk setIntValue:ext->get_opn()];
    [_scm_chk setIntValue:ext->get_cm()];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)validDialog:(id)sender{
bToolShape* ext=(bToolShape*)_ext;
    ext->set_ctr([_cip_chk intValue]);
    ext->set_opn([_opf_chk intValue]);
    ext->set_cm([_scm_chk intValue]);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolShape* ext,
					  long* code){
ToolShapeWindowController    *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolShapeWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
