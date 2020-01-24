//----------------------------------------------------------------------------
// File : ToolJustificationWindowController.h
// Project : MacMap
// Purpose : Header file : Tool Justification window controller
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

#import "ToolJustificationWindowController.h"
#import "bToolJustification.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <std_ext/bXMapStdIntf.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolJustificationWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolJustificationWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolJustificationWindowController awakeFromNib]",true);
    [super awakeFromNib];
bToolJustification* ext=(bToolJustification*)_ext;
    
    _tm_(ext->get_jmd());
    [_int_mtx selectCellAtRow:ext->get_jmd()-1 column:0];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)validDialog:(id)sender{
_bTrace_("[ToolJustificationWindowController validDialog]",true);
bToolJustification* ext=(bToolJustification*)_ext;

    _tm_([_int_mtx selectedRow]);
    ext->set_jmd([_int_mtx selectedRow]+1);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bToolJustification* ext,
					  long* code){
ToolJustificationWindowController    *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];
    controller=[[ToolJustificationWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
