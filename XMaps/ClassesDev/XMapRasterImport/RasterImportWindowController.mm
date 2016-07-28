//----------------------------------------------------------------------------
// File : RasterImportWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap raster import window controller
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
// 14/03/2016 creation.
//----------------------------------------------------------------------------

#import "RasterImportWindowController.h"
#import "bXMapRasterImport.h" 
#import "CocoaStuff.h" 

#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation RasterImportWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[RasterImportWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[RasterImportWindowController awakeFromNib]",true);
bXMapRasterImport* ext=(bXMapRasterImport*)_ext;
   
    [_chcpop selectItemAtIndex:ext->get_import_type()-1];
    [self chooseMethod:self];
    
d2dvertex   loc=ext->get_topleft();
    [_xtltxt setDoubleValue:loc.x];
    [_ytltxt setDoubleValue:loc.y];
    
    loc=ext->get_botright();
    [_xbrtxt setDoubleValue:loc.x];
    [_ybrtxt setDoubleValue:loc.y];
    
    [_scltxt setDoubleValue:ext->get_scale()];
    
bGenericUnit*   u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char            val[256];
    u->short_name(val);
    [_xtulbl setCharValue:val];
    [_ytulbl setCharValue:val];
    [_xbulbl setCharValue:val];
    [_ybulbl setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[RasterImportWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapRasterImport*  ext=(bXMapRasterImport*)_ext;
d2dvertex           loc;
    
    ext->set_import_type([_chcpop indexOfSelectedItem]+1);
    
    loc.x=[_xtltxt doubleValue];
    loc.y=[_ytltxt doubleValue];
    ext->set_topleft(loc);

    loc.x=[_xbrtxt doubleValue];
    loc.y=[_ybrtxt doubleValue];
    ext->set_botright(loc);

    ext->set_scale([_scltxt doubleValue]);

    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)chooseMethod:(id)sender{
    [_xbrtxt setHidden:([_chcpop indexOfSelectedItem]==1)];
    [_xbrlbl setHidden:([_chcpop indexOfSelectedItem]==1)];
    [_xbulbl setHidden:([_chcpop indexOfSelectedItem]==1)];
    [_ybrtxt setHidden:([_chcpop indexOfSelectedItem]==1)];
    [_ybrlbl setHidden:([_chcpop indexOfSelectedItem]==1)];
    [_ybulbl setHidden:([_chcpop indexOfSelectedItem]==1)];

    [_scltxt setHidden:([_chcpop indexOfSelectedItem]==0)];
    [_scllbl setHidden:([_chcpop indexOfSelectedItem]==0)];
 }

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapRasterImport* ext,
					  long* code){
RasterImportWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[RasterImportWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
