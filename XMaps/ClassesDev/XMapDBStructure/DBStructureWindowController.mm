//----------------------------------------------------------------------------
// File : DBStructureWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap database structure window controller
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
// 02/09/2015 creation.
//----------------------------------------------------------------------------

#import "DBStructureWindowController.h"
#import "bXMapDBStructure.h" 
#import "CocoaStuff.h" 
#import <MacMapSuite/bTrace.h> 
#import <mox_intf/bGenericMacMapApp.h> 
#import <mox_intf/Carb_Utils.h> 
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h> 
#import <mox_intf/NSUIUtils.h> 
#import <mox_intf/mm_messages.h>
#import <mox_intf/mm_errors.h>
#import <mox_intf/bStdAlert.h>
#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------

NSString* MMLocalizedString(const char* msg_id, int maj){
char    msg[__MESSAGE_STRING_LENGTH_MAX__];
    message_string(msg_id,msg,maj);
    return [NSString stringWithCString:msg encoding:NSMacOSRomanStringEncoding];
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation DBStructureWindowController

#if !_MCAsSubClasser_
// ---------------------------------------------------------------------------
//  
// ------------
-(id)initWithExt:(bXMapDBStructure*)ext{
_bTrace_("[DBStructureWindowController initWithExt]",true);
	self=[self initWithWindowNibName:@"Palette"];
	if(self){
		_ext=ext;
		_code=-1;
//_tm_("self ok");
	}
	else{
//_te_("pas de self");
	}
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[DBStructureWindowController dealloc]",true);
//_tm_((void*)self);
//long version;
//	Gestalt(gestaltSystemVersion,&version);
//	if(version<0x01070){ // Pb plantage en sortie sous 10.6
//		if([self window]!=nil){
//			[[self window] dealloc];
//			[self setWindow:nil];
//		}
//	}
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)windowDidLoad {
//_bTrace_("[DBStructureWindowController windowDidLoad]",true);
	[super windowDidLoad];
}
#endif

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[DBStructureWindowController awakeFromNib]",true);

	NSPopupButtonRemoveAllItems(_typepopup);
	NSPopupButtonPopulateWithTypes(_typepopup,(bGenericMacMapApp*)_ext->getapp(),kBaseNoKind,1);

	_tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get(1);
//	_findex=0;
	
	[_fldtblvw reloadData];

//	NSPopupButtonRemoveAllItems(_fieldfrompopup);	
//	NSPopupButtonPopulateWithFields(_fieldfrompopup,((bGenericType*)_tp),kOBJ_Dir_+1,1);	

	[[_genderpopup menu] setAutoenablesItems:NO];

	[self updateUI];
}

#if !_MCAsSubClasser_
// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[DBStructureWindowController close]",true);
//_tm_((void*)self);
	_tp=NULL;
