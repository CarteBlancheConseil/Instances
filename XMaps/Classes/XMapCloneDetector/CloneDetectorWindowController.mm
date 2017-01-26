//----------------------------------------------------------------------------
// File : CloneDetectorWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap clone detector window controller
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
// 09/02/2016 creation.
//----------------------------------------------------------------------------

#import "CloneDetectorWindowController.h"
#import "bXMapCloneDetector.h" 
#import "CocoaStuff.h" 

#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation CloneDetectorWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[CloneDetectorWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[CloneDetectorWindowController awakeFromNib]",true);
bXMapCloneDetector* ext=(bXMapCloneDetector*)_ext;
clonedetector_prm   prm;
    ext->get_infos(&prm);
    [_namebtn setIntValue:prm.name];
    [_sbtpbtn setIntValue:prm.subtype];
    [_colrbtn setIntValue:prm.color];
    [_dirtbtn setIntValue:prm.direction];
    [_sinvbtn setIntValue:prm.reversegeom];
    [_userbtn setIntValue:prm.userfields];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[CloneDetectorWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapCloneDetector* ext=(bXMapCloneDetector*)_ext;
clonedetector_prm   prm;
    prm.name=[_namebtn intValue];
    prm.subtype=[_sbtpbtn intValue];
    prm.color=[_colrbtn intValue];
    prm.direction=[_dirtbtn intValue];
    prm.reversegeom=[_sinvbtn intValue];
    prm.userfields=[_userbtn intValue];
    ext->set_infos(prm);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapCloneDetector* ext,
					  long* code){
CloneDetectorWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[CloneDetectorWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
