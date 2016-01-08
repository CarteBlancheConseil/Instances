//----------------------------------------------------------------------------
// File : vDefPaletteRangeRectWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Range rectangle vdef window controller
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

#import "vDefPaletteRangeRectWindowController.h"
#import "bvDefPaletteRangeRect.h"
#import "bvDefRangeRectStyle.h"
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
@implementation vDefPaletteRangeRectPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteRangeRectWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteRangeRectWindowController init]",true);
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
_bTrace_("[vDefPaletteRangeRectWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteRangeRectWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteRangeRectWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCentroid:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doPutCentroid]",true);
bvDefRangeRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_centro=[_cnt_chk intValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutHSize:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doPutHSize]",true);
bvDefRangeRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_h=[_hsz_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutVSize:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doPutVSize]",true);
bvDefRangeRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_v=[_vsz_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doPutWidth]",true);
bvDefRangeRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_width=[_wdt_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutStrokeColor:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doPutStrokeColor]",true);
bvDefRangeRectStyle*	stl;
NSColor*				clr=[_stk_clr color];
NSColor*				cclr;
	
	if(_ext->cmyk_get()){
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
	}
	else{
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
	}
	for(long i=1;i<=_ext->runs().count();i++){
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
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseColorimetry:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doChooseColorimetry]",true);
bvDefRangeRectStyle*	stl;	
	
	for(int i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_pat[0]=0;
	}
	[super doChooseColorimetry:sender];	
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseFillKind:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doChooseFillKind]",true);	
bvDefRangeRectStyle*	stl;
	[_fil_tab selectTabViewItemAtIndex:[_flk_pop indexOfSelectedItem]];
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			_tm_([_flk_pop indexOfSelectedItem]);
			if([_flk_pop indexOfSelectedItem]==0){
				stl->_pat[0]=0;
				stl->_fld[0]=0;
				stl->_visible=true;
			}
			else if([_flk_pop indexOfSelectedItem]==1){
				stl->_fld[0]=0;
				stl->_visible=true;
			}
			else if([_flk_pop indexOfSelectedItem]==2){
				stl->_pat[0]=0;
				_ext->type_get()->fields()->get_name(_ext->fld_get(),stl->_fld);
//				((bvDefPaletteRangeRect*)_ext)->limits().get(_last_click+1,&stl->_vmin);
//				((bvDefPaletteRangeRect*)_ext)->limits().get(_last_click+2,&stl->_vmax);
				((bvDefPaletteRangeRect*)_ext)->limits().get(i,&stl->_vmin);
				((bvDefPaletteRangeRect*)_ext)->limits().get(i+1,&stl->_vmax);
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
_bTrace_("[vDefPaletteRangeRectWindowController doChooseFillColor]",true);
bvDefRangeRectStyle*	stl;
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
			stl->_fcolor[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
			stl->_pat[0]=0;
			stl->_fld[0]=0;
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillPattern:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doChooseFillPattern]",true);
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
bvDefRangeRectStyle*	stl;
		for(long i=1;i<=_ext->runs().count();i++){
			if([_run_tbl isRowSelected:i-1]==YES){
				_ext->runs().get(i,&stl);
				strcpy(stl->_pat,prm.name);
				stl->_fld[0]=0;
			}
		}			
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillFromColor:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doChooseFillFromColor]",true);
bvDefRangeRectStyle*	stl;
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
			stl->_fcolor[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
			stl->_pat[0]=0;
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillToColor:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doChooseFillToColor]",true);
bvDefRangeRectStyle*	stl;
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
			stl->_tcolor[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
			stl->_pat[0]=0;
		}
	}	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFillAlpha:(id)sender{
_bTrace_("[vDefPaletteRangeRectWindowController doPutFillAlpha]",true);
bvDefRangeRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_fcolor[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
		stl->_tcolor[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
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
		
	[_flk_pop setEnabled:state];
	[_fil_clr setEnabled:state];
	[_flf_clr setEnabled:state];
	[_flt_clr setEnabled:state];
	[_fil_img setEnabled:state];
	
	if(state==YES){
		[_fil_sld setEnabled:([_flk_pop indexOfSelectedItem]==1)/*||([_flk_pop indexOfSelectedItem]==3)*/?NO:YES];
	}
	else{
		[_fil_sld setEnabled:YES];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteRangeRectWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefRangeRectStyle*	stl=NULL;
	for(int i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(stl->_visible){
			break;
		}
	}
	if(stl==NULL){
		return;
	}
	
	[_cnt_chk setIntValue:stl->_centro];
	[_hsz_fld setFloatValue:stl->_h];
	[_vsz_fld setFloatValue:stl->_v];
	[_wdt_fld setFloatValue:stl->_width];
	[_fil_sld setFloatValue:stl->_fcolor[_ext->cmyk_get()?4:3]];
	if(_ext->cmyk_get()){
		[_stk_clr setColor:[NSColor colorWithDeviceCyan:stl->_stroke[0] 
												magenta:stl->_stroke[1] 
												 yellow:stl->_stroke[2] 
												  black:stl->_stroke[3] 
												  alpha:1]];
	}
	else{
		[_stk_clr setColor:[NSColor colorWithDeviceRed:stl->_stroke[0]
												 green:stl->_stroke[1] 
												  blue:stl->_stroke[2] 
												 alpha:1]];
	}
	
	
long					cur=[_run_tbl selectedRow]+1;
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();
	
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
			if(strlen(stl->_pat)==0){
				if(strlen(stl->_fld)==0){
					[_flk_pop selectItemAtIndex:0];
					[_fil_tab selectTabViewItemAtIndex:0];
				}
				else{
					[_flk_pop selectItemAtIndex:2];
					[_fil_tab selectTabViewItemAtIndex:2];
				}
				[_fil_img setImage:NULL];
			}
			else{
				[_flk_pop selectItemAtIndex:1];
				[_fil_tab selectTabViewItemAtIndex:1];				
				[_fil_img setImage:GetNSImagePattern(gapp,_ext->type_get(),stl->_pat)];
			}
		}
		else{
			[_flk_pop selectItemAtIndex:3];
			[_fil_tab selectTabViewItemAtIndex:3];
		}
	}
	else{
		[_fil_clr setColor:[NSColor blackColor]];
		[_flf_clr setColor:[NSColor blackColor]];
		[_flt_clr setColor:[NSColor blackColor]];
		[_fil_img setImage:NULL];
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefRangeRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(_ext->cmyk_get()){
			compRGB2CMYK64(stl->_stroke);
			compRGB2CMYK64(stl->_fcolor);
			stl->_cc=5;
		}
		else{
			compCMYK2RGB64(stl->_stroke);
			compCMYK2RGB64(stl->_fcolor);
			stl->_cc=4;
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();	
HIRect					hir=(*((CGRect*)(&rect)));
CGPDFDocumentRef		pdf=NULL;
bvDefRangeRectStyle*	stl;
CGRect					shape;
	
	hir=CGRectInset(hir,1,1);
	hir.size.width=hir.size.width/(double)_ext->runs().count();
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		
		shape.origin.x=CGRectGetMidX(hir)-(stl->_h/2.0)*_ext->coef_get();
		shape.origin.y=CGRectGetMidY(hir)-(stl->_v/2.0)*_ext->coef_get();
		shape.size.width=stl->_h*_ext->coef_get();
		shape.size.height=stl->_v*_ext->coef_get();
		
CGPathDrawingMode	mode=kCGPathFillStroke;
		if(stl->_visible){
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
				if(strlen(stl->_fld)==0){
					MMCGContextSetFillColor64(ctx,
											  stl->_fcolor,
											  _ext->cmyk_get());
					CGContextAddRect(ctx,shape);
					CGContextDrawPath(ctx,mode);
				}
				else{
CGPoint				pts[3];
					MMCGContextSetFillColor64(ctx,
											  stl->_fcolor,
											  _ext->cmyk_get());
					pts[0].x=shape.origin.x;
					pts[0].y=shape.origin.y;
					pts[1].x=pts[0].x;
					pts[1].y=pts[0].y+stl->_v*_ext->coef_get();
					pts[2].x=pts[1].x+stl->_h*_ext->coef_get();
					pts[2].y=pts[1].y;
					CGContextAddLines(ctx,pts,3);
					CGContextClosePath(ctx);
					CGContextDrawPath(ctx,kCGPathFill);
					
					MMCGContextSetFillColor64(ctx,
											  stl->_tcolor,
											  _ext->cmyk_get());
					pts[0].x=shape.origin.x;
					pts[0].y=shape.origin.y;
					pts[1].x=pts[0].x+stl->_h*_ext->coef_get();
					pts[1].y=pts[0].y;
					pts[2].x=pts[1].x;
					pts[2].y=pts[1].y+stl->_v*_ext->coef_get();
					CGContextAddLines(ctx,pts,3);
					CGContextClosePath(ctx);
					CGContextDrawPath(ctx,kCGPathFill);
					
					if(stl->_width>0){
						CGContextAddRect(ctx,shape);
						CGContextDrawPath(ctx,kCGPathStroke);
					}
				}
			}
			else{
				pdf=GetPDFPattern(gapp,_ext->type_get(),stl->_pat);
				if(pdf){
CGPDFPageRef			pg=CGPDFDocumentGetPage(pdf,1);
CGRect					box=CGPDFPageGetBoxRect(pg,kCGPDFCropBox);
float					color[4]={1,0,0,1 };
CGPatternCallbacks		callbacks={0,&PDFPatternPlot,NULL};
CGColorSpaceRef			bspc=CGColorSpaceCreateDeviceRGB();
CGColorSpaceRef			pspc=CGColorSpaceCreatePattern(bspc);
						CGContextSetFillColorSpace(ctx,pspc);
						CGColorSpaceRelease(pspc);
						CGColorSpaceRelease(bspc);
CGPatternRef			pat=CGPatternCreate(pdf, 
											box,
											CGAffineTransformIdentity,
											box.size.width,
											box.size.height,
											kCGPatternTilingConstantSpacing,
											false, 
											&callbacks);   
					CGContextSetFillPattern(ctx,pat,color);
					CGPatternRelease(pat);			
					CGContextAddRect(ctx,shape);
					CGContextDrawPath(ctx,mode);
#warning Plantage à identifier sur release
					//CGPDFDocumentRelease(pdf);					
				}		
				else{
					CGContextSetEmptyStyle(ctx,hir);
				}
				
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
vDefPaletteRangeRectWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteRangeRectWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

