//----------------------------------------------------------------------------
// File : vDefPaletteQuickDirWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Arrow (direction) vdef window controller
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
// 26/06/2012 creation.
//----------------------------------------------------------------------------

#import "vDefPaletteQuickDirWindowController.h"
#import "bvDefPaletteQuickDir.h"
#import "bvDefQuickDirStyle.h"
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
@implementation vDefPaletteQuickDirPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteQuickDirWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteQuickDirWindowController init]",true);
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
_bTrace_("[vDefPaletteQuickDirWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteQuickDirWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique
	NSPopupButtonRemoveAllItems(_fdir_pop);
	NSPopupButtonPopulateWithFields(_fdir_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fwdt_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_ffil_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fstk_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdec_pop,_ext->type_get(),kOBJ_Name_,1);

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteQuickDirWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSize:(id)sender{
_bTrace_("[vDefPaletteQuickDirWindowController doPutSize]",true);
bvDefQuickDirStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_sz=[_siz_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPaletteQuickDirWindowController doPutWidth]",true);
bvDefQuickDirStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickDirWindowController doPutStrokeColor]",true);
bvDefQuickDirStyle*	stl;
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
_bTrace_("[vDefPaletteQuickDirWindowController doChooseFillKind]",true);	
bvDefQuickDirStyle*	stl;
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
_bTrace_("[vDefPaletteQuickDirWindowController doPutFillColor]",true);
bvDefQuickDirStyle*	stl;
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
_bTrace_("[vDefPaletteQuickDirWindowController doPutFillImage]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext=gapp->xmapMgr()->find('PPck');
picker_prm			prm={_ext->type_get(),""};

	if((ext->edit(&prm))&&(strlen(prm.name))){
NSImage*	nsimg=GetNSImagePattern(gapp,
									_ext->type_get(),
									prm.name);
		if(!nsimg){
_te_("pas de nsimg");
			return;
		}
		[_fil_img setImage:nsimg];
bvDefQuickDirStyle*	stl;
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
_bTrace_("[vDefPaletteQuickDirWindowController doPutFillAlpha]",true);
bvDefQuickDirStyle*	stl;
	
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
// -----------
-(IBAction)doPutDec:(id)sender{
_bTrace_("[vDefPaletteQuickDirWindowController doPutDec]",true);
bvDefQuickDirStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_dec=[_dec_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDirField:(id)sender{
_bTrace_("[vDefPaletteQuickDirWindowController doPutSizeField]",true);
bvDefQuickDirStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		//if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fdir=[_fdir_pop indexOfSelectedItem]+kOBJ_Name_;
		//}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutSizeField:(id)sender{
_bTrace_("[vDefPaletteQuickDirWindowController doPutSizeField]",true);
bvDefQuickDirStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fsz=[self getPopupValueForField:_fsiz_pop];//[_fsiz_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutWidthField:(id)sender{
_bTrace_("[vDefPaletteQuickDirWindowController doPutWidthField]",true);
bvDefQuickDirStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickDirWindowController doPutFillColorField]",true);
bvDefQuickDirStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickDirWindowController doPutStrokeColorField]",true);
bvDefQuickDirStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fstroke=[self getPopupValueForField:_fstk_pop];//[_fstk_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDecField:(id)sender{
_bTrace_("[vDefPaletteQuickDirWindowController doPutDecField]",true);
bvDefQuickDirStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fdec=[self getPopupValueForField:_fdec_pop];//[_fdec_pop indexOfSelectedItem]-2+kOBJ_Name_;
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

	[_fdir_pop setEnabled:YES];

BOOL	state=NO;
	if([_run_tbl numberOfSelectedRows]>0){
		state=YES;
	}
		
	[_siz_fld setEnabled:state];
	[_wdt_fld setEnabled:state];
	[_flk_pop setEnabled:state];
	[_fil_clr setEnabled:state];
	[_fil_img setEnabled:state];
	[_stk_clr setEnabled:state];
	[_dec_fld setEnabled:state];
	
	[_fsiz_pop setEnabled:state];
	[_fwdt_pop setEnabled:state];
	[_ffil_pop setEnabled:state];
	[_fstk_pop setEnabled:state];
	[_fdec_pop setEnabled:state];

	if(state==YES){
		[_fil_sld setEnabled:([_flk_pop indexOfSelectedItem]==1)?NO:YES];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteQuickDirWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefQuickDirStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		return;
	}
	[_fdir_pop selectItemAtIndex:stl->_fdir?stl->_fdir-kOBJ_Name_:0];	

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
		
		[_siz_fld setFloatValue:stl->_sz];
		[_wdt_fld setFloatValue:stl->_width];
		[_fil_sld setFloatValue:stl->_fill[_ext->cmyk_get()?4:3]];
		[_dec_fld setFloatValue:stl->_dec];

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
				
		[_fsiz_pop selectItemAtIndex:stl->_fsz?stl->_fsz-kOBJ_Name_+2:0];	
		[_fwdt_pop selectItemAtIndex:stl->_fwidth?stl->_fwidth-kOBJ_Name_+2:0];	
		[_ffil_pop selectItemAtIndex:stl->_ffill?stl->_ffill-kOBJ_Name_+2:0];		
		[_fstk_pop selectItemAtIndex:stl->_fstroke?stl->_fstroke-kOBJ_Name_+2:0];		
		[_fdec_pop selectItemAtIndex:stl->_fdec?stl->_fdec-kOBJ_Name_+2:0];		
	}
	else{
		[_siz_fld setFloatValue:0];
		[_fil_clr setColor:[NSColor blackColor]];
		[_stk_clr setColor:[NSColor blackColor]];
		[_wdt_fld setFloatValue:0];
		[_fil_sld setFloatValue:0];
		[_dec_fld setFloatValue:0];

		[_fsiz_pop selectItemAtIndex:0];		
		[_fwdt_pop selectItemAtIndex:0];		
		[_ffil_pop selectItemAtIndex:0];		
		[_fstk_pop selectItemAtIndex:0];		
		[_fdec_pop selectItemAtIndex:0];		
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefQuickDirStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickDirWindowController drawPreview]",true);
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();	
HIRect					hir=(*((CGRect*)(&rect)));
CGPDFDocumentRef		pdf=NULL;
bvDefQuickDirStyle*		stl;
CGPoint					pts[5];
double					a=0;
CGPoint					pa,pb,px;
	
	hir=CGRectInset(hir,1,1);
	hir.size.width=hir.size.width/(double)_ext->runs().count();
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		
		a=0;
		pb.x=CGRectGetMidX(hir)+stl->_sz/2.0;
		pb.y=CGRectGetMidY(hir);
		CGPointNewPos(&pb,stl->_sz/2.0,a+M_PI,&pa);	
		CGPointNewPos(&pa,stl->_sz/2.0,a+M_PI,&px);
		CGPointNewPos(&pa,stl->_sz/3.0,a+M_PI,&pb);
		pts[0]=pb;
		CGPointNewPos(&px,stl->_sz/3.0,a+(M_PI*1.5),&pb);
		pts[1]=pb;
		CGPointNewPos(&pa,stl->_sz/2.0,a,&pb);
		pts[2]=pb;
		CGPointNewPos(&px,stl->_sz/3.0,a+(M_PI*0.5),&pb);
		pts[3]=pb;
		pts[4]=pts[0];

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
		
		if(stl->_sz!=0){
			CGContextAddLines(ctx,pts,5);
			CGContextClosePath(ctx);
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
vDefPaletteQuickDirWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteQuickDirWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

