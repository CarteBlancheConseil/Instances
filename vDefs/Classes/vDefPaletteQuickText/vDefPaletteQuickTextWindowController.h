//----------------------------------------------------------------------------
// File : vDefPaletteQuickTextWindowController.h
// Project : MacMap
// Purpose : Header file : Text vdef window controller
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

#import <Cocoa/Cocoa.h>
#import <vdef_lib/bvDefPaletteQuickWindowController.h>
#import <std_ext/bStdNSPalettevDefWindowController.h>
//#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPaletteQuickTextPanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end


//----------------------------------------------------------------------------

@interface vDefPaletteQuickTextWindowController : bvDefPaletteQuickWindowController{
	// Interface	
	IBOutlet NSButton*				_cnt_chk;
	
	IBOutlet NSPopUpButton*			_fld_pop;
	
	IBOutlet NSButton*				_fnt_btn;
	IBOutlet NSTextField*			_fnt_fld;
	IBOutlet NSTextField*			_fsz_fld;
	IBOutlet NSTextField*			_fwd_fld;
	IBOutlet NSColorWell*			_ffl_clr;
	IBOutlet NSColorWell*			_fst_clr;
	
	IBOutlet NSSlider*				_bfl_sld;
	IBOutlet NSColorWell*			_bfl_clr;
	IBOutlet NSTextField*			_bwd_fld;
	IBOutlet NSColorWell*			_bst_clr;
	IBOutlet NSTextField*			_bmv_fld;
	IBOutlet NSTextField*			_bmh_fld;
	IBOutlet NSTextField*			_brd_fld;
	IBOutlet NSTextField*			_bdc_fld;
	
	IBOutlet NSPopUpButton*			_alg_pop;
	IBOutlet NSTextField*			_ilt_fld;
	IBOutlet NSTextField*			_iwd_fld;
	IBOutlet NSTextField*			_rot_fld;
	IBOutlet NSTextField*			_dec_fld;
	IBOutlet NSTextField*			_dxx_fld;
	IBOutlet NSTextField*			_dyy_fld;
	IBOutlet NSButton*				_smt_chk;
	IBOutlet NSButton*				_leg_chk;
	
	
	IBOutlet NSPopUpButton*			_ffnt_pop;//
	IBOutlet NSPopUpButton*			_ffsz_pop;//
	IBOutlet NSPopUpButton*			_ffwd_pop;//
	IBOutlet NSPopUpButton*			_fffl_pop;//
	IBOutlet NSPopUpButton*			_ffst_pop;//
	
	IBOutlet NSPopUpButton*			_fbfl_pop;//
	IBOutlet NSPopUpButton*			_fbst_pop;//
	IBOutlet NSPopUpButton*			_fbwd_pop;//
	IBOutlet NSPopUpButton*			_fbmv_pop;//
	IBOutlet NSPopUpButton*			_fbmh_pop;//
	IBOutlet NSPopUpButton*			_fbrd_pop;//
	IBOutlet NSPopUpButton*			_fbdc_pop;//
	
	IBOutlet NSPopUpButton*			_falg_pop;
	IBOutlet NSPopUpButton*			_filt_pop;
	IBOutlet NSPopUpButton*			_fiwd_pop;
	IBOutlet NSPopUpButton*			_frot_pop;
	IBOutlet NSPopUpButton*			_fdec_pop;//
	IBOutlet NSPopUpButton*			_fdxx_pop;//
	IBOutlet NSPopUpButton*			_fdyy_pop;//
	IBOutlet NSPopUpButton*			_fsmt_pop;//
	IBOutlet NSPopUpButton*			_fleg_pop;//
}

//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doPutCentroid:(id)sender;

-(IBAction)doPutField:(id)sender;

-(IBAction)doPutFont:(id)sender;
-(IBAction)doPutFontSize:(id)sender;
-(IBAction)doPutFontWidth:(id)sender;
-(IBAction)doPutFontFillColor:(id)sender;
-(IBAction)doPutFontStrokeColor:(id)sender;

-(IBAction)doPutBackAlpha:(id)sender;
-(IBAction)doPutBackWidth:(id)sender;
-(IBAction)doPutBackFillColor:(id)sender;
-(IBAction)doPutBackStrokeColor:(id)sender;
-(IBAction)doPutBackVerticalMargin:(id)sender;
-(IBAction)doPutBackHorizontalMargin:(id)sender;
-(IBAction)doPutBackRadius:(id)sender;
-(IBAction)doPutBackDec:(id)sender;

-(IBAction)doPutAlignement:(id)sender;
-(IBAction)doPutInterLetter:(id)sender;
-(IBAction)doPutInterWord:(id)sender;
-(IBAction)doPutRotation:(id)sender;
-(IBAction)doPutDec:(id)sender;
-(IBAction)doPutDX:(id)sender;
-(IBAction)doPutDY:(id)sender;
-(IBAction)doPutSmoothing:(id)sender;
-(IBAction)doPutLegibility:(id)sender;


-(IBAction)doPutFontField:(id)sender;
-(IBAction)doPutFontSizeField:(id)sender;
-(IBAction)doPutFontWidthField:(id)sender;
-(IBAction)doPutFontFillColorField:(id)sender;
-(IBAction)doPutFontStrokeColorField:(id)sender;

-(IBAction)doPutBackWidthField:(id)sender;
-(IBAction)doPutBackFillColorField:(id)sender;
-(IBAction)doPutBackStrokeColorField:(id)sender;
-(IBAction)doPutBackVerticalMarginField:(id)sender;
-(IBAction)doPutBackHorizontalMarginField:(id)sender;
-(IBAction)doPutBackRadiusField:(id)sender;
-(IBAction)doPutBackDecField:(id)sender;

-(IBAction)doPutAlignementField:(id)sender;
-(IBAction)doPutInterLetterField:(id)sender;
-(IBAction)doPutInterWordField:(id)sender;
-(IBAction)doPutRotationField:(id)sender;
-(IBAction)doPutDecField:(id)sender;
-(IBAction)doPutDXField:(id)sender;
-(IBAction)doPutDYField:(id)sender;
-(IBAction)doPutSmoothingField:(id)sender;
-(IBAction)doPutLegibilityField:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)checkIntfAvailability;
-(void)plot2Intf;
-(void)convertColor;
-(void)drawPreview:(CGRect)Text context:(CGContextRef)ctx;

//----------------------------------------------------------------------------

-(void)close;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
