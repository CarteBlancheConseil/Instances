//----------------------------------------------------------------------------
// File : vDefPalettePieChartWindowController.h
// Project : MacMap
// Purpose : Header file : Pie chart vdef window controller
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
// 09/07/2013 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSPalettevDefWindowController.h>
#import <std_ext/vDefPalettePreview.h>

//----------------------------------------------------------------------------
// Juste pour avoir la classe en local pour IB
@interface vDefPalettePieChartPanel : bStdNSPalettevDefPanel{
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------

@interface vDefPalettePieChartWindowController : bStdNSPalettevDefWindowController{
// Interface
// Std Cocoa Palette vDef
	IBOutlet NSTableView*			_run_tbl;	// StyleRuns
	IBOutlet vDefPalettePreview*	_prvw;		// Preview
	IBOutlet NSTextField*			_tnm_fld;	// Nom du type
	
// Statistiques
	IBOutlet NSPopUpButton*			_fld_pop;	// Champs
	IBOutlet NSButton*				_add_btn;	// Ajouter un champ
	IBOutlet NSButton*				_rmv_btn;	// Supprimer un champ

	IBOutlet NSTextField*			_rad_fld;
	IBOutlet NSTextField*			_szx_fld;
	IBOutlet NSColorWell*			_fil_clr;	// Couleur
	IBOutlet NSSlider*				_fil_sld;

	IBOutlet NSColorWell*			_stk_clr;
	IBOutlet NSTextField*			_wdt_fld;

	IBOutlet NSButton*				_prop_chk;		// Proportionnalité
	IBOutlet NSPopUpButton*			_prop_fld_pop;	// Champ proportionnalité
	IBOutlet NSPopUpButton*			_prop_prp_pop;	// Méthode proportionnalité
	IBOutlet NSPopUpButton*			_prop_min_pop;	// Calcul du min
	IBOutlet NSTextField*			_prop_min_fld;	// Minimum	
	IBOutlet NSPopUpButton*			_prop_max_pop;	// Calcul du max
	IBOutlet NSTextField*			_prop_max_fld;	// Maximum	

// Visibilité
	IBOutlet NSPopUpButton*			_smn_pop;	// Echelle min
	IBOutlet NSPopUpButton*			_smx_pop;	// Echelle max
	
// Options : general
	IBOutlet NSPopUpButton*			_o_srf_pop;	// Echelle de référence
	IBOutlet NSPopUpButton*			_o_unt_pop;	// Unité
	IBOutlet NSButton*				_o_cls_chk;	// CMYK
	
// Options : conditions
	IBOutlet NSButton*				_o_dif_chk; // Afficher si
	IBOutlet NSPopUpButton*			_o_cnf_pop;	// Champ condition
	IBOutlet NSPopUpButton*			_o_cno_pop;	// Opérateur
	IBOutlet NSTextField*			_o_val_fld;	// Valeur
	
// Options : offset
	IBOutlet NSButton*				_o_off_chk; // Offset
	IBOutlet NSPopUpButton*			_o_xof_pop;	// Champ offset X
	IBOutlet NSPopUpButton*			_o_yof_pop;	// Champ offset Y
	
	IBOutlet NSButton*				_upd_btn;
	
	NSInteger						_last_click;
	BOOL							_hprev;
	double							_qmin;
	double							_qmax;

}


//----------------------------------------------------------------------------
// Actions principal
-(IBAction)doChooseField:(id)sender;
-(IBAction)doAddField:(id)sender;
-(IBAction)doRemoveField:(id)sender;

-(IBAction)doPutRadius:(id)sender;
-(IBAction)doChooseFillColor:(id)sender;
-(IBAction)doPutFillAlpha:(id)sender;
-(IBAction)doPutWidth:(id)sender;
-(IBAction)doPutStrokeColor:(id)sender;

-(IBAction)doCheckProp:(id)sender;
-(IBAction)doChoosePropField:(id)sender;
-(IBAction)doChoosePropMethod:(id)sender;
-(IBAction)doChooseMin:(id)sender;
-(IBAction)doPutMin:(id)sender;
-(IBAction)doChooseMax:(id)sender;
-(IBAction)doPutMax:(id)sender;

-(IBAction)doChooseScaleMin:(id)sender;
-(IBAction)doChooseScaleMax:(id)sender;

-(IBAction)doClickPreview:(id)sender;//

// Actions options
-(IBAction)doChooseScaleRef:(id)sender;
-(IBAction)doChooseUnit:(id)sender;
-(IBAction)doChooseColorSpace:(id)sender;

-(IBAction)doCheckCondition:(id)sender;
-(IBAction)doChooseCondField:(id)sender;
-(IBAction)doChooseCondOperator:(id)sender;
-(IBAction)doPutCondValue:(id)sender;

-(IBAction)doCheckOffset:(id)sender;
-(IBAction)doChooseOffsetXField:(id)sender;
-(IBAction)doChooseOffsetYField:(id)sender;

// Actions appliquer
-(IBAction)doApply:(id)sender;

//----------------------------------------------------------------------------
// Gestion table
-(NSInteger)	numberOfRowsInTableView:(NSTableView*)aTableView;
-(id)			tableView:(NSTableView *)aTableView 
				objectValueForTableColumn:(NSTableColumn*)aTableColumn 
				row:(NSInteger)rowIndex;
-(void)			tableViewSelectionDidChange:(NSNotification*)notification;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)updateSizeMax;
-(void)checkIntfAvailability;
-(void)plot2Intf;
-(void)convertColor;
-(void)drawPreview:(CGRect)rect context:(CGContextRef)ctx;
//-(void)clickPreview:(CGPoint)point modifiers:(NSUInteger)mod;

//----------------------------------------------------------------------------
// Fonctions de calcul des tailles max
-(double)sizeMax;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
