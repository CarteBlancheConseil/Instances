//----------------------------------------------------------------------------
// File : MakeSquaringWindowController.h
// Project : MacMap
// Purpose : Header file : XMap MakeSquaring window controller
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
// 05/07/2016 creation.
//----------------------------------------------------------------------------

#import <std_ext/bStdNSAppModalWindowController.h>

//----------------------------------------------------------------------------
@interface MakeSquaringWindowController : bStdNSAppModalWindowController{
    IBOutlet NSTextField*	_xxxtxt;
    IBOutlet NSTextField*	_xxxlbl;
    IBOutlet NSTextField*	_yyytxt;
    IBOutlet NSTextField*	_yyylbl;

    IBOutlet NSTextField*	_nbhtxt;
    IBOutlet NSTextField*	_nbvtxt;

    IBOutlet NSTextField*	_csztxt;
    IBOutlet NSTextField*	_cszlbl;
    
    IBOutlet NSPopUpButton*	_shppop;
}

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
