//----------------------------------------------------------------------------
// File : vDefPalettePropRectWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : proportionnal rectangle vdef window controller
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
// 28/01/2013 creation.
//----------------------------------------------------------------------------

#import "vDefPalettePropRectWindowController.h"
#import "bvDefPalettePropRect.h"
#import "bvDefPropRectStyle.h"
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

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPalettePropRectPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPalettePropRectWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPalettePropRectWindowController init]",true);
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
_bTrace_("[vDefPalettePropRectWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPalettePropRectWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPalettePropRectWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutWidth:(id)sender{
_bTrace_("[vDefPalettePropRectWindowController doPutWidth]",true);
bvDefPropRectStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_width=[_wdt_fld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFillAlpha:(id)sender{
_bTrace_("[vDefPalettePropRectWindowController doPutFillAlpha]",true);
bvDefPropRectStyle*	stl;
color_range64		rng;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(stl->_arr.count()<2){
			stl->_color[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];		
		}
		else{
			for(long j=1;j<stl->_arr.count();j++){
				stl->_arr.get(j,&rng);
				rng.clrs[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];		
				stl->_arr.put(j,&rng);
			}
		}
	}		
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutStrokeColor:(id)sender{
_bTrace_("[vDefPalettePropRectWindowController doPutStrokeColor]",true);
bvDefPropRectStyle*	stl;
NSColor*			clr=[_stk_clr color];
NSColor*			cclr;
	
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
-(IBAction)doChooseFillKind:(id)sender{
_bTrace_("[vDefPalettePropRectWindowController doChooseFillKind]",true);	
bvDefPropRectStyle*	stl;
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
			stl->_pat[0]=0;
			stl->reset();
		}
		else if([_fil_pop indexOfSelectedItem]==1){
			stl->reset();
		}
		else{
			stl->_pat[0]=0;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseColor:(id)sender{
_bTrace_("[vDefPalettePropRectWindowController doChooseFillColor]",true);
	[super doChooseColor:sender];
bvDefPropRectStyle*	stl;
NSColor*			clr=[_fil_clr color];
NSColor*			cclr;
	
	if(_ext->cmyk_get()){
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceCMYKColorSpace"];
	}
	else{
		cclr=[clr colorUsingColorSpaceName:@"NSDeviceRGBColorSpace"];
	}
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_color[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseFillPattern:(id)sender{
_bTrace_("[vDefPalettePropRectWindowController doChooseFillPattern]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*		ext=gapp->xmapMgr()->find('PPck');
picker_prm			prm={_ext->type_get(),""};
	
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
bvDefPropRectStyle*	stl;
		for(long i=1;i<=_ext->runs().count();i++){
			_ext->runs().get(i,&stl);
			strcpy(stl->_pat,prm.name);
		}		
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseClassFillColor:(id)sender{
_bTrace_("[vDefPalettePropRectWindowController doChooseClassFillColor]",true);
	[super doChooseClassFillColor:sender];
bvDefPropRectStyle*	stl;
color_range64		rng;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		for(long j=1;j<stl->_arr.count();j++){
			if([_g_run_tbl isRowSelected:j-1]==YES){
				stl->_arr.get(j,&rng);
				rng.clrs[_ext->cmyk_get()?4:3]=[_fil_sld floatValue];
				stl->_arr.put(j,&rng);
			}
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
	[_fil_sld setEnabled:([_fil_pop indexOfSelectedItem]==1)?NO:YES];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPalettePropRectWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefPropRectStyle*	stl=NULL;
color_range64		rng;
	
	if(!_ext->runs().get(1,&stl)){
		[_fil_img setImage:NULL];
		return;
	}
	
	[_wdt_fld setFloatValue:stl->_width];
	
	if(stl->_arr.count()<2){
		[_fil_sld setFloatValue:stl->_color[_ext->cmyk_get()?4:3]];
	}
	else{
		stl->_arr.get(1,&rng);
		[_fil_sld setFloatValue:rng.clrs[_ext->cmyk_get()?4:3]];
	}
	
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

bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
	if(stl->_arr.count()>1){
		[_fil_pop selectItemAtIndex:2];
		[_fil_tab selectTabViewItemAtIndex:2];				
		[_fil_img setImage:NULL];
	}
	else if(strlen(stl->_pat)==0){
		[_fil_pop selectItemAtIndex:0];
		[_fil_tab selectTabViewItemAtIndex:0];
		[_fil_img setImage:NULL];
	}
	else{
		[_fil_pop selectItemAtIndex:1];
		[_fil_tab selectTabViewItemAtIndex:1];				
		[_fil_img setImage:GetNSImagePattern(gapp,_ext->type_get(),stl->_pat)];
	}
	[self checkIntfAvailability];
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
	[super convertColor];

bvDefPropRectStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(_ext->cmyk_get()){
			compRGB2CMYK64(stl->_stroke);
		}
		else{
			compCMYK2RGB64(stl->_stroke);
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPalettePropRectWindowController drawPreview]",true);
bvDefPropRectStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	
NSTabViewItem	*tabitem=[_tab selectedTabViewItem];
	if(tabitem==NULL){
		return;
	}
NSString* str=[tabitem identifier];
	if([str compare:@"Defi"]!=NSOrderedSame){
		[super drawPreview:rect context:ctx];
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();	
HIRect				hir=(*((CGRect*)(&rect)));
CGPDFDocumentRef	pdf=NULL;
CGRect				shape;
color_range64		rng;
int					nsv=0;

	hir=CGRectInset(hir,1,1);
	
	if(stl->_arr.count()>1){
		hir.size.width=hir.size.width/(stl->_arr.count()-1);
	}
	
	for(long i=1;i<=2;i++){
		hir=(*((CGRect*)(&rect)));
		hir=CGRectInset(hir,1,1);
		if(stl->_arr.count()>1){
			hir.size.width=hir.size.width/(stl->_arr.count()-1);
		}
		
		if(i==1){
			shape.origin.x=CGRectGetMidX(hir)-([self sizeMax]*_ext->coef_get())*0.5;
			shape.origin.y=CGRectGetMidY(hir)-([self sizeMax]*_ext->coef_get())*0.5;
			shape.size.width=[self sizeMax]*_ext->coef_get();
			shape.size.height=[self sizeMax]*_ext->coef_get();
		}
		else{
			shape.origin.x=CGRectGetMidX(hir)-([self sizeMax]*_ext->coef_get())*0.5;
			shape.origin.y=CGRectGetMidY(hir)-([self sizeMax]*_ext->coef_get())*0.5;
			shape.size.width=stl->_rref*_ext->coef_get();
			shape.size.height=stl->_rref*_ext->coef_get();
		}
		
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

		if(!CGRectIsEmpty(shape)){
			nsv++;
		}
		
		if(strlen(stl->_pat)==0){
			if(stl->_arr.count()<2){
_tm_("color "+stl->_rref);
				MMCGContextSetFillColor64(ctx,
										  stl->_color,
										  _ext->cmyk_get());
				CGContextAddRect(ctx,shape);
				CGContextDrawPath(ctx,mode);
			}
			else{
_tm_("classes");
				for(long j=1;j<stl->_arr.count();j++){
					stl->_arr.get(j,&rng);
					MMCGContextSetFillColor64(ctx,
											  rng.clrs,
											  _ext->cmyk_get());
					CGContextAddRect(ctx,shape);
					CGContextDrawPath(ctx,mode);
					shape.origin.x+=hir.size.width;
				}
			}
		}
		else{
_tm_("pattern");
			pdf=GetPDFPattern(gapp,_ext->type_get(),stl->_pat);
			if(pdf){
CGPDFPageRef		pg=CGPDFDocumentGetPage(pdf,1);
CGRect				box=CGPDFPageGetBoxRect(pg,kCGPDFCropBox);
CGFloat				color[4]={1,0,0,1 };
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
				CGContextAddRect(ctx,shape);
				CGContextDrawPath(ctx,mode);
#warning Plantage à identifier sur release
				//CGPDFDocumentRelease(pdf);					
			}
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
vDefPalettePropRectWindowController	*controller;
NSAutoreleasePool					*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPalettePropRectWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

