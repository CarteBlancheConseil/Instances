//----------------------------------------------------------------------------
// File : SelectorWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap selector window controller
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

#import "SelectorWindowController.h"
#import "bXMapSelector.h"
#import "bXMapSelectorCriterion.h"
#import "CocoaStuff.h"

#import <mox_intf/bGenericCalc.h>
#import <mox_intf/bGenericGeog.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/mm_messages.h>
#import <mox_intf/mm_errors.h>
#import <mox_intf/bStdAlert.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/endian.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation SelectorWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[SelectorWindowController awakeFromNib]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapSelector*      ext=(bXMapSelector*)_ext;
UInt32              sign;
    
    if(ext->get_type()==NULL){
        ext->set_type(gapp->typesMgr()->get(1));
    }

	NSPopupButtonRemoveAllItems(_typ_pop);
	NSPopupButtonPopulateWithTypes(_typ_pop,gapp,kBaseNoKind,ext->get_type()->index());

    NSPopupButtonRemoveItemsFrom(_geo_pop,2);
    if(ext->get_geog()){
        sign=GetSignature(ext->get_geog());
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&sign,sizeof(UInt32));
#endif
        NSPopupButtonPopulateWithGeogs(_geo_pop,
                                       gapp,
                                       ext->get_type()->kind(),
                                       gapp->geogMgr()->ext_index(sign)+2);
        [self doGeog:nil];
    }
    else{
        NSPopupButtonPopulateWithGeogs(_geo_pop,gapp,ext->get_type()->kind(),1);
    }

    NSPopupButtonRemoveItemsFrom(_mcr_pop,2);
    sign=ext->get_next();
    if(sign!=0){
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&sign,sizeof(UInt32));
#endif
        NSPopupButtonPopulateWithMacros(_mcr_pop,
                                        gapp,
                                        gapp->macroMgr()->ext_index(sign)+2);
    }
    else{
        NSPopupButtonPopulateWithMacros(_mcr_pop,
                                        gapp,
                                        1);
    }
	
    [_ras_mtx selectCellAtRow:ext->get_selwhat()-1 column:0];
    [_tcn_chk setIntValue:ext->get_add2cnt()];
    [_tms_chk setIntValue:ext->get_add2hdn()?1:0];
    if(ext->get_add2hdn()){
        [_tot_mtx selectCellAtRow:ext->get_add2hdn()-1 column:0];
    }
    else{
        [_tot_mtx selectCellAtRow:0 column:0];
    }
    [_msk_chk setIntValue:ext->get_use_mask()];
    
    [_fld_tbl reloadData];
    [_itm_tab selectFirstTabViewItem:self];

