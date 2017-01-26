//----------------------------------------------------------------------------
// File : AssociationWithFieldWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap AssociationWithField window controller
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
// 30/06/2016 creation.
//----------------------------------------------------------------------------

#import "AssociationWithFieldWindowController.h"
#import "bXMapAssociationWithField.h"
#import "CocoaStuff.h"

#import <mox_intf/NSUIUtils.h>
#import <mox_intf/bStdAlert.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation AssociationWithFieldWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[AssociationWithFieldWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[AssociationWithFieldWindowController awakeFromNib]",true);
bXMapAssociationWithField*  ext=(bXMapAssociationWithField*)_ext;
associationwithfield_prm    prm=ext->get_data();
   
    if((prm.field<0)||(prm.field>ext->get_type()->fields()->count())){
        prm.field=kOBJ_Name_;
    }
    NSPopupButtonRemoveAllItems(_fldpop);
    NSPopupButtonPopulateWithFields(_fldpop,ext->get_type(),kOBJ_Name_,prm.field-kOBJ_Name_+1);

    [_nhichk setIntValue:prm.needhier];
    [_mintxt setDoubleValue:prm.lmin];
    [_maxtxt setDoubleValue:prm.lmax];

bGenericUnit*	u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char			val[256];
    u->short_name(val);
    [_minlbl setCharValue:val];
    [_maxlbl setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[AssociationWithFieldWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapAssociationWithField*  ext=(bXMapAssociationWithField*)_ext;
associationwithfield_prm    prm;

    prm.field=[_fldpop indexOfSelectedItem]+kOBJ_Name_;

    prm.needhier=[_nhichk intValue];
    prm.lmin=[_mintxt doubleValue];
    prm.lmax=[_maxtxt doubleValue];
    
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
void runCocoaAppModal(bXMapAssociationWithField* ext,
					  long* code){
AssociationWithFieldWindowController	*controller;
NSAutoreleasePool                       *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[AssociationWithFieldWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
