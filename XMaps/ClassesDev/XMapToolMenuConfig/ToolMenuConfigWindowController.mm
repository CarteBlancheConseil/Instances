//----------------------------------------------------------------------------
// File : ToolMenuConfigWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap tool menu configuration window controller
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
// 24/02/2016 creation.
//----------------------------------------------------------------------------

#import "ToolMenuConfigWindowController.h"
#import "bXMapToolMenuConfig.h"
#import "CocoaStuff.h"

#import <mox_intf/xmldesc_utils.h>
#import <mox_intf/endian.h>

#import <std_ext/bStdTool.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
//
// ------------
int sgn_comp(   const void* a,
                const void* b){
UInt32	sa=*((UInt32*)a);
UInt32	sb=*((UInt32*)b);
    if(sa<sb){
        return(-1);
    }
    if(sa>sb){
        return(1);
    }
    return(0);
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation ToolMenuConfigWindowController
// ---------------------------------------------------------------------------
//
// ------------
-(id)initWithExt:(bStdExt*)ext{
_bTrace_("[ToolMenuConfigWindowController initWithExt]",true);
    self=[super initWithExt:ext];
    if(self){
        _arr=new bArray(sizeof(UInt32));
    }
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[ToolMenuConfigWindowController dealloc]",true);
_tm_((void*)self);
    if(_arr){
        delete _arr;
        _arr=NULL;
    }
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[ToolMenuConfigWindowController awakeFromNib]",true);
bGenericXMLBaseElement* root=NULL;
bGenericXMLBaseElement* elt=NULL;
char					val[_values_length_max_];
UInt32					sgn;
bGenericMacMapApp*      gapp=(bGenericMacMapApp*)_ext->getapp();
    
    gapp->document()->readTree(&root,kStdToolConfigSign,kStdToolMenuConfig);
    if(root){
        for(long i=1;i<=gapp->classMgr()->CountElements(root,"sign");i++){
            elt=gapp->classMgr()->NthElement(root,i,"sign");
            if(!elt){
                break;
            }
            elt->getvalue(val);
            sgn=*((UInt32*)val);
#ifdef __LITTLE_ENDIAN__
            LBSwapWord(&sgn,sizeof(UInt32));
#endif
            if(gapp->toolMgr()->ext_index(sgn)>0){
_tm_(":"+(int*)&sgn);
                _arr->add(&sgn);
            }
        }
        gapp->classMgr()->ReleaseXMLInstance(root);
    }

    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[ToolMenuConfigWindowController close]",true);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bArray              arr(sizeof(xmlelt));
UInt32              sgn;
char                val[_values_length_max_];
    
    add_cdesc(arr,0,"param","");
    add_cdesc(arr,1,"version","3.0.0");
    
    for(long i=1;i<=_arr->count();i++){
        _arr->get(i,&sgn);
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&sgn,sizeof(UInt32));
#endif
        sprintf(val,"%.4s",&sgn);
        add_cdesc(arr,1,"sign",val);
    }

bGenericXMLBaseElement*	root=gapp->classMgr()->ParseXMLDescriptors(&arr);
    if(!gapp->document()->writeTree(root,kStdToolConfigSign,kStdToolMenuConfig)){
    }
    gapp->classMgr()->ReleaseXMLInstance(root);
    _arr->reset();

    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)cancelDialog:(id)sender{
    _arr->reset();
    [super cancelDialog:sender];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doAdd:(id)sender{
_bTrace_("[ToolMenuConfigWindowController doAdd]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
NSIndexSet*         set=[_flftbl selectedRowIndexes];
NSUInteger          idx=[set firstIndex];
UInt32              sgn;
    
    while(idx!=NSNotFound){
        sgn=gapp->toolMgr()->ext_signature(idx+1);
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&sgn,sizeof(UInt32));
#endif
        if(!_arr->search(&sgn,sgn_comp)){
            _arr->add(&sgn);
        }
        idx=[set indexGreaterThanIndex:idx];
    }
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doInsert:(id)sender{
_bTrace_("[ToolMenuConfigWindowController doInsert]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
NSIndexSet*         set=[_flftbl selectedRowIndexes];
NSUInteger          idx=[set lastIndex];
UInt32              sgn;
int                 iidx=[_flttbl selectedRow]+1;

    while(idx!=NSNotFound){
        sgn=gapp->toolMgr()->ext_signature(idx+1);
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&sgn,sizeof(UInt32));
#endif
        if(!_arr->search(&sgn,sgn_comp)){
            _arr->insert(iidx,&sgn);
        }
        idx=[set indexLessThanIndex:idx];
    }
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doAll:(id)sender{
_bTrace_("[ToolMenuConfigWindowController doAll]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
UInt32              sgn;

    _arr->reset();
    for(long i=1;i<=gapp->toolMgr()->count();i++){
        sgn=gapp->toolMgr()->ext_signature(i);
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&sgn,sizeof(UInt32));
#endif
        _arr->add(&sgn);
    }
    [_flttbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doRemove:(id)sender{
_bTrace_("[ToolMenuConfigWindowController doRemove]",true);
NSIndexSet* set=[_flttbl selectedRowIndexes];
NSUInteger  idx=[set lastIndex];

    while(idx!=NSNotFound){
        _arr->rmv(idx+1);
        idx=[set indexLessThanIndex:idx];
    }
    [_flttbl reloadData];
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
    if(aTableView==_flftbl){
        return(((bGenericMacMapApp*)_ext->getapp())->toolMgr()->count());
    }
    else{
        return(_arr->count());
    }
    return 0;
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)	tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
            row:(NSInteger)rowIndex{
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
NSString*           nsstr=nil;
char                str[256]="";
    if(aTableView==_flftbl){
        gapp->toolMgr()->ext_name(rowIndex+1,str);
    }
    else{
UInt32  sign;
        _arr->get(rowIndex+1,&sign);
        gapp->toolMgr()->ext_name(gapp->toolMgr()->ext_index(sign),str);
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
void runCocoaAppModal(bXMapToolMenuConfig* ext,
					  long* code){
ToolMenuConfigWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[ToolMenuConfigWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
