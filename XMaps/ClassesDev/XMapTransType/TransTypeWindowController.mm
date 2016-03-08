//----------------------------------------------------------------------------
// File : TransTypeWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap type transfert window controller
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
// 15/02/2016 creation.
//----------------------------------------------------------------------------

#import "TransTypeWindowController.h"
#import "bXMapTransType.h" 
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
@implementation TransTypeWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[TransTypeWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[TransTypeWindowController awakeFromNib]",true);
bXMapTransType* ext=(bXMapTransType*)_ext;
transtype_prm   prm;
    ext->get_infos(&prm);
    if(prm.type_dest>((bGenericMacMapApp*)ext->getapp())->typesMgr()->count()){
        prm.type_dest=1;
    }

    NSPopupButtonRemoveAllItems(_typpop);
    NSPopupButtonPopulateWithTypes(_typpop,(bGenericMacMapApp*)_ext->getapp(),kBaseNoKind,prm.type_dest);

    [_kepbtn setIntValue:prm.keep_objects];
    [_crfbtn setIntValue:prm.create_fields];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[TransTypeWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
    bXMapTransType* ext=(bXMapTransType*)_ext;
    transtype_prm   prm;
    ext->get_infos(&prm);
    prm.type_dest=[_typpop indexOfSelectedItem]+1;
    prm.keep_objects=[_kepbtn intValue];
    prm.create_fields=[_crfbtn intValue];
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
void runCocoaAppModal(bXMapTransType* ext,
					  long* code){
TransTypeWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[TransTypeWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
