//----------------------------------------------------------------------------
// File : StyleMgrWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : Styles manager XMapBox window controller
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
// 12/11/2014 creation.
//----------------------------------------------------------------------------

#import "StyleMgrWindowController.h"
#import "bXBoxStyleMgr.h"
#import "CocoaStuff.h"

#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/endian.h>

#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
// 
// ------------
static void NSPopupButtonPopulateWithvDefs(NSPopUpButton* c, 
										   bGenericMacMapApp* gapp, 
										   bGenericType* tp){
_bTrace_("NSPopupButtonPopulateWithvDefs",true);
char			str[256];
bGenericExt*	vdef;
	
//NSPopupButtonRemoveItemsFrom(c,2);
    NSPopupButtonRemoveItemsFrom(c,1);
	for(long i=1;i<=gapp->vdefMgr()->count();i++){
		vdef=gapp->vdefMgr()->get(i);
		gapp->vdefMgr()->ext_name(i,str);
_tm_((int)i+"=>"+str);
		NSPopupButtonAddMenuItemValue(c,str);
		if(!vdef->test(tp)){
			NSPopupButtonMenuItemDisable(c,i-1+2);
		}	
	}
	[c selectItemAtIndex:0];
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation StyleMgrPanel

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
@implementation StyleMgrWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[StyleMgrWindowController init]",true);
	self=[super init];
	if(self){
		_tp_index=0;
		_vdef_sgn=_kNULLSign_;
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[StyleMgrWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[StyleMgrWindowController awakeFromNib]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
long				idx=gapp->layersMgr()->get_current();
    if(gapp->typesMgr()->count()==0){
        idx=0;
    }
_tm_(idx);
bGenericType*		tp=NULL;
	if(idx==0){
		_tp_index=-1;
	}
	else{
bGenericStyle*	stl=gapp->layersMgr()->get(idx);
		tp=stl->gettype();
		if(tp){
			_tp_index=stl->gettype()->index();
            _last_count=tp->styles()->count();
		}
		else{
			_tp_index=-1;
            _last_count=gapp->document()->styles()->count();
		}
	}
	NSPopupButtonPopulateWithTypes(_typ_pop,(bGenericMacMapApp*)_ext->getapp(),kBaseNoKind,_tp_index==-1?1:_tp_index+2);
	NSPopupButtonPopulateWithvDefs(_stl_pop,gapp,tp);
	[[_stl_pop menu] setAutoenablesItems:NO];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[StyleMgrWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseType:(id)sender{
//_bTrace_("[StyleMgrWindowController doChooseType]",true);
	_tp_index=[_typ_pop indexOfSelectedItem]-1;
	_vdef_sgn=_kNULLSign_;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
	NSPopupButtonPopulateWithvDefs(_stl_pop,gapp,tp);
	[_stl_tbl reloadData];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doChooseStyle:(id)sender{
//_bTrace_("[StyleMgrWindowController doChooseStyle]",true);
long		idx=[_stl_pop indexOfSelectedItem];
	if(idx==1){
		_vdef_sgn=_kNULLSign_;
	}
	else{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
		_vdef_sgn=gapp->vdefMgr()->ext_signature(idx-1);
	}
	[_stl_tbl reloadData];	
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doAddStyle:(id)sender{
//_bTrace_("[StyleMgrWindowController doAddStyle]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
unsigned int		sign=_vdef_sgn;
#ifdef __LITTLE_ENDIAN__
	LBSwapWord(&sign,sizeof(int));
#endif

	if(tp){
		if(!tp->styles()->create(sign)){
			NSBeep();
		}
	}
	else{
		if(!gapp->document()->styles()->create(sign)){
			NSBeep();
		}
	}	
	[_stl_tbl reloadData];		
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doEditStyle:(id)sender{
//_bTrace_("[StyleMgrWindowController doEditStyle]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
int					idx=[self getStyleIndex:[_stl_tbl selectedRow]];
	if(idx<0){
		return;
	}
UInt32				sign=_vdef_sgn;
#ifdef __LITTLE_ENDIAN__
	LBSwapWord(&sign,sizeof(UInt32));
#endif
	if(tp){
		if(!tp->styles()->edit(idx,sign)){
			NSBeep();
		}
	}
	else{
		if(!gapp->document()->styles()->edit(idx,sign)){
			NSBeep();
		}
	}
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doDuplicateStyle:(id)sender{
//_bTrace_("[StyleMgrWindowController doDuplicateStyle]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
int					idx=[self getStyleIndex:[_stl_tbl selectedRow]];
	if(idx<0){
		return;
	}
	if(tp){
		if(!tp->styles()->duplicate(idx)){	
			NSBeep();
		}
	}
	else{
		if(!gapp->document()->styles()->duplicate(idx)){	
			NSBeep();
		}
	}
	[_stl_tbl reloadData];		
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doRenameStyle:(id)sender{
int	idx=[_stl_tbl selectedRow];
	if(idx<0){
		return;
	}
	[_stl_tbl editColumn:0 row:idx withEvent:nil select:YES];
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doDeleteStyle:(id)sender{
//_bTrace_("[StyleMgrWindowController doDeleteStyle]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
int					idx=[self getStyleIndex:[_stl_tbl selectedRow]];
	if(idx<0){
		return;
	}
	if(tp){
		if(!tp->styles()->remove(idx)){
			NSBeep();
		}
	}
	else{
		if(!gapp->document()->styles()->remove(idx)){
			NSBeep();
		}
	}
	[_stl_tbl reloadData];		
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doEditStyleAsXML:(id)sender{
//_bTrace_("[StyleMgrWindowController doEditStyleAsXML]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
int					idx=[self getStyleIndex:[_stl_tbl selectedRow]];
	if(idx<0){
		return;
	}
UInt32				sign=kvDefUltraSignature;
	if(tp){
		if(!tp->styles()->edit(idx,sign)){
			NSBeep();
		}
	}
	else{
		if(!gapp->document()->styles()->edit(idx,sign)){
			NSBeep();
		}
	}
	[_stl_tbl reloadData];			
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doAddStyleToView:(id)sender{
//_bTrace_("[StyleMgrWindowController doAddStyleToView]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
int					idx=[self getStyleIndex:[_stl_tbl selectedRow]];
	if(idx<0){
		return;
	}
    if(gapp->layersMgr()->add(_tp_index,idx)){
        gapp->layersMgr()->set_current(gapp->layersMgr()->count());
    }
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
	[_new_btn setEnabled:(_vdef_sgn!=_kNULLSign_)];
	
	[_edt_btn setEnabled:([_stl_tbl selectedRow]>=0)&&(_vdef_sgn!=_kNULLSign_)];

	[_dup_btn setEnabled:([_stl_tbl selectedRow]>=0)];
	[_ren_btn setEnabled:([_stl_tbl selectedRow]>=0)];
    
	[_xml_btn setEnabled:([_stl_tbl selectedRow]>=0)];
	[_avw_btn setEnabled:([_stl_tbl selectedRow]>=0)];
    
BOOL state=NO;
    if([_stl_tbl selectedRow]>=0){
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
int					idx=[self getStyleIndex:[_stl_tbl selectedRow]];
   
        if(tp){
            if(!tp->styles()->get_on_screen(idx) &&
               !tp->styles()->get_on_edit(idx)   ){
                state=YES;
            }
        }
        else{
            if(!gapp->document()->styles()->get_on_screen(idx) &&
               !gapp->document()->styles()->get_on_edit(idx)   ){
                state=YES;
            }
        }
    }
    [_del_btn setEnabled:state];

}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
NSInteger			nr=0;
	
	if(tp){
		if(_vdef_sgn==_kNULLSign_){
			nr=tp->styles()->count();
		}
		else{
			for(long i=1;i<=tp->styles()->count();i++){		
				if((tp->styles()->signature(i)==_vdef_sgn)){
					nr++;
				}
			}
		}
	}
	else{
		if(_vdef_sgn==_kNULLSign_){
			nr=gapp->document()->styles()->count();
		}
		else{
			for(long i=1;i<=gapp->document()->styles()->count();i++){		
				if((gapp->document()->styles()->signature(i)==_vdef_sgn)){
					nr++;
				}
			}
		}		
	}
	return(nr);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{
_bTrace_("[StyleMgrWindowController tableView:objectValueForTableColumn:row]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
NSInteger			nr=0;
char				name[256]="uninit";
	
	nr=[self getStyleIndex:rowIndex];
	if(tp){
		tp->styles()->get_name(nr,name);
	}
	else{
		gapp->document()->styles()->get_name(nr,name);
	}
	return [NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)	tableView:(NSTableView *)aTableView
   setObjectValue:(id)anObject
   forTableColumn:(NSTableColumn*)aTableColumn
			  row:(NSInteger)rowIndex{
_bTrace_("[StyleMgrWindowController tableView:setObjectValue:forTableColumn:row]",true);
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
NSInteger			nr=0;
char				name[256]="uninit";
NSString*			nsstr=(NSString*)anObject;
_tm_(rowIndex);
	
	[nsstr getCString:name maxLength:255 encoding:NSMacOSRomanStringEncoding];
	nr=[self getStyleIndex:rowIndex];
	if(tp){
_tm_(nr);
		if(!tp->styles()->set_name(nr,name)){
			NSBeep();
		}
	}
	else{
		if(!gapp->document()->styles()->set_name(nr,name)){
			NSBeep();
		}
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)getStyleIndex:(NSInteger)rowIndex{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
NSInteger			nr=0;

	if(rowIndex<0){
		return(-1);
	}
	
	if(tp){
		if(_vdef_sgn==_kNULLSign_){
			nr=rowIndex+1;
		}
		else{
			for(long i=1;i<=tp->styles()->count();i++){		
				if((tp->styles()->signature(i)==_vdef_sgn)){
					nr++;
					if(nr==rowIndex+1){
						nr=i;
						break;
					}
				}
			}
		}
	}
	else{
		if(_vdef_sgn==_kNULLSign_){
			nr=rowIndex+1;
		}
		else{
			for(long i=1;i<=gapp->document()->styles()->count();i++){		
				if((gapp->document()->styles()->signature(i)==_vdef_sgn)){
					nr++;
					if(nr==rowIndex+1){
						nr=i;
						break;
					}
				}
			}
		}		
	}
	return(nr);
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
//
// ------------
-(void)idle{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(_tp_index);
NSInteger			nr=0;
    
    if(tp){
        nr=tp->styles()->count();
    }
    else{
        nr=gapp->document()->styles()->count();
    }
    if(nr!=_last_count){
        _last_count=nr;
        [_stl_tbl reloadData];
    }
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)checkMacMapEvent{
    [super checkMacMapEvent];
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bArray*				arr=gapp->eventMgr()->events();
bGenericEvent*		evt;
    
    for(long i=1;i<=arr->count();i++){
        arr->get(i,&evt);
        if((evt->action()==kEventActionCreate)     &&
           (evt->kind()==kEventKindTypeElement)    ){
            NSPopupButtonRemoveItemsFrom(_typ_pop,1);
            NSPopupButtonPopulateWithTypes(_typ_pop,gapp,kBaseNoKind,_tp_index==-1?1:_tp_index+2);
        }
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
StyleMgrWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[StyleMgrWindowController alloc] init];
    [controller setExt:(bStdNSXBox*)ext];
    [localPool release];
    return((void*)controller);
}

