//----------------------------------------------------------------------------
// File : LineUpWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap LineUp window controller
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
// 04/07/2016 creation.
//----------------------------------------------------------------------------

#import "LineUpWindowController.h"
#import "bXMapLineUp.h"
#import "CocoaStuff.h"

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation LineUpWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[LineUpWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[LineUpWindowController awakeFromNib]",true);
bXMapLineUp*  ext=(bXMapLineUp*)_ext;
    
    [_dirpop selectItemAtIndex:ext->get_kind()-1];
    [_nbotxt setIntValue:ext->get_nb()];
    [_hortxt setDoubleValue:ext->get_horizontal()];
    [_vertxt setDoubleValue:ext->get_vertical()];
    [_inschk setIntValue:ext->get_insurf()];

bGenericUnit*	u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char			val[256];
    u->short_name(val);
    [_horlbl setCharValue:val];
    [_verlbl setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[LineUpWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapLineUp*  ext=(bXMapLineUp*)_ext;

    ext->set_kind([_dirpop indexOfSelectedItem]+1);
    ext->set_nb([_nbotxt intValue]);
    ext->set_horizontal([_hortxt doubleValue]);
    ext->set_vertical([_vertxt doubleValue]);
    ext->set_insurf([_inschk intValue]);

    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapLineUp* ext,
					  long* code){
LineUpWindowController	*controller;
NSAutoreleasePool       *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[LineUpWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
