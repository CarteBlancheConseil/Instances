//----------------------------------------------------------------------------
// File : TranslationWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap Translation window controller
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
// 22/07/2016 creation.
//----------------------------------------------------------------------------

#import "TranslationWindowController.h"
#import "bXMapTranslation.h"
#import "CocoaStuff.h"

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation TranslationWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[TranslationWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[TranslationWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapTranslation*   ext=(bXMapTranslation*)_ext;
translation_prm     prm=ext->get_data();
    
    if(gapp->cntMgr()->count()>0){
bGenericGeoElement*	o;
ivertices*			vxs;
d2dvertex			dvx;
        gapp->cntMgr()->elements()->get(1,&o);
        o->getVertices(&vxs);
        gapp->locConverter()->convert(&dvx,&vxs->vx.vx2[0]);
        prm.x=dvx.x;
        prm.y=dvx.y;
        [_wchpop selectItemAtIndex:1];
    }

    [_xxxtxt setDoubleValue:prm.x];
    [_yyytxt setDoubleValue:prm.y];
    
bGenericUnit*	u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char			val[256];
    u->short_name(val);
    [_xxxunt setCharValue:val];
    [_yyyunt setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[TranslationWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapTranslation*   ext=(bXMapTranslation*)_ext;
translation_prm     prm;
    
    prm.kind=[_wchpop indexOfSelectedItem]+1;
    prm.x=[_xxxtxt doubleValue];
    prm.y=[_yyytxt doubleValue];
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
void runCocoaAppModal(bXMapTranslation* ext,
					  long* code){
TranslationWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[TranslationWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
