//----------------------------------------------------------------------------
// File : AssociationWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap Association window controller
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
// 06/04/2016 creation.
//----------------------------------------------------------------------------

#import "AssociationWindowController.h"
#import "bXMapAssociation.h"
#import "CocoaStuff.h"
#import <MacMapSuite/bTrace.h> 
#import <mox_intf/bGenericMacMapApp.h> 
#import <mox_intf/Carb_Utils.h> 
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h> 
#import <mox_intf/NSUIUtils.h> 
#import <mox_intf/mm_messages.h>
#import <mox_intf/mm_errors.h>
#import <mox_intf/bStdAlert.h>
#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation AssociationWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[AssociationWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[AssociationWindowController awakeFromNib]",true);
bXMapAssociation*   ext=(bXMapAssociation*)_ext;
association_prm     prm=ext->get_data();
    
    [_dsttxt setDoubleValue:prm.dmax];
    [_delchk setIntValue:prm.kill];

bGenericUnit*	u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char			val[256];
    u->short_name(val);
    [_untlbl setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[AssociationWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapAssociation*   ext=(bXMapAssociation*)_ext;
association_prm     prm;

    prm.dmax=[_dsttxt doubleValue];
    prm.kill=[_delchk intValue];
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
void runCocoaAppModal(bXMapAssociation* ext,
					  long* code){
AssociationWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[AssociationWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
