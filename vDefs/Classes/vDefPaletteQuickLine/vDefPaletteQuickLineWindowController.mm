//----------------------------------------------------------------------------
// File : vDefPaletteQuickLineWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Line vdef window controller
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
// 27/06/2012 creation.
//----------------------------------------------------------------------------

#import "vDefPaletteQuickLineWindowController.h"
#import "bvDefPaletteQuickLine.h"
#import "bvDefQuickLineStyle.h"
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
@implementation vDefPaletteQuickLinePanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteQuickLineWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteQuickLineWindowController init]",true);
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
_bTrace_("[vDefPaletteQuickLineWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteQuickLineWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique
	NSPopupButtonPopulateWithDashes(_dsh_pop,_ext->type_get(),1);

	NSPopupButtonPopulateWithFields(_fwdt_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fcap_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fjon_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdsh_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fstk_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fmit_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdec_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fsmt_pop,_ext->type_get(),kOBJ_Name_,1);
	
	_cur=0;
	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteQuickLineWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doSwitchLine:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doSwitchLine]",true);
	_cur=[_swc_pop indexOfSelectedItem];
_tm_((int)_cur);
	[self plot2Intf];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutWidth]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_width[_cur]=[_wdt_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCap:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutCap]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_cap[_cur]=[_cap_pop indexOfSelectedItem];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutJoin:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutJoin]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_join[_cur]=[_jon_pop indexOfSelectedItem];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doAddDash:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doAddDash]",true);
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
_bTrace_("[vDefPaletteQuickLineWindowController doPutDash]",true);
bvDefQuickLineStyle*	stl;
char					val[256]="";
long					idx=[_dsh_pop indexOfSelectedItem];
	
	if(idx>1){
		_ext->type_get()->fields()->get_param_name("dashes",idx+1-2,val);
	}
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			strcpy(stl->_dsh[_cur],val);
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutStrokeColor:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutStrokeColor]",true);
bvDefQuickLineStyle*	stl;
NSColor*				clr=[_stk_clr color];
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
				stl->_stroke[_cur][0]=[cclr cyanComponent];
				stl->_stroke[_cur][1]=[cclr magentaComponent];
				stl->_stroke[_cur][2]=[cclr yellowComponent];
				stl->_stroke[_cur][3]=[cclr blackComponent];
			}
			else{
				stl->_stroke[_cur][0]=[cclr redComponent];
				stl->_stroke[_cur][1]=[cclr greenComponent];
				stl->_stroke[_cur][2]=[cclr blueComponent];
			}
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutMiter:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutMiter]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_limit[_cur]=[_mit_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDec:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutDec]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_dec[_cur]=[_dec_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSmooth:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutSmooth]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_smooth[_cur]=[_smt_chk intValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutWidthField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutWidthField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fwidth[_cur]=[self getPopupValueForField:_fwdt_pop];//[_fwdt_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutCapField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutCapField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fcap[_cur]=[self getPopupValueForField:_fcap_pop];//[_fcap_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutJoinField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutJoinField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fjoin[_cur]=[self getPopupValueForField:_fjon_pop];//[_fjon_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDashField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutDashField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fdsh[_cur]=[self getPopupValueForField:_fdsh_pop];//[_fdsh_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutStrokeColorField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutStrokeColorField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fstroke[_cur]=[self getPopupValueForField:_fstk_pop];//[_fstk_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutMiterField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutMiterField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_flimit[_cur]=[self getPopupValueForField:_fmit_pop];//[_fmit_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDecField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutDecField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fdec[_cur]=[self getPopupValueForField:_fdec_pop];//[_fdec_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutSmoothField:(id)sender{
_bTrace_("[vDefPaletteQuickLineWindowController doPutSmoothField]",true);
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fsmooth[_cur]=[self getPopupValueForField:_fsmt_pop];//[_fsmt_pop indexOfSelectedItem]-2+kOBJ_Name_;
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

BOOL	state=NO;
	if([_run_tbl numberOfSelectedRows]>0){
		state=YES;
	}
		
	[_wdt_fld setEnabled:state];
	[_cap_pop setEnabled:state];
	[_jon_pop setEnabled:state];
	[_dsh_btn setEnabled:state];
	[_dsh_pop setEnabled:state];
	[_stk_clr setEnabled:state];
	[_mit_fld setEnabled:state];
	[_dec_fld setEnabled:state];
	[_smt_chk setEnabled:state];
	
	[_fwdt_pop setEnabled:state];
	[_fcap_pop setEnabled:state];
	[_fjon_pop setEnabled:state];
	[_fdsh_pop setEnabled:state];
	[_fstk_pop setEnabled:state];
	[_fmit_pop setEnabled:state];
	[_fdec_pop setEnabled:state];
	[_fsmt_pop setEnabled:state];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteQuickLineWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefQuickLineStyle*	stl;
long					cur=[_run_tbl selectedRow]+1;
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();
	
	if(cur){
		_ext->runs().get(cur,&stl);
		
		if(_ext->cmyk_get()){
			[_stk_clr setColor:[NSColor colorWithDeviceCyan:stl->_stroke[_cur][0] 
													magenta:stl->_stroke[_cur][1] 
													 yellow:stl->_stroke[_cur][2] 
													  black:stl->_stroke[_cur][3] 
													  alpha:1]];
		}
		else{
			[_stk_clr setColor:[NSColor colorWithDeviceRed:stl->_stroke[_cur][0]
													 green:stl->_stroke[_cur][1] 
													  blue:stl->_stroke[_cur][2] 
													 alpha:1]];
		}
		
		[_wdt_fld setFloatValue:stl->_width[_cur]];
		[_cap_pop selectItemAtIndex:stl->_cap[_cur]];
		[_jon_pop selectItemAtIndex:stl->_join[_cur]];
		
long	idx=getDashIndex(_ext->type_get(),stl->_dsh[_cur]);
		if(idx>0){
			idx++;
		}
		[_dsh_pop selectItemAtIndex:idx];
		
		[_mit_fld setFloatValue:stl->_limit[_cur]];
		[_dec_fld setFloatValue:stl->_dec[_cur]];
		[_smt_chk setIntValue:stl->_smooth[_cur]];
		
		[_fwdt_pop selectItemAtIndex:stl->_fwidth[_cur]?stl->_fwidth[_cur]-kOBJ_Name_+2:0];	
		[_fcap_pop selectItemAtIndex:stl->_fcap[_cur]?stl->_fcap[_cur]-kOBJ_Name_+2:0];	
		[_fjon_pop selectItemAtIndex:stl->_fjoin[_cur]?stl->_fjoin[_cur]-kOBJ_Name_+2:0];	
		[_fdsh_pop selectItemAtIndex:stl->_fdsh[_cur]?stl->_fdsh[_cur]-kOBJ_Name_+2:0];	
		[_fstk_pop selectItemAtIndex:stl->_fstroke[_cur]?stl->_fstroke[_cur]-kOBJ_Name_+2:0];		
		[_fmit_pop selectItemAtIndex:stl->_flimit[_cur]?stl->_flimit[_cur]-kOBJ_Name_+2:0];	
		[_fdec_pop selectItemAtIndex:stl->_fdec[_cur]?stl->_fdec[_cur]-kOBJ_Name_+2:0];
		[_fsmt_pop selectItemAtIndex:stl->_fsmooth[_cur]?stl->_fsmooth[_cur]-kOBJ_Name_+2:0];	
		
	}
	else{
		[_wdt_fld setFloatValue:0];
		[_cap_pop selectItemAtIndex:0];
		[_jon_pop selectItemAtIndex:0];
		[_dsh_pop selectItemAtIndex:0];
		[_mit_fld setFloatValue:0];
		[_dec_fld setFloatValue:0];
		[_smt_chk setIntValue:0];
		
		[_fwdt_pop selectItemAtIndex:0];	
		[_fcap_pop selectItemAtIndex:0];	
		[_fjon_pop selectItemAtIndex:0];	
		[_fdsh_pop selectItemAtIndex:0];	
		[_fstk_pop selectItemAtIndex:0];		
		[_fmit_pop selectItemAtIndex:0];	
		[_fdec_pop selectItemAtIndex:0];
		[_fsmt_pop selectItemAtIndex:0];	
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefQuickLineStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(_ext->cmyk_get()){
			compRGB2CMYK64(stl->_stroke[0]);
			compRGB2CMYK64(stl->_stroke[1]);
			compRGB2CMYK64(stl->_stroke[2]);
			stl->_cc=5;
		}
		else{
			compCMYK2RGB64(stl->_stroke[0]);
			compCMYK2RGB64(stl->_stroke[1]);
			compCMYK2RGB64(stl->_stroke[2]);
			stl->_cc=4;
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPaletteQuickLineWindowController drawPreview]",true);
HIRect					hir=(*((CGRect*)(&rect)));
bvDefQuickLineStyle*	stl;
CGPoint					pts[4];
int						nsv;
	hir=CGRectInset(hir,1,1);
	hir.size.width=hir.size.width/(double)_ext->runs().count();
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		
		pts[0].x=hir.origin.x+stl->_width[0]*_ext->coef_get()+3.0;
		pts[0].y=hir.origin.y+stl->_width[0]*_ext->coef_get()+3.0;
		pts[1].x=hir.origin.x+hir.size.width*0.75;
		pts[1].y=CGRectGetMidY(hir);
		pts[2].x=hir.origin.x+hir.size.width*0.25;
		pts[2].y=CGRectGetMidY(hir);
		pts[3].x=hir.origin.x+hir.size.width-stl->_width[0]*_ext->coef_get()-3.0;
		pts[3].y=hir.origin.y+hir.size.height-stl->_width[0]*_ext->coef_get()-3.0;
		
		nsv=0;
		CGContextSaveGState(ctx);
		for(long j=0;j<3;j++){
			if(stl->_width>0){
				CGContextSetLineWidth(ctx,stl->_width[j]*_ext->coef_get());
				MMCGContextSetStrokeColor64(ctx,
											stl->_stroke[j],
											_ext->cmyk_get());
				CGContextSetLineCap(ctx,(CGLineCap)stl->_cap[j]);
				CGContextSetLineJoin(ctx,(CGLineJoin)stl->_join[j]);
			
				CGContextAddLines(ctx,pts,4);
				CGContextDrawPath(ctx,kCGPathStroke);
				nsv++;
			}
		}
		CGContextRestoreGState(ctx);
		
		if(nsv==0){
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
vDefPaletteQuickLineWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteQuickLineWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

