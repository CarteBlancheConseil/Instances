//----------------------------------------------------------------------------
// File : ToolSymbRotationWindowController.h
// Project : MacMap
// Purpose : Header file : Tool SymbRotation window controller
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

#import "ToolSymbRotationWindowController.h"
#import "bToolSymbRotation.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolSymbRotationWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolSymbRotationWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolSymbRotationWindowController awakeFromNib]",true);
    [super awakeFromNib];
bToolSymbRotation* ext=(bToolSymbRotation*)_ext;
    
    [_uac_chk setIntValue:ext->get_use_angle()];
    [_ang_txt setDoubleValue:ext->get_angle()];
    [self updateUI];
}

#pragma mark ---- Gestion Interface ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
    [_ang_lbl setEnabled:[_uac_chk intValue]];
    [_ang_txt setEnabled:[_uac_chk intValue]];
    [_ang_unt setEnabled:[_uac_chk intValue]];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)validDialog:(id)sender{
bToolSymbRotation*  ext=(bToolSymbRotation*)_ext;

    ext->set_use_angle([_uac_chk intValue]);
    ext->set_angle([_ang_txt doubleValue]);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doUseAngleConstraint:(id)sender{
_bTrace_("[ToolSymbRotationWindowController doUseAngleConstraint]",true);
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolSymbRotation* ext,
					  long* code){
ToolSymbRotationWindowController    *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolSymbRotationWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
