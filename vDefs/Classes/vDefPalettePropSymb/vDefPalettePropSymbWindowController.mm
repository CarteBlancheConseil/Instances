//----------------------------------------------------------------------------
// File : vDefPalettePropSymbWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : proportionnal symbols vdef window controller
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

#import "vDefPalettePropSymbWindowController.h"
#import "bvDefPalettePropSymb.h"
#import "bvDefPropSymbStyle.h"
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
@implementation vDefPalettePropSymbPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPalettePropSymbWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPalettePropSymbWindowController init]",true);
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
_bTrace_("[vDefPalettePropSymbWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPalettePropSymbWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPalettePropSymbWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSymb:(id)sender{
_bTrace_("[vDefPalettePropSymbWindowController doPutSymb]",true);
bvDefPropSymbStyle*	stl;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();	
bGenericExt*		ext=gapp->xmapMgr()->find('IPck');
picker_prm			prm={_ext->type_get(),""};
double				ratio=1;
	
	if(!ext->edit(&prm)){
		return;
	}	
	if(strlen(prm.name)>0){
CGRect	box={{0,0},{0,0}};
		if(GetImageKind(stl->_smb)==kFileTypePDF){
CGPDFDocumentRef	pdf=GetPDFIcon(gapp,_ext->type_get(),prm.name);
			if(pdf!=NULL){
				box=CGPDFDocumentGetMediaBox(pdf,1);
				CGPDFDocumentRelease(pdf);
				ratio=box.size.width/box.size.height;
			}
			else{
_te_("pdf==NULL");
			}
		}
		else{
CGImageRef	img=GetImageIcon(gapp,_ext->type_get(),prm.name);
			if(img!=NULL){
				box.size.width=CGImageGetWidth(img);
				box.size.height=CGImageGetHeight(img);
				CGImageRelease(img);
				ratio=box.size.width/box.size.height;
			}
			else{
_te_("img==NULL");
			}
		}
	}
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		strcpy(stl->_smb,prm.name);
		stl->_rat=ratio;
_tm_(stl->_rat);
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFillAlpha:(id)sender{
_bTrace_("[vDefPalettePropSymbWindowController doPutFillAlpha]",true);
bvDefPropSymbStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_alpha=[_fil_sld floatValue];		
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
_bTrace_("[vDefPalettePropSymbWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefPropSymbStyle*	stl=NULL;
	
	if(!_ext->runs().get(1,&stl)){
		return;
	}
	
	if(strlen(stl->_smb)>0){
char	val[256];
CGRect	box={{0,0},{0,0}};
		if(GetImageKind(stl->_smb)==kFileTypePDF){
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
	[_fil_sld setFloatValue:stl->_alpha];
	[self checkIntfAvailability];
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPalettePropSymbWindowController drawPreview]",true);
bvDefPropSymbStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	
NSTabViewItem	*tabitem=[_tab selectedTabViewItem];
	if(tabitem==NULL){
		return;
	}
	if([_tab indexOfTabViewItem:tabitem]==1){
		[super drawPreview:rect context:ctx];
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	   
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();	
HIRect				hir=(*((CGRect*)(&rect)));
CGPDFDocumentRef	pdf;
CGImageRef			img;
CGRect				shape;
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
			shape.origin.x=CGRectGetMidX(hir)-([self sizeMax]*stl->_rat*_ext->coef_get())*0.5;
			shape.origin.y=CGRectGetMidY(hir)-([self sizeMax]*_ext->coef_get())*0.5;
			shape.size.width=[self sizeMax]*stl->_rat*_ext->coef_get();
			shape.size.height=[self sizeMax]*_ext->coef_get();
		}
		else{
			shape.origin.x=CGRectGetMidX(hir)-([self sizeMax]*stl->_rat*_ext->coef_get())*0.5;
			shape.origin.y=CGRectGetMidY(hir)-([self sizeMax]*_ext->coef_get())*0.5;
			shape.size.width=stl->_rref*stl->_rat*_ext->coef_get();
			shape.size.height=stl->_rref*_ext->coef_get();
		}
				
		if(GetImageKind(stl->_smb)==kFileTypePDF){
			pdf=GetPDFIcon(gapp,_ext->type_get(),stl->_smb);
			if(pdf!=NULL){
				CGContextDrawPDFDocument(ctx,shape,pdf,1);
				CGPDFDocumentRelease(pdf);
			}
		}
		else{
			img=GetImageIcon(gapp,_ext->type_get(),stl->_smb);
			if(img!=NULL){
				CGContextDrawImage(ctx,shape,img);
				CGImageRelease(img);
			}
		}
		
		if(stl->_rref>0){
			nsv++;
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
vDefPalettePropSymbWindowController	*controller;
NSAutoreleasePool					*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPalettePropSymbWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