//	_findex=0;
	[super close];
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(void)runAppModal:(long*)code{
_bTrace_("[DBStructureWindowController runAppModal]",true);
	[[self window] makeKeyAndOrderFront:nil];
	[[self window] makeFirstResponder:nil];
    [NSApp runModalForWindow:[self window]];
	[[self window] setViewsNeedDisplay:NO];
	[[self window] orderOut:self];
	*code=_code;
}
#endif

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseType:(id)sender{
//_bTrace_("[DBStructureWindowController doChooseType]",true);
	_tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typepopup indexOfSelectedItem]+1);
	[_fldtblvw deselectAll:nil];
	[_fldtblvw reloadData];

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseGender:(id)sender{
//_bTrace_("[DBStructureWindowController doChooseGender]",true);
    switch([_genderpopup indexOfSelectedItem]){
        case 0:
            [_namefld setEnabled:YES];
            [_lengfld setEnabled:YES];
            [_lenmfld setEnabled:YES];
            [_valufld setEnabled:YES];
            [_vanmfld setEnabled:YES];
            [_maskbtn setEnabled:YES];
            [_delpbtn setEnabled:YES];
            [_edtpbtn setEnabled:YES];
            [_lenmfld setStringValue:MMLocalizedString(kMsgLength,1)];
            break;
        case 1:
        case 4:
        case 5:
            [_namefld setEnabled:YES];
            [_lengfld setEnabled:NO];
            [_lenmfld setEnabled:NO];
            [_valufld setEnabled:NO];
            [_vanmfld setEnabled:NO];
            [_maskbtn setEnabled:YES];
            [_delpbtn setEnabled:YES];
            [_edtpbtn setEnabled:YES];
            [_lenmfld setStringValue:MMLocalizedString(kMsgLength,1)];
            break;
        case 2:
            [_namefld setEnabled:YES];
            [_lengfld setEnabled:NO];
            [_lenmfld setEnabled:NO];
            [_valufld setEnabled:YES];
            [_vanmfld setEnabled:YES];
            [_maskbtn setEnabled:YES];
            [_delpbtn setEnabled:YES];
            [_edtpbtn setEnabled:YES];
            [_lenmfld setStringValue:MMLocalizedString(kMsgLength,1)];
            break;
        case 3:
            [_namefld setEnabled:YES];
            [_lengfld setEnabled:YES];
            [_lenmfld setEnabled:YES];
            [_valufld setEnabled:YES];
            [_vanmfld setEnabled:YES];
            [_maskbtn setEnabled:YES];
            [_delpbtn setEnabled:YES];
            [_edtpbtn setEnabled:YES];
            [_lenmfld setStringValue:MMLocalizedString(kMsgDecimals,1)];
            break;
        default:
            [_namefld setEnabled:NO];
            [_lengfld setEnabled:NO];
            [_lenmfld setEnabled:NO];
            [_valufld setEnabled:NO];
            [_vanmfld setEnabled:NO];
            [_maskbtn setEnabled:NO];
            [_delpbtn setEnabled:NO];
            [_edtpbtn setEnabled:NO];
            [_lenmfld setStringValue:MMLocalizedString(kMsgLength,1)];
             break;
    }
    [self checkModify];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRemove:(id)sender{
_bTrace_("[DBStructureWindowController doRemove]",true);
bXMapDBStructure*	ext=(bXMapDBStructure*)(void*)_ext;
int                 status;
    for(long i=0;i<[_fldtblvw numberOfRows];i++){
        if([_fldtblvw isRowSelected:i]==YES){
            if((status=ext->remove(_tp,i+kOBJ_Dir_+1))){
char			msg[__MESSAGE_STRING_LENGTH_MAX__];
                error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop      alrt(msg,"");
                break;
            }
        }
    }
    [_fldtblvw reloadData];
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doAdd:(id)sender{
_bTrace_("[DBStructureWindowController doAdd]",true);
bXMapDBStructure*	ext=(bXMapDBStructure*)(void*)_ext;
int                 status,len,decs,kind,fld;
char                name[256],buff[256];
char                msg[__MESSAGE_STRING_LENGTH_MAX__];
char                exp[__MESSAGE_STRING_LENGTH_MAX__];
    
    switch([_genderpopup indexOfSelectedItem]){
        case 0:
            kind=_char;
            len=[_lengfld intValue];
            decs=0;
            break;
        case 1:
            kind=_bool;
            len=1;
            decs=0;
            break;
        case 2:
            kind=_int;
            len=_kIntLen;
            decs=0;
            break;
        case 3:
            kind=_double;
            len=_kDoubleLen;
            decs=[_lengfld intValue];
            break;
        case 4:
            kind=_date;
            len=_kDateTimeLen;
            decs=0;
            break;
        case 5:
            kind=_time;
            len=_kDateTimeLen;
            decs=0;
            break;
    }
    if([[_namefld stringValue] getCString:name maxLength:255 encoding:NSMacOSRomanStringEncoding]==NO){
        return;
    }
    if(strlen(name)==0){
        return;
    }

    if((status=ext->add(_tp,kind,len,decs,name))){
        error_string(error_num(_bDataBaseErr_,status),msg);
        sprintf(exp,"\"%s\"",name);
bAlertStop	alrt(msg,exp);
        return;
    }
    
    [_fldtblvw reloadData];
    [self updateUI];
    
// New field index
    fld=_tp->fields()->get_index(name);
    [_fldtblvw selectRowIndexes:[NSIndexSet indexSetWithIndex:fld-kOBJ_Dir_-1] byExtendingSelection:NO];

// Masked flag
    if((status=ext->set_masked(_tp,fld,[_maskbtn intValue]))){
        error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        return;
    }
// Delete protected flag
    if((status=ext->set_delete_protected(_tp,fld,[_delpbtn intValue]))){
        error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        return;
    }
// Write protected flag
    if((status=ext->set_write_protected(_tp,fld,[_edtpbtn intValue]))){
        error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        return;
    }
    

// Default value
    if([[_valufld stringValue] getCString:name maxLength:255 encoding:NSMacOSRomanStringEncoding]==NO){
        return;
    }
    if(strlen(name)==0){
        return;
    }
    if(!charToX(kind,decs,name,buff)){
        error_string(error_num(_bDataBaseErr_,_bDataBaseSetDefaultValueErr_),msg);
        b_message_string("unsupported def val err exp",exp,ext->getbundle(),1);
bAlertStop	alrt(msg,"");
        return;
    }
bool    init=false;
    if((strlen(name)>0)&&(_tp->nb_live()>0)){
        b_message_string("init existing",msg,ext->getbundle(),1);
        b_message_string("init existing exp",exp,ext->getbundle(),1);
bAlertWarningYes	alrt(msg,exp);
        init=alrt.result();
    }
    if((status=ext->set_default_value(_tp,fld,buff,init))){
        error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        return;
    }
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doModify:(id)sender{
_bTrace_("[DBStructureWindowController doModify]",true);
bXMapDBStructure*	ext=(bXMapDBStructure*)(void*)_ext;
int                 status,len,decs,kind,fld;
char                name[256],buff[256];
char                msg[__MESSAGE_STRING_LENGTH_MAX__];
char                exp[__MESSAGE_STRING_LENGTH_MAX__];
    
    fld=[_fldtblvw selectedRow]+kOBJ_Dir_+1;
    
// Field kind & name
   switch([_genderpopup indexOfSelectedItem]){
        case 0:
            kind=_char;
            len=[_lengfld intValue];
            decs=0;
            break;
        case 1:
            kind=_bool;
            len=1;
            decs=0;
            break;
        case 2:
            kind=_int;
            len=_kIntLen;
            decs=0;
            break;
        case 3:
            kind=_double;
            len=_kDoubleLen;
            decs=[_lengfld intValue];
            break;
        case 4:
            kind=_date;
            len=_kDateTimeLen;
            decs=0;
            break;
        case 5:
            kind=_time;
            len=_kDateTimeLen;
            decs=0;
            break;
    }
    if([[_namefld stringValue] getCString:name maxLength:255 encoding:NSMacOSRomanStringEncoding]==NO){
        return;
    }
    if(strlen(name)==0){
        return;
    }

int	ok,ol,od;
    _tp->fields()->get_kind(fld,&ok);
    _tp->fields()->get_len(fld,&ol);
    _tp->fields()->get_decs(fld,&od);
    if((kind!=ok)	||
       (decs!=od)	||
       (len!=ol)	){
        if(!_tp->fields()->is_dyn(fld)){
_tm_(kind+":"+ok+" ; "+decs+":"+od+" ; "+len+":"+ol);
            b_message_string("lossy conversion",msg,ext->getbundle(),1);
            b_message_string("lossy conversion exp",exp,ext->getbundle(),1);
bAlertWarningNo	alrt(msg,exp);
            if(alrt.result()){
                return;
            }
        }
    }

    if(!_tp->fields()->is_dyn(fld)&&!_tp->fields()->is_dyn_ref(fld)){
        if((status=ext->modify(_tp,fld,kind,len,decs,name))){
            error_string(error_num(_bDataBaseErr_,status),msg);
            sprintf(exp,"\"%s\"",name);
bAlertStop	alrt(msg,exp);
            return;
        }
    }
    else{
        _tp->fields()->get_name(fld,name);
        [_namefld setCharValue:name];
        
        [self setKind:ok];
        if(ok==_double){
            [_lengfld setIntValue:od];
        }
        else{
            [_lengfld setIntValue:ol];
        }
    }

// Masked flag
    if((status=ext->set_masked(_tp,fld,[_maskbtn intValue]))){
        error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        [_fldtblvw reloadData];
        [self updateUI];
        return;
    }
// Delete protected flag
    if((status=ext->set_delete_protected(_tp,fld,[_delpbtn intValue]))){
        error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        [_fldtblvw reloadData];
        [self updateUI];
        return;
    }
// Write protected flag
    if(!_tp->fields()->is_dyn(fld)){
        if((status=ext->set_write_protected(_tp,fld,[_edtpbtn intValue]))){
            error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
            [_fldtblvw reloadData];
            [self updateUI];
            return;
        }
    }
    else{
        [_edtpbtn setIntValue:1];
    }

    
// Default value
    if([[_valufld stringValue] getCString:name maxLength:255 encoding:NSMacOSRomanStringEncoding]==NO){
        [_fldtblvw reloadData];
        [self updateUI];
        return;
    }
    if(strlen(name)==0){
        if((status=ext->set_default_value(_tp,fld,NULL,false))){
            error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        }
    }
    else{
int		ck=_tp->fields()->get_constraints_kind(fld);
        if(ck==0){
            ck=kind;
        }

        if(kind==ck){// Pour les champs naturels, on prend le type naturel
            if(!charToX(kind,decs,name,buff)){
                error_string(error_num(_bDataBaseErr_,_bDataBaseSetDefaultValueErr_),msg);
                b_message_string("unsupported def val err exp",exp,ext->getbundle(),1);
bAlertStop      alrt(msg,exp);
                [_fldtblvw reloadData];
                [self updateUI];
                return;
            }
        }
        else if(ck==_bit){// Pour les champs bit, on prend le type naturel
            if(!charToX(kind,decs,name,buff)){
                error_string(error_num(_bDataBaseErr_,_bDataBaseSetDefaultValueErr_),msg);
                b_message_string("unsupported def val err exp",exp,ext->getbundle(),1);
bAlertStop      alrt(msg,exp);
                [_fldtblvw reloadData];
                [self updateUI];
                return;
            }
        }
        else{// Pour les champs classe, on prend le nom de la contrainte
            sprintf(buff,"%s",name);
        }
        if((status=ext->set_default_value(_tp,fld,buff,false))){
            error_string(error_num(_bDataBaseErr_,status),msg);
bAlertStop	alrt(msg,"");
        }
    }
    [_fldtblvw reloadData];
    [self updateUI];
}

// ---------------------------------------------------------------------------
//
// -----------
-(IBAction)doUpdate:(id)sender{
    [self checkModify];
}

#if !_MCAsSubClasser_
#pragma mark ---- Gestion Modal ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)validDialog:(id)sender{
	_code=1;
	[NSApp stopModal];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)cancelDialog:(id)sender{
	_code=0;
	[NSApp stopModal];
}
#endif

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
//
// -----------
-(void)setKind:(long)kind{
long    k;
    switch(kind){
        case _char:
            k=0;
            break;
        case _bool:
            k=1;
            break;
        case _int:
            k=2;
            break;
        case _double:
            k=3;
            break;
        case _date:
            k=4;
            break;
        case _time:
            k=5;
            break;
        default:
            k=0;
            break;
    }
    [_genderpopup selectItemAtIndex:k];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
_bTrace_("[DBStructureWindowController updateUI]",true);
    
int     fld=[_fldtblvw selectedRow]+kOBJ_Dir_+1;
    if(fld==kOBJ_Dir_){
        [_namefld setStringValue:@""];
        [_lengfld setStringValue:@""];
        [_valufld setStringValue:@""];
        [_infofld setStringValue:@""];
        [_lenmfld setStringValue:MMLocalizedString(kMsgLength,1)];
        [_maskbtn setIntValue:0];
        [_delpbtn setIntValue:0];
        [_edtpbtn setIntValue:0];
        [_infofld setStringValue:@""];
        [self setKind:_char];
        [self checkDel];
        [self checkAdd];
        [self checkModify];
        return;
    }
    
_tm_(fld);
    
char	name[256];
    _tp->fields()->get_name(fld,name);
    [_namefld setCharValue:name];

int	kind,d,l,ck;
    _tp->fields()->get_kind(fld,&kind);
    _tp->fields()->get_len(fld,&l);
    _tp->fields()->get_decs(fld,&d);
    ck=_tp->fields()->get_constraints_kind(fld);
    if(ck==0){
        ck=kind;
    }
    [self setKind:kind];
    
    switch(kind){
        case _char:
            [_lengfld setIntValue:l];
            break;
        case _bool:
        case _int:
            [_lengfld setStringValue:@""];
            break;
        case _double:
            [_lengfld setIntValue:d];
            break;
        case _date:
        case _time:
            [_lengfld setStringValue:@""];
            break;
        default:
            [_lengfld setStringValue:@""];
            break;
    }
    [self doChooseGender:_genderpopup];
    
char	def[256];
    if(_tp->fields()->get_default_value(fld,def)){
        if(kind==ck){// Pour les champs naturels, on prend le type naturel
            if(!xToChar(kind,d,def,name)){
_te_("xToChar for (kind==ck)");
            }
        }
        else if(ck==_bit){// Pour les champs bit, on prend le type naturel
            if(!xToChar(kind,d,def,name)){
_te_("xToChar for (kind==ck)");
            }
        }
        else{// Pour les champs classe, on prend le nom de la contrainte
            sprintf(name,"%s",def);
        }
    }
    else{
        name[0]=0;
    }
    [_valufld setStringValue:[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding]];
    
//    -(IBAction)doChooseGender:(id)sender{

    [_maskbtn setIntValue:_tp->fields()->is_hidden(fld)];
    [_delpbtn setIntValue:_tp->fields()->is_delprotected(fld)];
    [_edtpbtn setIntValue:_tp->fields()->is_writeprotected(fld)];
    
    [_infofld setStringValue:[NSString stringWithFormat:@"id=%d, idx=%d",_tp->fields()->get_id(fld),fld]];
     
	[self checkDel];
	[self checkAdd];
	[self checkModify];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Supprimer
// -----------
-(void)checkDel{
_bTrace_("[DBStructureWindowController checkDel]",true);
BOOL    flg=[_fldtblvw numberOfSelectedRows]>0;
    
    for(long i=0;i<[_fldtblvw numberOfRows];i++){
        if([_fldtblvw isRowSelected:i]==YES){
            if(_tp->fields()->is_dyn_ref(i+kOBJ_Dir_+1)){
                flg=NO;
                _tm_(i+": NO");
                break;
            }
        }
    }
    [_rmvbtn setEnabled:flg];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Ajouter
// -----------
-(void)checkAdd{
_bTrace_("[DBStructureWindowController checkAdd]",true);
BOOL    flg=NO;
char	val[256];

    for(;;){
        if([[_namefld stringValue] getCString:val maxLength:255 encoding:NSMacOSRomanStringEncoding]==NO){
            break;
        }
        if(strlen(val)==0){
            break;
        }
        if(_tp->fields()->get_index(val)>0){
            break;
        }
int		n=[_lengfld intValue];
        switch([_genderpopup indexOfSelectedItem]){
            case 0:
                flg=((n>0)&&(n<256));
                break;
            case 1:
            case 2:
                flg=true;
                break;
            case 3:
                //b=((n<30)&&(strlen(val)>=0));
                flg=(n<30);
                break;
            case 4:
            case 5:
                flg=YES;
                break;
        }
        break;
    }
	[_addbtn setEnabled:flg];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Modifier
// -----------
-(void)checkModify{
_bTrace_("[DBStructureWindowController checkModify]",true);
BOOL	flg=NO;
bool	bad=false;
int		idx,ibf,ck,curc;
char	val[256],buffer[1024],buffer2[1024];
    
    for(;;){
        if([_fldtblvw numberOfSelectedRows]!=1){
            break;
        }
        
        if([_fldtblvw selectedRow]+kOBJ_Dir_+1<=kOBJ_Dir_){
            break;
        }
        
        if(_tp->fields()->is_dyn_ref([_fldtblvw selectedRow]+kOBJ_Dir_+1)){
            break;
        }
        
        if([[_namefld stringValue] getCString:val maxLength:255 encoding:NSMacOSRomanStringEncoding]==NO){
            break;
        }
        if(strlen(val)==0){
            break;
        }
        idx=_tp->fields()->get_index(val);
        if(idx==0){
            flg=YES;
        }
        
int		n=[_lengfld intValue];
        switch([_genderpopup indexOfSelectedItem]){
            case 0:
                _tp->fields()->get_len(idx,&ibf);
                if((n<=0)||(n>255)){
                    bad=true;
                }
                else if(ibf!=n){
                    flg=YES;
                }
                break;
            case 1:
            case 2:
                flg=NO;
                break;
            case 3:
                _tp->fields()->get_decs(idx,&ibf);
                if((n<0)||(n>29)){
                    bad=true;
                }
                else if(ibf!=n){
                    flg=YES;
                }
                break;
            case 4:
            case 5:
                flg=NO;
                break;
        }
        if(bad){
_tm_("bad");
            break;
        }
        if(flg){
            break;
        }

// modif de la valeur par défaut
       [[_valufld stringValue] getCString:val maxLength:255 encoding:NSUTF8StringEncoding];
        if(strlen(val)>0){
            if(_tp->fields()->has_default_value(idx)){
                if(_tp->fields()->count_constraints(idx)>0){
                    ck=_tp->fields()->get_constraints_kind(idx);
                    if(ck==_bit){
                        ck=_char;
                    }
                    charToX(ck,0,val,(void*)buffer);
                    curc=_tp->fields()->get_constraint_index(idx,(void*)buffer);
                    if(curc>0){
                        _tp->fields()->get_default_value(idx,buffer);
                        flg=(curc!=_tp->fields()->get_constraint_index(idx,(void*)buffer));
                    }
                    else{
                        bad=true;
                        flg=NO;
                    }
                }
                else{
                    _tp->fields()->get_default_value(idx,buffer2);
                    _tp->fields()->get_kind(idx,&ck);
                    _tp->fields()->get_size(idx,&ibf);
                    charToX(ck,0,val,(void*)buffer);
                    if(ck==_char){
                        flg=(strcmp(buffer,buffer2)!=0);
                    }
                    else{
                        flg=(memcmp(buffer,buffer2,ibf)!=0);
                    }
                }
            }
            else{
                flg=YES;
            }
        }
        else{
            if(	(_tp->fields()->count_constraints(idx)>0)		&&
                (_tp->fields()->get_constraints_kind(idx)!=_bit)){
                flg=NO;
                bad=true;
            }
            else{
                flg=_tp->fields()->has_default_value(idx);
            }
        }
        if(bad){
            break;
        }
        if(flg){
            break;
        }
            
// modif du genre
_tm_("modif du genre");

        _tp->fields()->get_kind(idx,&ibf);
        switch([_genderpopup indexOfSelectedItem]){
            case 0:
                flg=(ibf!=_char);
                if(flg){
                    _tp->fields()->get_len(idx,&ibf);
                    flg=((n>0)&&(n<256));
                }
                _tm_("_char "+flg+"/"+n);
                break;
            case 1:
                flg=(ibf!=_bool);
                _tm_("_bool "+flg);
                break;
            case 2:
                flg=(ibf!=_int);
                _tm_("_int "+flg);
                break;
            case 3:
                flg=(ibf!=_double);
                if(flg){
                    _tp->fields()->get_decs(idx,&ibf);
                    flg=((n<30)&&(n>=0));
                }
                _tm_("_double "+flg+"/"+n);
                break;
            case 4:
                flg=(ibf!=_date);
                _tm_("_date "+flg);
                break;
            case 5:
                flg=(ibf!=_time);
                _tm_("_time "+flg);
                break;
        }

// modif des flags
        if([_maskbtn intValue]!=_tp->fields()->is_hidden(idx)){
            flg=true;
        }
        if([_delpbtn intValue]!=_tp->fields()->is_delprotected(idx)){
            flg=true;
        }
        if([_edtpbtn intValue]!=_tp->fields()->is_writeprotected(idx)){
            flg=true;
        }
        break;
    }
    
	[_modibtn setEnabled:flg];
}

// ---------------------------------------------------------------------------
// Disponibilité et valeur du popup Genre
// -----------
//-(void)checkKind{
//_bTrace_("[DBStructureWindowController checkKind]",true);
//bool		b=false;
//int			idx=1,ck,fk;
//	
//	for(;;){
//		if(_findex==0){
//			break;
//		}
//		if(((bGenericType*)_tp)->fields()->version()<_kVersion310){
//			break;
//		}
//		((bGenericType*)_tp)->fields()->get_kind(_findex,&fk);
//		ck=((bGenericType*)_tp)->fields()->get_constraints_kind(_findex);
//		if(((bGenericType*)_tp)->fields()->count_constraints(_findex)!=0){
//			if(ck==_bit){
//				fk=_UBbit;
//				idx=3;
//			}
//			else if(ck!=fk){
//				idx=2;
//			}
//			else{
//				fk=_UBbit;
//				idx=1;
//			}
//			break;
//		}
//		b=true;
//		switch(fk){
//			case _int:
//			case _char:
//				NSPopupButtonMenuItemEnable(_genderpopup,0);
//				NSPopupButtonMenuItemEnable(_genderpopup,1);
//				NSPopupButtonMenuItemEnable(_genderpopup,2);
//				b=true;
//				break;
//			case _double:
//				NSPopupButtonMenuItemEnable(_genderpopup,0);
//				NSPopupButtonMenuItemEnable(_genderpopup,1);
//				NSPopupButtonMenuItemDisable(_genderpopup,2);
//				b=true;
//				break;
//			case _date:
//			case _time:
//				NSPopupButtonMenuItemEnable(_genderpopup,0);
//				NSPopupButtonMenuItemDisable(_genderpopup,1);
//				NSPopupButtonMenuItemDisable(_genderpopup,2);
//				b=true;
//				break;
//			default:
//				NSPopupButtonMenuItemDisable(_genderpopup,0);
//				NSPopupButtonMenuItemDisable(_genderpopup,1);
//				NSPopupButtonMenuItemDisable(_genderpopup,2);
//				break;
//		}
//		break;
//	}
//	[_genderpopup setEnabled:b];
//	if((idx-1)>=0){
//		[_genderpopup selectItemAtIndex:(idx-1)];
//	}
//}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
	if(_code!=-1){
		return 0;
	}
	if(_tp==NULL){
		return 0;
	}
    return(((bGenericType*)_tp)->fields()->count()-kOBJ_Dir_);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{	
//_bTrace_("[DBStructureWindowController tableView objectValueForTableColumn]",false);
	if(_code!=-1){
//		_tw_("(_code!=-1)");
		return nil;
	}
	if(_tp==NULL){
//		_tw_("(_tp==NULL)");
		return nil;
	}
	
NSString*	nsstr;
char		str[256];

    ((bGenericType*)_tp)->fields()->get_name(rowIndex+kOBJ_Dir_+1,str);
    nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
	return nsstr;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
//_bTrace_("[DBStructureWindowController tableViewSelectionDidChange]",true);

	if(_code!=-1){
		return;
	}
	if(_tp==NULL){
		return;
	}
    
//    _findex=[_fldtblvw selectedRow]+kOBJ_Dir_+1;
//    [_addbtn setEnabled:NO];
//    [_rmvbtn setEnabled:NO];
//    [_modibtn setEnabled:NO];
    
    
//    NSTextFieldSetValue(_namefld,"");
    
    [self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(BOOL)	tableView:(NSTableView *)tableView 
		shouldEditTableColumn:(NSTableColumn *)tableColumn 
		row:(NSInteger)row{
	return NO;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(BOOL)	tableView:(NSTableView *)tableView 
		shouldSelectTableColumn:(NSTableColumn *)tableColumn{
	return NO;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)controlTextDidChange:(NSNotification*)notification{
_bTrace_("[DBStructureWindowController controlTextDidChange]",true);
	[self checkAdd];
	[self checkModify];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
#if _MCAsSubClasser_
void runCocoaAppModal(bGenericExt* ext,
					  long* code){
#else
void runCocoaAppModal(bXMapDBStructure* ext,
					  long* code){
#endif
DBStructureWindowController	*controller;
NSAutoreleasePool				*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[DBStructureWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
