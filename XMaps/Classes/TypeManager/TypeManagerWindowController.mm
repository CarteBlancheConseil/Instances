//----------------------------------------------------------------------------
// File : TypeManagerWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap type manager window controller
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
// 16/06/2011
//----------------------------------------------------------------------------

#import "TypeManagerWindowController.h"
#import "bXMapTypeManager.h" 
#import "CocoaStuff.h" 
#import <MacMapSuite/bTrace.h> 
#import <MacMapSuite/bStdProj.h> 
#import <MacMapSuite/valconv.h> 
#import <mox_intf/bGenericMacMapApp.h> 
#import <mox_intf/Carb_Utils.h> 
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h> 
#import <mox_intf/NSUIUtils.h> 
#import <mox_intf/mm_messages.h> 
#import <mox_intf/bStdAlert.h> 
#import <std_ext/bXMapStdIntf.h> 
#import <sys/syslimits.h>

// ---------------------------------------------------------------------------
// 
// ------------
static void getUnitShortLib(bGenericMacMapApp* gapp, double coef, char *lib){
bGenericUnitMgr*	mgr=gapp->distMgr();
bGenericUnit*		lu;
	
	for(int i=1;i<=mgr->count();i++){
		lu=mgr->get(i);
		if(lu->coef()==coef){
			lu->short_name(lib);
			return;
		}
	} 
}

// ---------------------------------------------------------------------------
// 
// ------------
@implementation TypeManagerWindowController

