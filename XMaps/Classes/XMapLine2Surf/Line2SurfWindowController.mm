//----------------------------------------------------------------------------
// File : Line2SurfWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap Line2Surf window controller
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
// 01/07/2016 creation.
//----------------------------------------------------------------------------

#import "Line2SurfWindowController.h"
#import "bXMapLine2Surf.h"
#import "CocoaStuff.h"

#import <mox_intf/ext_utils.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation Line2SurfWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[Line2SurfWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[Line2SurfWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=NthTypeOfKind(gapp,1,kBaseKindPolyline);

    NSPopupButtonRemoveAllItems(_limpop);
    NSPopupButtonPopulateWithTypes(_limpop,
                                   gapp,
                                   kBaseKindPolyline,
                                   tp->index());

    tp=NthTypeOfKind(gapp,1,kBaseKindPolygon);
    NSPopupButtonRemoveAllItems(_srfpop);
    NSPopupButtonPopulateWithTypes(_srfpop,
                                   gapp,
                                   kBaseKindPolygon,
                                   tp->index());
    
    [self doSurfType:_srfpop];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[Line2SurfWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doSurfType:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*       tp=gapp->typesMgr()->get([_srfpop indexOfSelectedItem]+1);

    NSPopupButtonRemoveAllItems(_stppop);
    NSPopupButtonPopulateWithConstraints(_stppop,tp,kOBJ_SubType_,1);
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapLine2Surf*  ext=(bXMapLine2Surf*)_ext;
    ext->set_data([_limpop indexOfSelectedItem]+1,
                  [_srfpop indexOfSelectedItem]+1,
                  [_stppop indexOfSelectedItem]+1);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapLine2Surf* ext,
					  long* code){
Line2SurfWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[Line2SurfWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
