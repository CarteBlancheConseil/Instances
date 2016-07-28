//----------------------------------------------------------------------------
// File : DataFillWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap data fill window controller
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
// 15/02/2016 creation.
//----------------------------------------------------------------------------

#import "DataFillWindowController.h"
#import "bXMapDataFill.h"
#import "bXMapDataFillRun.h"
#import "CocoaStuff.h"

#import <mox_intf/NSUIUtils.h>
#import <mox_intf/mm_messages.h>

#import <std_ext/bXMapStdIntf.h>

#import <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
@implementation DataFillWindowController
// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[DataFillWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[DataFillWindowController awakeFromNib]",true);
    [self doChooseKind:nil];
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[DataFillWindowController close]",true);
	[super close];
}

// ---------------------------------------------------------------------------
//
// ------------
-(void)make_text:(char*)text{
bXMapDataFill*  ext=(bXMapDataFill*)_ext;
char            s1[256],s2[256],s3[256],s4[256];
long            field=[_fldtbl selectedRow];

    if(field<0){
        return;
    }
    field+=kOBJ_Name_;
    
    b_message_string(kXMapDataFillMsgFillField,s1,ext->getbundle(),0);
    ext->get_type()->fields()->get_name(field,s2);
    switch([_wthpop indexOfSelectedItem]){
        case 0:
            b_message_string(kXMapDataFillMsgWithValue,s3,ext->getbundle(),0);
            NSTextFieldGetValue(_valcmb,s4,sizeof(s4)-1);
            break;
        case 1:
            b_message_string(kXMapDataFillMsgWithCalc,s3,ext->getbundle(),0);
            NSPopupButtonMenuItemGetTitle(_chspop,[_chspop indexOfSelectedItem]/*+1*/,s4,sizeof(s4)-1);
            break;
        case 2:
            b_message_string(kXMapDataFillMsgWithField,s3,ext->getbundle(),0);
            NSPopupButtonMenuItemGetTitle(_chspop,[_chspop indexOfSelectedItem]/*+1*/,s4,sizeof(s4)-1);
            break;
    }
    sprintf(text,"%s %s %s %s",s1,s2,s3,s4);
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doChooseKind:(id)sender{
//_bTrace_("[DataFillWindowController doChooseKink]",true);
bXMapDataFill*  ext=(bXMapDataFill*)_ext;
    switch([_wthpop indexOfSelectedItem]){
        case 0:
            [_valcmb setHidden:NO];
            [_chspop setHidden:YES];
            NSPopupButtonRemoveAllItems(_chspop);
            break;
            
        case 1:
            [_valcmb setHidden:YES];
            [_chspop setHidden:NO];
            NSPopupButtonRemoveAllItems(_chspop);
            NSPopupButtonPopulateWithCalcs(_chspop,(bGenericMacMapApp*)_ext->getapp(),1);
            break;
            
        case 2:
            [_valcmb setHidden:YES];
            [_chspop setHidden:NO];
            NSPopupButtonRemoveAllItems(_chspop);
            NSPopupButtonPopulateWithFields(_chspop,ext->get_type(),kOBJ_Name_,1);
            break;
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doConstraint:(id)sender{
//_bTrace_("[DataFillWindowController doConstraint]",true);
bXMapDataFill*  ext=(bXMapDataFill*)_ext;
long            field=[_fldtbl selectedRow];
    if(field<0){
        return;
    }
    field+=kOBJ_Name_;

int	idx=[_valcmb indexOfSelectedItem]+1;
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
        NSTextFieldSetValue(_valcmb,str);
    }
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doAdd:(id)sender{
//_bTrace_("[DataFillWindowController doAdd]",true);
bGenericMacMapApp*  gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapDataFill*      ext=(bXMapDataFill*)_ext;
bXMapDataFillRun*	run;
int					k,sz,d;
char				runstr[256];
    
long                field=[_fldtbl selectedRow];
    if(field<0){
//_te_("bad field index");
        return;
    }
    field+=kOBJ_Name_;

    ext->get_type()->fields()->get_kind(field,&k);
    ext->get_type()->fields()->get_size(field,&sz);
    ext->get_type()->fields()->get_decs(field,&d);
    
    [self make_text:runstr];
    
    switch([_wthpop indexOfSelectedItem]){
        case 0:{
char	str[256];
            NSTextFieldGetValue(_valcmb,str,sizeof(str)-1);
            run=new bXMapDataFillRunValue(runstr,
                                          field,sz,k,d,
                                          str);
//_tm_("add value "+str+" to field "+field);
        }break;
        case 1:{
bGenericCalc* clc=(bGenericCalc*)(void*)gapp->calcMgr()->get([_chspop indexOfSelectedItem]+1);
            if(!clc){
                return;
            }
            run=new bXMapDataFillRunCalc(runstr,
                                         field,sz,k,d,
                                         clc);
//_tm_("add calc "+([_chspop indexOfSelectedItem]+1)+" to field "+field);
        }break;
        case 2:{
int		f,fk,fsz,fd;
            f=[_chspop indexOfSelectedItem]+kOBJ_Name_;
            ext->get_type()->fields()->get_kind(f,&fk);
            ext->get_type()->fields()->get_size(f,&fsz);
            ext->get_type()->fields()->get_decs(f,&fd);
            run=new bXMapDataFillRunField(runstr,
                                          field,sz,k,d,
                                          f,fsz,fk,fd);
//_tm_("add field "+f+" to field "+field);
        }break;
        default:
//_te_("bad choice index");
            return;
            break;
    }
    if(!ext->get_runs().add(&run)){
//_te_("add failed");
        delete run;
        return;
    }
    [_runtbl reloadData];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doRemove:(id)sender{
//_bTrace_("[DataFillWindowController doRemove]",true);
bXMapDataFill*      ext=(bXMapDataFill*)_ext;
bXMapDataFillRun*	run;
long                idx=[_fldtbl selectedRow];
    if(idx<0){
        return;
    }
    idx++;
    ext->get_runs().get(idx,&run);
    ext->get_runs().rmv(idx);
    delete run;
    [_runtbl reloadData];
}

#pragma mark ---- Gestion TableView ----
// -------------------------------------------------------------------------;--
//
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bXMapDataFill*  ext=(bXMapDataFill*)_ext;
    if(ext->get_type()==NULL){
        return 0;
    }
    if(aTableView==_fldtbl){
        return(ext->get_type()->fields()->count()-kOBJ_Name_+1);
    }
    else{
        return(ext->get_runs().count());
    }
    return 0;
}

// ---------------------------------------------------------------------------
//
// -----------
-(id)	tableView:(NSTableView*)aTableView
objectValueForTableColumn:(NSTableColumn*)aTableColumn
            row:(NSInteger)rowIndex{
bXMapDataFill*  ext=(bXMapDataFill*)_ext;
NSString*       nsstr;
char            str[256];
    
    if(aTableView==_fldtbl){
        ext->get_type()->fields()->get_name(rowIndex+kOBJ_Name_,str);
        nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
    }
    else{
bXMapDataFillRun*	run=NULL;
        if(ext->get_runs().get(rowIndex+1,&run)){
            strcpy(str,run->get_text());
        }
        else{
            strcpy(str,"????");
        }
        nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
    }
    return nsstr;
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
    [self updateUI];
}

#pragma mark ---- Gestion ComboBox ----
// ---------------------------------------------------------------------------
//
// ------------
-(NSInteger)numberOfItemsInComboBox:(NSComboBox *)aComboBox{
bXMapDataFill*  ext=(bXMapDataFill*)_ext;
long            field=[_fldtbl selectedRow];
    if([_fldtbl selectedRow]<0){
        return 0;
    }
    field+=kOBJ_Name_;
    if(	(ext->get_type()->fields()->count_constraints(field)==0)        ||
        (ext->get_type()->fields()->get_constraints_kind(field)==_bit)) {
        return 0;
    }
    return ext->get_type()->fields()->count_constraints(field);
}

// ---------------------------------------------------------------------------
//
// ------------
-(id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(NSInteger)index{
bXMapDataFill*  ext=(bXMapDataFill*)_ext;
long            field=[_fldtbl selectedRow];
    if([_fldtbl selectedRow]<0){
        return nil;
    }
    field+=kOBJ_Name_;
char	buffer[1024];
char	str[256];
int		k=ext->get_type()->fields()->get_constraints_kind(field);
int		d;
    ext->get_type()->fields()->get_decs(field,&d);
    ext->get_type()->fields()->get_constraint(field,index+1,buffer);
    xToChar(k,d,buffer,str);
    return [NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)updateUI{
//_bTrace_("[MakeConstraintsWindowController updateUI]",true);
    [_addbtn setEnabled:([_fldtbl selectedRow]>=0)];
    [_rmvbtn setEnabled:([_runtbl selectedRow]>=0)];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void runCocoaAppModal(bXMapDataFill* ext,
					  long* code){
DataFillWindowController	*controller;
NSAutoreleasePool               *localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[DataFillWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
