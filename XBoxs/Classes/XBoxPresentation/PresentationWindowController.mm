//----------------------------------------------------------------------------
// File : PresentationWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Presentation XMapBox window controller
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
// 01/04/2015 creation.
//----------------------------------------------------------------------------

#import "PresentationWindowController.h"
#import "bXBoxPresentation.h"
#import "CocoaStuff.h"

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/bGenericExtLib.h>
#import <mox_intf/Carb_Utils.h>
#import <mox_intf/bStdAlert.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/CGUtils.h>
#import <mox_intf/mm_messages.h>
#import <mox_intf/bitmap_utils.h>
#import <mox_intf/endian.h>

#import <mox_intf/NSOpenSavePanelWrappers.h>
#import <mox_intf/NSContextualMenuWrappers.h>
#import <mox_intf/MacMapCWrappers.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

#pragma mark ----> Define & structs
// ---------------------------------------------------------------------------
//
// -----------
#define PresentationDraggedDatatype     @"PresentationDraggedDatatype"
#define kXMapStyleWdNewStyleMsgID		"NewStyle"
#define kXMapStyleWdNoEditorMsgID		"NoEditor"
#define kXMapStyleWdAskToSaveMsgID		"AskToSave"
#define kXMapStyleWdSaveMsgID			"Save"
#define kXMapStyleWdSaveAsMsgID			"SaveAs"
#define kXMapStyleWdDontSaveMsgID		"DontSave"
#define kXMapStyleWdAskViewNameMsgID	"NameView"
#define kXMapStyleWdLineHeigth          26
#define kXMapStyleWdMidLineHeigth       kXMapStyleWdLineHeigth/2

// ---------------------------------------------------------------------------
//
// ------------
typedef struct styl_desc{
    int		idx;
    char	name[256];
    UInt32	sign;
    int		editor;
    int		current;
    int		sub;
    int		subidx;
}styl_desc;

#pragma mark ----> Drawing utils
// ---------------------------------------------------------------------------
//
// ------------
static void PDFFillPatternPlot(void* info, CGContextRef ctx){
bGenericGraphicContext*	cg=(bGenericGraphicContext*)info;
CGPDFDocumentRef		pat=cg->getFillPattern();
CGPDFPageRef			pg=CGPDFDocumentGetPage(pat,1);
CGRect					cgr=CGPDFPageGetBoxRect(pg,kCGPDFCropBox);
float					cf=cg->getUnitCoef()*cg->getFixConv();
    cgr.size.width*=cf;
    cgr.size.height*=cf;
    
CGAffineTransform       mtx=CGPDFPageGetDrawingTransform(pg,kCGPDFCropBox,cgr,0,true);

    CGContextSaveGState(ctx);
    CGContextConcatCTM(ctx,mtx);
    CGContextDrawPDFPage(ctx,pg);
    CGContextClipToRect(ctx,cgr);
    CGContextRestoreGState(ctx);
}

// ---------------------------------------------------------------------------
//
// ------------
static void PDFStrokePatternPlot(void* info, CGContextRef ctx){
bGenericGraphicContext*	cg=(bGenericGraphicContext*)info;
CGPDFDocumentRef	pat=cg->getStrokePattern();
CGPDFPageRef		pg=CGPDFDocumentGetPage(pat,1);
CGRect				cgr=CGPDFPageGetBoxRect(pg,kCGPDFCropBox);
float				cf=cg->getUnitCoef()*cg->getFixConv();
    cgr.size.width*=cf;
    cgr.size.height*=cf;
    
CGAffineTransform       mtx=CGPDFPageGetDrawingTransform(pg,kCGPDFCropBox,cgr,0,true);
    
    CGContextSaveGState(ctx);
    CGContextConcatCTM(ctx,mtx);
    CGContextDrawPDFPage(ctx,pg);
    CGContextClipToRect(ctx,cgr);
    CGContextRestoreGState(ctx);
}

