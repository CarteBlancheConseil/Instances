//----------------------------------------------------------------------------
// File : vDefPaletteQuickRectWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Rectangle vdef window controller
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
// 25/06/2012 creation.
//----------------------------------------------------------------------------

#import "vDefPaletteQuickRectWindowController.h"
#import "bvDefPaletteQuickRect.h"
#import "bvDefQuickRectStyle.h"
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

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteQuickRectPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteQuickRectWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteQuickRectWindowController init]",true);
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
_bTrace_("[vDefPaletteQuickRectWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteQuickRectWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique
	NSPopupButtonPopulateWithFields(_fdmw_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdmh_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fwdt_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_ffil_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fstk_pop,_ext->type_get(),kOBJ_Name_,1);

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteQuickRectWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCentroid:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutCentroid]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_centro=[_cnt_chk intValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDimW:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutDimW]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_h=[_dmw_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDimH:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutDimH]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_v=[_dmh_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutWidth]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_width=[_wdt_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutStrokeColor:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutStrokeColor]",true);
bvDefQuickRectStyle*	stl;
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
				stl->_stroke[0]=[cclr cyanComponent];
				stl->_stroke[1]=[cclr magentaComponent];
				stl->_stroke[2]=[cclr yellowComponent];
				stl->_stroke[3]=[cclr blackComponent];
			}
			else{
				stl->_stroke[0]=[cclr redComponent];
				stl->_stroke[1]=[cclr greenComponent];
				stl->_stroke[2]=[cclr blueComponent];
			}
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseFillKind:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doChooseFillKind]",true);	
bvDefQuickRectStyle*	stl;
	[_fil_tab selectTabViewItemAtIndex:[_flk_pop indexOfSelectedItem]];
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			if([_flk_pop indexOfSelectedItem]==1){
				stl->_fill[0]=0;
				stl->_fill[1]=0;
				stl->_fill[2]=0;
				stl->_fill[3]=0;
				stl->_fill[4]=0;
			}
			else{	
				stl->_pat[0]=0;
			}
		}
	}		
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFillColor:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutFillColor]",true);
bvDefQuickRectStyle*	stl;
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
				stl->_fill[0]=[cclr cyanComponent];
				stl->_fill[1]=[cclr magentaComponent];
				stl->_fill[2]=[cclr yellowComponent];
				stl->_fill[3]=[cclr blackComponent];
			}
			else{
				stl->_fill[0]=[cclr redComponent];
				stl->_fill[1]=[cclr greenComponent];
				stl->_fill[2]=[cclr blueComponent];
			}
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFillImage:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutFillImage]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext=gapp->xmapMgr()->find('PPck');
picker_prm			prm={_ext->type_get(),""};
//CGPDFDocumentRef	pdf;

	if((ext->edit(&prm))&&(strlen(prm.name))){
_tm_(prm.name);
NSImage*	nsimg=GetNSImagePattern(gapp,
									_ext->type_get(),
									prm.name);
		if(!nsimg){
_te_("pas de nsimg");
			return;
		}
		[_fil_img setImage:nsimg];
bvDefQuickRectStyle*	stl;
		for(long i=1;i<=_ext->runs().count();i++){
			if([_run_tbl isRowSelected:i-1]==YES){
				_ext->runs().get(i,&stl);
				strcpy(stl->_pat,prm.name);
			}
		}			
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFillAlpha:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutFillAlpha]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fill[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDimWField:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutDimWField]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fh=[self getPopupValueForField:_fdmw_pop];//[_fdmw_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDimHField:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutDimHField]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fv=[self getPopupValueForField:_fdmh_pop];//[_fdmh_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutWidthField:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutWidthField]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fwidth=[self getPopupValueForField:_fwdt_pop];//[_fwdt_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFillColorField:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutFillColorField]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_ffill=[self getPopupValueForField:_ffil_pop];//[_ffil_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutStrokeColorField:(id)sender{
_bTrace_("[vDefPaletteQuickRectWindowController doPutStrokeColorField]",true);
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fstroke=[self getPopupValueForField:_fstk_pop];//[_fstk_pop indexOfSelectedItem]-2+kOBJ_Name_;
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
	[_cnt_chk setEnabled:YES];
BOOL	state=NO;
	if([_run_tbl numberOfSelectedRows]>0){
		state=YES;
	}
		
	[_dmw_fld setEnabled:state];
	[_dmh_fld setEnabled:state];
	[_wdt_fld setEnabled:state];
	[_flk_pop setEnabled:state];
	[_fil_clr setEnabled:state];
	[_fil_img setEnabled:state];
	[_stk_clr setEnabled:state];
	
	[_fdmw_pop setEnabled:state];
	[_fdmh_pop setEnabled:state];
	[_fwdt_pop setEnabled:state];
	[_ffil_pop setEnabled:state];
	[_fstk_pop setEnabled:state];

	if(state==YES){
		[_fil_sld setEnabled:([_flk_pop indexOfSelectedItem]==1)?NO:YES];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteQuickRectWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefQuickRectStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		return;
	}
	[_cnt_chk setIntValue:stl->_centro];
	
