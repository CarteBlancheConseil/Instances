//----------------------------------------------------------------------------
// File : ToolsWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Tools XMapBox window controller
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
// 31/12/2014 creation.
//----------------------------------------------------------------------------

#import "ToolsWindowController.h"
#import "bXBoxTools.h"
#import "CocoaStuff.h"

#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/endian.h>
#import <mox_intf/bGenericTool.h>

#import <mox_intf/NSContextualMenuWrappers.h>
#import <mox_intf/MacMapCWrappers.h>

#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
//
// ------------
#ifdef __LITTLE_ENDIAN__
#define kMenuConfigSignature		'TlMC'
#define kCursorTrackSignature		'CrTk'
#else
#define kMenuConfigSignature		'CMlT'
#define kCursorTrackSignature		'kTrC'
#endif

enum{
    kXMapToolWdToolPerLine	=4,
    kXMapToolWdCaseHSize	=26,
    kXMapToolWdCaseVSize	=22
};

#define kXMapToolWdNavigationMsg	@"navigation"
#define kXMapToolWdGeometryMsg		@"geometry"
#define kXMapToolWdPresentationMsg	@"presentation"

// ---------------------------------------------------------------------------
//
// -----------
static int tool_count(bGenericMacMapApp* gapp, int clss){
int				k=0;
bGenericTool*	ext;
    
    for(int i=1;i<=gapp->toolMgr()->count();i++){
        ext=(bGenericTool*)(void*)gapp->toolMgr()->get(i);
        if(ext->tool_class()==clss){
            k++;
        }
    }
    return(k);
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolsPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolsWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[ToolsWindowController init]",true);
	self=[super init];
	if(self){
        _pop=NO;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolsWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
bGenericMacMapApp*
            gapp=(bGenericMacMapApp*)_ext->getapp();
int         signs[]={kToolNav,kToolGeom,kToolPres};
NSRect      frameOtherBox;
NSRect      btnBox=NSMakeRect(0,0,kXMapToolWdCaseHSize,kXMapToolWdCaseVSize);
NSButton*   btn;
long        k,n,nl;
CGFloat     h,v=0;
NSView*     viw;
bool        b=false;
    
bGenericTool*   ext=(bGenericTool*)(void*)gapp->xmapMgr()->find(kCursorTrackSignature);
    if(ext){
        ext->process(kExtProcessCallGetData,&b);
    }
    [_trk_btn setIntValue:b];
    
    for(long j=0;j<3;j++){
        n=tool_count(gapp,signs[j]);
        if(n==0){
            [self hide:j];
            continue;
        }
        nl=ceil((CGFloat)n/(CGFloat)kXMapToolWdToolPerLine);
        [self sizeBoxAtIndex:j toSize:nl*kXMapToolWdCaseVSize];
        
        switch(j){
            case 0:
                viw=_nav_viw;
                [_nav_btn setTitle:NSLocalizedStringFromTableInBundle(kXMapToolWdNavigationMsg,nil,[NSBundle mainBundle],nil)];
                break;
            case 1:
                viw=_geo_viw;
                [_geo_btn setTitle:NSLocalizedStringFromTableInBundle(kXMapToolWdGeometryMsg,nil,[NSBundle mainBundle],nil)];
                break;
            default:
                viw=_prs_viw;
                [_prs_btn setTitle:NSLocalizedStringFromTableInBundle(kXMapToolWdPresentationMsg,nil,[NSBundle mainBundle],nil)];
                break;
        }
        frameOtherBox=[viw frame];
        
        v=kXMapToolWdCaseVSize;
        k=0;
NSImage*        img;
        for(long i=1;i<=gapp->toolMgr()->count();i++){
            ext=(bGenericTool*)(void*)gapp->toolMgr()->get(i);
            if(ext->tool_class()==signs[j]){
                if(k==kXMapToolWdToolPerLine){
                    k=0;
                    v+=kXMapToolWdCaseVSize;
                }
                h=k*kXMapToolWdCaseHSize;
                btnBox.origin.x=h;
                btnBox.origin.y=frameOtherBox.size.height-v/*+1*/;
                
                btnBox.size.width++;
                btnBox.size.height++;
                btn=[[[NSButton alloc] initWithFrame:btnBox] autorelease];
                btnBox.size.width--;
                btnBox.size.height--;
                [viw addSubview: btn];
                
                img=[[[NSImage alloc] initWithCGImage:ext->symb() size:NSZeroSize] autorelease];

                [btn setImage:img];
                [btn setButtonType:NSPushOnPushOffButton];
                [btn setBezelStyle:NSShadowlessSquareBezelStyle];
                [btn setTag:i];

                [btn setTarget:self];
                [btn setAction:@selector(doTool:)];
                
                [btn setContinuous:YES];
                [btn setPeriodicDelay:0.25 interval:1];

                k++;
            }
        }
    }

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)checkMacMapEvent{
	[super checkMacMapEvent];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[ToolsWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doNav:(id)sender{
NSWindow*   window=[sender window];
NSRect      frameWinOld=[window frame];
NSRect      frameOtherBox=[_nav_viw frame];
NSRect      ctrlBox;
CGFloat     heightOtherBoxWithMargin=frameOtherBox.size.height;
    
    switch([sender state]) {
        case NSOnState:
            [window setFrame:NSMakeRect(frameWinOld.origin.x,
                                        frameWinOld.origin.y-heightOtherBoxWithMargin,
                                        frameWinOld.size.width,
                                        frameWinOld.size.height+heightOtherBoxWithMargin) display:YES];
            [_nav_viw setHidden:NO];
            
            ctrlBox=[_geo_btn frame];
            ctrlBox.origin.y-=heightOtherBoxWithMargin;
            [_geo_btn setFrame:ctrlBox];
            ctrlBox=[_geo_viw frame];
            ctrlBox.origin.y-=heightOtherBoxWithMargin;
            [_geo_viw setFrame:ctrlBox];
            
            ctrlBox=[_prs_btn frame];
            ctrlBox.origin.y-=heightOtherBoxWithMargin;
            [_prs_btn setFrame:ctrlBox];
            ctrlBox=[_prs_viw frame];
            ctrlBox.origin.y-=heightOtherBoxWithMargin;
            [_prs_viw setFrame:ctrlBox];
            break;
        case NSOffState:
            [window setFrame:NSMakeRect(frameWinOld.origin.x,
                                        frameWinOld.origin.y+heightOtherBoxWithMargin,
                                        frameWinOld.size.width,
                                        frameWinOld.size.height-heightOtherBoxWithMargin) display:YES];
            [_nav_viw setHidden:YES];
            
            ctrlBox=[_geo_btn frame];
            ctrlBox.origin.y+=heightOtherBoxWithMargin;
            [_geo_btn setFrame:ctrlBox];
            ctrlBox=[_geo_viw frame];
            ctrlBox.origin.y+=heightOtherBoxWithMargin;
            [_geo_viw setFrame:ctrlBox];
            
            ctrlBox=[_prs_btn frame];
            ctrlBox.origin.y+=heightOtherBoxWithMargin;
            [_prs_btn setFrame:ctrlBox];
            ctrlBox=[_prs_viw frame];
            ctrlBox.origin.y+=heightOtherBoxWithMargin;
            [_prs_viw setFrame:ctrlBox];
            
            break;
        default:
            break;
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doGeom:(id)sender{
NSWindow*   window=[sender window];
NSRect      frameWinOld=[window frame];
NSRect      frameOtherBox=[_geo_viw frame];
NSRect      ctrlBox;
CGFloat     heightOtherBoxWithMargin=frameOtherBox.size.height;
    
    switch([sender state]) {
        case NSOnState:
            [window setFrame:NSMakeRect(frameWinOld.origin.x,
                                        frameWinOld.origin.y-heightOtherBoxWithMargin,
                                        frameWinOld.size.width,
                                        frameWinOld.size.height+heightOtherBoxWithMargin) display:YES];
            [_geo_viw setHidden:NO];
            
            ctrlBox=[_prs_btn frame];
            ctrlBox.origin.y-=heightOtherBoxWithMargin;
            [_prs_btn setFrame:ctrlBox];
            ctrlBox=[_prs_viw frame];
            ctrlBox.origin.y-=heightOtherBoxWithMargin;
            [_prs_viw setFrame:ctrlBox];
            break;
        case NSOffState:
            [window setFrame:NSMakeRect(frameWinOld.origin.x,
                                        frameWinOld.origin.y+heightOtherBoxWithMargin,
                                        frameWinOld.size.width,
                                        frameWinOld.size.height-heightOtherBoxWithMargin) display:YES];
            [_geo_viw setHidden:YES];
            
            ctrlBox=[_prs_btn frame];
            ctrlBox.origin.y+=heightOtherBoxWithMargin;
            [_prs_btn setFrame:ctrlBox];
            ctrlBox=[_prs_viw frame];
            ctrlBox.origin.y+=heightOtherBoxWithMargin;
            [_prs_viw setFrame:ctrlBox];
            
            break;
        default:
            break;
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPres:(id)sender{
NSWindow*   window=[sender window];
NSRect      frameWinOld=[window frame];
NSRect      frameOtherBox=[_prs_viw frame];
CGFloat     heightOtherBoxWithMargin=frameOtherBox.size.height;

    switch([sender state]) {
        case NSOnState:
            [window setFrame:NSMakeRect(frameWinOld.origin.x,
                                        frameWinOld.origin.y-heightOtherBoxWithMargin,
                                        frameWinOld.size.width,
                                        frameWinOld.size.height+heightOtherBoxWithMargin) display:YES];
            [_prs_viw setHidden:NO];
            break;
        case NSOffState:
            [window setFrame:NSMakeRect(frameWinOld.origin.x,
                                        frameWinOld.origin.y+heightOtherBoxWithMargin,
                                        frameWinOld.size.width,
                                        frameWinOld.size.height-heightOtherBoxWithMargin) display:YES];
            [_prs_viw setHidden:YES];
            break;
        default:
            break;
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doTool:(id)sender{
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
    
    gapp->toolMgr()->set_current([sender tag]);

bGenericTool*   ext=(bGenericTool*)CurTool(gapp);
NSEvent*        event=[NSApp currentEvent];
    if(event!=nil){
        switch([event type]){
//            case NSRightMouseDown:{
//                _tm_("NSRightMouseDown");
//NSPoint             pt=[sender frame].origin;
//                    pt=[sender convertPoint:pt fromView:[sender superview]];
//                    pt=[sender convertPoint:pt fromView:nil];
//                    pt.x=fabs(pt.x);
//cocoaMenuPrm        prm;
//                    prm.wdIsCocoa=true;
//                    prm.inWindow=[self window];
//                    prm.location.x=pt.x;
//                    prm.location.y=pt.y;
//                    ext->process(kToolProcessCocoaMenu,&prm);
//                }
//                break;
            case NSLeftMouseDown:
//                _tm_("NSLeftMouseDown");
                break;
            case NSLeftMouseUp:
//                _tm_("NSLeftMouseUp");
                [sender setContinuous:YES];
                if([event clickCount]==2){
                    ext->edit(NULL);
                }
                else if(_pop){
NSPoint             pt=[sender frame].origin;
                    pt=[sender convertPoint:pt fromView:[sender superview]];
                    pt=[sender convertPoint:pt fromView:nil];
                    pt.x=fabs(pt.x);
cocoaMenuPrm        prm;
                    prm.wdIsCocoa=true;
                    prm.inWindow=[self window];
                    prm.location.x=pt.x;
                    prm.location.y=pt.y;
                    ext->process(kToolProcessCocoaMenu,&prm);
                }
                _pop=NO;
                break;
            case NSPeriodic:
//                _tm_("NSPeriodic");
                _pop=YES;
                break;
        }
    }
    [sender setIntValue:1];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doMenuConfig:(id)sender{
    SendCommandToApplication('TlMC');
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doEnableTrack:(id)sender{
    SendCommandToApplication('CrTk');
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
    [_nav_viw setNeedsDisplay:YES];
    [_geo_viw setNeedsDisplay:YES];
    [_prs_viw setNeedsDisplay:YES];
    [_nav_btn setNeedsDisplay:YES];
    [_geo_btn setNeedsDisplay:YES];
    [_prs_btn setNeedsDisplay:YES];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)hide:(long)index{
NSRect  vbox,bbox;
CGFloat val;
    if(index==0){
        vbox=[_nav_viw frame];
        bbox=[_nav_btn frame];
        val=vbox.size.height+bbox.size.height;
        
        vbox=[[self window] frame];
        [[self window] setFrame:NSMakeRect(vbox.origin.x,
                                           vbox.origin.y+val,
                                           vbox.size.width,
                                           vbox.size.height-val) display:NO];
        
        [_nav_viw setHidden:YES];
        [_nav_btn setHidden:YES];
        
        bbox=[_geo_btn frame];
        bbox.origin.y+=val;
        [_geo_btn setFrame:bbox];
        
        bbox=[_geo_viw frame];
        bbox.origin.y+=val;
        [_geo_viw setFrame:bbox];
        
        bbox=[_prs_btn frame];
        bbox.origin.y+=val;
        [_prs_btn setFrame:bbox];
        
        bbox=[_prs_viw frame];
        bbox.origin.y+=val;
        [_prs_viw setFrame:bbox];
        
    }
    else if(index==1){
        vbox=[_geo_viw frame];
        bbox=[_geo_btn frame];
        val=vbox.size.height+bbox.size.height;
        
        vbox=[[self window] frame];
        [[self window] setFrame:NSMakeRect(vbox.origin.x,
                                           vbox.origin.y+val,
                                           vbox.size.width,
                                           vbox.size.height-val) display:NO];
        
        [_geo_viw setHidden:YES];
        [_geo_btn setHidden:YES];
        
        bbox=[_prs_btn frame];
        bbox.origin.y+=val;
        [_prs_btn setFrame:bbox];
        
        bbox=[_prs_viw frame];
        bbox.origin.y+=val;
        [_prs_viw setFrame:bbox];
    }
    else if(index==2){
        vbox=[_prs_viw frame];
        bbox=[_prs_btn frame];
        val=vbox.size.height+bbox.size.height;
        
        vbox=[[self window] frame];
        [[self window] setFrame:NSMakeRect(vbox.origin.x,
                                           vbox.origin.y+val,
                                           vbox.size.width,
                                           vbox.size.height-val) display:NO];
        
        [_prs_viw setHidden:YES];
        [_prs_btn setHidden:YES];
        
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)sizeBoxAtIndex:(long)index toSize:(CGFloat)newSize{
NSRect  box;
CGFloat val;
    if(index==0){
        box=[_nav_viw frame];
        val=box.size.height-newSize;
        
        box=[[self window] frame];
        [[self window] setFrame:NSMakeRect(box.origin.x,
                                           box.origin.y+val,
                                           box.size.width,
                                           box.size.height-val) display:NO];
        
        box=[_nav_viw frame];
        box.size.height=newSize;
        box.origin.y+=val;
        [_nav_viw setFrame:box];
        
        box=[_geo_btn frame];
        box.origin.y+=val;
        [_geo_btn setFrame:box];
        
        box=[_geo_viw frame];
        box.origin.y+=val;
        [_geo_viw setFrame:box];
        
        box=[_prs_btn frame];
        box.origin.y+=val;
        [_prs_btn setFrame:box];
        
        box=[_prs_viw frame];
        box.origin.y+=val;
        [_prs_viw setFrame:box];
    }
    else if(index==1){
        box=[_geo_viw frame];
        val=box.size.height-newSize;
        
        box=[[self window] frame];
        [[self window] setFrame:NSMakeRect(box.origin.x,
                                           box.origin.y+val,
                                           box.size.width,
                                           box.size.height-val) display:NO];
        
        box=[_geo_viw frame];
        box.size.height=newSize;
        box.origin.y+=val;
        [_geo_viw setFrame:box];
        
        box=[_prs_btn frame];
        box.origin.y+=val;
        [_prs_btn setFrame:box];
        
        box=[_prs_viw frame];
        box.origin.y+=val;
        [_prs_viw setFrame:box];
    }
    else if(index==2){
        box=[_prs_viw frame];
        val=box.size.height-newSize;
        
        box=[[self window] frame];
        [[self window] setFrame:NSMakeRect(box.origin.x,
                                           box.origin.y+val,
                                           box.size.width,
                                           box.size.height-val) display:NO];
        
        box=[_prs_viw frame];
        box.size.height=newSize;
        box.origin.y+=val;
        [_prs_viw setFrame:box];
    }
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(void)prepareForClose{	
	[super prepareForClose];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)idle{
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
    if(_cur!=gapp->toolMgr()->get_current()){
NSArray*    subviews=[_nav_viw subviews];
        for(NSButton *btn in subviews){
            [btn setIntValue:([btn tag]==gapp->toolMgr()->get_current())];
        }
        subviews=[_geo_viw subviews];
        for(NSButton *btn in subviews){
            [btn setIntValue:([btn tag]==gapp->toolMgr()->get_current())];
        }
        subviews=[_prs_viw subviews];
        for(NSButton *btn in subviews){
            [btn setIntValue:([btn tag]==gapp->toolMgr()->get_current())];
        }
        
char	buff[256],name[256];
        gapp->toolMgr()->ext_name(gapp->toolMgr()->get_current(),buff);
        sprintf(name," %s",buff);
        [_glb_btn setTitle:[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding]];
        [_glb_btn setTag:gapp->toolMgr()->get_current()];
    }
    _cur=gapp->toolMgr()->get_current();
}

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
// ------------
@end

#pragma mark ---- CPP/Carbon Entry Point ----
// ---------------------------------------------------------------------------
// 
// ------------
void* initializeCocoa(void* gapp, 
					  void* ext) {
ToolsWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[ToolsWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