// ---------------------------------------------------------------------------
//  
// ------------
-(id)initWithExt:(bXMapTypeManager*)ext{
//_bTrace_("[MakeConstraintsWindowController initWithExt]",true);
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
-(void)awakeFromNib{	
	[self updateUI];
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(void)runTypeManagerCocoaAppModal:(long*)code{
_bTrace_("[MakeConstraintsWindowController runTypeManagerCocoaAppModal]",true);
	[[self window] makeKeyAndOrderFront:nil];
	[[self window] makeFirstResponder:nil];
    [NSApp runModalForWindow:[self window]];
	[[self window] setViewsNeedDisplay:NO];
	[[self window] orderOut:self];
	*code=_code;
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doNew:(id)sender{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapTypeManager*	ext=(bXMapTypeManager*)_ext;
	if(!ext->new_action()){
	}
	[_typetbl reloadData];
	[_typetbl selectRowIndexes:[NSIndexSet indexSetWithIndex:(gapp->typesMgr()->count()-1)]
          byExtendingSelection:NO];
    [_typetbl scrollRowToVisible:(gapp->typesMgr()->count()-1)];
	[self checkRemove];
	[self checkRename];
	[self checkProtect];
	[self checkUnprotect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doOpen:(id)sender{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bXMapTypeManager*	ext=(bXMapTypeManager*)(void*)_ext;
	if(!ext->add_action()){
	}
    [_typetbl reloadData];
    [_typetbl selectRowIndexes:[NSIndexSet indexSetWithIndex:(gapp->typesMgr()->count()-1)]
          byExtendingSelection:NO];
    [_typetbl scrollRowToVisible:(gapp->typesMgr()->count()-1)];
	[self checkRemove];
	[self checkRename];
	[self checkProtect];
	[self checkUnprotect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRemove:(id)sender{
long				index=[_typetbl selectedRow]+1;
bXMapTypeManager*	ext=(bXMapTypeManager*)_ext;
	if(!ext->rmv_action(index)){
	}
	[self checkRemove];
	[self checkRename];
	[self checkProtect];
	[self checkUnprotect];
char		msg[__MESSAGE_STRING_LENGTH_MAX__];
char		exp[__MESSAGE_STRING_LENGTH_MAX__];	
	b_message_string("close database",msg,ext->getbundle(),1);
	b_message_string("close database exp",exp,ext->getbundle(),1);
bAlertStop	alrt(msg,exp);	
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doRename:(id)sender{
	[_renbtn setEnabled:NO];
	[_typetbl editColumn:0 row:[_typetbl selectedRow] withEvent:nil select:YES];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doProtect:(id)sender{
long				index=[_typetbl selectedRow]+1;
bXMapTypeManager*	ext=(bXMapTypeManager*)_ext;
	if(!ext->prot_action(index)){
	}
	[self checkRemove];
	[self checkRename];
	[self checkProtect];
	[self checkUnprotect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(IBAction)doUnprotect:(id)sender{
long				index=[_typetbl selectedRow]+1;
bXMapTypeManager*	ext=(bXMapTypeManager*)_ext;
	if(!ext->unprot_action(index)){
	}
	[self checkRemove];
	[self checkRename];
	[self checkProtect];
	[self checkUnprotect];
}

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

// ---------------------------------------------------------------------------
// 
// ------------

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI{
//_bTrace_("[MakeConstraintsWindowController updateUI]",false);
	[self checkRemove];
	[self checkRename];
	[self checkProtect];
	[self checkUnprotect];
	
	if([_typetbl numberOfSelectedRows]>0){
long				index=[_typetbl selectedRow]+1;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(index);
double				d;
int					i;
char				c[PATH_MAX];
bool				b;

		tp->location(c);
        [_pathfld setCharValue:c];
		
		tp->fields()->h_read(1,kHDR_unit2m_,&d);
		getUnitShortLib(gapp,d,c);
        [_unitfld setCharValue:c];
		
		tp->fields()->h_read(1,kHDR_precs_,&d);
		[_resofld setDoubleValue:d];
		
		[_olivfld setIntValue:tp->nb_live()];
		[_okilfld setIntValue:tp->nb_killed()];
		
		switch(tp->kind()){
			case kBaseKindPoint:
				message_string(kMsgKindPoint,c,1);
				break;
			case kBaseKindText:
				message_string(kMsgKindText,c,1);
				break;
			case kBaseKindPolyline:
				message_string(kMsgKindLine,c,1);
				break;
			case kBaseKindPolygon:
				message_string(kMsgKindArea,c,1);
				break;
			case kBaseKindRaster:
				message_string(kMsgKindRaster,c,1);
				break;
			default:
				strcpy(c,"????");
				break;
		}
        [_gndrfld setCharValue:c];
		
		tp->fields()->h_read(1,kHDR_unit2m_,&d);

		tp->fields()->h_read(1,kHDR_srid_,&i);
bStdProjExt	prj(i,&b);
        [_projfld setCharValue:prj.name()];
		[_sridfld setIntValue:i];
	
		
		[_tpidfld setDoubleValue:tp->tid()];
		
		tp->fields()->h_read(1,kHDR_CrDate_,&d);
		dateToX(_char,0,d,c);
        [_crdtfld setCharValue:c];
		
		[_nbflfld setIntValue:tp->fields()->count()];
	}
	else{
		[_pathfld setStringValue:@""];
		[_unitfld setStringValue:@""];
		[_resofld setStringValue:@""];
		[_olivfld setStringValue:@""];
		[_okilfld setStringValue:@""];
		[_gndrfld setStringValue:@""];
		[_projfld setStringValue:@""];
		[_sridfld setStringValue:@""];
		[_tpidfld setStringValue:@""];
		[_crdtfld setStringValue:@""];
		[_nbflfld setStringValue:@""];
	}
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Retirer
// -----------
-(void)checkRemove{
BOOL	state=NO;
	if([_typetbl numberOfSelectedRows]>0){
long				index=[_typetbl selectedRow]+1;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(index);
		if(tp->is_remove()==false){
			state=YES;
		}
	}
	[_rmvbtn setEnabled:state];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Renommer
// -----------
-(void)checkRename{
BOOL	state=NO;
	if([_typetbl numberOfSelectedRows]>0){
long				index=[_typetbl selectedRow]+1;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(index);
		if((tp->is_remove()==false)&&(tp->is_lock()==false)){
			state=YES;
		}
	}
	[_renbtn setEnabled:state];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Protéger
// -----------
-(void)checkProtect{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
BOOL				state=NO;
	
	if([_typetbl numberOfSelectedRows]>0){
long				index=[_typetbl selectedRow]+1;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(index);
		if(tp->is_lock()==false){
			state=YES;
		}
	}
	[_prtbtn setEnabled:state];
}

// ---------------------------------------------------------------------------
// Disponibilité du bouton Déprotéger
// -----------
-(void)checkUnprotect{
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
BOOL				state=NO;

	if([_typetbl numberOfSelectedRows]>0){
		long				index=[_typetbl selectedRow]+1;
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(index);
		if(tp->is_lock()==true){
			state=YES;
		}
	}
	[_unpbtn setEnabled:state];
}

#pragma mark ---- Gestion TableView ----
// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
bGenericMacMapApp* gapp=(bGenericMacMapApp*)_ext->getapp();
	return gapp->typesMgr()->count();
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)	tableView:(NSTableView*)aTableView 
		objectValueForTableColumn:(NSTableColumn*)aTableColumn 
		row:(NSInteger)rowIndex{	
	
NSString*			nsstr;
char				str[256];
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();
bGenericType*		tp=gapp->typesMgr()->get(rowIndex+1);

	tp->name(str);
	nsstr=[NSString stringWithCString:str encoding:NSMacOSRomanStringEncoding];
	return nsstr;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)	tableView:(NSTableView *)aTableView
   setObjectValue:(id)anObject
   forTableColumn:(NSTableColumn*)aTableColumn
			  row:(NSInteger)rowIndex{
NSString*			nsstr=(NSString*)anObject;
bXMapTypeManager*	ext=(bXMapTypeManager*)(void*)_ext;
char				name[256];
	[nsstr getCString:name maxLength:255 encoding:NSMacOSRomanStringEncoding];
	if(strlen(name)==0){
		return;
	}
	if(!ext->ren_action(rowIndex+1,name)){
		return;
	}
	
	[self checkRemove];
	[self checkRename];
	[self checkProtect];
	[self checkUnprotect];
	
char		msg[__MESSAGE_STRING_LENGTH_MAX__];
char		exp[__MESSAGE_STRING_LENGTH_MAX__];	
	b_message_string("close database",msg,ext->getbundle(),1);
	b_message_string("close database exp",exp,ext->getbundle(),1);
bAlertStop	alrt(msg,exp);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)tableViewSelectionDidChange:(NSNotification*)notification{
	[self updateUI];
}

// ---------------------------------------------------------------------------
// 
// ------------
@end

// ---------------------------------------------------------------------------
// 
// ------------
void C_runTypeManagerCocoaAppModal(bXMapTypeManager* ext,
								   long* code){
TypeManagerWindowController	*controller;
NSAutoreleasePool			*localPool;

    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[TypeManagerWindowController alloc] initWithExt:ext];
    [controller runTypeManagerCocoaAppModal:code];
	[controller close];
	[controller release];
    [localPool release];
}

