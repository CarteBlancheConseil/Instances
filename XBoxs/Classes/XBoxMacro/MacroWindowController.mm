//----------------------------------------------------------------------------
// File : MacroWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Macros XMapBox window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 1997-2015 Carte Blanche Conseil.
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
// 20/01/2015 creation.
//----------------------------------------------------------------------------

#import "MacroWindowController.h"
#import "bXBoxMacro.h"
#import "CocoaStuff.h"

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation MacroPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation MacroWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[MacroWindowController init]",true);
	self=[super init];
	if(self){
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[MacroWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
    [super awakeFromNib];
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
    _mgr=gapp->macroMgr();
    _xsign=kXMLSubClassExtMacro;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[MacroWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doAdd:(id)sender{
_bTrace_("[MacroWindowController doAdd]",true);
bGenericMacMapApp*
    gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt* x=gapp->xmapMgr()->find('find');
    if(x==NULL){
        return;
    }
    x->edit((void*)-1);
    [_mgr_viw reloadData];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doEdit:(id)sender{
_bTrace_("[MacroWindowController doEdit]",true);
NSInteger rowNumber=[_mgr_viw selectedRow];
_tm_(rowNumber);
    if(rowNumber==-1){
        return;
    }
    
bGenericMacMapApp*
    gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt* ext=_mgr->get(rowNumber+1);
    if(ext==NULL){
        return;
    }
bGenericExt* x=gapp->xmapMgr()->find('find');
    if(x==NULL){
        return;
    }
    x->edit(ext);
    [_mgr_viw reloadData];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

#pragma mark ---- CPP/Carbon Entry Point ----
// ---------------------------------------------------------------------------
// 
// ------------
void* initializeCocoa(void* gapp, 
					  void* ext) {
MacroWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[MacroWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

