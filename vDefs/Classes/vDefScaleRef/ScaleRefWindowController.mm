//----------------------------------------------------------------------------
// File : ScaleRefWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap ScaleRef window controller
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
// 18/07/2017 creation.
//----------------------------------------------------------------------------

#import "ScaleRefWindowController.h"
#import "bvDefScaleRef.h"
#import "CocoaStuff.h"
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ScaleRefWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ScaleRefWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ScaleRefWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    NSPopupButtonRemoveItemsFrom(_scl_pop,2);
    NSPopupButtonPopulateWithScales(_scl_pop,gapp,1);
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[ScaleRefWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bvDefScaleRef*      ext=(bvDefScaleRef*)_ext;
long                idx=[_scl_pop indexOfSelectedItem];

    if(idx>1){
bGenericUnit*   u=gapp->scaleMgr()->get(idx-1);
        ext->set_scale(u->coef());
    }
    else{
        ext->set_scale(0);
    }
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bvDefScaleRef* ext,
					  long* code){
ScaleRefWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[ScaleRefWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
