//----------------------------------------------------------------------------
// File : SelectorWindowController.h
// Project : MacMap
// Purpose : Header file : XMap selector window controller
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
// 29/07/2016 creation.
//----------------------------------------------------------------------------

#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------
@interface SelectorWindowController : bStdNSAppModalWindowController{
    IBOutlet NSTabView*     _itm_tab;

    
	IBOutlet NSPopUpButton*	_typ_pop;
	IBOutlet NSPopUpButton*	_foc_pop;
    IBOutlet NSPopUpButton*	_ope_pop;

	IBOutlet NSTableView*	_fld_tbl;
    IBOutlet NSTextField*	_val_val;
    IBOutlet NSPopUpButton*	_cnt_pop;
    IBOutlet NSButton*		_add_btn;
    IBOutlet NSButton*		_oqs_chk;
    IBOutlet NSMatrix*		_a_o_mtx;

    IBOutlet NSTableView*	_crt_tbl;
    IBOutlet NSButton*		_rmv_btn;
    
    
    IBOutlet NSPopUpButton*	_geo_pop;
    IBOutlet NSView*        _geo_viw;

    
    IBOutlet NSMatrix*		_ras_mtx;
    IBOutlet NSButton*		_tcn_chk;
    IBOutlet NSButton*		_tms_chk;
    IBOutlet NSMatrix*		_tot_mtx;
    IBOutlet NSButton*		_msk_chk;
    IBOutlet NSPopUpButton*	_mcr_pop;
    
    
    IBOutlet NSTextField*	_nam_val;
}

//----------------------------------------------------------------------------
-(IBAction)doChooseType:(id)sender;
-(IBAction)doChooseFieldOrCalc:(id)sender;
-(IBAction)doRemove:(id)sender;
-(IBAction)doAdd:(id)sender;
-(IBAction)doConstraints:(id)sender;
-(IBAction)doCheckMask:(id)sender;
-(IBAction)doGeog:(id)sender;

//----------------------------------------------------------------------------
-(void)updateUI;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
