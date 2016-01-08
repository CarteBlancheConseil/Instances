//----------------------------------------------------------------------------
// File : CoordWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Coordinates XMapBox window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 1997-2015 Carte Blanche Conseil.
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
// 22/01/2015 creation.
//----------------------------------------------------------------------------

#import "CoordWindowController.h"
#import "bXBoxCoord.h"
#import "CocoaStuff.h"

#import <mox_intf/Carb_Utils.h>
#import <mox_intf/endian.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/ext_utils.h>

#import <MacMapSuite/bTrace.h>
#import <MacMapSuite/C_Utils.h>

#import <MacMapStats/MacMapStats.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation CoordPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation CoordWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[CoordWindowController init]",true);
	self=[super init];
	if(self){
        _from=NULL;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[CoordWindowController dealloc]",true);
_tm_((void*)self);
    if(_from){
        delete _from;
        _from=NULL;
    }
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
    [super awakeFromNib];
bGenericMacMapApp*
        gapp=(bGenericMacMapApp*)_ext->getapp();
bool    init;
NSRect  vbox;
    _from=new bStdProj(gapp->document()->srid(),&init);
    if(!init){
        delete _from;
        _from=NULL;
        vbox=[[self window] frame];
        [[self window] setFrame:NSMakeRect(vbox.origin.x,
                                           vbox.origin.y+22,
                                           vbox.size.width,
                                           vbox.size.height-22) display:NO];
    }
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[CoordWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Interface XMapBox ----
// ---------------------------------------------------------------------------
//
// ------------
-(void)setExt:(bStdNSXBox*)ext{
    _ext=ext;
CGRect	bnds;
    
    _ext->get_bounds(&bnds);
    if(!CGRectIsEmpty(bnds)){
NSRect	newbnds=[[self window] frame];
        newbnds.origin.x=bnds.origin.x;
        newbnds.origin.y=bnds.origin.y;
        [[self window] setFrame:newbnds display:NO];
    }
    else{
        bnds=NSRectToCGRect([[self window] frame]);
        _ext->set_bounds(&bnds);
    }
    
    [[self window] makeKeyAndOrderFront:self];
    [[self window] makeFirstResponder:self];
    [[self window] makeKeyWindow];
    
char	name[256];
    GetName(_ext,name);
    strrep(name,"…","");
    strrep(name,"...","");
    [[self window] setTitle:[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding]];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)report:(i2dvertex)vx{
bGenericMacMapApp*
            gapp=(bGenericMacMapApp*)_ext->getapp();
d2dvertex	dvx;
char		sx[256];
char		sy[256];
char		slg[256]="";
char		sla[256]="";
int			d=gapp->document()->dist_pref_digits();
    
    gapp->locConverter()->convert(&dvx,&vx);
    sprintf(sx,"%.*f",d,dvx.x);
    sprintf(sy,"%.*f",d,dvx.y);
    [_xxx_txt setCharValue:sx];
    [_yyy_txt setCharValue:sy];

    if(_from){
dvertices	dvxs={_2D_VX,1,0,NULL};
        
        dvxs.vx.vx2[0]=dvx;
        _to.transform(*_from,&dvxs);
        sprintf(slg,"%f",dvxs.vx.vx2[0].x);
        sprintf(sla,"%f",dvxs.vx.vx2[0].y);
        [_lon_txt setCharValue:slg];
        [_lat_txt setCharValue:sla];
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)erase{
    [_xxx_txt setStringValue:@""];
    [_yyy_txt setStringValue:@""];
    [_lon_txt setStringValue:@""];
    [_lat_txt setStringValue:@""];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

#pragma mark ---- CPP/Carbon Entry Point ----
// ---------------------------------------------------------------------------
// 
// ------------
void* initializeCocoa(void* gapp, 
					  void* ext) {
CoordWindowController	*controller;
NSAutoreleasePool		*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[CoordWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

// ---------------------------------------------------------------------------
//
// ------------
void reportCocoa(void* instance,
                 i2dvertex vx){
NSAutoreleasePool		*localPool;
CoordWindowController	*mmc=(CoordWindowController*)instance;
    
    if(mmc==NULL){
        return;
    }
    localPool=[[NSAutoreleasePool alloc] init];
    [mmc report:vx];
    [localPool release];
}

// ---------------------------------------------------------------------------
//
// ------------
void eraseCocoa(void* instance){
NSAutoreleasePool		*localPool;
CoordWindowController	*mmc=(CoordWindowController*)instance;
    
    if(mmc==NULL){
        return;
    }
    localPool=[[NSAutoreleasePool alloc] init];
    [mmc erase];
    [localPool release];
}


