//----------------------------------------------------------------------------
// File : vDefPaletteQuickTextWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Text vdef window controller
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
// 28/06/2012 creation.
//----------------------------------------------------------------------------

#import "vDefPaletteQuickTextWindowController.h"
#import "bvDefPaletteQuickText.h"
#import "bvDefQuickTextStyle.h"
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
@implementation vDefPaletteQuickTextPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation vDefPaletteQuickTextWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[vDefPaletteQuickTextWindowController init]",true);
	self=[super init];
	if(self){
		_hprev=NO;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[vDefPaletteQuickTextWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[vDefPaletteQuickTextWindowController awakeFromNib]",true);
	[super awakeFromNib];
		
// Spécifique
	NSPopupButtonRemoveAllItems(_fld_pop);
	NSPopupButtonPopulateWithFields(_fld_pop,_ext->type_get(),kOBJ_Name_,1);

	NSPopupButtonPopulateWithFields(_ffnt_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_ffsz_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_ffwd_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fffl_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_ffst_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fbfl_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fbwd_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fbmv_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fbmh_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fbrd_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fbdc_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_falg_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_filt_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fiwd_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_frot_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdec_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdxx_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fdyy_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fsmt_pop,_ext->type_get(),kOBJ_Name_,1);
	NSPopupButtonPopulateWithFields(_fleg_pop,_ext->type_get(),kOBJ_Name_,1);
	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[vDefPaletteQuickTextWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions principal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutCentroid:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutCentroid]",true);
bvDefQuickTextStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		stl->_centro=[_cnt_chk intValue];
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_field=[_fld_pop indexOfSelectedItem]+kOBJ_Name_;
		}
	}
	[self updateUI];
}


// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFont:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFont]",true);
NSFontManager *fontManager=[NSFontManager sharedFontManager];
	[fontManager setTarget:self];
	
bvDefQuickTextStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			[fontManager setSelectedFont:[NSFont fontWithName:[NSString stringWithCString:stl->_font encoding:NSMacOSRomanStringEncoding] size:stl->_size] isMultiple:NO];
			[fontManager orderFrontFontPanel:self];
			return;
		}
	}
	
	[fontManager setSelectedFont:[NSFont fontWithName:@"Geneva" size:12.0] isMultiple:NO];
	[fontManager orderFrontFontPanel:self];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFontSize:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontSize]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_size=[_fsz_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutFontWidth:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontWidth]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_width=[_fwd_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFontFillColor:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontFillColor]",true);
bvDefQuickTextStyle*	stl;
NSColor*				clr=[_ffl_clr color];
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
-(IBAction)doPutFontStrokeColor:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontStrokeColor]",true);
bvDefQuickTextStyle*	stl;
NSColor*				clr=[_fst_clr color];
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
-(IBAction)doPutBackAlpha:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackAlpha]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackWidth]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackFillColor]",true);
bvDefQuickTextStyle*	stl;
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackStrokeColor]",true);
bvDefQuickTextStyle*	stl;
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackVerticalMargin]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackHorizontalMargin]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackRadius]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackDec]",true);
bvDefQuickTextStyle*	stl;
	
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
// -----------
-(IBAction)doPutAlignement:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutAlignement]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			switch([_alg_pop indexOfSelectedItem]){
				case 0:
					stl->_just=0;
					break;
				case 1:
					stl->_just=0.5;
					break;
				case 2:
					stl->_just=1;
					break;
				case 3:
					stl->_just=2;
					break;
			}
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutInterLetter:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutInterLetter]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_iltr=[_ilt_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutInterWord:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutInterWord]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_iwrd=[_iwd_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutRotation:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutRotation]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_angle=[_rot_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDec:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutDec]",true);
bvDefQuickTextStyle*	stl;
	
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
// -----------
-(IBAction)doPutDX:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutDX]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_dx=[_dxx_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutDY:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutDY]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_dy=[_dyy_fld floatValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutSmoothing:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutSmoothing]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_smooth=[_smt_chk intValue];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doPutLegibility:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutLegibility]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_legible=[_leg_chk intValue];
		}
	}
	[self updateUI];
}




// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFontField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_ffont=[self getPopupValueForField:_ffnt_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFontSizeField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontSizeField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fsize=[self getPopupValueForField:_ffsz_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFontWidthField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontWidthField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fwidth=[self getPopupValueForField:_ffwd_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFontFillColorField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontFillColorField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_ffill=[self getPopupValueForField:_fffl_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutFontStrokeColorField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutFontStrokeColorField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fstroke=[self getPopupValueForField:_ffst_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutBackWidthField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackWidthField]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackFillColorField]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackStrokeColorField]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackVerticalMarginField]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackHorizontalMarginField]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackRadiusField]",true);
bvDefQuickTextStyle*	stl;
	
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
_bTrace_("[vDefPaletteQuickTextWindowController doPutBackDecField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fbackshiftx=[self getPopupValueForField:_fbdc_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutAlignementField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutAlignementField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fjust=[self getPopupValueForField:_falg_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutInterLetterField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutInterLetterField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_filtr=[self getPopupValueForField:_filt_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutInterWordField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutInterWordField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fiwrd=[self getPopupValueForField:_fiwd_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutRotationField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutRotationField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fangle=[self getPopupValueForField:_frot_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDecField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutDecField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fdec=[self getPopupValueForField:_fdec_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDXField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutDXField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fdx=[self getPopupValueForField:_fdxx_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutDYField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutDYField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fdy=[self getPopupValueForField:_fdyy_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutSmoothingField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutSmoothingField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_fsmooth=[self getPopupValueForField:_fsmt_pop];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPutLegibilityField:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController doPutLegibilityField]",true);
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			stl->_flegible=[self getPopupValueForField:_fleg_pop];
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
	
	[_fld_pop setEnabled:state];
	[_fnt_btn setEnabled:state];
	[_fnt_fld setEnabled:state];
	[_fsz_fld setEnabled:state];
	[_fwd_fld setEnabled:state];
	[_ffl_clr setEnabled:state];
	[_fst_clr setEnabled:state];
	[_alg_pop setEnabled:state];
	[_ilt_fld setEnabled:state];
	[_iwd_fld setEnabled:state];
	[_dec_fld setEnabled:state];
	[_dxx_fld setEnabled:state];
	[_dyy_fld setEnabled:state];
	
	[_ffnt_pop setEnabled:state];
	[_ffsz_pop setEnabled:state];
	[_ffwd_pop setEnabled:state];
	[_fffl_pop setEnabled:state];
	[_ffst_pop setEnabled:state];
	[_falg_pop setEnabled:state];
	[_filt_pop setEnabled:state];
	[_fiwd_pop setEnabled:state];
	[_fdec_pop setEnabled:state];
	[_fdxx_pop setEnabled:state];
	[_fdyy_pop setEnabled:state];
	
	
