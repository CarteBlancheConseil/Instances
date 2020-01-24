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

    NSPopupButtonPopulateWithFields(_fbfl_pop,_ext->type_get(),kOBJ_Name_,1);
    NSPopupButtonPopulateWithFields(_fbwd_pop,_ext->type_get(),kOBJ_Name_,1);
    NSPopupButtonPopulateWithFields(_fbmv_pop,_ext->type_get(),kOBJ_Name_,1);
    NSPopupButtonPopulateWithFields(_fbmh_pop,_ext->type_get(),kOBJ_Name_,1);
    NSPopupButtonPopulateWithFields(_fbrd_pop,_ext->type_get(),kOBJ_Name_,1);
    NSPopupButtonPopulateWithFields(_fbdc_pop,_ext->type_get(),kOBJ_Name_,1);

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
// -----------
-(IBAction)doPutBackAlpha:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackAlpha]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_backfill[_ext->cmyk_get()?4:3]=[_bfl_sld floatValue];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doPutBackWidth:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackWidth]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_backwidth=[_bwd_fld floatValue];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doPutBackFillColor:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackFillColor]",true);
bvDefQuickSymbStyle*	stl;
NSColor*				clr=[_bfl_clr color];
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
                stl->_backfill[0]=[cclr cyanComponent];
                stl->_backfill[1]=[cclr magentaComponent];
                stl->_backfill[2]=[cclr yellowComponent];
                stl->_backfill[3]=[cclr blackComponent];
            }
            else{
                stl->_backfill[0]=[cclr redComponent];
                stl->_backfill[1]=[cclr greenComponent];
                stl->_backfill[2]=[cclr blueComponent];
            }
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doPutBackStrokeColor:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackStrokeColor]",true);
bvDefQuickSymbStyle*	stl;
NSColor*				clr=[_bst_clr color];
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
                stl->_backstroke[0]=[cclr cyanComponent];
                stl->_backstroke[1]=[cclr magentaComponent];
                stl->_backstroke[2]=[cclr yellowComponent];
                stl->_backstroke[3]=[cclr blackComponent];
            }
            else{
                stl->_backstroke[0]=[cclr redComponent];
                stl->_backstroke[1]=[cclr greenComponent];
                stl->_backstroke[2]=[cclr blueComponent];
            }
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doPutBackVerticalMargin:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackVerticalMargin]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_backheightmaj=[_bmv_fld floatValue];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doPutBackHorizontalMargin:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackHorizontalMargin]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_backwidthmaj=[_bmh_fld floatValue];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doPutBackRadius:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackRadius]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_rradius=[_brd_fld floatValue];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutBackDec:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackDec]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_backshifty=[_bdc_fld floatValue];
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




// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPutBackWidthField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackWidthField]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_fbackwidth=[self getPopupValueForField:_fbwd_pop];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPutBackFillColorField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackFillColorField]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_fbackfill=[self getPopupValueForField:_fbfl_pop];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPutBackStrokeColorField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackStrokeColorField]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_fbackstroke=[self getPopupValueForField:_fbst_pop];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPutBackVerticalMarginField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackVerticalMarginField]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_fbackheightmaj=[self getPopupValueForField:_fbmv_pop];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPutBackHorizontalMarginField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackHorizontalMarginField]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_fbackwidthmaj=[self getPopupValueForField:_fbmh_pop];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPutBackRadiusField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackRadiusField]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_frradius=[self getPopupValueForField:_fbrd_pop];
        }
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// ------------
-(IBAction)doPutBackDecField:(id)sender{
_bTrace_("[vDefPaletteQuickSymbWindowController doPutBackDecField]",true);
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        if([_run_tbl isRowSelected:i-1]==YES){
            _ext->runs().get(i,&stl);
            stl->_fbackshiftx=[self getPopupValueForField:_fbdc_pop];
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
    
    
    [_bfl_sld setEnabled:state];
    [_bfl_clr setEnabled:state];
    [_bwd_fld setEnabled:state];
    [_bst_clr setEnabled:state];
    [_bmv_fld setEnabled:state];
    [_bmh_fld setEnabled:state];
    [_brd_fld setEnabled:state];
    [_bdc_fld setEnabled:state];
    
    [_fbfl_pop setEnabled:state];
    [_fbst_pop setEnabled:state];
    [_fbwd_pop setEnabled:state];
    [_fbmv_pop setEnabled:state];
    [_fbmh_pop setEnabled:state];
    [_fbrd_pop setEnabled:state];
    [_fbdc_pop setEnabled:state];
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
		
        
        
        if(_ext->cmyk_get()){
            [_bfl_clr setColor:[NSColor colorWithDeviceCyan:stl->_backfill[0]
                                                    magenta:stl->_backfill[1]
                                                     yellow:stl->_backfill[2]
                                                      black:stl->_backfill[3]
                                                      alpha:1]];
            [_bst_clr setColor:[NSColor colorWithDeviceCyan:stl->_backstroke[0]
                                                    magenta:stl->_backstroke[1]
                                                     yellow:stl->_backstroke[2]
                                                      black:stl->_backstroke[3]
                                                      alpha:1]];
        }
        else{
            [_bfl_clr setColor:[NSColor colorWithDeviceRed:stl->_backfill[0]
                                                     green:stl->_backfill[1] 
                                                      blue:stl->_backfill[2] 
                                                     alpha:1]];
            [_bst_clr setColor:[NSColor colorWithDeviceRed:stl->_backstroke[0]
                                                     green:stl->_backstroke[1] 
                                                      blue:stl->_backstroke[2] 
                                                     alpha:1]];
        }
        [_bfl_sld setFloatValue:stl->_backfill[_ext->cmyk_get()?4:3]];
        [_bwd_fld setFloatValue:stl->_backwidth];
        [_bmv_fld setFloatValue:stl->_backheightmaj];
        [_bmh_fld setFloatValue:stl->_backwidthmaj];
        [_brd_fld setFloatValue:stl->_rradius];
        [_bdc_fld setFloatValue:stl->_backshifty];

        
        
		if(strlen(stl->_smb)>0){
			char	val[256];
			CGRect				box={{0,0},{0,0}};
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

		[_dmw_fld setFloatValue:stl->_h];
		[_dmh_fld setFloatValue:stl->_v];
		[_rot_fld setFloatValue:stl->_a];
		[_alp_sld setFloatValue:stl->_alpha];
        
        
        
        [_fbfl_pop selectItemAtIndex:stl->_fbackfill?stl->_fbackfill-kOBJ_Name_+2:0];
        [_fbst_pop selectItemAtIndex:stl->_fbackstroke?stl->_fbackstroke-kOBJ_Name_+2:0];
        [_fbwd_pop selectItemAtIndex:stl->_fbackwidth?stl->_fbackwidth-kOBJ_Name_+2:0];
        [_fbmv_pop selectItemAtIndex:stl->_fbackheightmaj?stl->_fbackheightmaj-kOBJ_Name_+2:0];
        [_fbmh_pop selectItemAtIndex:stl->_fbackwidthmaj?stl->_fbackwidthmaj-kOBJ_Name_+2:0];
        [_fbrd_pop selectItemAtIndex:stl->_frradius?stl->_frradius-kOBJ_Name_+2:0];
        [_fbdc_pop selectItemAtIndex:stl->_fbackshifty?stl->_fbackshifty-kOBJ_Name_+2:0];

        
        
		[_fsmb_pop selectItemAtIndex:stl->_fsmb?stl->_fsmb-kOBJ_Name_+2:0];	
		[_fdmw_pop selectItemAtIndex:stl->_fh?stl->_fh-kOBJ_Name_+2:0];	
		[_fdmh_pop selectItemAtIndex:stl->_fv?stl->_fv-kOBJ_Name_+2:0];
		[_frot_pop selectItemAtIndex:stl->_fa?stl->_fa-kOBJ_Name_+2:0];
		[_falp_pop selectItemAtIndex:stl->_falpha?stl->_falpha-kOBJ_Name_+2:0];
	}
	else{
        [_bfl_clr setColor:[NSColor blackColor]];
        [_bst_clr setColor:[NSColor blackColor]];

        [_bfl_sld setFloatValue:0];
        [_bwd_fld setFloatValue:0];
        [_bmv_fld setFloatValue:0];
        [_bmh_fld setFloatValue:0];
        [_brd_fld setFloatValue:0];
        [_bdc_fld setFloatValue:0];

        
        
        [_smb_fld setCharValue:""];

		[_dmw_fld setFloatValue:0];
		[_dmh_fld setFloatValue:0];
		[_rot_fld setFloatValue:0];
		[_alp_sld setFloatValue:0];

        
        
        [_fbfl_pop selectItemAtIndex:0];
        [_fbst_pop selectItemAtIndex:0];
        [_fbwd_pop selectItemAtIndex:0];
        [_fbmv_pop selectItemAtIndex:0];
        [_fbmh_pop selectItemAtIndex:0];
        [_fbrd_pop selectItemAtIndex:0];
        [_fbdc_pop selectItemAtIndex:0];

        
        
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
-(void)convertColor{
bvDefQuickSymbStyle*	stl;
    
    for(long i=1;i<=_ext->runs().count();i++){
        _ext->runs().get(i,&stl);
        if(_ext->cmyk_get()){
            compRGB2CMYK64(stl->_backfill);
            compRGB2CMYK64(stl->_backstroke);
            stl->_cc=5;
        }
        else{
            compCMYK2RGB64(stl->_backfill);
            compCMYK2RGB64(stl->_backstroke);
            stl->_cc=4;
        }
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
CGRect					shape,cgr;
	
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
		
        cgr=shape;
        cgr.origin.x-=(stl->_backwidthmaj*_ext->coef_get());
        cgr.origin.y-=(stl->_backheightmaj*_ext->coef_get());
        cgr.origin.x+=(stl->_backshiftx*_ext->coef_get());
        cgr.origin.y+=(stl->_backshifty*_ext->coef_get());
        cgr.size.width+=(stl->_backwidthmaj*_ext->coef_get()*2.0);
        cgr.size.height+=(stl->_backheightmaj*_ext->coef_get()*2.0);
        
        MMCGContextSetFillColor64(ctx,stl->_backfill,_ext->cmyk_get());
        MMCGContextSetStrokeColor64(ctx,stl->_backstroke,_ext->cmyk_get());
        CGContextSetLineWidth(ctx,stl->_backwidth*_ext->coef_get());
        if(stl->_rradius>0){
            CGContextAddRoundedRect(ctx,cgr,stl->_rradius*_ext->coef_get());
        }
        else{
            CGContextAddRect(ctx,cgr);
        }
        CGContextDrawPath(ctx,kCGPathFillStroke);

        
		if((stl->_h==0)||(stl->_v==0)){
			CGContextSetEmptyStyle(ctx,hir);
		}
		else if(GetImageKind(stl->_smb)==kFileTypePDF){
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

