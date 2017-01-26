//----------------------------------------------------------------------------
// File : FExpWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap export format window controller
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
// 23/02/2016 creation.
//----------------------------------------------------------------------------

#import "FExpWindowController.h"
#import "bXMapFExp.h"
#import "CocoaStuff.h"

#import <mox_intf/ext_utils.h>
#import <mox_intf/NSUIUtils.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
//
// ------------
int fexp_field_comp(const void* a,
                    const void* b){
fexp_field*	fa=(fexp_field*)a;
fexp_field*	fb=(fexp_field*)b;
    if(fa->fid<fb->fid){
        return(-1);
    }
    if(fa->fid>fb->fid){
        return(1);
    }
    return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation FExpWindowController
// ---------------------------------------------------------------------------
//
// ------------
-(id)initWithExt:(bStdExt*)ext{
_bTrace_("[FExpWindowController initWithExt]",true);
    self=[super initWithExt:ext];
    if(self){
        _arr=new bArray(sizeof(type_p*));
    }
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[FExpWindowController dealloc]",true);
_tm_((void*)self);
    if(_arr){
type_p*	p;
        for(long i=1;i<=_arr->count();i++){
            _arr->get(i,&p);
            delete p;
        }
        delete _arr;
        _arr=NULL;
    }
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[FExpWindowController awakeFromNib]",true);
bXMapFExp*  ext=(bXMapFExp*)_ext;
    NSPopupButtonRemoveAllItems(_typpop);
    NSPopupButtonPopulateWithTypes(_typpop,(bGenericMacMapApp*)ext->getapp(),kBaseNoKind,1);

//    [_flftbl setFrameOrigin:NSZeroPoint];
//    [_flttbl setFrameOrigin:NSZeroPoint];
    
bGenericType*   tp;
type_p*         p;
    for(long i=1;i<=((bGenericMacMapApp*)ext->getapp())->typesMgr()->count();i++){
        tp=((bGenericMacMapApp*)ext->getapp())->typesMgr()->get(i);
        p=new type_p(tp);
        p->load((bGenericMacMapApp*)ext->getapp());
        _arr->add(&p);
    }
    
bArray  tmp(sizeof(fexp_field));
char	name[512];
    ext->get(1,&tmp,&_srid);
    GetProjName(_srid,name);
    NSTextFieldSetValue(_prjtxt,name);

    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[FExpWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bXMapFExp*  ext=(bXMapFExp*)_ext;
type_p*     p;
    
    for(long i=1;i<=_arr->count();i++){
        _arr->get(i,&p);
        ext->set(i,&p->_flds,_srid);
        delete p;
    }
    _arr->reset();
    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)cancelDialog:(id)sender{
type_p* p;
    
    for(long i=1;i<=_arr->count();i++){
        _arr->get(i,&p);
        delete p;
    }
    _arr->reset();
    [super cancelDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doType:(id)sender{
_bTrace_("[FExpWindowController doAdd]",true);
    [_flftbl reloadData];
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doAdd:(id)sender{
_bTrace_("[FExpWindowController doAdd]",true);
NSIndexSet*     set=[_flftbl selectedRowIndexes];
NSUInteger      idx=[set firstIndex];
bGenericType*   tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typpop indexOfSelectedItem]+1);
type_p*         p;
fexp_field		fld={0,""};
    
    _arr->get([_typpop indexOfSelectedItem]+1,&p);
    while(idx!=NSNotFound){
        fld.fid=tp->fields()->get_id(idx+kOBJ_Name_);
        if(!p->_flds.search(&fld,fexp_field_comp)){
            p->_flds.add(&fld);
        }
        idx=[set indexGreaterThanIndex:idx];
    }
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doInsert:(id)sender{
_bTrace_("[FExpWindowController doInsert]",true);
NSIndexSet*     set=[_flftbl selectedRowIndexes];
NSUInteger      idx=[set lastIndex];
bGenericType*   tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typpop indexOfSelectedItem]+1);
type_p*         p;
fexp_field		fld={0,""};
int             iidx=[_flttbl selectedRow]+1;
    
    _arr->get([_typpop indexOfSelectedItem]+1,&p);
    while(idx!=NSNotFound){
        fld.fid=tp->fields()->get_id(idx+kOBJ_Name_);
        if(!p->_flds.search(&fld,fexp_field_comp)){
            p->_flds.insert(iidx,&fld);
        }
        idx=[set indexLessThanIndex:idx];
    }
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doAll:(id)sender{
_bTrace_("[FExpWindowController doAll]",true);
bGenericType*   tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typpop indexOfSelectedItem]+1);
type_p*         p;
fexp_field		fld={0,""};
    
    _arr->get([_typpop indexOfSelectedItem]+1,&p);
    p->_flds.reset();
    for(long i=kOBJ_Name_;i<=tp->fields()->count();i++){
        fld.fid=tp->fields()->get_id(i);
        p->_flds.add(&fld);
    }
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doRemove:(id)sender{
_bTrace_("[FExpWindowController doRemove]",true);
NSIndexSet*     set=[_flttbl selectedRowIndexes];
NSUInteger      idx=[set lastIndex];
type_p*         p;
    
    _arr->get([_typpop indexOfSelectedItem]+1,&p);
    while(idx!=NSNotFound){
        p->_flds.rmv(idx+1);
        idx=[set indexLessThanIndex:idx];
    }
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseProj:(id)sender{
_bTrace_("[FExpWindowController doChooseProj]",true);
    [[self window] setIsVisible:NO];
    if(GetAProj(&_srid,true)){
char	name[512];
        GetProjName(_srid,name);
        NSTextFieldSetValue(_prjtxt,name);
    }
    [[self window] setIsVisible:YES];
}

#pragma mark ---- Gestion TableView ----
// -------------------------------------------------------------------------;--
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
    if(aTableView==_flftbl){
bGenericType*   tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typpop indexOfSelectedItem]+1);
        return(tp->fields()->count()-kOBJ_Name_+1);
    }
    else{
type_p* p;
        _arr->get([_typpop indexOfSelectedItem]+1,&p);
        return(p->_flds.count());
    }
    return 0;
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)	tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
            row:(NSInteger)rowIndex{
NSString*       nsstr=nil;
char            str[256]="";
fexp_field      fld;
bGenericType*   tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typpop indexOfSelectedItem]+1);
    if(aTableView==_flftbl){
        tp->fields()->get_name(rowIndex+kOBJ_Name_,str);
    }
    else{
type_p* p;
        _arr->get([_typpop indexOfSelectedItem]+1,&p);
        p->_flds.get(rowIndex+1,&fld);
        tp->fields()->get_name(tp->fields()->get_index(fld.fid),str);
    }
    nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
    return nsstr;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
    [self updateUI];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
    [_addbtn setEnabled:([_flftbl selectedRow]>=0)];
    [_insbtn setEnabled:(([_flftbl selectedRow]>=0)&&([_flttbl selectedRow]>=0))];
    [_allbtn setEnabled:YES];
    [_rmvbtn setEnabled:([_flttbl selectedRow]>=0)];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapFExp* ext,
					  long* code){
FExpWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[FExpWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
