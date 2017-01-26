//----------------------------------------------------------------------------
// File : PaintWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap paint window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2015 Carte Blanche Conseil.
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
// 20/08/2015 creation.
//----------------------------------------------------------------------------

#import "PaintWindowController.h"
#import "bXMapPaint.h"
#import "CocoaStuff.h"

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation PaintPanel

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[PaintPanel close]",true);
_tm_((void*)self);

PaintWindowController*	mmc=(PaintWindowController*)[self windowController];
	if(mmc){
		[mmc prepareForClose];
	}
	[super close];
}

// ---------------------------------------------------------------------------
// Just for debug
// ------------
-(void)dealloc{
_bTrace_("[PaintPanel dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end



// ---------------------------------------------------------------------------
// 
// ------------
@implementation PaintWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[PaintWindowController init]",true);
	self=[super init];
	if(self){
	}	
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[PaintWindowController dealloc]",true);
_tm_((void*)self);
_tm_("window: "+(void*)[self window]);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[PaintWindowController awakeFromNib]",true);
	[super awakeFromNib];
	_ls=0;
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)idle{
bGenericMacMapApp*	gapp=[self getApp];
	if(_ls!=gapp->selMgr()->getState()){
		[self updateUI];
		_ls=gapp->selMgr()->getState();
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[PaintWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPaint:(id)sender{
    if(_ext){
        ((bXMapPaint*)_ext)->paint([(NSControl*)sender tag],false);
    }
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
bGenericMacMapApp*	gapp=[self getApp];
    [_blk setEnabled:gapp->selMgr()->count()>0];
    [_wht setEnabled:gapp->selMgr()->count()>0];
    [_red setEnabled:gapp->selMgr()->count()>0];
    [_grn setEnabled:gapp->selMgr()->count()>0];
    [_blu setEnabled:gapp->selMgr()->count()>0];
    [_cyn setEnabled:gapp->selMgr()->count()>0];
    [_mgt setEnabled:gapp->selMgr()->count()>0];
    [_ylw setEnabled:gapp->selMgr()->count()>0];
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(bGenericMacMapApp*)getApp{
	return((bGenericMacMapApp*)_ext->getapp());
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
PaintWindowController	*controller;
NSAutoreleasePool		*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[PaintWindowController alloc] init];
    [controller setExt:(bStdNSXMap*)ext];
    [localPool release];
    return((void*)controller);
}

// ---------------------------------------------------------------------------
// 
// ------------
void disposeCocoa(const void* instance){
NSAutoreleasePool		*localPool;
PaintWindowController	*mmc=(PaintWindowController*)instance;
	
    if(mmc==NULL){
		return;
	}
    localPool=[[NSAutoreleasePool alloc] init];
	[mmc release];
    [localPool release];
}

// ---------------------------------------------------------------------------
// 
// ------------
void closeCocoa(const void* instance){
NSAutoreleasePool		*localPool;
PaintWindowController	*mmc=(PaintWindowController*)instance;
	
	if(mmc==NULL){
		return;
	}	
    localPool=[[NSAutoreleasePool alloc] init];        
	[mmc close];
    [localPool release];
}

