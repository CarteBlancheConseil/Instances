//----------------------------------------------------------------------------
// File : IconPickerWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap icon picker window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2016 Carte Blanche Conseil.
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
// 08/03/2016 creation.
//----------------------------------------------------------------------------

#import "IconPickerWindowController.h"
#import "bXMapIconPicker.h" 
#import "CocoaStuff.h" 
#import <mox_intf/CGUtils.h>
#import <mox_intf/ext_utils.h>
#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
//
// ------------
@implementation IconPickerPreview

// ---------------------------------------------------------------------------
//
// ------------
-(id)initWithFrame:(NSRect)frameRect{
_bTrace_("[IconPickerPreview initWithFrame]",true);
    if((self=[super initWithFrame:frameRect])!=nil){
    }
    return self;
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)dealloc{
_bTrace_("[IconPickerPreview dealloc]",true);
    [super dealloc];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)installController:(IconPickerWindowController*)controller{
    _ctrlr=controller;
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)drawRect:(NSRect)rect{
_bTrace_("[IconPickerPreview drawRect]",true);
CGRect				cgr=(*((CGRect*)(&rect)));
NSGraphicsContext*	nsctx=[NSGraphicsContext currentContext];
CGContextRef		ctx=(CGContextRef)[nsctx graphicsPort];
    
    CGContextSetRGBFillColor(ctx,1,1,1,1);
    CGContextSetRGBStrokeColor(ctx,0.5,0.5,0.5,1);
    CGContextSetLineWidth(ctx,0.5);
    CGContextAddRect(ctx,cgr);
    CGContextDrawPath(ctx,kCGPathFillStroke);
    
    [_ctrlr drawPreview:cgr context:ctx];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end



// ---------------------------------------------------------------------------
// 
// ------------
@implementation IconPickerWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[IconPickerWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[IconPickerWindowController awakeFromNib]",true);
bXMapIconPicker*	ext=(bXMapIconPicker*)_ext;
picker_prm          prm;
    ext->get_infos(&prm);

    [_prvviw installController:self];
    [_rsctbl reloadData];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[IconPickerWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
long idx=[_rsctbl selectedRow];
    if(idx>=0){
bXMapIconPicker*    ext=(bXMapIconPicker*)_ext;
picker_prm          prm;
        ext->get_infos(&prm);
        if(!(prm.tp->fields()->get_param_name("icons",idx+1,prm.name))){
            prm.name[0]=0;
        }
        ext->set_infos(prm);
    }
    
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doAdd:(id)sender{
_bTrace_("[IconPickerWindowController doAdd]",true);
NSOpenPanel*	opn=[NSOpenPanel openPanel];
    
    [opn setCanChooseDirectories:NO];
    [opn setCanChooseFiles:YES];
    [opn setAllowsMultipleSelection:YES];
    [opn setResolvesAliases:YES];
    [opn setDelegate:self];
    
    [opn beginSheetForDirectory:nil
                           file:nil
                 modalForWindow:[self window]
                  modalDelegate:self
                 didEndSelector:@selector(openPanelDidEnd:returnCode:contextInfo:)
                    contextInfo:nil];
}


#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
_bTrace_("[IconPickerWindowController updateUI]",true);
    [_prvviw setNeedsDisplay:YES];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)drawPreview:(CGRect)cgr context:(CGContextRef)ctx{
_bTrace_("[IconPickerWindowController drawPreview]",true);
long idx=[_rsctbl selectedRow];
    if(idx<0){
        return;
    }
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapIconPicker*	ext=(bXMapIconPicker*)_ext;
picker_prm          prm;
char                str[256];
CGRect              box;
        
    ext->get_infos(&prm);
    if(!(prm.tp->fields()->get_param_name("icons",idx+1,str))){
        return;
    }
    if(GetImageKind(str)==kQTFileTypePDF){
CGPDFDocumentRef	pdf=GetPDFIcon(gapp,prm.tp,str);
        if(pdf!=NULL){
CGPDFPageRef
            pg=CGPDFDocumentGetPage(pdf,1);
CGAffineTransform
            mx=CGPDFPageGetDrawingTransform(pg,kCGPDFMediaBox,cgr,0,true);
            box=CGPDFPageGetBoxRect(pg,kCGPDFMediaBox);
            CGContextConcatCTM(ctx,mx);
            CGContextClipToRect(ctx,box);
            CGContextDrawPDFPage(ctx,pg);
            CGPDFDocumentRelease(pdf);
        }
    }
    else{
CGImageRef
        img=GetImageIcon(gapp,prm.tp,str);
        if(img!=NULL){
            box.size.width=CGImageGetWidth(img);
            box.size.height=CGImageGetHeight(img);
            box.origin.x=0;
            box.origin.y=0;
            box=CGScaleRect(cgr,box);
            box=CGRectInset(box,1,1);
            CGContextDrawImage(ctx,box,img);
            CGImageRelease(img);
        }
    }
}

#pragma mark ---- Open Panel ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)openPanelDidEnd:(NSOpenPanel *)panel
            returnCode:(int)returnCode
           contextInfo:(void *)contextInfo{
_bTrace_("[IconPickerWindowController openPanelDidEnd]",true);
    if(NSOKButton==returnCode){
bXMapIconPicker*	ext=(bXMapIconPicker*)_ext;
picker_prm          prm;
        ext->get_infos(&prm);
char    fpath[PATH_MAX];
char	path[PATH_MAX];
char	name[FILENAME_MAX];
void*	data;
int		sz;
        
        for(long i=0;i<[[panel filenames] count];i++){
NSString*	filename=[[panel filenames] objectAtIndex:i];
            if([filename getCString:fpath maxLength:PATH_MAX encoding:NSMacOSRomanStringEncoding]==NO){
            }
            else{
                splitPath(fpath,path,name);
bStdFile		f(fpath,"r");
                if(f.status()){
_te_("File bad status "+f.status());
                    return;
                }
                f.mount((char**)&data,&sz);
                if(f.status()){
_te_("File bad status at mount "+f.status());
                    return;
                }
                if(prm.tp){
                    (void)prm.tp->fields()->set_param("icons",name,data,sz);
                }
                else{
                    //(void)_gapp->document()->set_param(_sub,name,data,sz);
                }
                free(data);
            }
        }
        
        [_rsctbl reloadData];
        [self updateUI];
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(BOOL)panel:(id)sender shouldShowFilename:(NSString *)filename{
BOOL    isDirectory=NO;
    
    (void)[[NSFileManager defaultManager] fileExistsAtPath:filename isDirectory:&isDirectory];
    if(isDirectory){
        return ![[NSWorkspace sharedWorkspace] isFilePackageAtPath:filename];
    }
    
NSString*   ext=[filename pathExtension];
    if( [ext length]==0                      ||
        [ext compare:@"/"]==NSOrderedSame    ||
        [ext length]<1                       ||
        ext==nil                             ){
        return NO;
    }
NSEnumerator*   tagEnumerator=[[NSArray arrayWithObjects:@"png", @"tiff", @"jpg", @"pdf", @"jpeg", nil] objectEnumerator];
NSString*       allowedExt;
    while((allowedExt=[tagEnumerator nextObject])){
        if([ext caseInsensitiveCompare:allowedExt]==NSOrderedSame){
            return YES;
        }
    }
    return NO;
}


#pragma mark ---- TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bXMapIconPicker*	ext=(bXMapIconPicker*)_ext;
picker_prm          prm;
    ext->get_infos(&prm);
    return(prm.tp->fields()->count_param("icons"));
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{
bXMapIconPicker*	ext=(bXMapIconPicker*)_ext;
picker_prm          prm;
char                str[256];
    ext->get_infos(&prm);
    if(!(prm.tp->fields()->get_param_name("icons",rowIndex+1,str))){
        return nil;
    }
	return [NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapIconPicker* ext,
					  long* code){
IconPickerWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[IconPickerWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
