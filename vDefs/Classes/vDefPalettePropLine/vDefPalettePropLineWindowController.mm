//----------------------------------------------------------------------------
// File : vDefPalettePropLineWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : proportionnal line vdef window controller
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
// 29/01/2013 creation.
//----------------------------------------------------------------------------

#import "vDefPalettePropLineWindowController.h"
#import "bvDefPalettePropLine.h"
#import "bvDefPropLineStyle.h"
#import "CocoaStuff.h"
#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>

#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/Color_Utils.h>
#import <mox_intf/xmldesc_utils.h>
#import <mox_intf/NSUIUtils.h> 
#import <mox_intf/CGUtils.h> 

#import <std_ext/bXMapStdIntf.h>

#import <vdef_lib/vdef_utils.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPalettePropLinePanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPalettePropLineWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPalettePropLineWindowController init]",true);
	self=[super init];
	if(self){
		_area=NO;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[vDefPalettePropLineWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPalettePropLineWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique
	NSPopupButtonPopulateWithDashes(_dsh_pop,_ext->type_get(),1);

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPalettePropLineWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCap:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doPutCap]",true);
bvDefPropLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_cap=[_cap_pop indexOfSelectedItem];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutJoin:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doPutJoin]",true);
bvDefPropLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_join=[_jon_pop indexOfSelectedItem];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doAddDash:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doAddDash]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext=gapp->xmapMgr()->find('DPck');
picker_prm			prm={_ext->type_get(),""};
char				val[256];
	
	if(ext->edit(&prm)){
		NSPopupButtonRemoveItemsFrom(_dsh_pop,2);
		NSPopupButtonPopulateWithDashes(_dsh_pop,_ext->type_get(),1);
		for(long i=1;i<=_ext->type_get()->fields()->count_param("dashes");i++){
			_ext->type_get()->fields()->get_param_name("dashes",i,val);
			if(strcmp(val,prm.name)==0){
				[_dsh_pop selectItemAtIndex:(i-1+2)];
			}
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDash:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doPutDash]",true);
bvDefPropLineStyle*	stl;
char				val[256]="";
long				idx=[_dsh_pop indexOfSelectedItem];
	
	if(idx>1){
		_ext->type_get()->fields()->get_param_name("dashes",idx+1-2,val);
	}
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		strcpy(stl->_dsh,val);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutMiter:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doPutMiter]",true);
bvDefPropLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_limit=[_mit_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDec:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doPutDec]",true);
bvDefPropLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_dec=[_dec_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doPutDecKind:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doPutDecKind]",true);
bvDefPropLineStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        _ext->runs().get(i,&stl);
        stl->_wdec=[_dec_pop indexOfSelectedItem]==1;
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSmoothing:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doPutSmoothing]",true);
bvDefPropLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_smooth=[_smt_chk intValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseFillKind:(id)sender{
_bTrace_("[vDefPalettePropLineWindowController doChooseFillKind]",true);	
bvDefPropLineStyle*	stl;
	[_fil_tab selectTabViewItemAtIndex:[_fil_pop indexOfSelectedItem]];
	
	if([_fil_pop indexOfSelectedItem]>1){
		[_tab selectTabViewItemAtIndex:1];
		_uclss=YES;
	}
	else{
		_uclss=NO;
	}
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if([_fil_pop indexOfSelectedItem]==0){
			stl->reset();
		}
		else if([_fil_pop indexOfSelectedItem]==1){
			stl->reset();
		}
		else{
		}
	}
	[self updateUI];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPalettePropLineWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefPropLineStyle*	stl=NULL;
	
	if(!_ext->runs().get(1,&stl)){
		[_fil_img setImage:NULL];
		return;
	}
	
	[_cap_pop selectItemAtIndex:stl->_cap];
	[_jon_pop selectItemAtIndex:stl->_join];
long	idx=getDashIndex(_ext->type_get(),stl->_dsh);
	if(idx>0){
		idx++;
	}
	[_dsh_pop selectItemAtIndex:idx];
	[_mit_fld setFloatValue:stl->_limit];
	[_dec_fld setFloatValue:stl->_dec];
    [_dec_pop selectItemAtIndex:stl->_wdec];
	[_smt_chk setIntValue:stl->_smooth];	

	if(stl->_arr.count()>1){
		[_fil_pop selectItemAtIndex:2];
		[_fil_tab selectTabViewItemAtIndex:2];		
		[_fil_img setImage:NULL];
	}
	else{
		[_fil_pop selectItemAtIndex:0];
		[_fil_tab selectTabViewItemAtIndex:0];
		[_fil_img setImage:NULL];
	}
	[self checkIntfAvailability];
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPalettePropLineWindowController drawPreview]",true);
bvDefPropLineStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	
NSTabViewItem	*tabitem=[_tab selectedTabViewItem];
	if(tabitem==NULL){
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
NSString* str=[tabitem identifier];
	if([str compare:@"Defi"]!=NSOrderedSame){
		[super drawPreview:rect context:ctx];
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	
HIRect			hir=(*((CGRect*)(&rect)));
color_range64	rng;
CGPoint			pts[4];
CGFloat			width;
int				nsv=0;
	
	hir=CGRectInset(hir,1,1);
	
	if(stl->_arr.count()>1){
		hir.size.width=hir.size.width/(stl->_arr.count()-1);
	}
	
	hir=(*((CGRect*)(&rect)));
	hir=CGRectInset(hir,1,1);
	if(stl->_arr.count()>1){
		hir.size.width=hir.size.width/(stl->_arr.count()-1);
	}
	
	width=stl->_rref*_ext->coef_get();
	if(stl->_rref>0){
		nsv++;
	}
	
	CGContextSetLineWidth(ctx,width);
	CGContextSetLineCap(ctx,(CGLineCap)stl->_cap);
	CGContextSetLineJoin(ctx,(CGLineJoin)stl->_join);

	if(stl->_arr.count()<2){
_tm_("color "+stl->_rref);
	pts[0].x=hir.origin.x+width+3.0;
		pts[0].y=hir.origin.y+width+3.0;
		pts[1].x=hir.origin.x+hir.size.width*0.75;
		pts[1].y=CGRectGetMidY(hir);
		pts[2].x=hir.origin.x+hir.size.width*0.25;
		pts[2].y=CGRectGetMidY(hir);
		pts[3].x=hir.origin.x+hir.size.width-width-3.0;
		pts[3].y=hir.origin.y+hir.size.height-width-3.0;
		MMCGContextSetStrokeColor64(ctx,
									stl->_color,
									_ext->cmyk_get());
		CGContextAddLines(ctx,pts,4);
		CGContextDrawPath(ctx,kCGPathStroke);
	}
	else{
_tm_("classes");
		for(long j=1;j<stl->_arr.count();j++){
			pts[0].x=hir.origin.x+width+3.0;
			pts[0].y=hir.origin.y+width+3.0;
			pts[1].x=hir.origin.x+hir.size.width*0.75;
			pts[1].y=CGRectGetMidY(hir);
			pts[2].x=hir.origin.x+hir.size.width*0.25;
			pts[2].y=CGRectGetMidY(hir);
			pts[3].x=hir.origin.x+hir.size.width-width-3.0;
			pts[3].y=hir.origin.y+hir.size.height-width-3.0;
			
			stl->_arr.get(j,&rng);
			MMCGContextSetStrokeColor64(ctx,
										rng.clrs,
										_ext->cmyk_get());
			CGContextAddLines(ctx,pts,4);
			CGContextDrawPath(ctx,kCGPathStroke);
			
			hir.origin.x+=hir.size.width;
		}
	}
	if(nsv==0){
		CGContextSetEmptyStyle(ctx,rect);
	}	
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
vDefPalettePropLineWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPalettePropLineWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