BOOL	ctro=[_cnt_chk intValue];
	[_rot_fld setEnabled:state&&ctro];
	[_bfl_sld setEnabled:state&&ctro];
	[_bfl_clr setEnabled:state&&ctro];
	[_bwd_fld setEnabled:state&&ctro];
	[_bst_clr setEnabled:state&&ctro];
	[_bmv_fld setEnabled:state&&ctro];
	[_bmh_fld setEnabled:state&&ctro];
	[_brd_fld setEnabled:state&&ctro];
	[_bdc_fld setEnabled:state&&ctro];
	
	[_frot_pop setEnabled:state&&ctro];
	[_fbfl_pop setEnabled:state&&ctro];
	[_fbst_pop setEnabled:state&&ctro];
	[_fbwd_pop setEnabled:state&&ctro];
	[_fbmv_pop setEnabled:state&&ctro];
	[_fbmh_pop setEnabled:state&&ctro];
	[_fbrd_pop setEnabled:state&&ctro];
	[_fbdc_pop setEnabled:state&&ctro];

	
	[_smt_chk setEnabled:state&&!ctro];
	[_leg_chk setEnabled:state&&!ctro];	
	
	[_fsmt_pop setEnabled:state&&!ctro];
	[_fleg_pop setEnabled:state&&!ctro];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)plot2Intf{
_bTrace_("[vDefPaletteQuickTextWindowController plot2Intf]",true);
	[super plot2Intf];

bvDefQuickTextStyle*	stl;
long					cur=[_run_tbl selectedRow]+1;
	
	if(cur){
		_ext->runs().get(cur,&stl);
		
		if(_ext->cmyk_get()){
			[_ffl_clr setColor:[NSColor colorWithDeviceCyan:stl->_fill[0] 
													magenta:stl->_fill[1] 
													 yellow:stl->_fill[2] 
													  black:stl->_fill[3] 
													  alpha:1]];
			[_fst_clr setColor:[NSColor colorWithDeviceCyan:stl->_stroke[0] 
													magenta:stl->_stroke[1] 
													 yellow:stl->_stroke[2] 
													  black:stl->_stroke[3] 
													  alpha:1]];
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
			[_ffl_clr setColor:[NSColor colorWithDeviceRed:stl->_fill[0]
													 green:stl->_fill[1] 
													  blue:stl->_fill[2] 
													 alpha:1]];
			[_fst_clr setColor:[NSColor colorWithDeviceRed:stl->_stroke[0]
													 green:stl->_stroke[1] 
													  blue:stl->_stroke[2] 
													 alpha:1]];
			[_bfl_clr setColor:[NSColor colorWithDeviceRed:stl->_backfill[0]
													 green:stl->_backfill[1] 
													  blue:stl->_backfill[2] 
													 alpha:1]];
			[_bst_clr setColor:[NSColor colorWithDeviceRed:stl->_backstroke[0]
													 green:stl->_backstroke[1] 
													  blue:stl->_backstroke[2] 
													 alpha:1]];
		}
		
		[_cnt_chk setIntValue:stl->_centro];

		[_fld_pop selectItemAtIndex:stl->_field-kOBJ_Name_];
		
		[_fnt_fld setCharValue:stl->_font];
		
		[_fsz_fld setFloatValue:stl->_size];
		[_fwd_fld setFloatValue:stl->_width];

		[_bfl_sld setFloatValue:stl->_backfill[_ext->cmyk_get()?4:3]];
		[_bwd_fld setFloatValue:stl->_backwidth];
		[_bmv_fld setFloatValue:stl->_backheightmaj];
		[_bmh_fld setFloatValue:stl->_backwidthmaj];
		[_brd_fld setFloatValue:stl->_rradius];
		[_bdc_fld setFloatValue:stl->_backshifty];

		if(stl->_just==0){
			[_alg_pop selectItemAtIndex:0];
		}
		else if(stl->_just==0.5){
			[_alg_pop selectItemAtIndex:1];
		}
		else if(stl->_just==1){
			[_alg_pop selectItemAtIndex:2];
		}
		else{
			[_alg_pop selectItemAtIndex:3];
		}		
		[_ilt_fld setFloatValue:stl->_iltr];
		[_iwd_fld setFloatValue:stl->_iwrd];
		[_rot_fld setFloatValue:stl->_angle];
		[_dec_fld setFloatValue:stl->_dec];
		[_dxx_fld setFloatValue:stl->_dx];
		[_dyy_fld setFloatValue:stl->_dy];
		[_smt_chk setIntValue:stl->_smooth];
		[_leg_chk setIntValue:stl->_legible];
		
		[_ffnt_pop selectItemAtIndex:stl->_ffont?stl->_ffont-kOBJ_Name_+2:0];	
		[_ffsz_pop selectItemAtIndex:stl->_fsize?stl->_fsize-kOBJ_Name_+2:0];	
		[_ffwd_pop selectItemAtIndex:stl->_fwidth?stl->_fwidth-kOBJ_Name_+2:0];	
		[_fffl_pop selectItemAtIndex:stl->_ffill?stl->_ffill-kOBJ_Name_+2:0];	
		[_ffst_pop selectItemAtIndex:stl->_fstroke?stl->_fstroke-kOBJ_Name_+2:0];	
		[_fbfl_pop selectItemAtIndex:stl->_fbackfill?stl->_fbackfill-kOBJ_Name_+2:0];	
		[_fbst_pop selectItemAtIndex:stl->_fbackstroke?stl->_fbackstroke-kOBJ_Name_+2:0];	
		[_fbwd_pop selectItemAtIndex:stl->_fbackwidth?stl->_fbackwidth-kOBJ_Name_+2:0];	
		[_fbmv_pop selectItemAtIndex:stl->_fbackheightmaj?stl->_fbackheightmaj-kOBJ_Name_+2:0];	
		[_fbmh_pop selectItemAtIndex:stl->_fbackwidthmaj?stl->_fbackwidthmaj-kOBJ_Name_+2:0];	
		[_fbrd_pop selectItemAtIndex:stl->_frradius?stl->_frradius-kOBJ_Name_+2:0];	
		[_fbdc_pop selectItemAtIndex:stl->_fbackshifty?stl->_fbackshifty-kOBJ_Name_+2:0];	
		[_falg_pop selectItemAtIndex:stl->_fjust?stl->_fjust-kOBJ_Name_+2:0];	
		[_filt_pop selectItemAtIndex:stl->_filtr?stl->_filtr-kOBJ_Name_+2:0];	
		[_fiwd_pop selectItemAtIndex:stl->_fiwrd?stl->_fiwrd-kOBJ_Name_+2:0];	
		[_frot_pop selectItemAtIndex:stl->_fangle?stl->_fangle-kOBJ_Name_+2:0];	
		[_fdec_pop selectItemAtIndex:stl->_fdec?stl->_fdec-kOBJ_Name_+2:0];	
		[_fdxx_pop selectItemAtIndex:stl->_fdx?stl->_fdx-kOBJ_Name_+2:0];	
		[_fdyy_pop selectItemAtIndex:stl->_fdy?stl->_fdy-kOBJ_Name_+2:0];	
		[_fsmt_pop selectItemAtIndex:stl->_fsmooth?stl->_fsmooth-kOBJ_Name_+2:0];	
		[_fleg_pop selectItemAtIndex:stl->_flegible?stl->_flegible-kOBJ_Name_+2:0];	
	}
	else{
		[_ffl_clr setColor:[NSColor blackColor]];
		[_fst_clr setColor:[NSColor blackColor]];
		[_bfl_clr setColor:[NSColor blackColor]];
		[_bst_clr setColor:[NSColor blackColor]];
		
		[_cnt_chk setIntValue:0];
		
		[_fld_pop selectItemAtIndex:0];

		[_fnt_fld setCharValue:0];
		
		[_fsz_fld setFloatValue:0];
		[_fwd_fld setFloatValue:0];
		
		[_bfl_sld setFloatValue:0];
		[_bwd_fld setFloatValue:0];
		[_bmv_fld setFloatValue:0];
		[_bmh_fld setFloatValue:0];
		[_brd_fld setFloatValue:0];
		[_bdc_fld setFloatValue:0];
		
		[_alg_pop selectItemAtIndex:0];
		[_ilt_fld setFloatValue:0];
		[_iwd_fld setFloatValue:0];
		[_rot_fld setFloatValue:0];
		[_dec_fld setFloatValue:0];
		[_dxx_fld setFloatValue:0];
		[_dyy_fld setFloatValue:0];
		[_smt_chk setIntValue:0];
		[_leg_chk setIntValue:0];
		
		[_ffnt_pop selectItemAtIndex:0];	
		[_ffsz_pop selectItemAtIndex:0];	
		[_ffwd_pop selectItemAtIndex:0];	
		[_fffl_pop selectItemAtIndex:0];	
		[_ffst_pop selectItemAtIndex:0];	
		[_fbfl_pop selectItemAtIndex:0];	
		[_fbst_pop selectItemAtIndex:0];	
		[_fbwd_pop selectItemAtIndex:0];	
		[_fbmv_pop selectItemAtIndex:0];	
		[_fbmh_pop selectItemAtIndex:0];	
		[_fbrd_pop selectItemAtIndex:0];	
		[_fbdc_pop selectItemAtIndex:0];	
		[_falg_pop selectItemAtIndex:0];	
		[_filt_pop selectItemAtIndex:0];	
		[_fiwd_pop selectItemAtIndex:0];	
		[_frot_pop selectItemAtIndex:0];	
		[_fdec_pop selectItemAtIndex:0];	
		[_fdxx_pop selectItemAtIndex:0];	
		[_fdyy_pop selectItemAtIndex:0];	
		[_fsmt_pop selectItemAtIndex:0];	
		[_fleg_pop selectItemAtIndex:0];	
		
	}
}	

