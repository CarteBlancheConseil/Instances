//----------------------------------------------------------------------------
// File : MakePolyWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap MakePoly window controller
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

#import "MakePolyWindowController.h"
#import "bXMapMakePoly.h"
#import "CocoaStuff.h"

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/ext_utils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation MakePolyWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[MakePolyWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[MakePolyWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapMakePoly*  ext=(bXMapMakePoly*)_ext;
makepoly_prm    prm=ext->get_data();
    
    if(prm.justo){
        
    }
    else if(gapp->cntMgr()->count()>0){
bGenericGeoElement*	o;
ivertices*			vxs;
        gapp->cntMgr()->elements()->get(1,&o);
        o->getVertices(&vxs);
        gapp->locConverter()->convert(&prm.o,&vxs->vx.vx2[0]);
    }
    else{
i2dvertex	vx;
        gapp->mapIntf()->screenCenter(&vx);
        gapp->locConverter()->convert(&prm.o,&vx);
    }

    [_xxxtxt setDoubleValue:prm.o.x];
    [_yyytxt setDoubleValue:prm.o.y];
    [_radtxt setDoubleValue:prm.sz];
    [_nbstxt setIntValue:prm.nb];
    
bGenericUnit*	u=((bGenericMacMapApp*)ext->getapp())->distMgr()->get();
char			val[256];
    u->short_name(val);
    [_xxxlbl setCharValue:val];
    [_yyylbl setCharValue:val];
    if(prm.sui==1){
        sprintf(val,"cm*");
    }
    [_radlbl setCharValue:val];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[MakePolyWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapMakePoly*  ext=(bXMapMakePoly*)_ext;
makepoly_prm    prm=ext->get_data();
    
    prm.o.x=[_xxxtxt doubleValue];
    prm.o.y=[_yyytxt doubleValue];
    prm.sz=[_radtxt doubleValue];
    prm.nb=[_nbstxt intValue];
   
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
void runCocoaAppModal(bXMapMakePoly* ext,
					  long* code){
MakePolyWindowController	*controller;
NSAutoreleasePool       *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[MakePolyWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
