//----------------------------------------------------------------------------
// File : MakeConstraintsWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap make constraints window controller
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
// 19/06/2008 creation.
//----------------------------------------------------------------------------

#import "MakeConstraintsWindowController.h"
#import "bXMapMakeConstraints.h" 
#import "CocoaStuff.h" 
#import <MacMapSuite/bTrace.h> 
#import <mox_intf/bGenericMacMapApp.h> 
#import <mox_intf/Carb_Utils.h> 
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h> 
#import <mox_intf/NSUIUtils.h> 
#import <std_ext/bXMapStdIntf.h> 

// ---------------------------------------------------------------------------

#ifdef __LITTLE_ENDIAN__
#define	_UBbit	'TIB_'
#else
#define	_UBbit	_bit
#endif

// ---------------------------------------------------------------------------
// 
// ------------
@implementation MakeConstraintsWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[MakeConstraintsWindowController dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)awakeFromNib{
_bTrace_("[MakeConstraintsWindowController awakeFromNib]",true);
MakeConstraints_prm *prm=(MakeConstraints_prm*)((bXMapMakeConstraints*)_ext)->get_prm();
        
    _tp=prm->tp;
    _findex=prm->field;
	
    NSPopupButtonRemoveAllItems(_typepopup);
    NSPopupButtonPopulateWithTypes(_typepopup,(bGenericMacMapApp*)_ext->getapp(),kBaseNoKind,_tp->index());

    if(_findex<=kOBJ_Dir_){
        _findex=0;
    }
    if(_findex>kOBJ_Dir_){
        [_fldtblvw selectRowIndexes:[NSIndexSet indexSetWithIndex:_findex-kOBJ_Dir_] byExtendingSelection:NO];
    }
    else{
        _findex=0;
    }

    [_fldtblvw reloadData];
	[_cnttblvw reloadData];
    
	NSPopupButtonRemoveAllItems(_fieldfrompopup);	
	NSPopupButtonPopulateWithFields(_fieldfrompopup,((bGenericType*)_tp),kOBJ_Dir_+1,1);

	[[_genderpopup menu] setAutoenablesItems:NO];

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[MakeConstraintsWindowController close]",true);
	_tp=NULL;
	_findex=0;
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseType:(id)sender{
//_bTrace_("[MakeConstraintsWindowController doChooseType]",true);
	_tp=((bGenericMacMapApp*)_ext->getapp())->typesMgr()->get([_typepopup indexOfSelectedItem]+1);
	[_fldtblvw deselectAll:nil];
	[_cnttblvw deselectAll:nil];
	[_fldtblvw reloadData];
	_findex=0;
	[_cnttblvw reloadData];

	NSPopupButtonRemoveAllItems(_fieldfrompopup);	
	NSPopupButtonPopulateWithFields(_fieldfrompopup,((bGenericType*)_tp),kOBJ_Dir_+1,1);	

	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doChooseGender:(id)sender{
//_bTrace_("[MakeConstraintsWindowController doChooseGender]",true);
	[self checkCreate];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRemove:(id)sender{
//_bTrace_("[MakeConstraintsWindowController doRemove]",true);
long					cnst=[_cnttblvw selectedRow]+1;
bXMapMakeConstraints*	ext=(bXMapMakeConstraints*)_ext;

	if(!ext->do_remove(((bGenericType*)_tp),_findex,cnst)){
//_te_("remove_constraint failed for "+(int)cnst);		
		return;
	}
	[_cnttblvw reloadData];
	[self checkKind];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doAdd:(id)sender{
//_bTrace_("[MakeConstraintsWindowController doAdd]",true);
char	val[256],buff[256];
int		k,d,ck;
	
	((bGenericType*)_tp)->fields()->get_kind(_findex,&k);
	switch([_genderpopup indexOfSelectedItem]+1){
		case 1:
			ck=k;
			break;
		case 2:
			ck=_char;
			break;
		case 3:
			ck=_bit;
			break;
	}
	NSTextFieldGetValue(_textfld,val,sizeof(val)-1);
	((bGenericType*)_tp)->fields()->get_decs(_findex,&d);
	if(k==_double){
		strrep(val,",",".");
	}
	if(ck==_bit){
		strcpy(buff,val);
	}
	else{
		if(!charToX(ck,d,val,buff)){
//_te_("charToX failed for "+val+" to "+(UInt32*)&k);
			return;
		}
	}
bXMapMakeConstraints*	ext=(bXMapMakeConstraints*)_ext;
	if(!ext->do_add(((bGenericType*)_tp),_findex,ck,buff)){
//_te_("add_constraint failed");
		return;
	}	
long	cindex=((bGenericType*)_tp)->fields()->count_constraints(_findex);
	[_cnttblvw reloadData];
	[_cnttblvw selectRowIndexes:[NSIndexSet indexSetWithIndex:cindex-1] byExtendingSelection:NO];
    [_cnttblvw scrollRowToVisible:(cindex-1)];
	[self checkKind];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doModify:(id)sender{
//_bTrace_("[MakeConstraintsWindowController doModify]",true);
char	val[256],buff[256];
int		k,d;
	
	NSTextFieldGetValue(_textfld,val,sizeof(val)-1);
	k=((bGenericType*)_tp)->fields()->get_constraints_kind(_findex);
	((bGenericType*)_tp)->fields()->get_decs(_findex,&d);
	if(k==_double){
		strrep(val,",",".");
	}
	if(k==_bit){
		strcpy(buff,val);
	}
	else if(!charToX(k,d,val,buff)){
//_te_("charToX failed for "+val+" to "+(UInt32*)&k);
		return;
	}
	
long					cnst=[_cnttblvw selectedRow]+1;
bXMapMakeConstraints*	ext=(bXMapMakeConstraints*)_ext;
	if(!ext->do_modify(((bGenericType*)_tp),_findex,cnst,buff)){
//_te_("set_constraint failed for "+(int)cnst);		
		return;
	}
	[_cnttblvw reloadData];
	[self checkKind];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doCreateFromField:(id)sender{
//_bTrace_("[MakeConstraintsWindowController doCreateFromField]",true);
long					src=[_fieldfrompopup indexOfSelectedItem]+kOBJ_Dir_;
//_tm_("source index="+(int)src);		
//long					cnst=[_cnttblvw selectedRow]+1;
//_tm_("constraint index="+(int)cnst);		
bXMapMakeConstraints*	ext=(bXMapMakeConstraints*)_ext;
//_tm_("ext="+(void*)ext);		

	if(!ext->do_make_from_field(((bGenericType*)_tp),_findex,src,([_genderpopup indexOfSelectedItem]==0))){
//_te_("set_constraint failed for "+(int)cnst);		
		return;
	}
//_tm_("ext->do_make_from_field passed");
	[_cnttblvw reloadData];
	[self checkKind];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
//_bTrace_("[MakeConstraintsWindowController updateUI]",true);
	[self checkDel];
	[self checkAdd];
	[self checkModify];
	[self checkCreate];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Supprimer
// -----------
-(void)checkDel{
//_bTrace_("[MakeConstraintsWindowController checkDel]",true);
int		k;
	((bGenericType*)_tp)->fields()->get_kind(_findex,&k);
	[_rmvbtn setEnabled:((((bGenericType*)_tp)->nb_live()==0)&&
						 ([_cnttblvw numberOfSelectedRows]>0)&&
						 (k!=_bool)&&
						 (!((bGenericType*)_tp)->fields()->is_dyn(_findex)))];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Ajouter
// -----------
-(void)checkAdd{
//_bTrace_("[MakeConstraintsWindowController checkAdd]",true);
bool	b=false;
	for(;;){
		if(_findex==0){
			break;
		}
		if(((bGenericType*)_tp)->fields()->is_dyn(_findex)){
			break;
		}
		
char	val[256],buff[256];
		NSTextFieldGetValue(_textfld,val,sizeof(val)-1);
		if(strlen(val)==0){
			break;
		}
		
int		fk,ck,d,l;
		((bGenericType*)_tp)->fields()->get_kind(_findex,&fk);
		switch([_genderpopup indexOfSelectedItem]+1){
			case 1:
				ck=fk;
				break;
			case 2:
				ck=_char;
				break;
			case 3:
				ck=_bit;
				break;				
		}
		((bGenericType*)_tp)->fields()->get_decs(_findex,&d);
		((bGenericType*)_tp)->fields()->get_len(_findex,&l);

		switch(ck){
			case _int:
				b=strint(val,true);
				break;
			case _double:
				b=strfloat(val,true);
				break;
			case _char:
			case _bit:
				b=true;
				break;
		}
		if(!b){
			break;
		}
		b=false;
		if(((bGenericType*)_tp)->fields()->count_constraints(_findex)==0){
			b=true;
			break;
		}
		if(ck==_bit){
			if(fk==_char){
				if(((bGenericType*)_tp)->fields()->count_constraints(_findex)>=l){
					break;
				}
			}
			else if(fk==_int){
				if(((bGenericType*)_tp)->fields()->count_constraints(_findex)>=32){
					break;
				}			
			}
			else{
				break;
			}
			strcpy(buff,val);
		}
		else if(!charToX(ck,d,val,buff)){
			break;
		}
		if(((bGenericType*)_tp)->fields()->get_constraint_index(_findex,buff)){
			break;
		}
		b=true;
		break;
	}
	[_addbtn setEnabled:b];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Modifier
// -----------
-(void)checkModify{
//_bTrace_("[MakeConstraintsWindowController checkModify]",true);
bool	b=false;	
	for(;;){
		if(_findex==0){
			break;
		}
		if(((bGenericType*)_tp)->fields()->is_dyn(_findex)){
			break;
		}
		if(((bGenericType*)_tp)->fields()->count_constraints(_findex)==0){
			break;
		}
		if([_cnttblvw selectedRow]<0){
			break;
		}
char	val[256],buff[256];
		NSTextFieldGetValue(_textfld,val,sizeof(val)-1);
		if(strlen(val)==0){
			break;
		}
		
int		k,d;
bool	flg=[_genderpopup selectedItem]==0;

		k=((bGenericType*)_tp)->fields()->get_constraints_kind(_findex);
		if(k==_bit){
			k=_char;
		}
		((bGenericType*)_tp)->fields()->get_decs(_findex,&d);
		switch(k){
			case _int:
				b=strint(val,true);
				break;
			case _double:
				b=strfloat(val,true);
				break;
			case _char:
				b=true;
				break;
		}
		if(!b){
			break;
		}
		b=false;
		if(!charToX(k,d,val,buff)){
			break;
		}
		if(((bGenericType*)_tp)->fields()->get_constraint_index(_findex,buff)){
			break;
		}
		if((flg)&&(((bGenericType*)_tp)->nb_live()!=0)){
			break;
		}
		b=true;
		break;
	}
	[_modibtn setEnabled:b];
}

// ---------------------------------------------------------------------------
// Disponibilité et valeur du popup Genre
// -----------
-(void)checkKind{
_bTrace_("[MakeConstraintsWindowController checkKind]",true);
bool		b=false;
int			idx=1,ck,fk;
	
	for(;;){
		if(_findex==0){
			break;
		}
		if(((bGenericType*)_tp)->fields()->version()<_kVersion310){
			break;
		}
		((bGenericType*)_tp)->fields()->get_kind(_findex,&fk);
		ck=((bGenericType*)_tp)->fields()->get_constraints_kind(_findex);
		if(((bGenericType*)_tp)->fields()->count_constraints(_findex)!=0){
			if(ck==_bit){
				fk=_UBbit;
				idx=3;
			}
			else if(ck!=fk){
				idx=2;
			}
			else{
				fk=_UBbit;
				idx=1;
			}
			break;
		}
		b=true;
		switch(fk){
			case _int:
			case _char:
				NSPopupButtonMenuItemEnable(_genderpopup,0);
				NSPopupButtonMenuItemEnable(_genderpopup,1);
				NSPopupButtonMenuItemEnable(_genderpopup,2);
				b=true;
				break;
			case _double:
				NSPopupButtonMenuItemEnable(_genderpopup,0);
				NSPopupButtonMenuItemEnable(_genderpopup,1);
				NSPopupButtonMenuItemDisable(_genderpopup,2);
				b=true;
				break;
			case _date:
			case _time:
				NSPopupButtonMenuItemEnable(_genderpopup,0);
				NSPopupButtonMenuItemDisable(_genderpopup,1);
				NSPopupButtonMenuItemDisable(_genderpopup,2);
				b=true;
				break;
			default:
				NSPopupButtonMenuItemDisable(_genderpopup,0);
				NSPopupButtonMenuItemDisable(_genderpopup,1);
				NSPopupButtonMenuItemDisable(_genderpopup,2);
				break;
		}
		break;
	}
	[_genderpopup setEnabled:b];
	if((idx-1)>=0){
		[_genderpopup selectItemAtIndex:(idx-1)];
	}
}

// ---------------------------------------------------------------------------
// Disponibilité du popup "A partir du champ"
// -----------
-(void)checkCreate{
_bTrace_("[MakeConstraintsWindowController checkCreate]",true);
	[_fieldfrompopup setEnabled:([_genderpopup indexOfSelectedItem]<2)&&(_findex>0)];
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
//_bTrace_("[MakeConstraintsWindowController numberOfRowsInTableView]",true);
	if(_code!=-1){
//_tw_("_code!=-1");
		return 0;
	}
	if(_tp==NULL){
		return 0;
	}
//_tm_("((bGenericType*)_tp)="+(void*)((bGenericType*)_tp));
//_tm_("_findex="+(int)_findex);

	if(aTableView==_fldtblvw){
//_tm_("_fldtblvw");
		return(1+((bGenericType*)_tp)->fields()->count()-kOBJ_Dir_);
	}
	else{
//_tm_("_cnttblvw");
		if(_findex<=0){
			return(0);
		}
		return(((bGenericType*)_tp)->fields()->count_constraints(_findex));
	}
	return 0;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{	
//_bTrace_("[MakeConstraintsWindowController tableView objectValueForTableColumn]",false);
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

	if(aTableView==_fldtblvw){
//		_tm_("_fldtblvw");
		if(rowIndex==0){
			((bGenericType*)_tp)->fields()->get_name(kOBJ_SubType_,str);
		}
		else{
			((bGenericType*)_tp)->fields()->get_name(rowIndex+kOBJ_Dir_,str);
		}
		nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
	}
	else{
//		_tm_("_cnttblvw");
int		ck,d;
char	val[1024];
		ck=((bGenericType*)_tp)->fields()->get_constraints_kind(_findex);
		((bGenericType*)_tp)->fields()->get_decs(_findex,&d);
		if(!((bGenericType*)_tp)->fields()->get_constraint(_findex,rowIndex+1,val)){
		}
		if(ck==_bit){
			strcpy(str,val);				
		}
		else{
			xToChar(ck,d,val,str);
		}
		nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
	}
	
	return nsstr;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
//_bTrace_("[MakeConstraintsWindowController tableViewSelectionDidChange]",true);

	if(_code!=-1){
		return;
	}
	if(_tp==NULL){
		return;
	}
	if([notification object]==_fldtblvw){
		if([_fldtblvw selectedRow]==0){
			_findex=kOBJ_SubType_;
		}
		else if([_fldtblvw selectedRow]>0){
			_findex=[_fldtblvw selectedRow]+kOBJ_Dir_;
//_tm_((int)_findex);
		}
		else{
			_findex=0;
		}
		[_cnttblvw reloadData];
		[_addbtn setEnabled:NO];
		[_rmvbtn setEnabled:NO];
		[_modibtn setEnabled:NO];
		NSTextFieldSetValue(_textfld,"");
		[self checkKind];
		[self checkCreate];
	}
	else if([notification object]==_cnttblvw){
		if([_cnttblvw selectedRow]>=0){
int		k,d;
			k=((bGenericType*)_tp)->fields()->get_constraints_kind(_findex);
			((bGenericType*)_tp)->fields()->get_decs(_findex,&d);
char	val[256],buff[256];
			val[0]=0;
			if(((bGenericType*)_tp)->fields()->get_constraint(_findex,[_cnttblvw selectedRow]+1,buff)){
				if(k==_bit){
					strcpy(val,buff);
				}
				else if(!xToChar(k,d,buff,val)){
				}
			}
			NSTextFieldSetValue(_textfld,val);
		}
		else{
			NSTextFieldSetValue(_textfld,"");
		}
		[self checkDel];
		[self checkAdd];
		[self checkModify];
		[self checkCreate];
	}
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
//_bTrace_("[MakeConstraintsWindowController controlTextDidChange]",true);
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
void runCocoaAppModal(bXMapMakeConstraints* ext,
					  long* code){
MakeConstraintsWindowController	*controller;
NSAutoreleasePool				*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[MakeConstraintsWindowController alloc] initWithExt:ext];
    [controller runAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}
