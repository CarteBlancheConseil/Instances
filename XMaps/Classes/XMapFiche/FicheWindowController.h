//----------------------------------------------------------------------------
// File : FicheWindowController.h
// Project : MacMap
// Purpose : Header file : XMap fiche (i.e. card) window controller
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
// 14/04/2014 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSXMapWindowController.h>
#import <MacMapSuite/bArray.h>

//----------------------------------------------------------------------------

@interface FicheObjView : NSView{
	bGenericMacMapApp*	_gapp;
	bGenericGeoElement*	_o;
	bGenericType*		_tp;	
	NSMutableArray*		_cells;
	BOOL				_addNew;
	long				_lastCell;
	BOOL				_cic;
	BOOL				_first;
}

//----------------------------------------------------------------------------

-(id)initWithFrame:(NSRect)frameRect;
-(void)dealloc;
-(void)read_p;
-(void)write_p;
-(bGenericXMLBaseElement*)make_p;
-(void)resetType;
-(void)initType;
-(BOOL)abort;
-(void)putBounds;
-(void)updateField:(long)fieldId;
-(void)removeField:(long)fieldId;
-(void)addField:(long)fieldId;

//----------------------------------------------------------------------------

@end


//----------------------------------------------------------------------------

@interface FichePanel : bStdNSXMapPanel{
	IBOutlet FicheObjView*	_viw;
}

//----------------------------------------------------------------------------

@end


//----------------------------------------------------------------------------

@interface FicheWindowController : bStdNSXMapWindowController{
	IBOutlet NSButton*		_sel;
	IBOutlet NSButton*		_frs;
	IBOutlet NSButton*		_prv;
	IBOutlet NSButton*		_nxt;
	IBOutlet NSButton*		_lst;
	IBOutlet NSButton*		_rin;
	IBOutlet NSTextField*	_cnt;
	IBOutlet NSTextField*	_typ;

	IBOutlet NSScrollView*	_svw;
	IBOutlet FicheObjView*	_viw;
	
	bArray*					_arr;
	long					_cur;
	
	long					_ls;
    
    NSString*               _fke;
    NSUInteger              _fkm;
    NSString*               _nke;
    NSUInteger              _nkm;
    NSString*               _pke;
    NSUInteger              _pkm;
    NSString*               _lke;
    NSUInteger              _lkm;
}

//----------------------------------------------------------------------------
// Actions
-(IBAction)doSelect:(id)sender;
-(IBAction)doFirst:(id)sender;
-(IBAction)doPrevious:(id)sender;
-(IBAction)doNext:(id)sender;
-(IBAction)doLast:(id)sender;
-(IBAction)doReorganize:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI:(BOOL)reload;
-(void)setKeyEquivalent:(BOOL)on;

//----------------------------------------------------------------------------
// Interface XMap
-(bGenericMacMapApp*)getApp;
-(void)getParamsInfos:(char*)directory 
				 name:(char*)prmName;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
