//----------------------------------------------------------------------------
// File : IGridWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap import grid window controller
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

#import "IGridWindowController.h"
#import "bXMapIGrid.h" 
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
@implementation IGridWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[IGridWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[IGridWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapIGrid*         ext=(bXMapIGrid*)_ext;
    ext->get_infos(&_prm);
    
    NSPopupButtonPopulateWithTypes(_linpop,(bGenericMacMapApp*)_ext->getapp(),kBaseKindPolyline,1);
    NSPopupButtonPopulateWithTypes(_gonpop,(bGenericMacMapApp*)_ext->getapp(),kBaseKindPolygon,1);
    NSPopupButtonPopulateWithTypes(_pctpop,(bGenericMacMapApp*)_ext->getapp(),kBaseKindPoint,1);
    NSPopupButtonPopulateWithTypes(_txtpop,(bGenericMacMapApp*)_ext->getapp(),kBaseKindText,1);
    NSPopupButtonPopulateWithTypes(_rstpop,(bGenericMacMapApp*)_ext->getapp(),kBaseKindRaster,1);

    [_linpop selectItemAtIndex:gapp->typesMgr()->index(_prm.t_line)];
    [_gonpop selectItemAtIndex:gapp->typesMgr()->index(_prm.t_poly)];
    [_pctpop selectItemAtIndex:gapp->typesMgr()->index(_prm.t_point)];
    [_txtpop selectItemAtIndex:gapp->typesMgr()->index(_prm.t_text)];
    [_rstpop selectItemAtIndex:gapp->typesMgr()->index(_prm.t_raster)];
    
char	name[512];
    GetProjName(_prm.srid,name);
    NSTextFieldSetValue(_prjtxt,name);
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[IGridWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseProj:(id)sender{
//_bTrace_("[IGridWindowController doChooseProj]",true);
    [[self window] setIsVisible:NO];
	if(GetAProj(&_prm.srid,true)){
char	name[512];
		GetProjName(_prm.srid,name);
        NSTextFieldSetValue(_prjtxt,name);
	}
    [[self window] setIsVisible:YES];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapIGrid*         ext=(bXMapIGrid*)_ext;

    _prm.t_line=[_linpop indexOfSelectedItem]?gapp->typesMgr()->get([_linpop indexOfSelectedItem])->tid():0;
    _prm.t_poly=[_gonpop indexOfSelectedItem]?gapp->typesMgr()->get([_gonpop indexOfSelectedItem])->tid():0;
    _prm.t_point=[_pctpop indexOfSelectedItem]?gapp->typesMgr()->get([_pctpop indexOfSelectedItem])->tid():0;
    _prm.t_text=[_txtpop indexOfSelectedItem]?gapp->typesMgr()->get([_txtpop indexOfSelectedItem])->tid():0;
    _prm.t_raster=[_rstpop indexOfSelectedItem]?gapp->typesMgr()->get([_rstpop indexOfSelectedItem])->tid():0;
    ext->set_infos(_prm);
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapIGrid* ext,
					  long* code){
IGridWindowController	*controller;
NSAutoreleasePool       *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[IGridWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