long					cur=[_run_tbl selectedRow]+1;
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();
	
	if(cur){
		_ext->runs().get(cur,&stl);
		if(_ext->cmyk_get()){
			[_fil_clr setColor:[NSColor colorWithDeviceCyan:stl->_fill[0] 
													magenta:stl->_fill[1] 
													 yellow:stl->_fill[2] 
													  black:stl->_fill[3] 
													  alpha:1]];
			[_stk_clr setColor:[NSColor colorWithDeviceCyan:stl->_stroke[0] 
													magenta:stl->_stroke[1] 
													 yellow:stl->_stroke[2] 
													  black:stl->_stroke[3] 
													  alpha:1]];
		}
		else{
			[_fil_clr setColor:[NSColor colorWithDeviceRed:stl->_fill[0]
													 green:stl->_fill[1] 
													  blue:stl->_fill[2] 
													 alpha:1]];
			[_stk_clr setColor:[NSColor colorWithDeviceRed:stl->_stroke[0]
													 green:stl->_stroke[1] 
													  blue:stl->_stroke[2] 
													 alpha:1]];
		}
		
		[_dmw_fld setFloatValue:stl->_h];
		[_dmh_fld setFloatValue:stl->_v];
		[_wdt_fld setFloatValue:stl->_width];
		[_fil_sld setFloatValue:stl->_fill[_ext->cmyk_get()?4:3]];
		
		if(strlen(stl->_pat)==0){
			[_flk_pop selectItemAtIndex:0];
			[_fil_tab selectTabViewItemAtIndex:0];
			[_fil_sld setEnabled:YES];
			
			[_fil_img setImage:NULL];
		}
		else{
			[_flk_pop selectItemAtIndex:1];
			[_fil_tab selectTabViewItemAtIndex:1];
			[_fil_sld setEnabled:NO];		
			
			[_fil_img setImage:GetNSImagePattern(gapp,_ext->type_get(),stl->_pat)];
		}
				
		[_fdmw_pop selectItemAtIndex:stl->_fh?stl->_fh-kOBJ_Name_+2:0];	
		[_fdmh_pop selectItemAtIndex:stl->_fv?stl->_fv-kOBJ_Name_+2:0];	
		[_fwdt_pop selectItemAtIndex:stl->_fwidth?stl->_fwidth-kOBJ_Name_+2:0];	
		[_ffil_pop selectItemAtIndex:stl->_ffill?stl->_ffill-kOBJ_Name_+2:0];		
		[_fstk_pop selectItemAtIndex:stl->_fstroke?stl->_fstroke-kOBJ_Name_+2:0];		
	}
	else{
		[_dmw_fld setFloatValue:0];
		[_dmh_fld setFloatValue:0];
		[_fil_clr setColor:[NSColor blackColor]];
		[_stk_clr setColor:[NSColor blackColor]];
		[_wdt_fld setFloatValue:0];
		[_fil_sld setFloatValue:0];

		[_fdmw_pop selectItemAtIndex:0];		
		[_fdmh_pop selectItemAtIndex:0];		
		[_fwdt_pop selectItemAtIndex:0];		
		[_ffil_pop selectItemAtIndex:0];		
		[_fstk_pop selectItemAtIndex:0];		
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefQuickRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(_ext->cmyk_get()){
			compRGB2CMYK64(stl->_stroke);
			compRGB2CMYK64(stl->_fill);
			stl->_cc=5;
		}
		else{
			compCMYK2RGB64(stl->_stroke);
			compCMYK2RGB64(stl->_fill);
			stl->_cc=4;
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPaletteQuickRectWindowController drawPreview]",true);
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();	
HIRect					hir=(*((CGRect*)(&rect)));
CGPDFDocumentRef		pdf=NULL;
bvDefQuickRectStyle*	stl;
CGRect					shape;
	
	hir=CGRectInset(hir,1,1);
	hir.size.width=hir.size.width/(double)_ext->runs().count();
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		
		shape.origin.x=CGRectGetMidX(hir)-stl->_h/2.0;
		shape.origin.y=CGRectGetMidY(hir)-stl->_v/2.0;
		shape.size.width=stl->_h;
		shape.size.height=stl->_v;
		
CGPathDrawingMode	mode=kCGPathFillStroke;
		
		if(stl->_width>0){
			CGContextSetLineWidth(ctx,stl->_width*_ext->coef_get());
			MMCGContextSetStrokeColor64(ctx,
										stl->_stroke,
										_ext->cmyk_get());
			CGContextSetLineCap(ctx,kCGLineCapButt);
			CGContextSetLineJoin(ctx,kCGLineJoinMiter);
		}
		else{
			mode=kCGPathFill;
		}
		
		if(strlen(stl->_pat)==0){							
			MMCGContextSetFillColor64(ctx,
									  stl->_fill,
									  _ext->cmyk_get());
		}
		else{
			pdf=GetPDFPattern(gapp,_ext->type_get(),stl->_pat);
			if(pdf){
CGPDFPageRef		pg=CGPDFDocumentGetPage(pdf,1);
CGRect				box=CGPDFPageGetBoxRect(pg,kCGPDFCropBox);
float				color[4]={1,0,0,1 };
CGPatternCallbacks	callbacks={0,&PDFPatternPlot,NULL};
CGColorSpaceRef		bspc=CGColorSpaceCreateDeviceRGB();
CGColorSpaceRef		pspc=CGColorSpaceCreatePattern(bspc);
					CGContextSetFillColorSpace(ctx,pspc);
					CGColorSpaceRelease(pspc);
					CGColorSpaceRelease(bspc);
CGPatternRef		pat=CGPatternCreate(pdf, 
										box,
										CGAffineTransformIdentity,
										box.size.width,
										box.size.height,
										kCGPatternTilingConstantSpacing,
										false, 
										&callbacks);   
				CGContextSetFillPattern(ctx,pat,color);
				CGPatternRelease(pat);
			}
		}
		
		if((stl->_h>0)&&(stl->_v>0)){
			CGContextAddRect(ctx,shape);
			CGContextDrawPath(ctx,mode);
		}
		else{
			CGContextSetEmptyStyle(ctx,hir);
		}
		
		if(pdf){
#warning Plantage à identifier sur release
			//CGPDFDocumentRelease(pdf);
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
vDefPaletteQuickRectWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteQuickRectWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

