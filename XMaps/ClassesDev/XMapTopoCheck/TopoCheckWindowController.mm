//----------------------------------------------------------------------------
// File : TopoCheckWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap clone detector window controller
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
// 08/03/2016 creation.
//----------------------------------------------------------------------------

#import "TopoCheckWindowController.h"
#import "bXMapTopoCheck.h" 
#import "CocoaStuff.h" 

#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation TopoCheckWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[TopoCheckWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[TopoCheckWindowController awakeFromNib]",true);
bGenericMacMapApp*      gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapTopoCheck*         ext=(bXMapTopoCheck*)_ext;

    NSPopupButtonRemoveAllItems(_typpop);
    NSPopupButtonPopulateWithTypes(_typpop,gapp,kBaseNoKind,0);

bGenericType*	tp;
    for(long i=1;i<=ext->types().count();i++){
        ext->types().get(i,&tp);
        if(tp){
            [[_typpop itemAtIndex:i] setState:NSOnState];
        }
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[TopoCheckWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapTopoCheck*     ext=(bXMapTopoCheck*)_ext;
bGenericType*       tp;
    
    for(long i=1;i<[_typpop numberOfItems];i++){
        if([[_typpop itemAtIndex:i] state]==NSOnState){
            tp=gapp->typesMgr()->get(i);
        }
        else{
            tp=NULL;
        }
        ext->types().put(i,&tp);
    }

    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doCheckTypes:(id)sender{
    [[_typpop selectedItem] setState:(![[_typpop selectedItem] state])];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapTopoCheck* ext,
					  long* code){
TopoCheckWindowController   *controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[TopoCheckWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
