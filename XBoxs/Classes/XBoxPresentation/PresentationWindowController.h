//----------------------------------------------------------------------------
// File : PresentationWindowController.h
// Project : MacMap
// Purpose : Header file : Presentation XMapBox window controller
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
// 01/04/2015 creation.
//----------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#import <std_ext/bStdNSXBoxWindowController.h>

//----------------------------------------------------------------------------
// Panel subclass
@interface PresentationPanel : bStdNSXBoxPanel{
}
//----------------------------------------------------------------------------
@end

//----------------------------------------------------------------------------
// TableCellView subclass
@interface PresentationTableCellView : NSTableCellView{
    NSTextField*    _stylField;
}
//----------------------------------------------------------------------------
@property(nonatomic, retain) IBOutlet NSTextField *stylField;
//----------------------------------------------------------------------------
-(BOOL)popupStyle;
-(BOOL)popupClass;
-(void)mouseDownForCell:(NSEvent*)theEvent;
//----------------------------------------------------------------------------
@end


//----------------------------------------------------------------------------
// TableView subclass
@interface PresentationTableView : NSTableView{
}
//----------------------------------------------------------------------------
@end



//----------------------------------------------------------------------------

@interface PresentationWindowController : bStdNSXBoxWindowController{	
    IBOutlet NSTableView*	_stl_viw;

    IBOutlet NSButton*      _mup_btn;
    IBOutlet NSButton*      _mdn_btn;
    IBOutlet NSButton*      _rmv_btn;
    IBOutlet NSButton*      _lck_btn;
    IBOutlet NSButton*      _hid_btn;
    IBOutlet NSButton*      _trk_btn;

    IBOutlet NSPopUpButton*	_stl_pop;
    IBOutlet NSPopUpButton*	_viw_pop;

    long    _ld;
    long    _lv;
    
    BOOL    _reload;
    BOOL    _refresh;
    BOOL    _modi;
}

//----------------------------------------------------------------------------
// Actions
-(IBAction)doMoveUp:(id)sender;
-(IBAction)doMoveDown:(id)sender;
-(IBAction)doRemove:(id)sender;
-(IBAction)doLock:(id)sender;
-(IBAction)doHide:(id)sender;
-(IBAction)doTrack:(id)sender;

-(IBAction)doStyleMgr:(id)sender;
-(IBAction)doAddStyle:(id)sender;

-(IBAction)doViewMgr:(id)sender;
-(IBAction)doSaveView:(id)sender;
-(IBAction)doScaleRef:(id)sender;
-(IBAction)doLegend:(id)sender;
-(IBAction)doChooseView:(id)sender;

//----------------------------------------------------------------------------
// Gestion Interface
-(void)updateUI;
-(void)populateTypes;
-(void)populateViews;
-(void)askForViewSave;

-(void)redraw;
-(bGenericExt*)getExt;

//----------------------------------------------------------------------------

@end

//----------------------------------------------------------------------------
