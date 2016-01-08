//----------------------------------------------------------------------------
// File : vDefPaletteRangeLineWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Range line vdef window controller
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
// 30/08/2012 creation.
//----------------------------------------------------------------------------

#import "vDefPaletteRangeLineWindowController.h"
#import "bvDefPaletteRangeLine.h"
#import "bvDefRangeLineStyle.h"
#import "CocoaStuff.h"
#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/Carb_Utils.h>
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
@implementation vDefPaletteRangeLinePanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteRangeLineWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteRangeLineWindowController init]",true);
	self=[super init];
	if(self){
		_last_click=-1;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[vDefPaletteRangeLineWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteRangeLineWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique
	NSPopupButtonPopulateWithDashes(_dsh_pop,_ext->type_get(),1);

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteRangeLineWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPaletteRangeLineWindowController doPutWidth]",true);
bvDefRangeLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_width=[_wdt_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCap:(id)sender{
_bTrace_("[vDefPaletteRangeLineWindowController doPutCap]",true);
bvDefRangeLineStyle*	stl;
	
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
_bTrace_("[vDefPaletteRangeLineWindowController doPutJoin]",true);
bvDefRangeLineStyle*	stl;
	
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
_bTrace_("[vDefPaletteRangeLineWindowController doAddDash]",true);
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
_bTrace_("[vDefPaletteRangeLineWindowController doPutDash]",true);
bvDefRangeLineStyle*	stl;
char					val[256]="";
long					idx=[_dsh_pop indexOfSelectedItem];
	
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
_bTrace_("[vDefPaletteRangeLineWindowController doPutMiter]",true);
bvDefRangeLineStyle*	stl;
	
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
_bTrace_("[vDefPaletteRangeLineWindowController doPutDec]",true);
bvDefRangeLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_dec=[_dec_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSmoothing:(id)sender{
_bTrace_("[vDefPaletteRangeLineWindowController doPutSmoothing]",true);
bvDefRangeLineStyle*	stl;
	
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
_bTrace_("[vDefPaletteRangeLineWindowController doChooseFillKind]",true);	
bvDefRangeLineStyle*	stl;
	[_fil_tab selectTabViewItemAtIndex:[_flk_pop indexOfSelectedItem]];
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
_tm_([_flk_pop indexOfSelectedItem]);
			if([_flk_pop indexOfSelectedItem]==0){
				stl->_fld[0]=0;
				stl->_visible=true;
			}
			else if([_flk_pop indexOfSelectedItem]==1){
				_ext->type_get()->fields()->get_name(_ext->fld_get(),stl->_fld);
//				((bvDefPaletteRangeLine*)_ext)->limits().get(_last_click+1,&stl->_vmin);
//				((bvDefPaletteRangeLine*)_ext)->limits().get(_last_click+2,&stl->_vmax);
				((bvDefPaletteRangeLine*)_ext)->limits().get(i,&stl->_vmin);
				((bvDefPaletteRangeLine*)_ext)->limits().get(i+1,&stl->_vmax);
				stl->_visible=true;
			}
			else{
				stl->_visible=false;
			}
		}
	}		
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillColor:(id)sender{
_bTrace_("[vDefPaletteRangeLineWindowController doChooseFillColor]",true);
bvDefRangeLineStyle*	stl;
NSColor*				clr=[_fil_clr color];
NSColor*				cclr;
	
	if(_ext->cmyk_get()){
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
	}
	else{
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
	}
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			if(_ext->cmyk_get()){
				stl->_fcolor[0]=[cclr cyanComponent];
				stl->_fcolor[1]=[cclr magentaComponent];
				stl->_fcolor[2]=[cclr yellowComponent];
				stl->_fcolor[3]=[cclr blackComponent];
			}
			else{
				stl->_fcolor[0]=[cclr redComponent];
				stl->_fcolor[1]=[cclr greenComponent];
				stl->_fcolor[2]=[cclr blueComponent];
			}
			stl->_fcolor[_ext->cmyk_get()?4:3]=1;
			stl->_fld[0]=0;
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillFromColor:(id)sender{
_bTrace_("[vDefPaletteRangeLineWindowController doChooseFillFromColor]",true);
bvDefRangeLineStyle*	stl;
NSColor*				clr=[_flf_clr color];
NSColor*				cclr;
	
	if(_ext->cmyk_get()){
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
	}
	else{
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
	}
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			if(_ext->cmyk_get()){
				stl->_fcolor[0]=[cclr cyanComponent];
				stl->_fcolor[1]=[cclr magentaComponent];
				stl->_fcolor[2]=[cclr yellowComponent];
				stl->_fcolor[3]=[cclr blackComponent];
			}
			else{
				stl->_fcolor[0]=[cclr redComponent];
				stl->_fcolor[1]=[cclr greenComponent];
				stl->_fcolor[2]=[cclr blueComponent];
			}
			stl->_fcolor[_ext->cmyk_get()?4:3]=1;
_tm_(stl->_fcolor[0]+":"+stl->_fcolor[1]+":"+stl->_fcolor[2]);
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillToColor:(id)sender{
_bTrace_("[vDefPaletteRangeLineWindowController doChooseFillToColor]",true);
bvDefRangeLineStyle*	stl;
NSColor*				clr=[_flt_clr color];
NSColor*				cclr;
	
	if(_ext->cmyk_get()){
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
	}
	else{
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
	}
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			if(_ext->cmyk_get()){
				stl->_tcolor[0]=[cclr cyanComponent];
				stl->_tcolor[1]=[cclr magentaComponent];
				stl->_tcolor[2]=[cclr yellowComponent];
				stl->_tcolor[3]=[cclr blackComponent];
			}
			else{
				stl->_tcolor[0]=[cclr redComponent];
				stl->_tcolor[1]=[cclr greenComponent];
				stl->_tcolor[2]=[cclr blueComponent];
			}
			stl->_tcolor[_ext->cmyk_get()?4:3]=1;
_tm_(stl->_tcolor[0]+":"+stl->_tcolor[1]+":"+stl->_tcolor[2]);
		}
	}	
	[self updateUI];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)checkIntfAvailability{
	[super checkIntfAvailability];
	[_smt_chk setEnabled:YES];
BOOL	state=NO;
	if([_run_tbl numberOfSelectedRows]>0){
		state=YES;
	}
		
	[_flk_pop setEnabled:state];
	[_fil_clr setEnabled:state];
	[_flf_clr setEnabled:state];
	[_flt_clr setEnabled:state];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteRangeLineWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefRangeLineStyle*	stl=NULL;
	for(int i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(stl->_visible){
			break;
		}
	}
	if(stl==NULL){
		return;
	}
	
	[_wdt_fld setFloatValue:stl->_width];
	[_cap_pop selectItemAtIndex:stl->_cap];
	[_jon_pop selectItemAtIndex:stl->_join];
long	idx=getDashIndex(_ext->type_get(),stl->_dsh);
	if(idx>0){
		idx++;
	}
	[_dsh_pop selectItemAtIndex:idx];
	[_mit_fld setFloatValue:stl->_limit];
	[_dec_fld setFloatValue:stl->_dec];
	[_smt_chk setIntValue:stl->_smooth];	

long					cur=[_run_tbl selectedRow]+1;
	
	if(cur){
		_ext->runs().get(cur,&stl);
		if(_ext->cmyk_get()){
			[_fil_clr setColor:[NSColor colorWithDeviceCyan:stl->_fcolor[0] 
													magenta:stl->_fcolor[1] 
													 yellow:stl->_fcolor[2] 
													  black:stl->_fcolor[3] 
													  alpha:1]];
			[_flf_clr setColor:[NSColor colorWithDeviceCyan:stl->_fcolor[0] 
													magenta:stl->_fcolor[1] 
													 yellow:stl->_fcolor[2] 
													  black:stl->_fcolor[3] 
													  alpha:1]];
			[_flt_clr setColor:[NSColor colorWithDeviceCyan:stl->_fcolor[0] 
													magenta:stl->_fcolor[1] 
													 yellow:stl->_fcolor[2] 
													  black:stl->_fcolor[3] 
													  alpha:1]];
		}
		else{
			[_fil_clr setColor:[NSColor colorWithDeviceRed:stl->_fcolor[0]
													 green:stl->_fcolor[1] 
													  blue:stl->_fcolor[2] 
													 alpha:1]];
			[_flf_clr setColor:[NSColor colorWithDeviceRed:stl->_fcolor[0]
													 green:stl->_fcolor[1] 
													  blue:stl->_fcolor[2] 
													 alpha:1]];
			[_flt_clr setColor:[NSColor colorWithDeviceRed:stl->_tcolor[0]
													 green:stl->_tcolor[1] 
													  blue:stl->_tcolor[2] 
													 alpha:1]];
		}
		
		
		if(stl->_visible){
			if(strlen(stl->_fld)==0){
				[_flk_pop selectItemAtIndex:0];
				[_fil_tab selectTabViewItemAtIndex:0];
			}
			else{
				[_flk_pop selectItemAtIndex:1];
				[_fil_tab selectTabViewItemAtIndex:1];
			}
		}
		else{
			[_flk_pop selectItemAtIndex:2];
			[_fil_tab selectTabViewItemAtIndex:2];
		}
	}
	else{
		[_fil_clr setColor:[NSColor blackColor]];
		[_flf_clr setColor:[NSColor blackColor]];
		[_flt_clr setColor:[NSColor blackColor]];
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefRangeLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(_ext->cmyk_get()){
			compRGB2CMYK64(stl->_fcolor);
			compRGB2CMYK64(stl->_tcolor);
			stl->_cc=5;
		}
		else{
			compCMYK2RGB64(stl->_fcolor);
			compRGB2CMYK64(stl->_tcolor);
			stl->_cc=4;
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPaletteRangeLineWindowController drawPreview]",true);
HIRect					hir=(*((CGRect*)(&rect)));
bvDefRangeLineStyle*	stl;
CGPoint					pts[4];
	
	hir=CGRectInset(hir,1,1);
	hir.size.width=hir.size.width/(double)_ext->runs().count();
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		
		pts[0].x=hir.origin.x+stl->_width*_ext->coef_get()+3.0;
		pts[0].y=hir.origin.y+stl->_width*_ext->coef_get()+3.0;
		pts[1].x=hir.origin.x+hir.size.width*0.75;
		pts[1].y=CGRectGetMidY(hir);
		pts[2].x=hir.origin.x+hir.size.width*0.25;
		pts[2].y=CGRectGetMidY(hir);
		pts[3].x=hir.origin.x+hir.size.width-stl->_width*_ext->coef_get()-3.0;
		pts[3].y=hir.origin.y+hir.size.height-stl->_width*_ext->coef_get()-3.0;

		if(stl->_visible){
			CGContextSetLineWidth(ctx,stl->_width*_ext->coef_get());
			CGContextSetLineCap(ctx,(CGLineCap)stl->_cap);
			CGContextSetLineJoin(ctx,(CGLineJoin)stl->_join);
			
			if(strlen(stl->_fld)==0){
_tm_("color");
				MMCGContextSetStrokeColor64(ctx,
											stl->_fcolor,
											_ext->cmyk_get());
				CGContextAddLines(ctx,pts,4);
				CGContextDrawPath(ctx,kCGPathStroke);			
			}
			else{
_tm_("gradient");
				pts[0].x-=stl->_width*_ext->coef_get()/2.0;
				pts[1].x-=stl->_width*_ext->coef_get()/2.0;
				pts[2].x-=stl->_width*_ext->coef_get()/2.0;
				pts[3].x-=stl->_width*_ext->coef_get()/2.0;
				
				MMCGContextSetStrokeColor64(ctx,
											stl->_fcolor,
											_ext->cmyk_get());
				CGContextAddLines(ctx,pts,4);
				CGContextDrawPath(ctx,kCGPathStroke);
								
				pts[0].x+=stl->_width*_ext->coef_get();
				pts[1].x+=stl->_width*_ext->coef_get();
				pts[2].x+=stl->_width*_ext->coef_get();
				pts[3].x+=stl->_width*_ext->coef_get();

				MMCGContextSetStrokeColor64(ctx,
											stl->_tcolor,
											_ext->cmyk_get());
				CGContextAddLines(ctx,pts,4);
				CGContextDrawPath(ctx,kCGPathStroke);
				
				pts[0].x-=stl->_width*_ext->coef_get()/2.0;
				pts[1].x-=stl->_width*_ext->coef_get()/2.0;
				pts[2].x-=stl->_width*_ext->coef_get()/2.0;
				pts[3].x-=stl->_width*_ext->coef_get()/2.0;
				
			}
		}
		else{
			CGContextSetEmptyStyle(ctx,hir);
		}		
		
		if([_run_tbl isRowSelected:i-1]==YES){
			hir=CGRectInset(hir,1,1);
			CGContextSetLineWidth(ctx,1);
			CGContextSetRGBStrokeColor(ctx,0,0,0,1);
			CGContextStrokeRect(ctx,hir);
			hir=CGRectInset(hir,-1,-1);
		}
		hir.origin.x+=hir.size.width;
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
vDefPaletteRangeLineWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteRangeLineWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