// ---------------------------------------------------------------------------
// 
// -----------
-(void)convertColor{
bvDefQuickTextStyle*	stl;
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		if(_ext->cmyk_get()){
			compRGB2CMYK64(stl->_fill);
			compRGB2CMYK64(stl->_stroke);
			compRGB2CMYK64(stl->_backfill);
			compRGB2CMYK64(stl->_backstroke);
			stl->_cc=5;
		}
		else{
			compCMYK2RGB64(stl->_fill);
			compCMYK2RGB64(stl->_stroke);
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
_bTrace_("[vDefPaletteQuickTextWindowController drawPreview]",true);
HIRect					hir=(*((CGRect*)(&rect)));
bvDefQuickTextStyle*	stl;
char					txt[256]=kMacMapName;
CGFloat					x,y;
CGRect					cgr;
	
	CGContextSaveGState(ctx);
	
	CGContextSetTextMatrix(ctx,CGAffineTransformMake(1,0,0,-1,0,hir.size.height));
	CGContextConcatCTM(ctx,CGAffineTransformMake(1,0,0,-1,0,hir.size.height));
	
	hir=CGRectInset(hir,1,1);
	hir.size.height=hir.size.height/(double)_ext->runs().count();
	
	for(long i=1;i<=_ext->runs().count();i++){
		_ext->runs().get(i,&stl);
		
		CGContextSaveGState(ctx);

		CGContextClipToRect(ctx,hir);
		
		if(stl->_size>0){
			
bCoreTextInfo	ats(stl->_font,(stl->_size*_ext->coef_get()),0,0,0,txt);

			if(stl->_just==0){
				x=3+(stl->_backwidthmaj+stl->_backwidth+stl->_width)*_ext->coef_get();
			}
			else if(stl->_just==1){
				x=(hir.origin.x+hir.size.width-(3+(stl->_backwidthmaj+stl->_backwidth+stl->_width)*_ext->coef_get()))-ats.textWidth();
			}
			else{
				x=(hir.origin.x+hir.size.width)/2.0-ats.textWidth()/2.0;
			}
			
			y=hir.origin.y+(hir.size.height/2.0)-((stl->_size*_ext->coef_get())/4.0);
			
			if(stl->_centro){
				cgr.origin.x=x;
				cgr.origin.y=y;
				cgr.origin.y+=ats.descent();
				cgr.size.width=ats.textWidth();
				cgr.size.height=ats.textHeight();
				
				cgr.origin.x-=(stl->_backwidthmaj*_ext->coef_get());
				cgr.origin.y-=(stl->_backheightmaj*_ext->coef_get());
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
				
				cgr.origin.x+=(stl->_backwidthmaj*_ext->coef_get());
				cgr.origin.y+=(stl->_backheightmaj*_ext->coef_get());
				cgr.size.width-=(stl->_backwidthmaj*_ext->coef_get()*2.0);
				cgr.size.height-=(stl->_backheightmaj*_ext->coef_get()*2.0);
			}
			
			CGContextSelectFont(ctx,stl->_font,stl->_size*_ext->coef_get(),kCGEncodingMacRoman);
			
			if(stl->_width>0){
				CGContextSetLineWidth(ctx,stl->_width*_ext->coef_get());
				MMCGContextSetStrokeColor64(ctx,stl->_stroke,_ext->cmyk_get());
				CGContextSetTextDrawingMode(ctx,kCGTextFillStroke);
			}
			else{
				CGContextSetTextDrawingMode(ctx,kCGTextFill);
			}
// Rotation, inter-lettres, inter-mots, décalage...
			MMCGContextSetFillColor64(ctx,stl->_fill,_ext->cmyk_get());
			CGContextShowGlyphsAtPoint(ctx,
									   x,
									   y+(stl->_size*_ext->coef_get())/2.0,
									   ats.glyphs(),
									   ats.nGlyphs());
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
		hir.origin.y+=hir.size.height;
		
		CGContextRestoreGState(ctx);

	}
	
	CGContextRestoreGState(ctx);
}

#pragma mark ---- FontManager delegates ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSUInteger)validModesForFontPanel:(NSFontPanel*)fontPanel{
    return(NSFontPanelFaceModeMask|NSFontPanelCollectionModeMask);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)changeFont:(id)sender{
_bTrace_("[vDefPaletteQuickTextWindowController changeFont]",true);
_tm_((void*)sender);
NSFont* newFont = [[NSFontManager sharedFontManager] convertFont:[[NSFontManager sharedFontManager] selectedFont]];
NSLog(@"Font Changed to %@", [newFont fontName] );
	
char	str[256];
	if([[newFont fontName] getCString:str maxLength:(sizeof(str)-1) encoding:NSMacOSRomanStringEncoding]==NO){
		str[0]=0;
	}
	
bvDefQuickTextStyle*	stl;
	for(long i=1;i<=_ext->runs().count();i++){
		if([_run_tbl isRowSelected:i-1]==YES){
			_ext->runs().get(i,&stl);
			strcpy(stl->_font,str);
			[_fnt_fld setCharValue:str];
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)changeAttributes:(id)sender{
	NSBeep();
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
vDefPaletteQuickTextWindowController	*controller;
NSAutoreleasePool						*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[vDefPaletteQuickTextWindowController alloc] init];
    [controller setExt:(bStdNSPalettevDef*)ext];
    [localPool release];
    return((void*)controller);
}