char    name[256];
    switch(ext->get_action()){
        case kXMapSelectorSelect:
            [_nam_val setHidden:YES];
            break;
        case kXMapSelectorCreateMacro:
        case kXMapSelectorEditMacro:
            [_nam_val setHidden:NO];
            ext->get_name(name);
            [_nam_val setCharValue:name];
            break;
    }
    
    [self updateUI];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)validDialog:(id)sender{
//_bTrace_("[SelectorWindowController validDialog]",true);
bXMapSelector* ext=(bXMapSelector*)_ext;
    
    ext->set_selwhat([_ras_mtx selectedRow]+1);
    ext->set_add2cnt([_tcn_chk intValue]);
    if([_tms_chk intValue]){
        ext->set_add2hdn([_tot_mtx selectedRow]+1);
    }
    else{
        ext->set_add2hdn(0);
    }
    ext->set_use_mask([_msk_chk intValue]);

    
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
UInt32              sign=0;
    if([_mcr_pop indexOfSelectedItem]>1){
        sign=gapp->macroMgr()->ext_signature([_mcr_pop indexOfSelectedItem]-1);
    }
    ext->set_next(sign);
    
    if(ext->get_geog()){
        ext->get_geog()->end_edit();
    }

char    name[256];
    switch(ext->get_action()){
        case kXMapSelectorSelect:
            break;
        case kXMapSelectorCreateMacro:
        case kXMapSelectorEditMacro:
            NSTextFieldGetValue(_nam_val,name,sizeof(name)-1);
            ext->set_name(name);
            break;
    }

    [super validDialog:sender];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseType:(id)sender{
//_bTrace_("[SelectorWindowController doChooseType]",true);
bXMapSelector* ext=(bXMapSelector*)_ext;
	ext->set_type(((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typ_pop indexOfSelectedItem]+1));
	[_fld_tbl deselectAll:nil];
	[_fld_tbl reloadData];

	[self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseFieldOrCalc:(id)sender{
//_bTrace_("[SelectorWindowController doChooseFieldOrKind]",true);
    [_fld_tbl deselectAll:nil];
    [_fld_tbl reloadData];
    
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRemove:(id)sender{
//_bTrace_("[SelectorWindowController doRemove]",true);
long    idx=[_crt_tbl selectedRow];
    if(idx<0){
        return;
    }
bXMapSelector*          ext=(bXMapSelector*)_ext;
bXMapSelectorCriterion* crit;
    if(ext->criterions().get(idx+1,&crit)){
        ext->criterions().rmv(idx+1);
        delete crit;
        [_crt_tbl reloadData];
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doAdd:(id)sender{
//_bTrace_("[SelectorWindowController doAdd]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapSelector*      ext=(bXMapSelector*)_ext;
long                idx=[_fld_tbl selectedRow];
    if(idx<0){
        return;
    }
    
char	fieldname[256];
char	intfname[256];
int		kind;
int		sign;
    
    if([_foc_pop indexOfSelectedItem]==kXMapSelectorDTSourceField){
        ext->get_type()->fields()->get_name(idx+kOBJ_Name_,fieldname);
        ext->get_type()->fields()->get_kind(idx+kOBJ_Name_,&kind);
        sign=kDBFieldElement;
        sprintf(intfname,"%s",fieldname);
    }
    else{
bGenericCalc*   clc=(bGenericCalc*)(void*)gapp->calcMgr()->get(idx+1);
char			sgn[10];
        clc->get_params(fieldname,sgn);
        if(strlen(sgn)>0){
            sign=*((int*)sgn);
        }
        else{
            sign=0;
        }
        kind=clc->kind();
        gapp->calcMgr()->ext_name(idx,intfname);
    }
    
int		opi=[_ope_pop indexOfSelectedItem];
char	cop[256];

    NSPopupButtonGetMenuItemValue(_ope_pop,opi+1,cop,sizeof(cop)-1);
    
long    cmd=NSPopupButtonMenuItemGetTag(_ope_pop,opi);
char	val[1024];

    NSTextFieldGetValue(_val_val,val,sizeof(val)-1);
    if([_oqs_chk intValue]>0){
        kind='_??_';
    }
    
int cntop;
    switch([_a_o_mtx selectedRow]){
        case 0:
            cntop=kAndElement;
            break;
        case 1:
            cntop=kOrElement;
            break;
        case 2:
            cntop=kXOrElement;
            break;
        default:
            cntop=kAndElement;
            break;
    }

bool                    status;
bXMapSelectorCriterion* crit=new bXMapSelectorCriterion(gapp,
                                                        sign,
                                                        fieldname,
                                                        kind,
                                                        cmd,
                                                        val,
                                                        &status,
                                                        cntop);
    if(!ext->criterions().add(&crit)){
        NSBeep();
    }
    
    [_crt_tbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doConstraints:(id)sender{
//_bTrace_("[SelectorWindowController doConstraints]",true);
bXMapSelector*  ext=(bXMapSelector*)_ext;
int             field=[_fld_tbl selectedRow]+kOBJ_Name_;
int             idx=[_cnt_pop indexOfSelectedItem]+1;
    
    if(idx){
char	str[1024];
int		ck=ext->get_type()->fields()->get_constraints_kind(field);
int		d,fk;
        ext->get_type()->fields()->get_decs(field,&d);
        ext->get_type()->fields()->get_kind(field,&fk);
        if(fk!=ck){
            sprintf(str,"%d",idx);
        }
        else{
char	buffer[1024];
            ext->get_type()->fields()->get_constraint(field,idx,buffer);
            xToChar(ck,d,buffer,str);
        }
        NSTextFieldSetValue(_val_val,str);
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doCheckMask:(id)sender{
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doGeog:(id)sender{
//_bTrace_("[SelectorWindowController doGeog]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapSelector*      ext=(bXMapSelector*)_ext;
bGenericGeog*       g=(bGenericGeog*)(void*)gapp->geogMgr()->get([_geo_pop indexOfSelectedItem]-1);
    if(!g){
        return;
    }
    if(ext->get_geog()){
        ext->get_geog()->end_edit();
    }
    ext->set_geog(g);
    g->edit(_geo_viw);
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
//_bTrace_("[SelectorWindowController updateUI]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapSelector*      ext=(bXMapSelector*)_ext;
    
    [_add_btn setEnabled:([_fld_tbl selectedRow]>-1)];
    [_rmv_btn setEnabled:([_crt_tbl selectedRow]>-1)];
    [_tot_mtx setEnabled:[_tms_chk intValue]];
    [_cnt_pop setEnabled:(ext->get_type()->fields()->count_constraints([_fld_tbl selectedRow]+kOBJ_Name_)>0)];
    
char    name[256];
char    bckname[256];
    switch(ext->get_action()){
        case kXMapSelectorSelect:
            break;
        case kXMapSelectorCreateMacro:
            NSTextFieldGetValue(_nam_val,name,sizeof(name)-1);
            if(strlen(name)<=0){
                [_okbtn setEnabled:NO];
            }
            else if(gapp->macroMgr()->ext_index(name)>0){
                [_okbtn setEnabled:NO];
            }
            else{
                [_okbtn setEnabled:YES];
            }
            break;
        case kXMapSelectorEditMacro:
            NSTextFieldGetValue(_nam_val,name,sizeof(name)-1);
            ext->get_name(bckname);
            if(strlen(name)<=0){
                [_okbtn setEnabled:NO];
            }
            else if(    (gapp->macroMgr()->ext_index(name)>0)   &&
                        (   gapp->macroMgr()->ext_index(name)  !=
                            gapp->macroMgr()->ext_index(bckname))){
                [_okbtn setEnabled:NO];
            }
            else{
                [_okbtn setEnabled:YES];
            }
            break;
    }
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
//_bTrace_("[SelectorWindowController numberOfRowsInTableView]",true);
bXMapSelector* ext=(bXMapSelector*)_ext;
	if(_code!=-1){
		return 0;
	}
	if(ext->get_type()==NULL){
		return 0;
	}

    if(aTableView==_fld_tbl){
        if([_foc_pop indexOfSelectedItem]==0){
            return(ext->get_type()->fields()->count()-kOBJ_Vertices_);
        }
        else{
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
            return(gapp->calcMgr()->count());
        }
    }
    else{
bXMapSelector*  ext=(bXMapSelector*)_ext;
        return ext->criterions().count();
    }
    return(0);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{	
//_bTrace_("[SelectorWindowController tableView:objectValueForTableColumn:row]",true);
bXMapSelector* ext=(bXMapSelector*)_ext;
    if(_code!=-1){
		return nil;
	}
	if(ext->get_type()==NULL){
		return nil;
	}
	
NSString*	nsstr;
char		str[256];

    if(aTableView==_fld_tbl){
        if([_foc_pop indexOfSelectedItem]==0){
            ext->get_type()->fields()->get_name(rowIndex+kOBJ_Name_,str);
        }
        else{
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
            gapp->calcMgr()->ext_name(rowIndex+1,str);
        }
        nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
    }
    else{
bXMapSelector*          ext=(bXMapSelector*)_ext;
bXMapSelectorCriterion* crit;
        ext->criterions().get(rowIndex+1,&crit);
        nsstr=(NSString*)crit->get_string(ext->getbundle(),(ext->criterions().count()==(rowIndex+1)));
// Pas de release, sinon crash
    }

	return nsstr;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
bXMapSelector* ext=(bXMapSelector*)_ext;
	if(_code!=-1){
		return;
	}
	if(ext->get_type()==NULL){
		return;
	}
    if([notification object]==_fld_tbl){
        NSPopupButtonRemoveAllItems(_cnt_pop);
        if(ext->get_type()->fields()->count_constraints([_fld_tbl selectedRow]+kOBJ_Name_)>0){
            NSPopupButtonPopulateWithConstraints(_cnt_pop,ext->get_type(),[_fld_tbl selectedRow]+kOBJ_Name_,1);
        }
        else{            
        }
    }
    else{
        
    }
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)controlTextDidChange:(NSNotification*)notification{
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapSelector* ext,
					  long* code){
SelectorWindowController	*controller;
NSAutoreleasePool			*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[SelectorWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
