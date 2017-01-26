//----------------------------------------------------------------------------
// File : ScaleWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap Scale window controller
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
// 21/07/2016 creation.
//----------------------------------------------------------------------------

#import "ScaleWindowController.h"
#import "bXMapScale.h"
#import "CocoaStuff.h"

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ScaleWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ScaleWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ScaleWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapScale*         ext=(bXMapScale*)_ext;
scale_prm           prm=ext->get_data();

    [_hortxt setDoubleValue:prm.cx*100.0];
    [_vertxt setDoubleValue:prm.cy*100.0];
    
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
    
    [self doChooseMode:_wchpop];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[ScaleWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseMode:(id)sender{
    [_xxxlbl setHidden:[_wchpop indexOfSelectedItem]==0];
    [_xxxtxt setHidden:[_wchpop indexOfSelectedItem]==0];
    [_xxxunt setHidden:[_wchpop indexOfSelectedItem]==0];
    [_yyylbl setHidden:[_wchpop indexOfSelectedItem]==0];
    [_yyytxt setHidden:[_wchpop indexOfSelectedItem]==0];
    [_yyyunt setHidden:[_wchpop indexOfSelectedItem]==0];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapScale*         ext=(bXMapScale*)_ext;
scale_prm           prm;

    if([_wchpop indexOfSelectedItem]==1){
        prm.x=[_xxxtxt doubleValue];
        prm.y=[_yyytxt doubleValue];
    }
    else{
i2dvertex			ivx;
d2dvertex			dvx;
        ext->center(&ivx);
        gapp->locConverter()->convert(&dvx,&ivx);
        prm.x=dvx.x;
        prm.y=dvx.y;
    }

    prm.cx=[_hortxt doubleValue]/100.0;
    prm.cy=[_vertxt doubleValue]/100.0;

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
void runCocoaAppModal(bXMapScale* ext,
					  long* code){
ScaleWindowController	*controller;
NSAutoreleasePool           *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[ScaleWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
