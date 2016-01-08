//----------------------------------------------------------------------------
// File : XMapFicheCell.h
// Project : MacMap
// Purpose : Header file : XMap fiche (i.e. card) cell
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
// 15/04/2014 creation.
//----------------------------------------------------------------------------

#import <AppKit/AppKit.h>
#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/bGenericGeoElement.h>
#import <mox_intf/bGenericType.h>
#import <mox_intf/ext_utils.h>

//----------------------------------------------------------------------------

enum{
	kCellNoKind,
	kCellStaticKind,
	kCellEditKind,
	kCellCheckBoxKind,
	kCellPopupKind,
	kCellListKind,
	kCellCoordListKind,
	kCellImageKind
};

#define _MARGIN_	5.0

//----------------------------------------------------------------------------
// Base classe
//----------------------------------------------------------------------------
@interface XMapFicheCell : NSObject{
    NSRect	_frame;
    NSRect	_name_area;
    NSRect	_value_area;
	long	_field;
	long	_fieldId;
	BOOL	_current;
}

//----------------------------------------------------------------------------

-(id)initWithPoint:(NSPoint)point 
	   application:(bGenericMacMapApp*)gapp 
			  type:(bGenericType*)typ 
			 field:(long)fld;

+(void)setObject:(bGenericGeoElement*)geo;

-(void)setFrame:(NSRect)rect;
-(NSRect)frame;

-(void)setCurrent:(BOOL)flg;
-(BOOL)current;

-(long)fieldIndex;
-(void)name:(char*)buffer;
-(long)kind;

-(void)drawRect:(NSRect)rect;

// Managing mouse clic
-(BOOL)mouse:(NSEvent*)evt 
	  inView:(NSView*)view;
-(BOOL)rightMouse:(NSEvent*)evt 
	  inView:(NSView*)view;
// Managing keyboard event
-(BOOL)key:(NSEvent*)evt
	inView:(NSView*)view;
-(BOOL)abort;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// CheckBox
//----------------------------------------------------------------------------
@interface XMapFicheCheckBoxCell : XMapFicheCell{
}

//----------------------------------------------------------------------------

-(long)kind;
-(void)drawRect:(NSRect)rect;
-(BOOL)mouse:(NSEvent*)evt 
	  inView:(NSView*)view;
-(BOOL)key:(NSEvent*)evt
	inView:(NSView*)view;
-(void)assign;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// Subclasser for keyDown catching
//----------------------------------------------------------------------------
@interface XMapFicheCoordListCellTableView : NSTableView{
}

//----------------------------------------------------------------------------

-(void)keyDown:(NSEvent*)event;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// Coord List
//----------------------------------------------------------------------------
@interface XMapFicheCoordListCell : XMapFicheCell{
	NSScrollView*	_scl;
	NSTableView*	_tbl;
	NSTableColumn*	_clx;
	NSTableColumn*	_cly;
	ivertices*		_vxs;
	NSView*			_parent;
	NSResponder*	_responder;
}

//----------------------------------------------------------------------------

-(long)kind;
-(void)drawRect:(NSRect)rect;
-(BOOL)mouse:(NSEvent*)evt 
	  inView:(NSView*)view;
-(BOOL)rightMouse:(NSEvent*)evt 
		   inView:(NSView*)view;
-(BOOL)key:(NSEvent*)evt
	inView:(NSView*)view;
-(void)editInit:(NSView*)view;
-(void)assign;

-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView;
-(id)			tableView:(NSTableView *)aTableView 
objectValueForTableColumn:(NSTableColumn*)aTableColumn 
			  row:(NSInteger)rowIndex;
-(void)	tableView:(NSTableView *)aTableView
   setObjectValue:(id)anObject
   forTableColumn:(NSTableColumn*)aTableColumn
			  row:(NSInteger)rowIndex;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// Editable Text
//----------------------------------------------------------------------------
@interface XMapFicheEditTextCell : XMapFicheCell{
	NSTextField*	_fld;
	NSView*			_parent;
	NSResponder*	_responder;
}

//----------------------------------------------------------------------------

-(long)kind;
-(void)drawRect:(NSRect)rect;
-(BOOL)mouse:(NSEvent*)evt 
	  inView:(NSView*)view;
-(BOOL)key:(NSEvent*)evt
	inView:(NSView*)view;
-(void)editInit:(NSView*)view;
-(IBAction)assign:(id)sender;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// Popup Menu
//----------------------------------------------------------------------------
@interface XMapFichePopupCell : XMapFicheCell{
}

//----------------------------------------------------------------------------

-(long)kind;
-(void)drawRect:(NSRect)rect;
-(BOOL)mouse:(NSEvent*)evt 
	  inView:(NSView*)view;
-(BOOL)key:(NSEvent*)evt
	inView:(NSView*)view;
-(void)pop:(NSView*)view;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// Static text (ie : not editable)
//----------------------------------------------------------------------------
@interface XMapFicheStaticTextCell : XMapFicheCell{
}

//----------------------------------------------------------------------------

-(long)kind;
-(void)drawRect:(NSRect)rect;
-(BOOL)rightMouse:(NSEvent*)evt 
		   inView:(NSView*)view;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// List, not implemented
//----------------------------------------------------------------------------
@interface XMapFicheListCell : XMapFicheCell{
}

//----------------------------------------------------------------------------

-(long)kind;
-(void)drawRect:(NSRect)rect;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
// Image, not implemented
//----------------------------------------------------------------------------
@interface XMapFicheImageCell : XMapFicheCell{
}

//----------------------------------------------------------------------------

-(long)kind;
-(void)drawRect:(NSRect)rect;

//----------------------------------------------------------------------------

@end