// ---------------------------------------------------------------------------
//
// -----------
static void set_fpattern(CGContextRef ctx, bGenericGraphicContext* mgt){
int					cspace;
float*				clr=mgt->getColor(&cspace,_fill);

CGPDFPageRef		pg=CGPDFDocumentGetPage(mgt->getFillPattern(),1);
CGRect				box=CGPDFPageGetBoxRect(pg,kCGPDFCropBox);
float				color[4]={1,0,0,clr[_alpha]};
CGPatternCallbacks	callbacks={0,&PDFFillPatternPlot,NULL};
CGColorSpaceRef		bspc=CGColorSpaceCreateDeviceRGB();
CGColorSpaceRef		pspc=CGColorSpaceCreatePattern(bspc);
float				cf=mgt->getUnitCoef()*mgt->getFixConv();
    CGContextSetFillColorSpace(ctx,pspc);
    CGColorSpaceRelease(pspc);
    CGColorSpaceRelease(bspc);
    box.size.width*=cf;
    box.size.height*=cf;
CGPatternRef		pat=CGPatternCreate(mgt,
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

// ---------------------------------------------------------------------------
//
// -----------
static void set_fcolor(CGContextRef ctx, bGenericGraphicContext* mgt){
int		cspace;
float*	clr=mgt->getColor(&cspace,_fill);
    if(cspace==_rgb){
        CGContextSetRGBFillColor(	ctx,
                                 clr[_red],
                                 clr[_green],
                                 clr[_blue],
                                 clr[_alpha]);
    }
    else if(cspace==_cmyk){
        CGContextSetCMYKFillColor(	ctx,
                                  clr[_cyan],
                                  clr[_magenta],
                                  clr[_yellow],
                                  clr[_black],
                                  clr[_alpha]);
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void set_spattern(CGContextRef ctx, bGenericGraphicContext* mgt){
int					cspace;
float*				clr=mgt->getColor(&cspace,_stroke);
CGPDFPageRef		pg=CGPDFDocumentGetPage(mgt->getStrokePattern(),1);
CGRect				box=CGPDFPageGetBoxRect(pg,kCGPDFCropBox);
float				color[4]={1,0,0,clr[_alpha]};
CGPatternCallbacks	callbacks={0,&PDFStrokePatternPlot,NULL};
CGColorSpaceRef		bspc=CGColorSpaceCreateDeviceRGB();
CGColorSpaceRef		pspc=CGColorSpaceCreatePattern(bspc);
float				cf=mgt->getUnitCoef()*mgt->getFixConv();
    CGContextSetStrokeColorSpace(ctx,pspc);
    CGColorSpaceRelease(pspc);
    CGColorSpaceRelease(bspc);
    box.size.width*=cf;
    box.size.height*=cf;
CGPatternRef		pat=CGPatternCreate(mgt,
                                        box,
                                        CGAffineTransformIdentity,
                                        box.size.width,
                                        box.size.height,
                                        kCGPatternTilingConstantSpacing,
                                        false,
                                        &callbacks);
    CGContextSetStrokePattern(ctx,pat,color);
    CGPatternRelease(pat);
}

// ---------------------------------------------------------------------------
//
// -----------
static void set_scolor(CGContextRef ctx, bGenericGraphicContext* mgt){
int		cspace;
float*	clr=mgt->getColor(&cspace,_stroke);
    if(cspace==_rgb){
        CGContextSetRGBStrokeColor(	ctx,
                                   clr[_red],
                                   clr[_green],
                                   clr[_blue],
                                   clr[_alpha]);
    }
    else if(cspace==_cmyk){
        CGContextSetCMYKStrokeColor(ctx,
                                    clr[_cyan],
                                    clr[_magenta],
                                    clr[_yellow],
                                    clr[_black],
                                    clr[_alpha]);
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_nostyle(bGenericStyle* styl,
                         CGContextRef ctx,
                         CGRect hir){
    CGContextSetLineWidth(ctx,1);
    CGContextSetRGBStrokeColor(ctx,0.5,0.5,0.5,1);
    CGContextMoveToPoint(ctx,hir.origin.x,hir.origin.y);
    CGContextAddLineToPoint(ctx,hir.origin.x+hir.size.width,hir.origin.y+hir.size.height);
    CGContextMoveToPoint(ctx,hir.origin.x+hir.size.width,hir.origin.y);
    CGContextAddLineToPoint(ctx,hir.origin.x,hir.origin.y+hir.size.height);
    CGContextStrokePath(ctx);
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_frame(bGenericStyle* styl,
                       CGContextRef ctx,
                       CGRect hir){
    CGContextSetLineWidth(ctx,1);
    CGContextSetRGBStrokeColor(ctx,0.5,0.5,0.5,1);
    CGContextStrokeRect(ctx,CGRectInset(hir,-1,-1));
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_icon(bGenericStyle* styl,
                      CGContextRef ctx,
                      CGRect hir,
                      bool frameIt){
bGenericGraphicContext*	mgt;
CGPDFDocumentRef		pdf;
CGImageRef				img;
int						flg=0;
CGRect					box;

    CGContextSaveGState(ctx);
    CGContextClipToRect(ctx,hir);
    for(int i=1;i<=styl->getpasscount();i++){
        mgt=styl->get_context_for_class(styl->get_curclass(),i,true);
        if(!mgt){
            break;
        }
        if((mgt->getHSize()==0)||(mgt->getVSize()==0)){
            continue;
        }
        
        box.origin.x=(hir.origin.x+hir.size.width/2.0)-(mgt->getHSize()/2.0);
        box.origin.y=(hir.origin.y+hir.size.height/2.0)-(mgt->getVSize()/2.0);
        box.size.width=mgt->getHSize();
        box.size.height=mgt->getVSize();
        
        if(mgt->getAngle()!=0){
            CGContextTranslateCTM(	ctx,
                                  box.origin.x+(mgt->getHSize()/2.0),
                                  box.origin.y+(mgt->getVSize()/2.0));
            CGContextRotateCTM(ctx,mgt->getAngle());
            box.origin.x=-(mgt->getHSize()/2.0);
            box.origin.y=-(mgt->getVSize()/2.0);
        }
        
        pdf=mgt->getPDF();
        if(pdf){
            CGContextDrawPDFDocument(ctx,box,pdf,1);
        }
        else{
            img=mgt->getImage();
            if(img){
                CGContextDrawImage(ctx,box,img);
            }
            else{
                continue;
            }
        }
        mgt->reset();
        flg++;
    }
    CGContextRestoreGState(ctx);
    if(frameIt){
        draw_frame(styl,ctx,hir);
        if(flg==0){
            draw_nostyle(styl,ctx,hir);
        }
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_circle(bGenericStyle* styl,
                        CGContextRef ctx,
                        CGRect hir,
                        bool frameIt){
bGenericGraphicContext*	mgt;
CGPathDrawingMode		mode;
int						cspace,flg=0;
float*					clr;
    
    CGContextSaveGState(ctx);
    CGContextClipToRect(ctx,hir);
    for(int i=1;i<=styl->getpasscount();i++){
        mode=kCGPathFillStroke;
        mgt=styl->get_context_for_class(styl->get_curclass(),i,true);
        if(!mgt){
            break;
        }
        if(mgt->getWidth()>0){
            CGContextSetLineWidth(ctx,mgt->getWidth());
            if(mgt->getStrokePattern()){
                set_spattern(ctx,mgt);
            }
            else{
                set_scolor(ctx,mgt);
            }
            CGContextSetLineCap(ctx,(CGLineCap)mgt->getCap());
            CGContextSetLineJoin(ctx,(CGLineJoin)mgt->getJoin());
        }
        else{
            mode=kCGPathFill;
        }
        
        if(mgt->getFillPattern()){
            set_fpattern(ctx,mgt);
        }
        else{
            clr=mgt->getColor(&cspace,_fill);
            if(clr[_alpha]==0){
                if(mode==kCGPathFill){
                    continue;
                }
                else{
                    mode=kCGPathStroke;
                }
            }
            else{
                set_fcolor(ctx,mgt);
            }
        }
        
        CGContextAddArc(ctx,
                        hir.origin.x+hir.size.width/2.0,
                        hir.origin.y+hir.size.height/2.0,
                        mgt->getVSize(),
                        mgt->getStartAngle(),
                        mgt->getEndAngle(),
                        1);
        CGContextDrawPath(ctx,mode);
        
        mgt->reset();
        flg++;
    }
    CGContextRestoreGState(ctx);
    if(frameIt){
        draw_frame(styl,ctx,hir);
        if(flg==0){
            draw_nostyle(styl,ctx,hir);
        }
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_rect(bGenericStyle* styl,
                      CGContextRef ctx,
                      CGRect hir,
                      bool frameIt){
bGenericGraphicContext*	mgt;
CGPathDrawingMode		mode;
int						cspace,flg=0;
float*					clr;
    
    CGContextSaveGState(ctx);
    CGContextClipToRect(ctx,hir);
    for(int i=1;i<=styl->getpasscount();i++){
        mode=kCGPathFillStroke;
        mgt=styl->get_context_for_class(styl->get_curclass(),i,true);
        if(!mgt){
            break;
        }
        if(mgt->getWidth()>0){
            CGContextSetLineWidth(ctx,mgt->getWidth());
            if(mgt->getStrokePattern()){
                set_spattern(ctx,mgt);
            }
            else{
                set_scolor(ctx,mgt);
            }
            CGContextSetLineCap(ctx,(CGLineCap)mgt->getCap());
            CGContextSetLineJoin(ctx,(CGLineJoin)mgt->getJoin());
        }
        else{
            mode=kCGPathFill;
        }
        
        if(mgt->getFillPattern()){
            set_fpattern(ctx,mgt);
        }
        else{
            clr=mgt->getColor(&cspace,_fill);
            if(clr[_alpha]==0){
                if(mode==kCGPathFill){
                    continue;
                }
                else{
                    mode=kCGPathStroke;
                }
            }
            else{
                set_fcolor(ctx,mgt);
            }
        }
        
        CGContextAddRect(ctx,
                         CGRectMake((hir.origin.x+hir.size.width/2.0)-(mgt->getHSize()/2.0),
                                    (hir.origin.y+hir.size.height/2.0)-(mgt->getVSize()/2.0),
                                    mgt->getHSize(),
                                    mgt->getVSize()));
        CGContextDrawPath(ctx,mode);
        mgt->reset();
        flg++;
    }
    CGContextRestoreGState(ctx);
    if(frameIt){
        draw_frame(styl,ctx,hir);
        if(flg==0){
            draw_nostyle(styl,ctx,hir);
        }
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_text(bGenericStyle* styl,
                      CGContextRef ctx,
                      CGRect hir,
                      bool frameIt){
bGenericGraphicContext*	mgt;
CGTextDrawingMode		mode;
int						cspace,flg=0;
float*					clr;
CGRect					cgr;
    
    CGContextSaveGState(ctx);
    CGContextClipToRect(ctx,hir);
    for(int i=1;i<=styl->getpasscount();i++){
        mode=kCGTextFillStroke;
        mgt=styl->get_context_for_class(styl->get_curclass(),i,true);
        if(!mgt){
            break;
        }
        if(mgt->getVSize()<=0){
            continue;
        }
        if(mgt->getFont()==NULL){
            continue;
        }
        CGContextSelectFont(ctx,mgt->getFont(),mgt->getVSize(),kCGEncodingMacRoman);
        bCoreTextInfo	ats(mgt->getFont(),mgt->getVSize(),0,0,0,"T");
        
        if(mgt->getWidth()>0){
            CGContextSetLineWidth(ctx,mgt->getWidth());
            if(mgt->getStrokePattern()){
                set_spattern(ctx,mgt);
            }
            else{
                set_scolor(ctx,mgt);
            }
            CGContextSetLineCap(ctx,(CGLineCap)mgt->getCap());
            CGContextSetLineJoin(ctx,(CGLineJoin)mgt->getJoin());
        }
        else{
            mode=kCGTextFill;
        }
        
        clr=mgt->getColor(&cspace,_backfill);
        if(cspace==_rgb){
            CGContextSetRGBFillColor(	ctx,
                                     clr[_red],
                                     clr[_green],
                                     clr[_blue],
                                     clr[_alpha]);
        }
        else if(cspace==_cmyk){
            CGContextSetCMYKFillColor(	ctx,
                                      clr[_cyan],
                                      clr[_magenta],
                                      clr[_yellow],
                                      clr[_black],
                                      clr[_alpha]);
        }
        cgr.origin.x=hir.origin.x+(hir.size.width/2.0)-((ats.textWidth()+mgt->getWidth())/2.0);
        cgr.origin.y=hir.origin.y+2.0+ats.descent();
        cgr.size.width=ats.textWidth()+mgt->getWidth();
        cgr.size.height=mgt->getVSize()+mgt->getWidth();
        CGContextFillRect(ctx,cgr);
        
        if(mgt->getFillPattern()){
            set_fpattern(ctx,mgt);
        }
        else{
            clr=mgt->getColor(&cspace,_fill);
            if(clr[_alpha]==0){
                if(mode==kCGTextFill){
                    continue;
                }
                else{
                    mode=kCGTextStroke;
                }
            }
            else{
                set_fcolor(ctx,mgt);
            }
        }
        CGContextSetTextDrawingMode(ctx,mode);
        CGContextShowStringAtPoint(	ctx,
                                   hir.origin.x+(hir.size.width/2.0)-(ats.textWidth()/2.0),
                                   hir.origin.y+2,
                                   "T",
                                   mgt->getFont(),
                                   mgt->getVSize());
        mgt->reset();
        flg++;
    }
    CGContextRestoreGState(ctx);
    if(frameIt){
        draw_frame(styl,ctx,hir);
        if(flg==0){
            draw_nostyle(styl,ctx,hir);
        }
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_line(bGenericStyle* styl,
                      CGContextRef ctx,
                      CGRect hir,
                      bool frameIt){
bGenericGraphicContext*	mgt;
int						cspace,flg=0;
float*					clr;
    
    CGContextSaveGState(ctx);
    CGContextClipToRect(ctx,hir);
    for(int i=1;i<=styl->getpasscount();i++){
        mgt=styl->get_context_for_class(styl->get_curclass(),i,true);
        if(!mgt){
            continue;
        }
        if(mgt->getWidth()>0){
            clr=mgt->getColor(&cspace,_stroke);
            if(clr[_alpha]==0){
                continue;
            }
            CGContextSetLineWidth(ctx,mgt->getWidth());
            if(mgt->getStrokePattern()){
                set_spattern(ctx,mgt);
            }
            else{
                set_scolor(ctx,mgt);
            }
            CGContextSetLineCap(ctx,(CGLineCap)mgt->getCap());
            CGContextSetLineJoin(ctx,(CGLineJoin)mgt->getJoin());
        }
        else{
            continue;
        }
        
        CGContextMoveToPoint(ctx,hir.origin.x,hir.origin.y+hir.size.height/3.0);
        CGContextAddLineToPoint(ctx,hir.origin.x+hir.size.width,hir.origin.y+hir.size.height*2.0/3.0);
        CGContextDrawPath(ctx,kCGPathStroke);
        mgt->reset();
        flg++;
    }
    CGContextRestoreGState(ctx);
    if(frameIt){
        draw_frame(styl,ctx,hir);
        if(flg==0){
            draw_nostyle(styl,ctx,hir);
        }
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_surf(bGenericStyle* styl,
                      CGContextRef ctx,
                      CGRect hir,
                      bool frameIt){
bGenericGraphicContext*	mgt;
CGPathDrawingMode		mode;
int						cspace,flg=0;
float*					clr;
    
    CGContextSaveGState(ctx);
    CGContextClipToRect(ctx,hir);
    for(int i=1;i<=styl->getpasscount();i++){
        mode=kCGPathFillStroke;
        mgt=styl->get_context_for_class(styl->get_curclass(),i,true);
        if(!mgt){
            break;
        }
        if(mgt->getWidth()>0){
            CGContextSetLineWidth(ctx,mgt->getWidth());
            if(mgt->getStrokePattern()){
                set_spattern(ctx,mgt);
            }
            else{
                set_scolor(ctx,mgt);
            }
            CGContextSetLineCap(ctx,(CGLineCap)mgt->getCap());
            CGContextSetLineJoin(ctx,(CGLineJoin)mgt->getJoin());
        }
        else{
            mode=kCGPathFill;
        }
        
        if(mgt->getFillPattern()){
            set_fpattern(ctx,mgt);
        }
        else{
            clr=mgt->getColor(&cspace,_fill);
            if(clr[_alpha]==0){
                if(mode==kCGPathFill){
                    continue;
                }
                else{
                    mode=kCGPathStroke;
                }
            }
            else{
                set_fcolor(ctx,mgt);
            }
        }
        
        CGContextMoveToPoint(ctx,hir.origin.x-(hir.size.width*(1.0+(1.0/6.0))),hir.origin.y);
        CGContextAddLineToPoint(ctx,hir.origin.x+(hir.size.width*(2.0+(1.0/6.0))),hir.origin.y+hir.size.height);
        CGContextAddLineToPoint(ctx,hir.origin.x+(hir.size.width*(2.0+(1.0/6.0))),hir.origin.y);
        CGContextAddLineToPoint(ctx,hir.origin.x-(hir.size.width*(1.0+(1.0/6.0))),hir.origin.y);
        CGContextClosePath(ctx);
        CGContextDrawPath(ctx,mode);
        mgt->reset();
        flg++;
    }
    CGContextRestoreGState(ctx);
    if(frameIt){
        draw_frame(styl,ctx,hir);
        if(flg==0){
            draw_nostyle(styl,ctx,hir);
        }
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_raster(bGenericStyle* styl,
                        CGContextRef ctx,
                        CGRect hir,
                        CFBundleRef bndl,
                        bool frameIt){
CGImageRef	img=LoadPNGImageFromBundle(bndl,CFSTR("Raster.png"));
    CGContextDrawImage(ctx,hir,img);
    CGImageRelease(img);
    if(frameIt){
        draw_frame(styl,ctx,hir);
    }
}

// ---------------------------------------------------------------------------
//
// -----------
static void draw_unknown(bGenericStyle* styl,
                         CGContextRef ctx,
                         CGRect hir,
                         CFBundleRef bndl,
                         bool frameIt){
CGImageRef	img=LoadPNGImageFromBundle(bndl,CFSTR("Unknown.png"));
    CGContextDrawImage(ctx,hir,img);
    CGImageRelease(img);
    if(frameIt){
        draw_frame(styl,ctx,hir);
    }
}

#pragma mark ----> Styles utils
// ---------------------------------------------------------------------------
//
// ------------
int styl_desc_comp(const void* a,
                   const void* b){
styl_desc*	oa=(styl_desc*)a;
styl_desc*	ob=(styl_desc*)b;
int			k=ob->editor-oa->editor;
    if(k){
        return(k);
    }
    k=oa->sign-ob->sign;
    if(k){
        return(k);
    }
    return(strcmp(oa->name,ob->name));
}


#pragma mark ----> PresentationPanel
// ---------------------------------------------------------------------------
// 
// ------------
@implementation PresentationPanel
// ---------------------------------------------------------------------------
//
// ------------
-(void)performClose:(id)sender{
}

// ---------------------------------------------------------------------------
// 
// ------------
@end



#pragma mark ----> PresentationTableCellView
// ---------------------------------------------------------------------------
//
// ------------
@implementation PresentationTableCellView

// ---------------------------------------------------------------------------
//
// ------------
@synthesize stylField=_stylField;
 
// ---------------------------------------------------------------------------
//
// ------------
-(void)dealloc{
    [_stylField release];
    _stylField=nil;
    [super dealloc];
}


// ---------------------------------------------------------------------------
//
// ------------
-(BOOL)popupStyleType{
bGenericExt*        ext=[(PresentationWindowController*)[[self window] windowController] getExt];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)ext->getapp();
bGenericStyle*      styl=(bGenericStyle*)CurLayer(gapp);
    if(!styl){
        return NO;
    }
bGenericType*       tp=(bGenericType*)CurType(gapp);
    if(!tp){
        return NO;
    }
    
// Tri des styles
styl_desc	desc;
bArray		arr(sizeof(styl_desc));
    
    desc.sub=0;
    desc.subidx=0;
    for(desc.idx=1;desc.idx<=tp->styles()->count();desc.idx++){
        tp->styles()->get_name(desc.idx,desc.name);
        desc.sign=tp->styles()->signature(desc.idx);
        desc.editor=(gapp->vdefMgr()->find(desc.sign)!=NULL);
        desc.current=!strcmp(desc.name,styl->getname());
        arr.add(&desc);
    }
    arr.sort(styl_desc_comp);
    
bGenericExt*	vdef;
bGenericExtLib*	lib;
bArray			libs(sizeof(bGenericExtLib*));
menuitem_desc*  midesc=NULL;
long            nmidesc=0,maxEdit,count;
    
// Constitution du menu vdef standards
    gapp->extMgr()->getlibs(libs,kXMLSubClassExtvDef);
    for(int i=1;i<=libs.count();i++){
        libs.get(i,&lib);
        vdef=lib->inst();
        if(!vdef->test(tp)){
            continue;
        }
        
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        lib->name(midesc[nmidesc-1].name);
        midesc[nmidesc-1].index=0;
        midesc[nmidesc-1].disabled=false;
        midesc[nmidesc-1].checked=false;
// On affecte les styles à la vdef
        count=0;
        for(int i=1;i<=arr.count();i++){
            arr.get(i,&desc);
            if((desc.sign==lib->signature())	&&
               (desc.sub==0)					){
                count++;
                desc.sub=nmidesc;
                desc.subidx=count;
                arr.put(i,&desc);
            }
        }
    }
    maxEdit=nmidesc;
    
// Constitution du menu vdef sans éditeurs
UInt32	sign=0;
char	cname[256];
    
    for(int i=1;i<=arr.count();i++){
        arr.get(i,&desc);
        if(desc.sub==0){
            if(midesc==NULL){
                nmidesc++;
                midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
            }
            else{
                nmidesc++;
                midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
            }
            b_message_string(kXMapStyleWdNoEditorMsgID,cname,ext->getbundle(),0);
            sprintf(midesc[nmidesc-1].name,"%s (%.4s)",cname,(char*)&desc.sign);
            midesc[nmidesc-1].index=0;
            midesc[nmidesc-1].disabled=false;
            midesc[nmidesc-1].checked=false;
// On affecte les styles sans éditeurs
            sign=desc.sign;
            count=0;
            while(sign==desc.sign){
                count++;
                desc.sub=nmidesc;
                desc.subidx=count;
                arr.put(i,&desc);
                i++;
                if(!arr.get(i,&desc)){
                    break;
                }
            }
            i--;
        }
    }
    
// submenus creation
    for(int i=0;;i++){
        if(midesc[i].index!=0){
            break;
        }
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        b_message_string(kXMapStyleWdNewStyleMsgID,midesc[nmidesc-1].name,ext->getbundle(),0);
        midesc[nmidesc-1].index=i+1;
        midesc[nmidesc-1].disabled=maxEdit<=i;
        midesc[nmidesc-1].checked=false;
        
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        strcpy(midesc[nmidesc-1].name,"-");
        midesc[nmidesc-1].index=i+1;
        midesc[nmidesc-1].disabled=false;
        midesc[nmidesc-1].checked=false;
    }
    
// Affectation des styles aux sous menus
    for(int i=1;i<=arr.count();i++){
        arr.get(i,&desc);
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        strcpy(midesc[nmidesc-1].name,desc.name);
        midesc[nmidesc-1].index=desc.sub;
        midesc[nmidesc-1].disabled=false;
        midesc[nmidesc-1].checked=desc.current;
    }
    
// Menu contextuel
NSPoint nspt=[self convertPoint:NSMakePoint(kXMapStyleWdMidLineHeigth,kXMapStyleWdMidLineHeigth) toView:[[self window] contentView]];
CGPoint pt=CGPointMake(nspt.x,nspt.y);
long    res=popUpContextMenuWithCGPointAndNSWindow(pt,
                                                   (void*)[self window],
                                                   midesc,
                                                   nmidesc);
    free(midesc);
    if(res<10000){
        return NO;
    }
// Créer un nouveau style
long    high=res/10000;
long    low=res%10000;
    
    count=0;
    if(low==0){
        for(int i=1;i<=libs.count();i++){
            libs.get(i,&lib);
            vdef=lib->inst();
            if(!vdef->test(tp)){
                continue;
            }
            count++;
            sign=lib->signature();
#ifdef __LITTLE_ENDIAN__
            LBSwapWord(&sign,sizeof(UInt32));
#endif
            if(count==high){
                if(tp->styles()->create(sign)){
                    if(gapp->layersAccessCtx()->change(gapp->layersAccessCtx()->get_current(),
                                                       tp->styles()->count())){
                    }
                }
                break;
            }
        }
    }
// Changer de style
    else if((low>0)&&(high>0)){
        for(int i=1;i<=arr.count();i++){
            arr.get(i,&desc);
            if((desc.sub==high)&&(desc.subidx==(low-1))){
                if(!desc.current){
                    if(gapp->layersAccessCtx()->change(gapp->layersAccessCtx()->get_current(),
                                                       desc.idx)){
                    }
                }
            }
        }	
    }
    return YES;
}

// ---------------------------------------------------------------------------
//
// ------------
-(BOOL)popupStyleDocument{
bGenericExt*        ext=[(PresentationWindowController*)[[self window] windowController] getExt];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)ext->getapp();
bGenericStyle*      styl=(bGenericStyle*)CurLayer(gapp);
    if(!styl){
        return NO;
    }
    
// Tri des styles
styl_desc	desc;
bArray		arr(sizeof(styl_desc));
    
    desc.sub=0;
    desc.subidx=0;
    for(desc.idx=1;desc.idx<=gapp->document()->styles()->count();desc.idx++){
        gapp->document()->styles()->get_name(desc.idx,desc.name);
        desc.sign=gapp->document()->styles()->signature(desc.idx);
        desc.editor=(gapp->vdefMgr()->find(desc.sign)!=NULL);
        desc.current=!strcmp(desc.name,styl->getname());
        arr.add(&desc);
    }
    arr.sort(styl_desc_comp);
    
bGenericExt*	vdef;
bGenericExtLib*	lib;
bArray			libs(sizeof(bGenericExtLib*));
menuitem_desc*  midesc=NULL;
long            nmidesc=0,maxEdit,count;
    
// Constitution du menu vdef standards
    gapp->extMgr()->getlibs(libs,kXMLSubClassExtvDef);
    for(int i=1;i<=libs.count();i++){
        libs.get(i,&lib);
        vdef=lib->inst();
        if(!vdef->test(NULL)){
            continue;
        }
        
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        lib->name(midesc[nmidesc-1].name);
        midesc[nmidesc-1].index=0;
        midesc[nmidesc-1].disabled=false;
        midesc[nmidesc-1].checked=false;
        // On affecte les styles à la vdef
        count=0;
        for(int i=1;i<=arr.count();i++){
            arr.get(i,&desc);
            if((desc.sign==lib->signature())	&&
               (desc.sub==0)					){
                count++;
                desc.sub=nmidesc;
                desc.subidx=count;
                arr.put(i,&desc);
            }
        }
    }
    maxEdit=nmidesc;
    
// Constitution du menu vdef sans éditeurs
UInt32	sign=0;
char	cname[256];
    
    for(int i=1;i<=arr.count();i++){
        arr.get(i,&desc);
        if(desc.sub==0){
            if(midesc==NULL){
                nmidesc++;
                midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
            }
            else{
                nmidesc++;
                midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
            }
            b_message_string(kXMapStyleWdNoEditorMsgID,cname,ext->getbundle(),0);
            sprintf(midesc[nmidesc-1].name,"%s (%.4s)",cname,(char*)&desc.sign);
            midesc[nmidesc-1].index=0;
            midesc[nmidesc-1].disabled=false;
            midesc[nmidesc-1].checked=false;
// On affecte les styles sans éditeurs
            sign=desc.sign;
            count=0;
            while(sign==desc.sign){
                count++;
                desc.sub=nmidesc;
                desc.subidx=count;
                arr.put(i,&desc);
                i++;
                if(!arr.get(i,&desc)){
                    break;
                }
            }
            i--;
        }
    }
    
// submenus creation
    for(int i=0;;i++){
        if(midesc[i].index!=0){
            break;
        }
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        b_message_string(kXMapStyleWdNewStyleMsgID,midesc[nmidesc-1].name,ext->getbundle(),0);
        midesc[nmidesc-1].index=i+1;
        midesc[nmidesc-1].disabled=maxEdit<=i;
        midesc[nmidesc-1].checked=false;
        
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        strcpy(midesc[nmidesc-1].name,"-");
        midesc[nmidesc-1].index=i+1;
        midesc[nmidesc-1].disabled=false;
        midesc[nmidesc-1].checked=false;
    }
    
    // Affectation des styles aux sous menus
    for(int i=1;i<=arr.count();i++){
        arr.get(i,&desc);
        if(midesc==NULL){
            nmidesc++;
            midesc=(menuitem_desc*)malloc(sizeof(menuitem_desc));
        }
        else{
            nmidesc++;
            midesc=(menuitem_desc*)realloc(midesc,sizeof(menuitem_desc)*nmidesc);
        }
        strcpy(midesc[nmidesc-1].name,desc.name);
        midesc[nmidesc-1].index=desc.sub;
        midesc[nmidesc-1].disabled=false;
        midesc[nmidesc-1].checked=desc.current;
    }
    
// Menu contextuel
NSPoint nspt=[self convertPoint:NSMakePoint(kXMapStyleWdMidLineHeigth,kXMapStyleWdMidLineHeigth) toView:[[self window] contentView]];
CGPoint pt=CGPointMake(nspt.x,nspt.y);
long    res=popUpContextMenuWithCGPointAndNSWindow(pt,
                                                   (void*)[self window],
                                                   midesc,
                                                   nmidesc);
    free(midesc);
    if(res<10000){
        return NO;
    }
// Créer un nouveau style
long    high=res/10000;
long    low=res%10000;
        
    count=0;
    if(low==0){
        for(int i=1;i<=libs.count();i++){
            libs.get(i,&lib);
            vdef=lib->inst();
            if(!vdef->test(NULL)){
                continue;
            }
            count++;
            sign=lib->signature();
#ifdef __LITTLE_ENDIAN__
            LBSwapWord(&sign,sizeof(UInt32));
#endif
            if(count==high){
                if(gapp->document()->styles()->create(sign)){
                    if(gapp->layersAccessCtx()->change(gapp->layersAccessCtx()->get_current(),
                                                       gapp->document()->styles()->count())){
                    }
                }
                break;
            }
        }
    }
// Changer de style
    else if((low>0)&&(high>0)){
        for(int i=1;i<=arr.count();i++){
            arr.get(i,&desc);
            if((desc.sub==high)&&(desc.subidx==(low-1))){
                if(!desc.current){
                    if(gapp->layersAccessCtx()->change(gapp->layersAccessCtx()->get_current(),
                                                       desc.idx)){
                    }
                }
            }
        }	
    }
    return YES;
}

// ---------------------------------------------------------------------------
//
// ------------
-(BOOL)popupStyle{
bGenericExt*        ext=[(PresentationWindowController*)[[self window] windowController] getExt];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)ext->getapp();
bGenericStyle*      styl=(bGenericStyle*)CurLayer(gapp);
    if(!styl){
        return NO;
    }
    [(PresentationWindowController*)[[self window] windowController] modify];
bGenericType*       tp=(bGenericType*)CurType(gapp);
    if(!tp){
        return [self popupStyleDocument];
    }
    return [self popupStyleType];
}

// ---------------------------------------------------------------------------
//
// ------------
-(BOOL)popupClass{
bGenericExt*        ext=[(PresentationWindowController*)[[self window] windowController] getExt];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)ext->getapp();
bGenericStyle*      styl=(bGenericStyle*)CurLayer(gapp);
    if(!styl){
        return NO;
    }
bGenericType*       tp=(bGenericType*)CurType(gapp);
    if(!tp){
        return NO;
    }
    
// Constitution du menu
menuitem_desc*  midesc=NULL;
long            nmidesc=0;
int             idx=tp->fields()->get_index(styl->getclassfield());
int             d=0;
char*           pstr;
double          v;
   
    tp->fields()->get_decs(idx,&d);
    nmidesc=styl->getclasscount()-1;
    midesc=new menuitem_desc[nmidesc];
    for(int i=1;i<=nmidesc;i++){
        pstr=styl->getclassname(i);
        if(pstr){
            sprintf(midesc[i-1].name," %s",pstr);
            if(strlen(midesc[i-1].name)==0){
                v=styl->getclassbound(i);
                sprintf(midesc[i-1].name," %.*f",d,v);
            }
        }
        else{
            v=styl->getclassbound(i);
            sprintf(midesc[i-1].name," %.*f",d,v);
        }
        midesc[i-1].index=0;
        midesc[i-1].disabled=false;
        midesc[i-1].checked=false;
    }
    midesc[styl->get_curclass()-1].checked=true;
    
// Menu contextuel
NSPoint nspt=[self convertPoint:NSMakePoint(kXMapStyleWdMidLineHeigth,kXMapStyleWdLineHeigth) toView:[[self window] contentView]];
CGPoint pt=CGPointMake(nspt.x,nspt.y);
long    res=popUpContextMenuWithCGPointAndNSWindow(pt,
                                                   (void*)[self window],
                                                   midesc,
                                                   nmidesc);
    delete midesc;
    if(res>0){
        styl->set_curclass(res);
    }
    return YES;
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)mouseDownForCell:(NSEvent*)theEvent{
_bTrace_("[PresentationTableCellView mouseDownForCell]",false);
// Test pour éviter les problèmes d'incohérence entre le style courant
// et la ligne sélectionnée lors l'un clic dans la fenêtre désactivée
// Ne devrait plus survenir avec le changement de sélection
// au firstClic (cf mouseDown de PresentationTableView
/**/
NSTableView*        tvw=[[self superview] superview];
    if([tvw rowViewAtRow:[tvw selectedRow] makeIfNecessary:NO]!=[self superview]){
_tw_("SACREBLEU !!!");
        return;
    }
/**/
    
bGenericExt*        ext=[(PresentationWindowController*)[[self window] windowController] getExt];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)ext->getapp();
NSPoint             pt=[self convertPoint:[theEvent locationInWindow] fromView:nil];
    
    if(pt.x<kXMapStyleWdLineHeigth){
// On est dans la visu
    }
    else if(pt.x<(kXMapStyleWdLineHeigth+kXMapStyleWdMidLineHeigth)){
// On est dans la zone boutons
        if(pt.y<=kXMapStyleWdMidLineHeigth){
// Bouton popup style
            if([self popupStyle]){
            }
        }
        else{
// Bouton popup classe
            if([self popupClass]){
                [(PresentationWindowController*)[[self window] windowController] redraw];
            }
        }
    }
    else if(pt.y<=kXMapStyleWdMidLineHeigth){
// On est dans la zone style
        if([theEvent clickCount]>1){
// Double clic : edit style
bGenericStyle*	styl=(bGenericStyle*)CurLayer(gapp);
            if(!styl){
                return;
            }
bGenericType*	tp=(bGenericType*)CurType(gapp);
int				sidx;
            if(tp){
                sidx=tp->styles()->index(styl->root());
                if(!tp->styles()->edit(sidx,_kNULLSign_)){
                }
            }
            else{
                sidx=gapp->document()->styles()->index(styl->root());
                if(!gapp->document()->styles()->edit(sidx,_kNULLSign_)){
                }
            }
        }
    }
    else{
// On est dans la zone type
// Double clic :
        if([theEvent clickCount]>1){
bGenericType*	tp=(bGenericType*)CurType(gapp);
            if(tp){
// + shift : centrer sur les objets
                if([theEvent modifierFlags]&NSShiftKeyMask){
ivx_rect            bnd;
i2dvertex           vx;
                    tp->iterator()->bounds(&bnd);
                    ivr_mid(&bnd,&vx);
                    gapp->mapIntf()->setScreenCenter(vx);
                }
                else if([theEvent modifierFlags]&NSCommandKeyMask){
// + cmd : sélectionner les objets du type
bGenericExt*        ext=gapp->xmapMgr()->find('sall');
                    if(ext){
                        ext->process(kExtProcessCallWithParams,tp);
                    }
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
//
// ------------
@end



#pragma mark ----> PresentationTableView
// ---------------------------------------------------------------------------
//
// ------------
@implementation PresentationTableView

// ---------------------------------------------------------------------------
//
// ------------
-(void)mouseDown:(NSEvent*)theEvent{
    [super mouseDown:theEvent];
NSPoint     pt=[self convertPoint:[theEvent locationInWindow] fromView:nil];
NSInteger   row=[self rowAtPoint:pt];
    
    if(row>=0){
// firstClic en réactivation de fenêtre, dans le cas ou la cellule cliquée n'est pas celle sélectionnée
/**/
        if([self isRowSelected:row]==NO){
bGenericExt*        ext=[(PresentationWindowController*)[[self window] windowController] getExt];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)ext->getapp();
            gapp->layersAccessCtx()->set_current(row+1);
            [self selectRowIndexes:[NSIndexSet indexSetWithIndex:row] byExtendingSelection:NO];
        }
/**/
PresentationTableCellView*  cell=[self viewAtColumn:0 row:row makeIfNecessary:NO];
        [cell mouseDownForCell:theEvent];
    }
}

// ---------------------------------------------------------------------------
//
// ------------
@end



#pragma mark ----> PresentationWindowController
// ---------------------------------------------------------------------------
// 
// ------------
@implementation PresentationWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[PresentationWindowController init]",true);
	self=[super init];
	if(self){
        _ld=-1;
        _lv=-1;
        _reload=NO;
        _refresh=NO;
        _modi=NO;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[PresentationWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[PresentationWindowController awakeFromNib]",true);
//bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    
    [self populateTypes];
    [self populateViews];

    [_stl_viw registerForDraggedTypes:[NSArray arrayWithObjects:PresentationDraggedDatatype,nil]];
    
_tm_("tableView :"+(void*)_stl_viw);
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[PresentationWindowController close]",true);
_tm_((void*)self);
	[super close];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)redraw{
    _reload=YES;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)modify{
    _modi=YES;
}

// ---------------------------------------------------------------------------
//
// -----------
-(bGenericExt*)getExt{
    return _ext;
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doMoveUp:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    if(gapp->layersAccessCtx()->move(gapp->layersAccessCtx()->get_current(),-1)){
        _reload=YES;
        _modi=YES;
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doMoveDown:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    if(gapp->layersAccessCtx()->move(gapp->layersAccessCtx()->get_current(),1)){
        _reload=YES;
        _modi=YES;
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doRemove:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    if(gapp->layersAccessCtx()->remove(gapp->layersAccessCtx()->get_current())){
        _reload=YES;
        _modi=YES;
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doLock:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericStyle*      styl=(bGenericStyle*)CurLayer(gapp);
    if(!styl){
        return;
    }
    _reload=YES;
    _modi=YES;
   _ld--;
    
    gapp->layersAccessCtx()->setselectable(!styl->selectable());
    
bool            status=styl->selectable();
int				idx= gapp->layersAccessCtx()->get_current();
bGenericType*	tp=(bGenericType*)CurType(gapp);
bGenericStyle*	stl;
    
NSUInteger      modifiers=[[NSApp currentEvent] modifierFlags];

    if(modifiers&NSCommandKeyMask){
        for(int i=1;i<= gapp->layersAccessCtx()->count();i++){
            if(i==idx){
                continue;
            }
            stl= gapp->layersAccessCtx()->get(i);
            if(stl==NULL){
                continue;
            }
             gapp->layersAccessCtx()->set_current(i);
             gapp->layersAccessCtx()->setselectable(!status);
        }
         gapp->layersAccessCtx()->set_current(idx);
    }

    if(modifiers&NSShiftKeyMask){
        for(int i=1;i<= gapp->layersAccessCtx()->count();i++){
            if(i==idx){
                continue;
            }
            stl= gapp->layersAccessCtx()->get(i);
            if(stl==NULL){
                continue;
            }
            if(stl->gettype()==tp){
                 gapp->layersAccessCtx()->set_current(i);
                 gapp->layersAccessCtx()->setselectable(status);
            }
        }
         gapp->layersAccessCtx()->set_current(idx);
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doHide:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericStyle*      styl=(bGenericStyle*)CurLayer(gapp);
    if(!styl){
        return;
    }
    _reload=YES;
    _modi=YES;

    gapp->layersMgr()->StopDraw();
    gapp->layersAccessCtx()->setvisible(!styl->visible());
    
bool            status=styl->visible();
int				idx=gapp->layersAccessCtx()->get_current();
bGenericType*	tp=(bGenericType*)CurType(gapp);
bGenericStyle*	stl;
NSUInteger      modifiers=[[NSApp currentEvent] modifierFlags];
    
    if(modifiers&NSCommandKeyMask){
        for(int i=1;i<=gapp->layersAccessCtx()->count();i++){
            if(i==idx){
                continue;
            }
            stl=gapp->layersAccessCtx()->get(i);
            if(stl==NULL){
                continue;
            }
            gapp->layersAccessCtx()->set_current(i);
            gapp->layersAccessCtx()->setvisible(!status);
        }
        gapp->layersAccessCtx()->set_current(idx);
    }
    
    if(modifiers&NSShiftKeyMask){
        for(int i=1;i<=gapp->layersAccessCtx()->count();i++){
            if(i==idx){
                continue;
            }
            stl=gapp->layersAccessCtx()->get(i);
            if(stl==NULL){
                continue;
            }
            if(stl->gettype()==tp){
                gapp->layersAccessCtx()->set_current(i);
                gapp->layersAccessCtx()->setvisible(status);
            }
        }
        gapp->layersAccessCtx()->set_current(idx);
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doTrack:(id)sender{
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doStyleMgr:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*        ext=gapp->xboxMgr()->find('MgrS');
    if((ext)&&(ext->test(NULL))){
        gapp->xboxMgr()->edit(NULL,'MgrS',NULL);
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doAddStyle:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    if(gapp->layersAccessCtx()->add([sender tag],1)){
        gapp->layersAccessCtx()->set_current(gapp->layersAccessCtx()->count());
        _reload=YES;
        _ld=-1;
        _modi=true;
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doViewMgr:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*        ext=gapp->xmapMgr()->find('MgrV');
    if((ext)&&(ext->test(NULL))){
        gapp->xmapMgr()->edit(NULL,'MgrV',NULL);
        [self populateViews];
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doSaveView:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    gapp->viewMgr()->save();
    _modi=NO;
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doScaleRef:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericExt*        ext=gapp->vdefMgr()->find('SRef');
bGenericType*       tp;
bGenericStyle*      styl;
int                 sidx;
    
    if(ext){
        if(ext->process(kExtProcessCallFromIntf,NULL)){
            for(int i=1;i<=gapp->layersAccessCtx()->count();i++){
                styl=gapp->layersAccessCtx()->get(i);
                if(styl->visible()){
                    tp=styl->gettype();
                    if(tp){
                        sidx=tp->styles()->index(styl->root());
                        if(!tp->styles()->edit(sidx,'SRef')){
                        }
                    }
                    else{
                        sidx=gapp->document()->styles()->index(styl->root());
                        if(!gapp->document()->styles()->edit(sidx,'SRef')){
                        }
                    }
                }
            }
            ext->process(kExtProcessCallSetData,NULL);
        }
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doLegend:(id)sender{
_bTrace_("[PresentationWindowController doLegend]",false);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericStyle*	styl;
int				nlines=0;
//CGSize			sz;
CGRect			bbox;
    
    bbox.origin.x=0;
    bbox.origin.y=0;
    bbox.size.width=[[self window] frame].size.width;
    bbox.size.height=0;
    
    for(int i=1;i<=gapp->layersAccessCtx()->count();i++){
        styl=gapp->layersAccessCtx()->get(i);
        if(styl->visible()){
/*			if(styl->legend_size(&sz)){
             if(sz.width>bbox.size.width){
             bbox.size.width=sz.width;
             }
             bbox.size.height+=sz.height;
             }
             else{*/
            nlines=(styl->getclasscount());
            bbox.size.height+=(nlines*kXMapStyleWdLineHeigth);
//			}
        }
    }
    
    if(bbox.size.height==0){
        return;
    }
    
char    path[PATH_MAX];
    if(NSPutFilePath("pdf",
                     cNSUTF8StringEncoding,
                     NULL,
                     path)==cNSCancelButton){
        return;
    }
CFStringRef cfs=CFStringCreateWithCString(kCFAllocatorDefault,path,kCFStringEncodingUTF8);
    if(cfs==NULL){
_te_("CFStringCreateWithCString return NULL for "+path);
        return;
    }
CFURLRef    url=CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
                                              cfs,
                                              kCFURLPOSIXPathStyle,
                                              false);
    CFRelease(cfs);
    if(url==NULL){
_te_("CFURLCreateWithFileSystemPath return NULL for "+path);
        return;
    }
char			name[256];
bGenericType*	tp;
CGContextRef	ctx=CGPDFContextCreateWithURL(url,&bbox,NULL);
    if(!ctx){
        CFRelease(url);
_te_("CGPDFContextCreateWithURL failed");
        return;
    }
    CFRelease(url);
    
    CGContextBeginPage(ctx,&bbox);
    CGContextClipToRect(ctx,bbox);
    
    bbox.origin.y=bbox.size.height;
    bbox.size.height=kXMapStyleWdLineHeigth;
    bbox.size.width=kXMapStyleWdLineHeigth;
    
int	cur;
    for(int i=1;i<=gapp->layersAccessCtx()->count();i++){
        styl=gapp->layersAccessCtx()->get(i);
        if(!styl->visible()){
            continue;
        }
        
/*		if(styl->legend_size(&sz)){
         bbox.origin.y-=sz.height;
         styl->legend(ctx,bbox.origin);
         continue;
         }*/
        
        bbox.origin.y-=kXMapStyleWdLineHeigth;
        CGContextSetRGBFillColor(ctx,0,0,0,1);
        tp=styl->gettype();
        if(tp){
            tp->name(name);
        }
        else{
            message_string(kMsgVirtual,name,1);
        }
        CGContextSelectFont(ctx,"Helvetica-Bold",9,kCGEncodingMacRoman);
        CGContextShowStringAtPoint(ctx,
                                   bbox.origin.x-bbox.size.width+bbox.size.width+3,
                                   bbox.origin.y+2+(bbox.size.height/2.0),
                                   name,
                                   "Helvetica-Bold",
                                   9);
        
        CGContextSelectFont(ctx,"Helvetica",9,kCGEncodingMacRoman);
        CGContextShowStringAtPoint(ctx,
                                   bbox.origin.x-bbox.size.width+bbox.size.width+3,
                                   bbox.origin.y+2,
                                   styl->getname(),
                                   "Helvetica",
                                   9);
        
        
        cur=styl->get_curclass();
        for(int j=1;j<styl->getclasscount();j++){
            styl->set_curclass(j);
            bbox.origin.y-=kXMapStyleWdLineHeigth;
            switch(styl->getdrawingmethod()){
                case kIconStyleKind_:
                    draw_icon(styl,ctx,CGRectInset(bbox,1,1),false);
                    break;
                case kCircleStyleKind_:
                    draw_circle(styl,ctx,CGRectInset(bbox,1,1),false);
                    break;
                case kRectStyleKind_:
                    draw_rect(styl,ctx,CGRectInset(bbox,1,1),false);
                    break;
                case kTextStyleKind_:
                    draw_text(styl,ctx,CGRectInset(bbox,1,1),false);
                    break;
                case kLineStyleKind_:
                    draw_line(styl,ctx,CGRectInset(bbox,1,1),false);
                    break;
                case kSurfStyleKind_:
                    draw_surf(styl,ctx,CGRectInset(bbox,1,1),false);
                    break;
                case kRasterStyleKind_:
                    draw_raster(styl,ctx,CGRectInset(bbox,1,1),_ext->getbundle(),false);
                    break;
                default:
                    draw_unknown(styl,ctx,CGRectInset(bbox,1,1),_ext->getbundle(),false);
                    break;
            }
            if(styl->getclassname(j)){
                CGContextShowStringAtPoint(	ctx,
                                           bbox.origin.x+bbox.size.width+3,
                                           bbox.origin.y+bbox.size.height/2.0-3,
                                           styl->getclassname(j),
                                           "Helvetica",
                                           9);
            }
            //bbox.origin.y-=kXMapStyleWdLineHeigth;
        }
        styl->set_curclass(cur);
    }
    
    CGContextEndPage(ctx);
    CGContextRelease(ctx);
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doChooseView:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    [self askForViewSave];
// le viewmgr recharge la vue précédente au set_current
// pour que l'on soit sûr de retrouver la vue avant modification
// si nécessaire
    gapp->viewMgr()->set_current([sender tag]);
    _reload=YES;
    _ld=-1;
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericStyle*      styl=gapp->layersAccessCtx()->get([_stl_viw selectedRow]+1);
    [_mup_btn setEnabled:(styl!=NULL)];
    [_mdn_btn setEnabled:(styl!=NULL)];
    [_rmv_btn setEnabled:(styl!=NULL)];
    [_lck_btn setEnabled:(styl!=NULL)];
    [_hid_btn setEnabled:(styl!=NULL)];
    if(styl){
        [_lck_btn setIntValue:!styl->selectable()];
        [_hid_btn setIntValue:!styl->visible()];
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)askForViewSave{
_bTrace_("[PresentationWindowController askForViewSave]",true);
    if(!_modi){
        return;
    }
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();

char	msg[__MESSAGE_STRING_LENGTH_MAX__];
char	btn1[__MESSAGE_STRING_LENGTH_MAX__];
char	btn2[__MESSAGE_STRING_LENGTH_MAX__];
char	btn3[__MESSAGE_STRING_LENGTH_MAX__];

    b_message_string(kXMapStyleWdAskToSaveMsgID,msg,_ext->getbundle(),0);
    b_message_string(kXMapStyleWdSaveMsgID,btn1,_ext->getbundle(),0);
    b_message_string(kXMapStyleWdDontSaveMsgID,btn2,_ext->getbundle(),0);
    b_message_string(kXMapStyleWdSaveAsMsgID,btn3,_ext->getbundle(),0);

bAlertWarningYes	alrt(msg,"",false,SHRT_MAX,btn1,btn2,btn3);

    if(alrt.hit_button()==kAlertStdAlertOKButton){
        gapp->viewMgr()->save();
    }
    else if(alrt.hit_button()==kAlertStdAlertOtherButton){
        b_message_string(kXMapStyleWdAskViewNameMsgID,msg,_ext->getbundle(),0);


//#error En procédant comme ça on duplique la vue non modifiée
        gapp->viewMgr()->duplicate(gapp->viewMgr()->get_current());

//		_gapp->viewMgr()->get_name(_gapp->viewMgr()->count(),btn1);
//		if(GetAName(btn1,msg)){
//_tm_("saving as:"+btn1);
//			_gapp->viewMgr()->set_name(_gapp->viewMgr()->count(),btn1);
//		}

        gapp->viewMgr()->save();
        gapp->viewMgr()->get_name(btn2);
        gapp->viewMgr()->get_name(gapp->viewMgr()->count(),btn1);
        gapp->viewMgr()->set_name(gapp->viewMgr()->count(),"$$tmp$$");

        if(!GetAName(btn1,msg,true)){
//_gapp->viewMgr()->get_name(_gapp->viewMgr()->count(),btn1);
            gapp->viewMgr()->remove(gapp->viewMgr()->count());
            return;
        }
        if(strlen(btn1)==0){
            gapp->viewMgr()->get_name(gapp->viewMgr()->count(),btn1);
        }
        gapp->viewMgr()->set_name(btn1);
        gapp->viewMgr()->set_name(gapp->viewMgr()->count(),btn2);
    }
    _modi=NO;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)populateTypes{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
char                str[256];
NSMenuItem*         item;
bGenericType*       tp;
    
    NSPopupButtonRemoveItemsFrom(_stl_pop,3);
    for(long i=1;i<=gapp->typesMgr()->count();i++){
        tp=gapp->typesMgr()->get(i);
        tp->name(str);
        NSPopupButtonAddMenuItemValue(_stl_pop,str);
        item=[_stl_pop itemAtIndex:[_stl_pop numberOfItems]-1];
        [item setTag:i];
        [item setTarget:self];
        [item setAction:@selector(doAddStyle:)];
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)populateViews{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
char                str[256];
NSMenuItem*         item;
    
    NSPopupButtonRemoveItemsFrom(_viw_pop,7);
    for(long i=1;i<=gapp->viewMgr()->count();i++){
        gapp->viewMgr()->get_name(i,str);
        NSPopupButtonAddMenuItemValue(_viw_pop,str);
        item=[_viw_pop itemAtIndex:[_viw_pop numberOfItems]-1];
        [item setTag:i];
        [item setTarget:self];
        [item setAction:@selector(doChooseView:)];
        if(gapp->viewMgr()->get_current()==i){
            [item setState:NSOnState];
        }
    }
}


#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(void)prepareForClose{
    [self askForViewSave];
	[super prepareForClose];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)idle{
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
    if(gapp->layersAccessCtx()->get_current()!=_lv){
        if(gapp->layersAccessCtx()->get_current()>0){
            [_stl_viw selectRowIndexes:[NSIndexSet indexSetWithIndex:gapp->layersAccessCtx()->get_current()-1]
                  byExtendingSelection:NO];
        }
        _lv=gapp->layersAccessCtx()->get_current();
        [self populateViews];
    }
    if(_ld<gapp->mapIntf()->drawCount()||_reload){
        [_stl_viw reloadData];
        _refresh=YES;
        _reload=NO;
        _lv=-1;
        if(_refresh){
            [[[self window] contentView] setNeedsDisplay:YES];
            _refresh=NO;
        }
        _ld=gapp->mapIntf()->drawCount();
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)checkMacMapEvent{
    [super checkMacMapEvent];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bArray*				arr=gapp->eventMgr()->events();
bGenericEvent*		evt;
    
    for(long i=1;i<=arr->count();i++){
        arr->get(i,&evt);
        if( (evt->action()==kEventActionCreate)     &&
            (evt->kind()==kEventKindTypeElement)    ){
            [self populateTypes];
        }
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)clickAtLocation:(CGPoint)loc{
    if([_trk_btn intValue]==1){
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bArray*             ga;
int                 i,n=gapp->layersAccessCtx()->count();
bGenericStyle*      stl;

        for(i=n;i>0;i--){
            stl=gapp->layersAccessCtx()->get(i);
            if(!stl){
                continue;
            }
            ga=stl->objsatpoint(&loc,true);
            if(!ga){
                continue;
            }
            if(ga->count()<=0){
                delete ga;
                continue;
            }
            if(ga->count()>=1){
                gapp->layersAccessCtx()->set_current(i);
                delete ga;
                _reload=YES;
                break;
            }
            delete ga;
        }
    }
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
    return gapp->layersAccessCtx()->count();
}

// ---------------------------------------------------------------------------
//
// -----------
-(NSView*)tableView:(NSTableView*)tableView
 viewForTableColumn:(NSTableColumn *)tableColumn
                row:(NSInteger)rowIndex{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericStyle*      styl=gapp->layersAccessCtx()->get(rowIndex+1);
    if(!styl){
        return nil;
    }
PresentationTableCellView*  res=[tableView makeViewWithIdentifier:tableColumn.identifier owner:self];
    if(res==nil){
        return nil;
    }
    
char            name[256];
bGenericType*   tp=styl->gettype();
    if(tp){
        tp->name(name);
    }
    else{
        message_string(kMsgVirtual,name,1);
    }
    res.textField.stringValue=[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
    res.stylField.stringValue=[NSString stringWithCString:styl->getname() encoding:NSMacOSRomanStringEncoding];

CGContextRef    ctx=CreateBitmapContextWithSize(kXMapStyleWdLineHeigth,kXMapStyleWdLineHeigth);
CGImageRef      cgimg;
CGRect          hir=CGRectMake(0,0,kXMapStyleWdLineHeigth,kXMapStyleWdLineHeigth);
    
    if(styl->visible()){
        switch(styl->getdrawingmethod()){
            case kIconStyleKind_:
                draw_icon(styl,ctx,CGRectInset(hir,1,1),true);
                break;
            case kCircleStyleKind_:
                draw_circle(styl,ctx,CGRectInset(hir,1,1),true);
                break;
            case kRectStyleKind_:
                draw_rect(styl,ctx,CGRectInset(hir,1,1),true);
                break;
            case kTextStyleKind_:
                draw_text(styl,ctx,CGRectInset(hir,1,1),true);
                break;
            case kLineStyleKind_:
                draw_line(styl,ctx,CGRectInset(hir,1,1),true);
                break;
            case kSurfStyleKind_:
                draw_surf(styl,ctx,CGRectInset(hir,1,1),true);
                break;
            case kRasterStyleKind_:
                draw_raster(styl,ctx,CGRectInset(hir,1,1),_ext->getbundle(),true);
                break;
            default:
                draw_unknown(styl,ctx,CGRectInset(hir,1,1),_ext->getbundle(),true);
                break;
        }
    }
    else{
        cgimg=LoadPNGImageFromBundle(_ext->getbundle(),CFSTR("Hidden.png"));
        CGContextDrawImage(ctx,CGRectInset(hir,1,1),cgimg);
        CGImageRelease(cgimg);
    }
    if(!styl->selectable()){
        cgimg=LoadPNGImageFromBundle(_ext->getbundle(),CFSTR("NoSel.png"));
        CGContextDrawImage(ctx,CGRectInset(hir,1,1),cgimg);
        CGImageRelease(cgimg);
    }
    
    cgimg=CreateImageFromBitmapContext(ctx);
    res.imageView.image=[[[NSImage alloc] initWithCGImage:cgimg size:NSMakeSize(kXMapStyleWdLineHeigth,kXMapStyleWdLineHeigth)] autorelease];
    CGImageRelease(cgimg);
    CGContextRelease(ctx);

    return res;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
    if([_stl_viw selectedRow]<0){
        if(gapp->layersAccessCtx()->get_current()!=0){
            [_stl_viw selectRowIndexes:[NSIndexSet indexSetWithIndex:gapp->layersAccessCtx()->get_current()-1]
                  byExtendingSelection:NO];
       }
    }
    else{
        gapp->layersAccessCtx()->set_current([_stl_viw selectedRow]+1);
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)     tableView:(NSTableView*)tableView
 writeRowsWithIndexes:(NSIndexSet*)rowIndexes
         toPasteboard:(NSPasteboard*)pasteBoard{
NSData* data=[NSKeyedArchiver archivedDataWithRootObject:rowIndexes];
    [pasteBoard declareTypes:[NSArray arrayWithObjects:PresentationDraggedDatatype,nil] owner:self];
    [pasteBoard setData:data forType:PresentationDraggedDatatype];
    return YES;
}

// ---------------------------------------------------------------------------
//
// -----------
-(NSDragOperation)tableView:(NSTableView*)tableView
               validateDrop:(id<NSDraggingInfo>)info
                proposedRow:(NSInteger)rowIndex
      proposedDropOperation:(NSTableViewDropOperation)dropOperation{
    return NSDragOperationEvery;
}

// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)tableView:(NSTableView*)tableView
      acceptDrop:(id<NSDraggingInfo>)info
             row:(NSInteger)rowIndex
   dropOperation:(NSTableViewDropOperation)dropOperation{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
NSPasteboard*       pboard=[info draggingPasteboard];
NSData*             data=[pboard dataForType:PresentationDraggedDatatype];
NSIndexSet*         rowIndexes=[NSKeyedUnarchiver unarchiveObjectWithData:data];
long                n=rowIndex-[rowIndexes firstIndex];
    if(n>0){
        n--;
    }
    gapp->layersMgr()->StopDraw();
    gapp->layersAccessCtx()->move([rowIndexes firstIndex]+1,n);
    _reload=YES;
    return YES;
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
PresentationWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[PresentationWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

// ---------------------------------------------------------------------------
//
// ------------
void clickCocoa(void* instance,
                CGPoint loc){
NSAutoreleasePool               *localPool;
PresentationWindowController	*mmc=(PresentationWindowController*)instance;
    
    if(mmc==NULL){
        return;
    }
    localPool=[[NSAutoreleasePool alloc] init];
    [mmc clickAtLocation:loc];
    [localPool release];
}

// ---------------------------------------------------------------------------
//
// ------------
void refreshCocoa(void* instance){
NSAutoreleasePool               *localPool;
PresentationWindowController	*mmc=(PresentationWindowController*)instance;
    
    if(mmc==NULL){
        return;
    }
    localPool=[[NSAutoreleasePool alloc] init];
    [mmc populateTypes];
    [localPool release];
}

