//----------------------------------------------------------------------------
// File : vDefPaletteQuickSymbWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Symbols vdef window controller
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

#import "vDefPaletteQuickSymbWindowController.h"
#import "bvDefPaletteQuickSymb.h"
#import "bvDefQuickSymbStyle.h"
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
@implementation vDefPaletteQuickSymbPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteQuickSymbWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteQuickSymbWindowController init]",true);
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
_bTrace_("[vDefPaletteQuickSymbWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteQuickSymbWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique
	NSPopupButtonPopulateWithFields(_fsmb_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdmw_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdmh_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_frot_pop,_ext->type_get(),kOBJ_Name_,1);

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteQuickSymbWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCentroid:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutCentroid]",true);
bvDefQuickSymbStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_centro=[_cnt_chk intValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSymb:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutSymb]",true);
bvDefQuickSymbStyle*	stl;
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();	
bGenericExt*			ext=gapp->xmapMgr()->find('IPck');
picker_prm				prm={_ext->type_get(),""};
	
	if(!ext->edit(&prm)){
		return;
	}
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			strcpy(stl->_smb,prm.name);
		}
	}
	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDimW:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutDimW]",true);
bvDefQuickSymbStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickSymbWindowController doPutDimH]",true);
bvDefQuickSymbStyle*	stl;
	
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
-(IBAction)doPutRotation:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutRotation]",true);
bvDefQuickSymbStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_a=[_rot_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutAlpha:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutAlpha]",true);
bvDefQuickSymbStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_alpha=[_alp_sld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutSymbField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutSymbField]",true);
bvDefQuickSymbStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fsmb=[self getPopupValueForField:_fsmb_pop];//[_fsmb_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDimWField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutDimWField]",true);
bvDefQuickSymbStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickSymbWindowController doPutDimHField]",true);
bvDefQuickSymbStyle*	stl;
	
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
-(IBAction)doPutRotationField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutRotationField]",true);
bvDefQuickSymbStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fa=[self getPopupValueForField:_frot_pop];//[_frot_pop indexOfSelectedItem]-2+kOBJ_Name_;
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutAlphaField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutAlphaField]",true);
bvDefQuickSymbStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_falpha=[self getPopupValueForField:_falp_pop];//[_falp_pop indexOfSelectedItem]-2+kOBJ_Name_;
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
		
	[_smb_btn setEnabled:state];
	[_dmw_fld setEnabled:state];
	[_dmh_fld setEnabled:state];
	[_rot_fld setEnabled:state];
	[_alp_sld setEnabled:state];

	[_fsmb_pop setEnabled:state];
	[_fdmw_pop setEnabled:state];
	[_fdmh_pop setEnabled:state];
	[_frot_pop setEnabled:state];
	[_falp_pop setEnabled:state];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteQuickSymbWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefQuickSymbStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		return;
	}
	[_cnt_chk setIntValue:stl->_centro];
	
long	cur=[_run_tbl selectedRow]+1;
	
	if(cur){
		_ext->runs().get(cur,&stl);
		
		if(strlen(stl->_smb)>0){
			char	val[256];
			CGRect				box={{0,0},{0,0}};
			if(GetImageKind(stl->_smb)==kQTFileTypePDF){
				CGPDFDocumentRef	pdf=GetPDFIcon((bGenericMacMapApp*)_ext->getapp(),_ext->type_get(),stl->_smb);
				if(pdf!=NULL){
					box=CGPDFPageGetBoxRect(CGPDFDocumentGetPage(pdf,1),kCGPDFMediaBox);
					CGPDFDocumentRelease(pdf);
				}
			}
			else{
				CGImageRef	img=GetImageIcon((bGenericMacMapApp*)_ext->getapp(),_ext->type_get(),stl->_smb);
				if(img!=NULL){
					box.size.width=CGImageGetWidth(img);
					box.size.height=CGImageGetHeight(img);
					CGImageRelease(img);
				}
			}
			sprintf(val,"%s, (%.0fx%.0f)",stl->_smb,box.size.width,box.size.height);
			[_smb_fld setCharValue:val];
		}
		else{
			[_smb_fld setCharValue:""];
		}

		[_dmw_fld setFloatValue:stl->_h];
		[_dmh_fld setFloatValue:stl->_v];
		[_rot_fld setFloatValue:stl->_a];
		[_alp_sld setFloatValue:stl->_alpha];
			
		[_fsmb_pop selectItemAtIndex:stl->_fsmb?stl->_fsmb-kOBJ_Name_+2:0];	
		[_fdmw_pop selectItemAtIndex:stl->_fh?stl->_fh-kOBJ_Name_+2:0];	
		[_fdmh_pop selectItemAtIndex:stl->_fv?stl->_fv-kOBJ_Name_+2:0];
		[_frot_pop selectItemAtIndex:stl->_fa?stl->_fa-kOBJ_Name_+2:0];
		[_falp_pop selectItemAtIndex:stl->_falpha?stl->_falpha-kOBJ_Name_+2:0];
	}
	else{
		[_smb_fld setCharValue:""];

		[_dmw_fld setFloatValue:0];
		[_dmh_fld setFloatValue:0];
		[_rot_fld setFloatValue:0];
		[_alp_sld setFloatValue:0];

		[_fsmb_pop selectItemAtIndex:0];		
		[_fdmw_pop selectItemAtIndex:0];		
		[_fdmh_pop selectItemAtIndex:0];
		[_frot_pop selectItemAtIndex:0];
		[_falp_pop selectItemAtIndex:0];
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPaletteQuickSymbWindowController drawPreview]",true);
bGenericMacMapApp*		gapp=(bGenericMacMapApp*)_ext->getapp();	
HIRect					hir=(*((CGRect*)(&rect)));
bvDefQuickSymbStyle*	stl;
CGRect					shape;
	
	hir=CGRectInset(hir,1,1);
	hir.size.width=hir.size.width/(double)_ext->runs().count();
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		
		shape.origin.x=(hir.origin.x+hir.size.width/2.0)-(stl->_h/2.0);
		shape.origin.y=(hir.origin.y+hir.size.height/2.0)-(stl->_v/2.0);
		shape.size.width=stl->_h;
		shape.size.height=stl->_v;
		
		if(stl->_a!=0){
			CGContextSaveGState(ctx);
			CGContextTranslateCTM(ctx,
								  shape.origin.x+(stl->_h/2.0),
								  shape.origin.y+(stl->_v/2.0));
			CGContextRotateCTM(ctx,deg2rad(stl->_a));
			shape.origin.x=-(stl->_h/2.0);
			shape.origin.y=-(stl->_v/2.0);
		}
		
		if((stl->_h==0)||(stl->_v==0)){
			CGContextSetEmptyStyle(ctx,hir);
		}
		else if(GetImageKind(stl->_smb)==kQTFileTypePDF){
CGPDFDocumentRef	pdf=GetPDFIcon(gapp,_ext->type_get(),stl->_smb);
			if(pdf!=NULL){
				CGContextDrawPDFDocument(ctx,shape,pdf,1);
				CGPDFDocumentRelease(pdf);
			}
			else{
				CGContextSetEmptyStyle(ctx,hir);
			}
		}
		else{
CGImageRef	img=GetImageIcon(gapp,_ext->type_get(),stl->_smb);
			if(img!=NULL){
				CGContextDrawImage(ctx,shape,img);
				CGImageRelease(img);
			}
			else{
				CGContextSetEmptyStyle(ctx,hir);
			}
		}
		
		if(stl->_a!=0){
			CGContextRestoreGState(ctx);
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
vDefPaletteQuickSymbWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteQuickSymbWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

