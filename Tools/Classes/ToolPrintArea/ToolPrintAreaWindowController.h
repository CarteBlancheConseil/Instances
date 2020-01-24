//----------------------------------------------------------------------------
// File : ToolPrintAreaWindowController.h
// Project : MacMap
// Purpose : Header file : Tool PrintArea window controller
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 27/03/2017 creation.
//----------------------------------------------------------------------------

#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------
@interface ToolPrintAreaWindowController : bStdNSAppToolModalWindowController{

    IBOutlet NSTextField*    _orx_txt;
    IBOutlet NSTextField*    _ory_txt;
    IBOutlet NSTextField*    _orx_unt;
    IBOutlet NSTextField*    _ory_unt;
    
    IBOutlet NSPopUpButton* _knd_pop;
    IBOutlet NSTabView*     _are_viw;
    
    IBOutlet NSTextField*    _gwd_txt;
    IBOutlet NSTextField*    _ght_txt;
    IBOutlet NSTextField*    _gwd_unt;
    IBOutlet NSTextField*    _ght_unt;

    IBOutlet NSTextField*    _pwd_txt;
    IBOutlet NSTextField*    _pht_txt;

    IBOutlet NSTextField*    _cwd_txt;
    IBOutlet NSTextField*    _cht_txt;

    IBOutlet NSPopUpButton* _psz_pop;
    IBOutlet NSMatrix*      _hov_mtx;

    IBOutlet NSButton*      _shw_chk;
}

//----------------------------------------------------------------------------
-(IBAction)doChooseMethod:(id)sender;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
