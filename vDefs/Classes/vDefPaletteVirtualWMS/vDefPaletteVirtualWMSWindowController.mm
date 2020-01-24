//----------------------------------------------------------------------------
// File : vDefPaletteVirtualWMSWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : WMS vdef window controller
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
// 13/07/2013 creation.
//----------------------------------------------------------------------------

#import "vDefPaletteVirtualWMSWindowController.h"
#import "bvDefPaletteVirtualWMS.h"
#import "bvDefVirtualWMSStyle.h"
#import "CocoaStuff.h"
#import <MacMapSuite/bTrace.h>
#import <MacMapSuite/mmurl.h>

#import <mox_intf/bGenericMacMapApp.h>

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
#define kLayerProperty			'Name'
#define kLayerPreviewFont		"Geneva"
#define kLayerPreviewSize		9
#define kLayerPreviewHMargin	5
#define kLayerPreviewVMargin	5

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteVirtualWMSPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteVirtualWMSWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteVirtualWMSWindowController init]",true);
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
_bTrace_("[vDefPaletteVirtualWMSWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteVirtualWMSWindowController awakeFromNib]",true);
	[super awakeFromNib];
	
	[_prvw installController:self];

bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();

// Visibilité
	NSPopupButtonRemoveAllItems(_smn_pop);
	NSPopupButtonPopulateWithScales(_smn_pop,gapp,1);
	NSPopupButtonRemoveAllItems(_smx_pop);
	NSPopupButtonPopulateWithScales(_smx_pop,gapp,gapp->scaleMgr()->count());
	
	[self plot2Intf];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteVirtualWMSWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doConnect:(id)sender{
_bTrace_("[vDefPaletteVirtualWMSWindowController doConnect]",true);
char		fullurl[2048];	
NSString*	nsstr=[_url_fld stringValue];
	if([nsstr length]>0){
long	max=[nsstr length]*3+1;
char*	url=(char*)malloc(max);
		if([nsstr getCString:url maxLength:max-1 encoding:NSUTF8StringEncoding]==YES){
            
bool        https=(strstr(url,"https://")==url);
            
            strrep(url,"http://","");
            strrep(url,"https://","");
			strrep(url,"?","");
			
			sprintf(fullurl,"http%s://%s?SERVICE=WMS&VERSION=1.1.1&REQUEST=GetCapabilities",(https?"s":""),url);
_tm_("trying to connect to :"+fullurl);
			
void*	buffer=NULL;
size_t	sz;
			
			WMSCapabilitiesFreeDescs(((bvDefPaletteVirtualWMS*)_ext)->layers());
			
            ((bvDefPaletteVirtualWMS*)_ext)->url_put(url);
            ((bvDefPaletteVirtualWMS*)_ext)->https_put(https);
            
char	usr[256];
char	pwd[256];
            [[_usr_fld stringValue] getCString:usr maxLength:sizeof(usr)-1 encoding:NSUTF8StringEncoding];
            [[_pwd_fld stringValue] getCString:pwd maxLength:sizeof(pwd)-1 encoding:NSUTF8StringEncoding];
            
            ((bvDefPaletteVirtualWMS*)_ext)->usr_put(usr);
            ((bvDefPaletteVirtualWMS*)_ext)->pwd_put(pwd);
            
            if(strlen(usr)>0){
char	usrpwd[256];
                sprintf(usrpwd,"%s:%s",usr,pwd);
                if(mmurl_userGet(usrpwd,fullurl,NULL,NULL,&buffer,&sz)!=0){
_te_("mmurl_get failed");
                }
                else{
                    if(WMSCapabilitiesParser(buffer,sz,((bvDefPaletteVirtualWMS*)_ext)->layers())){
_te_("WMSCapabilitiesParser failed");
                    }
                }
            }
            else{
                if(mmurl_get(fullurl,NULL,NULL,&buffer,&sz)!=0){
_te_("mmurl_get failed");
                }
                else{
                    if(WMSCapabilitiesParser(buffer,sz,((bvDefPaletteVirtualWMS*)_ext)->layers())){
_te_("WMSCapabilitiesParser failed");
                    }
                }
            }
            if(buffer){
				free(buffer);
			}
		}
	}
	
	[_run_tbl reloadData];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doExport:(id)sender{
_bTrace_("[vDefPaletteVirtualWMSWindowController doExport]",true);
NSSavePanel*	savePanel=[NSSavePanel savePanel];	
    [savePanel setNameFieldStringValue:@"capabilities.xml"];
	[savePanel	beginSheetForDirectory:nil
								 file:nil
					   modalForWindow:[self window]
						modalDelegate:self
					   didEndSelector:@selector(savePanelDidEnd:returnCode:contextInfo:)
						  contextInfo:nil];
	
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutAlpha:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackAlpha]",true);
bvDefVirtualWMSStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_alpha=[_alp_sld floatValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseLayer:(id)sender{
_bTrace_("[vDefPaletteVirtualWMSWindowController doChooseLayer]",true);
bvDefVirtualWMSStyle*	stl;
	if(!_ext->runs().get(1,&stl)){
		return;
	}

//_tm_("_last_click="+_last_click);
wmslayerdesc	dsc={NULL,NULL,NULL,0};
	if(!((bvDefPaletteVirtualWMS*)_ext)->layers().get(_last_click,&dsc)){
		return;
	}
	
    stl->_https=((bvDefPaletteVirtualWMS*)_ext)->https_get();
    strcpy(stl->_url,((bvDefPaletteVirtualWMS*)_ext)->url_get());
    strcpy(stl->_usr,((bvDefPaletteVirtualWMS*)_ext)->usr_get());
    strcpy(stl->_pwd,((bvDefPaletteVirtualWMS*)_ext)->pwd_get());
	
	if(dsc.name){
		strcpy(stl->_layer,dsc.name);
	}
//	else if(dsc.title){
//		strcpy(stl->_layer,dsc.title);
//	}
	else{
		strcpy(stl->_layer,"");
	}

// Maintenant fixé prioritairement par le SRS du projet
	if((dsc.srs)&&(dsc.srs->count()>0)){
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
        if(gapp->document()->srid()>0){
            stl->_srs=gapp->document()->srid();
        }
        else if(dsc.srs->count()>1){
            for(int i=1;i<=dsc.srs->count();i++){
                dsc.srs->get(i,&stl->_srs);
                if(stl->_srs!=4326){
                    break;
                }
            }
        }
        else{
            stl->_srs=0;
        }
    }
    
//		if(dsc.srs->count()>1){
//bool				found=false;
//bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
//			for(int i=1;i<=dsc.srs->count();i++){
//				dsc.srs->get(i,&stl->_srs);
//				if(gapp->document()->srid()==stl->_srs){
//					found=true;
//					break;
//				}
//			}
//			if(!found){
//				for(int i=1;i<=dsc.srs->count();i++){
//					dsc.srs->get(i,&stl->_srs);
//					if(stl->_srs!=4326){
//						found=true;
//						break;
//					}
//				}
//			}
//			if(!found){
//				for(int i=1;i<=dsc.srs->count();i++){
//					dsc.srs->get(i,&stl->_srs);
//					if(stl->_srs==4326){
//						found=true;
//						break;
//					}
//				}
//			}
//		}
//		else{
//			dsc.srs->get(1,&stl->_srs);
//		}
//	}
//	else{
//		stl->_srs=0;
//	}
	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseScaleMin:(id)sender{
_bTrace_("[vDefPaletteVirtualWMSWindowController doChooseScaleMin]",true);
bGenericUnit*			u=((bGenericMacMapApp*)_ext->getapp())->scaleMgr()->get([_smn_pop indexOfSelectedItem]+1);
bvDefVirtualWMSStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_smin=u->coef();
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseScaleMax:(id)sender{
_bTrace_("[vDefPaletteVirtualWMSWindowController doChooseScaleMax]",true);
bGenericUnit*			u=((bGenericMacMapApp*)_ext->getapp())->scaleMgr()->get([_smx_pop indexOfSelectedItem]+1);
bvDefVirtualWMSStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_smax=u->coef()+1.0;
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doClickPreview:(id)sender{
_bTrace_("[vDefPaletteVirtualWMSWindowController doClickPreview]",true);
}


#pragma mark ---- Actions appliquer ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doApply:(id)sender{
_bTrace_("[vDefPaletteVirtualWMSWindowController doApply]",true);
	_ext->update();
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
	[_prvw setNeedsDisplay:YES];
	[self checkIntfAvailability];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)checkIntfAvailability{
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteVirtualWMSWindowController plot2Intf]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
const char*			url=((bvDefPaletteVirtualWMS*)_ext)->url_get();
	[_url_fld setStringValue:[NSString stringWithCString:url encoding:NSUTF8StringEncoding]];

bvDefVirtualWMSStyle*	stl;
	if(_ext->runs().get(1,&stl)==false){
		return;
	}	
wmslayerdesc	dsc;
	for(long i=1;i<=((bvDefPaletteVirtualWMS*)_ext)->layers().count();i++){
		((bvDefPaletteVirtualWMS*)_ext)->layers().get(i,&dsc);
		if(dsc.name){
			if(strcmp(dsc.name,stl->_layer)==0){
				[_run_tbl selectRowIndexes:[NSIndexSet indexSetWithIndex:i-1] byExtendingSelection:FALSE];
				[_run_tbl scrollRowToVisible:i-1];
			}
		}
	}
	[_alp_sld setFloatValue:stl->_alpha];
    [_usr_fld setCharValue:((bvDefPaletteVirtualWMS*)_ext)->usr_get()];
    [_pwd_fld setCharValue:((bvDefPaletteVirtualWMS*)_ext)->pwd_get()];

long	idx;
	idx=GetBestScaleIndexForValue(gapp,stl->_smin);
	[_smn_pop selectItemAtIndex:(idx-1)];
	idx=GetBestScaleIndexForValue(gapp,stl->_smax);
	[_smx_pop selectItemAtIndex:(idx-1)];					
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx{
_bTrace_("[vDefPaletteVirtualWMSWindowController drawPreview]",true);	
bvDefVirtualWMSStyle*	stl;
	if(_ext->runs().get(1,&stl)==false){
		CGContextSetEmptyStyle(ctx,rect);
		return;
	}
	
	if(_last_click>0){
wmslayerdesc	dsc={NULL,NULL,NULL,0};
		if(!((bvDefPaletteVirtualWMS*)_ext)->layers().get(_last_click,&dsc)){
			CGContextSetEmptyStyle(ctx,rect);
			return;
		}
		
		CGContextSaveGState(ctx);

HIRect	hir=(*((CGRect*)(&rect)));
char	txt[1024];

		CGContextSetTextMatrix(ctx,CGAffineTransformMake(1,0,0,-1,0,hir.size.height));
		CGContextConcatCTM(ctx,CGAffineTransformMake(1,0,0,-1,0,hir.size.height));
		
		CGContextSelectFont(ctx,kLayerPreviewFont,kLayerPreviewSize,kCGEncodingMacRoman);
		CGContextSetRGBFillColor(ctx,0,0,0,1);
		CGContextSetTextDrawingMode(ctx,kCGTextFill);
		
		if(dsc.name){
			strcpy(txt,dsc.name);
			sprintf(txt,"name:%s",dsc.name);
			CGContextShowStringAtPoint(ctx,
									   hir.origin.x+kLayerPreviewHMargin,
									   hir.origin.y+kLayerPreviewVMargin+kLayerPreviewSize,
									   txt,
									   kLayerPreviewFont,
									   kLayerPreviewSize);		
		}
		
		if(dsc.title){
			strcpy(txt,dsc.title);
			sprintf(txt,"title:%s",dsc.title);
			CGContextShowStringAtPoint(ctx,
									   hir.origin.x+kLayerPreviewHMargin,
									   hir.origin.y+(kLayerPreviewVMargin+kLayerPreviewSize)*2,
									   txt,
									   kLayerPreviewFont,
									   kLayerPreviewSize);		
		}
		
		if((dsc.srs)&&(dsc.srs->count()>0)){
char	srst[64];
int		srs,i;
			
			txt[0]=0;
			for(i=1;i<dsc.srs->count();i++){
				dsc.srs->get(i,&srs);
				sprintf(srst,"%d/",srs);
				strcat(txt,srst);
			}
			dsc.srs->get(i,&srs);
			sprintf(srst,"%d",srs);
			strcat(txt,srst);
			
			CGContextShowStringAtPoint(ctx,
									   hir.origin.x+kLayerPreviewHMargin,
									   hir.origin.y+(kLayerPreviewVMargin+kLayerPreviewSize)*3,
									   txt,
									   kLayerPreviewFont,
									   kLayerPreviewSize);		
		}		
		CGContextRestoreGState(ctx);
	}
	else{
		CGContextSetEmptyStyle(ctx,rect);
	}
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
//_bTrace_("[vDefPaletteVirtualWMSWindowController numberOfRowsInTableView]",false);
	return ((bvDefPaletteVirtualWMS*)_ext)->layers().count();
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{
//_bTrace_("[vDefPaletteVirtualWMSWindowController tableView objectValueForTableColumn row]",false);
NSString*		nsstr;
wmslayerdesc	dsc;
	
	if(((bvDefPaletteVirtualWMS*)_ext)->layers().get(rowIndex+1,&dsc)==false){
		nsstr=@"????";
	}
	else{
		if(dsc.name){
			nsstr=[NSString stringWithCString:dsc.name encoding:NSMacOSRomanStringEncoding];
		}
		else if(dsc.title){
			nsstr=[NSString stringWithCString:dsc.title encoding:NSMacOSRomanStringEncoding];
		}
		else{
			nsstr=@"????";
		}
	}
	return nsstr;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
_bTrace_("[vDefPaletteVirtualWMSWindowController tableViewSelectionDidChange]",false);
	_last_click=[_run_tbl selectedRow]+1;
	[self doChooseLayer:self];
	[self plot2Intf];
	[self updateUI];
}

#pragma mark ---- Gestion SavePanel ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)	savePanelDidEnd:(NSOpenPanel *)sheet 
			 returnCode:(int)returnCode 
			contextInfo:(void *)contextInfo{
_bTrace_("[vDefPaletteVirtualWMSWindowController savePanelDidEnd]",true);
    if(NSOKButton==returnCode){
NSString*	nsstr=[[sheet filenames] objectAtIndex:0];
long		max=[nsstr length]*3+1;
char*		path=(char*)malloc(max);
		if([nsstr getCString:path maxLength:max-1 encoding:NSUTF8StringEncoding]==YES){
			
char		fullurl[2048];	
char*		url;
			nsstr=[_url_fld stringValue];
			if([nsstr length]>0){
				max=[nsstr length]*3+1;
				url=(char*)malloc(max);
				if([nsstr getCString:url maxLength:max-1 encoding:NSUTF8StringEncoding]==YES){
                    
bool                https=(strstr(url,"https://")==url);
                    
                    strrep(url,"http://","");
                    strrep(url,"https://","");
                    strrep(url,"?","");
                    
                    sprintf(fullurl,"http%s://%s?SERVICE=WMS&VERSION=1.1.1&REQUEST=GetCapabilities",(https?"s":""),url);
_tm_("trying to connect to :"+fullurl);

                    
                    strrep(url,"http://","");
					strrep(url,"?","");
					
					sprintf(fullurl,"http://%s?SERVICE=WMS&VERSION=1.1.1&REQUEST=GetCapabilities",url);
_tm_("trying to connect to :"+fullurl);
					
                    
char                usr[256];
char                pwd[256];
                    [[_usr_fld stringValue] getCString:usr maxLength:sizeof(usr)-1 encoding:NSUTF8StringEncoding];
                    [[_pwd_fld stringValue] getCString:pwd maxLength:sizeof(pwd)-1 encoding:NSUTF8StringEncoding];
                    
                    
                    if(strlen(usr)>0){
char                    usrpwd[256];
                        sprintf(usrpwd,"%s:%s",usr,pwd);
                        if(mmurl_userGet(usrpwd,fullurl,NULL,path,NULL,NULL)!=0){
_te_("mmurl_get failed");
                        }
                    }
                    else{
                        if(mmurl_get(fullurl,NULL,path,NULL,NULL)!=0){
_te_("mmurl_get failed");
                        }
                    }
                }
			}
        }
		if(path){
			free(path);
		}
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
vDefPaletteVirtualWMSWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteVirtualWMSWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

