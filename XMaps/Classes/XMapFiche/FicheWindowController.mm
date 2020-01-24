//----------------------------------------------------------------------------
// File : FicheWindowController.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap fiche (i.e. card) window controller
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
// 14/04/2014 creation.
//----------------------------------------------------------------------------

#import "FicheWindowController.h"
#import "bXMapFiche.h"
#import "CocoaStuff.h"

#import "XMapFicheCell.h"

#import <MacMapSuite/bTrace.h>

#import <mox_intf/bGenericMacMapApp.h>
#import <mox_intf/bEventLog.h>
#import <mox_intf/ext_utils.h>
#import <mox_intf/xmldesc_utils.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/endian.h>
#import <mox_intf/NSContextualMenuWrappers.h>
#import <mox_intf/Type_Utils.h>

#import <std_ext/bXMapStdIntf.h>

// ---------------------------------------------------------------------------
// 
// ------------
typedef struct cell_p{
	bGenericMacMapApp*	gapp;
	bGenericType*		tp;
	NSMutableArray*		arr;	
	int					state;
	int					fx;
	int					knd;
	int					last;
	float				x;
	float				y;
}cell_p;

// ---------------------------------------------------------------------------
// 
// ------------
@implementation FicheObjView


// ---------------------------------------------------------------------------
// 
// -----------
static CGFloat getMaxY(NSMutableArray* cells){
CGFloat			y=0;
XMapFicheCell*	cell;
NSEnumerator*	numer=[cells objectEnumerator];
	while((cell=[numer nextObject])){
		if(NSMaxY([cell frame])>y){
			y=NSMaxY([cell frame]);
		}
	}
	return(y);
}

// ---------------------------------------------------------------------------
// 
// -----------
static XMapFicheCell* makeCell(bGenericMacMapApp* gapp, 
							   bGenericType* tp, 
							   NSMutableArray* cells,
							   int fld, 
							   CGPoint o, 
							   bool calc, 
							   bool addNew, 
							   int kind){
	if((tp->fields()->is_hidden(fld))&&(fld!=kOBJ_Vertices_)){
		return nil;
	}
int				k;
XMapFicheCell*	cell=nil;
float			top;
float			left;
	if(calc){
		top=getMaxY(cells)+_MARGIN_;
		left=0;
	}
	else{
		top=o.y;
		left=o.x;
	}

NSPoint	nsp=NSMakePoint(left,top);
	
	if((addNew)||(kind==kCellNoKind)){
// Create new cell
		tp->fields()->get_kind(fld,&k);
		if(tp->fields()->is_writeprotected(fld)){
			cell=[[XMapFicheStaticTextCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
		}
		else if(k==_bool){
			cell=[[XMapFicheCheckBoxCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
		}
		else if(k==_ivxs2){
			cell=[[XMapFicheCoordListCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
		}
		else if(tp->fields()->count_constraints(fld)>0){// on pourrait dire qu'au dela de 32 on passe en liste
			cell=[[XMapFichePopupCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
		}
		else{
			cell=[[XMapFicheEditTextCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
		}
	}
	else{
		switch(kind){
			case kCellStaticKind:
				cell=[[XMapFicheStaticTextCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
				break;
			case kCellEditKind:
				cell=[[XMapFicheEditTextCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
				break;
			case kCellCheckBoxKind:
				cell=[[XMapFicheCheckBoxCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
				break;
			case kCellPopupKind:
				cell=[[XMapFichePopupCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
				break;
			case kCellListKind:
				cell=[[XMapFicheListCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
				break;
			case kCellCoordListKind:
				cell=[[XMapFicheCoordListCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
				break;
			case kCellImageKind:
				cell=[[XMapFicheImageCell alloc] initWithPoint:nsp application:gapp type:tp field:fld];
				break;
			default:
				return nil;
				break;
		}
	}
	if(cell){
		[cells addObject:cell];
		[cell release];
		return [cells lastObject];
	}
	return nil;
}

// ---------------------------------------------------------------------------
// 
// ------------
static bool readProc(bGenericXMLBaseElement* elt,
					 void* prm,
					 int indent){
cell_p*	p=(cell_p*)prm;
char	name[_names_length_max_];
char	value[_values_length_max_];
	
	elt->getclassname(name);
	if(!strcmp(name,"name")){
		elt->getvalue(value);
		p->fx=p->tp->fields()->get_index(value);
		if(p->fx){
			p->state++;
		}
	}
	else if(!strcmp(name,"int")){
		if(p->state==1){
			p->state++;
			elt->getvalue(value);
			p->knd=atoi(value);
		}
		else{
			elt->getvalue(value);
			p->last=atoi(value);
		}
	}
	else if(!strcmp(name,"float")){
		if(p->state==1){
			p->state++;
		}
		if(p->fx){
			elt->getvalue(value);
			if(p->state==2){
				p->x=atof(value);
				p->state++;
			}
			else if(p->state==3){
				p->y=atof(value);
				(void)makeCell(p->gapp,p->tp,p->arr,p->fx,CGPointMake(p->x,p->y),false,false,p->knd);
				p->state=0;
			}
		}
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
-(id)initWithFrame:(NSRect)frameRect{
_bTrace_("[FicheObjView initWithFrame]",true);
	if((self=[super initWithFrame:frameRect])!=nil){
		_cells=[[NSMutableArray alloc] init];
		_cic=NO;
		_lastCell=-1;
		_first=YES;
		_gapp=NULL;
		_o=NULL;
		_tp=NULL;	
		_addNew=YES;
	}
	return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[FicheObjView dealloc]",true);
	[_cells release];
	[super dealloc];
}

// ---------------------------------------------------------------------------
// We need keydown when window is shown
// ------------
-(BOOL)acceptsFirstResponder{
	return(YES);
}

// ---------------------------------------------------------------------------
// We need mousedown when window is shown
// -----------
-(BOOL)acceptsFirstMouse:(NSEvent*)evt{
	[super acceptsFirstMouse:evt];
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)isFlipped{
    return YES;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)drawRect:(NSRect)rect{
XMapFicheCell*	cell;
NSEnumerator*	numer;
	if(_first==YES){
		[self putBounds];
		_first=NO;
	}
	numer=[_cells objectEnumerator];
	while((cell=[numer nextObject])){
		if(NSIntersectsRect([cell frame],rect)) {
			[cell drawRect:rect];
		}
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)viewDidEndLiveResize{
	_first=YES;
	[self putBounds];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(long)findCell:(NSPoint)location{
XMapFicheCell*	cell;
	for(long i=0;i<[_cells count];i++){
		cell=[_cells objectAtIndex:i];
		if(NSPointInRect(location,[cell frame])){
			return i+1;
		}
	}
	return 0;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)mouseDown:(NSEvent*)event{
long			idx=[self findCell:[self convertPoint:[event locationInWindow] fromView:nil]];
XMapFicheCell*	cell;
	if(idx>0){
		_cic=YES;
		if(_lastCell>-1){
			cell=[_cells objectAtIndex:_lastCell];
			if(cell){
				[cell setCurrent:NO];
			}
		}
		cell=[_cells objectAtIndex:idx-1];
		[cell setCurrent:YES];
		_lastCell=idx-1;
		[self setNeedsDisplay:YES];
		if([cell mouse:event inView:self]){
			_cic=NO;
		}
	}
	else{
		if(_lastCell>-1){
			cell=[_cells objectAtIndex:_lastCell];
			if(cell){
				if([cell mouse:event inView:self]){
					_cic=NO;
				}
			}
		}		
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)rightMouseDown:(NSEvent*)event{
long			idx=[self findCell:[self convertPoint:[event locationInWindow] fromView:nil]];
XMapFicheCell*	cell;
	_cic=NO;
	if(idx>0){
		if(_lastCell>-1){
			cell=[_cells objectAtIndex:_lastCell];
			if(cell){
				[cell setCurrent:NO];
			}
		}
		cell=[_cells objectAtIndex:idx-1];
		[cell setCurrent:YES];
		_lastCell=idx-1;
		[self setNeedsDisplay:YES];
		if([cell rightMouse:event inView:self]){
		}
	}
	else{
		if(_lastCell>-1){
			cell=[_cells objectAtIndex:_lastCell];
			if(cell){
				if([cell mouse:event inView:self]){
				}
			}
		}		
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)mouseUp:(NSEvent*)event{
	_cic=NO;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)mouseDragged:(NSEvent*)event{	
NSUInteger	mod=[event modifierFlags];
	if((_cic)&&(_lastCell>-1)&&(mod&NSAlternateKeyMask)){
CGFloat	dx=[event deltaX],dy=[event deltaY];		
// autoscroll
		if(![self mouse:[self convertPoint:[event locationInWindow] 
								  fromView:nil] 
				 inRect:[self visibleRect]]){
// Adding autoscroll delta to drag
NSScrollView*	scrollView=[self enclosingScrollView];
NSPoint			posa=[[scrollView contentView] bounds].origin;
			[self autoscroll:event];
NSPoint			posb=[[scrollView contentView] bounds].origin;
			dx+=(posb.x-posa.x);
			dy-=(posb.y-posa.y);
		}
// Moving cell
XMapFicheCell*	cell=[_cells objectAtIndex:_lastCell];
		[cell setFrame:NSOffsetRect([cell frame],dx,dy)];
		[self setNeedsDisplay:YES];
		[self putBounds];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)keyDown:(NSEvent*)event{
_bTrace_("[FicheObjView keyDown]",true);
	if([event keyCode]==kVK_Tab){// Change field
NSUInteger		mod=[event modifierFlags];
XMapFicheCell*	cell;

		cell=[_cells objectAtIndex:_lastCell];
		if(cell){
			[cell setCurrent:NO];
		}
		if(mod&NSShiftKeyMask){// Previous
			_lastCell--;
			if(_lastCell<0){
				_lastCell=[_cells count]-1;
			}
		}
		else{// Next
			_lastCell++;
			if(_lastCell>=[_cells count]){
				_lastCell=0;
			}
		}
		cell=[_cells objectAtIndex:_lastCell];
		if(cell){
			[cell setCurrent:YES];
			[self scrollRectToVisible:[cell frame]];
		}
		[self setNeedsDisplay:YES];
		return;
	}
	else if([event keyCode]==kVK_Escape){// close wd (because of acceptsFirstResponder trapping esc)
_tm_("[event keyCode]==kVK_Escape");
FicheWindowController*	ctrlr=[[self window] windowController];
		[ctrlr prepareForClose];
		return;
	}
	
	if((_cic==NO)&&(_lastCell>-1)){// Send event to current cell
XMapFicheCell*	cell=[_cells objectAtIndex:_lastCell];
		if([cell key:event inView:self]){
		}
	}
	else{
		[super keyDown:event];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)putObj:(bGenericGeoElement*)obj{
	if(_o!=NULL){
		[self write_p];
	}
	_o=obj;
	_tp=_gapp->typesMgr()->get(_o->getType());
	[XMapFicheCell setObject:obj];
	[_cells removeAllObjects];
	[self read_p];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)putApp:(bGenericMacMapApp*)gapp{
	_gapp=gapp;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)read_p{
char	directory[PATH_MAX];
char	fname[FILENAME_MAX];
FicheWindowController*	ctrlr=[[self window] windowController];
	[ctrlr getParamsInfos:directory name:fname];
	
bGenericXMLBaseElement*	root=GetXMLParamFromType(_gapp,_tp,directory,fname);
	if(!root){
		[self initType];
		return;
	}
	
cell_p	prm;
	prm.gapp=_gapp;
	prm.tp=_tp;
	prm.arr=_cells;
	prm.state=0;
	prm.fx=0;
	prm.last=0;
	prm.x=0;
	prm.y=0;
	root->dotoall(&prm,0,readProc);
	
	_addNew=NO;
	
bGenericXMLBaseElement*	elt=_gapp->classMgr()->NthElement(root,1,"bool");
	if(elt){
char					value[_values_length_max_];
		elt->getvalue(value);
		_addNew=atoi(value);
	}
	
XMapFicheCell*	cell;
NSRect			nsr;
	if(_addNew){
		for(long i=kOBJ_Vertices_;i<=_tp->fields()->count();i++){
bool			breaked=false;
NSEnumerator*	numer=[_cells objectEnumerator];
			while((cell=[numer nextObject])){
				if([cell fieldIndex]==i){
					breaked=true;
					break;
				}
			}
			if(breaked){
				continue;
			}
            cell=makeCell(_gapp,_tp,_cells,i,CGPointZero,true,true,kCellNoKind);
            if(cell){
                nsr=[cell frame];
                nsr.origin.x+=5;
                [cell setFrame:nsr];
            }
		}
	}
	
	if(prm.last==0){
		prm.last=1;
	}
	else if(prm.last>[_cells count]){
		prm.last=1;
	}
	
	_lastCell=prm.last;
	
	cell=[_cells objectAtIndex:_lastCell];
	[cell setCurrent:YES];
	_gapp->classMgr()->ReleaseXMLInstance(root);
	
	[self putBounds];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)write_p{
bGenericXMLBaseElement*	root=[self make_p];
	if(!root){
		return;
	}
char	directory[PATH_MAX];
char	fname[FILENAME_MAX];
FicheWindowController*	ctrlr=[[self window] windowController];
	[ctrlr getParamsInfos:directory name:fname];
	if(!SetXMLParamToType(_tp,directory,fname,root)){
	}
	_gapp->classMgr()->ReleaseXMLInstance(root);
}

// ---------------------------------------------------------------------------
// 
// ------------
-(bGenericXMLBaseElement*)make_p{
bArray			arr(sizeof(xmlelt));
char			buffer[256];
XMapFicheCell*	cell;
NSEnumerator*	numer;
NSRect			frame;
	
	add_cdesc(arr,0,"param","");
	add_cdesc(arr,1,"version","3.0.0");
	add_idesc(arr,1,"bool",_addNew);
	add_idesc(arr,1,"int",_lastCell);

	numer=[_cells objectEnumerator];
	while((cell=[numer nextObject])){
		[cell name:buffer];
		frame=[cell frame];
		add_cdesc(arr,1,"name",buffer);
		add_idesc(arr,1,"int",[cell kind]);
		add_ddesc(arr,1,"float",frame.origin.x,2);
		add_ddesc(arr,1,"float",frame.origin.y,2);
	}
		
bGenericXMLBaseElement*	root=_gapp->classMgr()->ParseXMLDescriptors(&arr);
	free_descs(arr);
	return(root);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)resetType{
	[_cells removeAllObjects];
	_lastCell=-1;
BOOL bckAddNew=_addNew;
	[self initType];
	_addNew=bckAddNew;
	[self write_p];
	[self putBounds];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)initType{
	for(int i=kOBJ_Vertices_;i<=_tp->fields()->count();i++){
		(void)makeCell(_gapp,_tp,_cells,i,CGPointZero,true,true,kCellNoKind);
	}
	_addNew=YES;
	[self putBounds];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)abort{
	if(_lastCell<0){
		return NO;
	}
XMapFicheCell*	cell=NULL;
	cell=[_cells objectAtIndex:_lastCell];
	if(!cell){
		return NO;
	}
	return [cell abort];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)putBounds{
NSScrollView*	scrollView=[self enclosingScrollView];
XMapFicheCell*	cell;
NSEnumerator*	numer=[_cells objectEnumerator];
NSRect			bnds=NSZeroRect;
	while((cell=[numer nextObject])){
		if(NSEqualRects(bnds,NSZeroRect)){
			bnds=[cell frame];
		}
		else{
			bnds=NSUnionRect(bnds,[cell frame]);
		}
	}

	numer=[_cells objectEnumerator];
	while((cell=[numer nextObject])){
		[cell setFrame:NSOffsetRect([cell frame],-bnds.origin.x,-bnds.origin.y)];
		[cell setFrame:NSOffsetRect([cell frame],5,5)];
	}

	bnds.origin.x=0;
	bnds.origin.y=0;
	bnds.size.width+=10;
	bnds.size.height+=10;
	
bool	vscroll=bnds.size.width>[scrollView bounds].size.width;
bool	hscroll=bnds.size.height>[scrollView bounds].size.height;
		
	bnds=NSUnionRect(bnds,[scrollView bounds]);

	if(!vscroll){
		bnds.size.width-=17;
	}
	if(!hscroll){
		bnds.size.height-=17;
		bnds.origin.y+=17;
	}
	
	[[scrollView documentView] setFrame:bnds];
	
	[self setNeedsDisplay:YES];
}


// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateField:(long)fieldId{
long			idx=_tp->fields()->get_index(fieldId);
	if(idx){
XMapFicheCell*	cell;
NSRect			frame;
bool			fok=false;
		for(long i=0;i<[_cells count];i++){
			cell=[_cells objectAtIndex:i];
			if([cell fieldIndex]==idx){
				frame=[cell frame];
				[_cells removeObjectAtIndex:i];
				(void)makeCell(_gapp,_tp,_cells,idx,CGPointZero,true,true,kCellNoKind);
				fok=true;
				break;
			}
		}
		if(fok){
			cell=[_cells lastObject];
			[cell setFrame:frame];
			[self write_p];
			[self setNeedsDisplay:YES];
		}
	}	
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)removeField:(long)fieldId{
long	idx=_tp->fields()->get_index(fieldId);
	if(idx){
XMapFicheCell*	cell;
		for(long i=0;i<[_cells count];i++){
			cell=[_cells objectAtIndex:i];
			if([cell fieldIndex]==idx){
				[_cells removeObjectAtIndex:i];
				break;
			}
		}		
		[self write_p];
		[self setNeedsDisplay:YES];
	}	
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)addField:(long)fieldId{
long			idx=_tp->fields()->get_index(fieldId);
NSRect			nsr;
XMapFicheCell*	cell;
	if(idx){
		cell=makeCell(_gapp,_tp,_cells,idx,CGPointZero,true,true,kCellNoKind);
		if(cell){
			nsr=[cell frame];
			nsr.origin.x+=5;
			[cell setFrame:nsr];
			[self write_p];
			[self setNeedsDisplay:YES];
		}
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
@end


// ---------------------------------------------------------------------------
// 
// ------------
@implementation FichePanel

// ---------------------------------------------------------------------------
// 
// ------------
- (id)initWithContentRect:(NSRect)contentRect 
				styleMask:(NSUInteger)aStyle 
				  backing:(NSBackingStoreType)bufferingType 
					defer:(BOOL)flag{
_bTrace_("[FichePanel initWithContentRect ...]",true);	
	return [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
}

// ---------------------------------------------------------------------------
// 
// ------------
- (id)initWithContentRect:(NSRect)contentRect 
				styleMask:(NSUInteger)aStyle 
				  backing:(NSBackingStoreType)bufferingType 
					defer:(BOOL)flag 
				   screen:(NSScreen *)screen{
_bTrace_("[FichePanel initWithContentRect ... screen]",true);
	return [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag screen:screen];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[FichePanel close]",true);
_tm_((void*)self);
	[_viw write_p];

FicheWindowController*	mmc=(FicheWindowController*)[self windowController];
	if(mmc){
		[mmc prepareForClose];
	}
	[super close];
}

// ---------------------------------------------------------------------------
// Just for debug
// ------------
-(void)dealloc{
_bTrace_("[FichePanel dealloc]",true);
_tm_((void*)self);
	[super dealloc];
}

// ---------------------------------------------------------------------------
// 
// ------------
- (void)performClose:(id)sender{
_bTrace_("[FichePanel performClose]",true);
	if(![_viw abort]){
		[super performClose:sender];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
@end



// ---------------------------------------------------------------------------
// 
// ------------
@implementation FicheWindowController

// ---------------------------------------------------------------------------
// 
// ------------
-(id)init{
_bTrace_("[FicheWindowController init]",true);
	self=[super init];
	if(self){
	}	
    return self;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)dealloc{
_bTrace_("[FicheWindowController dealloc]",true);
_tm_((void*)self);
_tm_("window: "+(void*)[self window]);
  
    [_fke release];
    [_nke release];
    [_pke release];
    [_lke release];
    
// Trouver pourquoi on est obligé de forcer le window close
// Le problème survient après une édition en mode NSTextField
// et suivi d'une fermeture provoquée par esc : le controller est désalloué
// mais la fenêtre reste affichée jusqu'à un changement d'ordre des fenêtres
    [[self window] close];

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
_bTrace_("[FicheWindowController awakeFromNib]",true);
	[super awakeFromNib];
bGenericMacMapApp*	gapp=(bGenericMacMapApp*)_ext->getapp();

	_arr=new bArray(*(gapp->selMgr()->elements()));
	_cur=1;
	_ls=0;
	
	[_viw putApp:gapp];
    
    _fke=[_frs keyEquivalent];
    [_fke retain];
    _fkm=[_frs keyEquivalentModifierMask];
    _nke=[_nxt keyEquivalent];
    [_nke retain];
    _nkm=[_nxt keyEquivalentModifierMask];
    _pke=[_prv keyEquivalent];
    [_pke retain];
    _pkm=[_prv keyEquivalentModifierMask];
    _lke=[_lst keyEquivalent];
    [_lke retain];
    _lkm=[_lst keyEquivalentModifierMask];
   
	[self updateUI:YES];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)checkMacMapEvent{
_bTrace_("[FicheWindowController checkMacMapEvent]",true);
bGenericMacMapApp*	gapp=[self getApp];
bArray*				arr=gapp->eventMgr()->events();
bGenericEvent*		evt;
int					i,j,k;
bool				needinval=false;
	
	for(i=1;i<=arr->count();i++){
		arr->get(i,&evt);
		switch(evt->kind()){
			case kEventKindGeoElement:{
bGenericGeoElement	*o,*mo;
int					k;
					if(evt->action()==kEventActionModify){
bArray					tmp(*_arr);
						tmp.sort(ObjRefComp);
						for(j=1;j<=evt->elements()->count();j++){
							evt->elements()->get(j,&mo);
							o=mo->get_ref();
							if(tmp.search(&o,ObjRefComp)){
								needinval=true;
								break;
							}
						}
					}
					else if(evt->action()==kEventActionDestroy){
bArray					tmp(*(evt->elements()));
						tmp.sort(ObjRefComp);
						for(j=_arr->count();j>0;j--){
							_arr->get(j,&o);
							if((k=tmp.search(&o,ObjRefComp))){
								needinval=true;
								_arr->rmv(j);
							}
						}
					}
				}
				break;
			case kEventKindDataStruct:{
bGenericGeoElement*	o;
					_arr->get(_cur,&o);
bGenericType*		tp=gapp->typesMgr()->get(o->getType());
					
field_info			fi;
					if(evt->action()==kEventActionModify){
						for(j=1;j<=evt->elements()->count();j++){
							evt->elements()->get(j,&fi);
							if(fi.tp!=tp){
								continue;
							}
							needinval=true;
							[_viw updateField:fi.fid];
						}
					}
					else if(evt->action()==kEventActionDestroy){
						for(j=1;j<=evt->elements()->count();j++){
							evt->elements()->get(j,&fi);
							if(fi.tp!=tp){
								continue;
							}
							needinval=true;
							[_viw removeField:fi.fid];
						}
					}
					else if(evt->action()==kEventActionCreate){
						for(j=1;j<=evt->elements()->count();j++){
							evt->elements()->get(j,&fi);
							if(fi.tp!=tp){
								continue;
							}
							needinval=true;
							[_viw addField:fi.fid];	
						}
					}
				}
				break;
			case kEventKindTypeElement:{
bGenericType*		tp;
bGenericGeoElement*	o;
					if(evt->action()==kEventActionDestroy){
						for(k=_arr->count();k>0;k--){
							_arr->get(k,&o);
							for(j=1;j<=evt->elements()->count();j++){
								evt->elements()->get(j,&tp);
								if(o->getType()==tp->index()){
									_arr->rmv(k);
									break;
								}
							}
						}
					}
				}
				break;
		}
	}
	if(_arr->count()==0){
		[self prepareForClose];
		return;
	}
	if(needinval){
		if(_cur>_arr->count()){
			_cur=_arr->count();
		}
		[self updateUI:YES];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)idle{
//_bTrace_("[FicheWindowController idle]",false);
//_tm_("WINDOW: "+(void*)[self window]);
//_tm_("FIRSTRESPONDER:"+(void*)[self window]);
bGenericMacMapApp*	gapp=[self getApp];
	if(_ls!=gapp->selMgr()->getState()){
		[self updateUI:NO];
		_ls=gapp->selMgr()->getState();
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)close{
_bTrace_("[FicheWindowController close]",true);
_tm_((void*)self);
	[super close];
}

#pragma mark ---- Actions ----
// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doSelect:(id)sender{
bGenericGeoElement* geo=NULL;
	if(_arr->get(_cur,&geo)){
		geo->setselect([_sel intValue],true);
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doFirst:(id)sender{
	_cur=1;
	[self updateUI:YES];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doPrevious:(id)sender{
	_cur--;
	if(_cur<1){
		_cur=1;
		NSBeep();
	}
	else{
		[self updateUI:YES];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doNext:(id)sender{
	_cur++;
	if(_cur>_arr->count()){
		_cur=_arr->count();
		NSBeep();
	}
	else{
		[self updateUI:YES];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doLast:(id)sender{
	_cur=_arr->count();
	[self updateUI:YES];
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)doReorganize:(id)sender{
	[_viw resetType];
	[self updateUI:YES];
}

#pragma mark ---- Update Intf ----
// ---------------------------------------------------------------------------
// 
// -----------
-(void)updateUI:(BOOL)reload{
bGenericMacMapApp*	gapp=[self getApp];
bGenericGeoElement*	geo;
	_arr->get(_cur,&geo);
	if(reload){
		[_viw putObj:geo];
		[_viw setNeedsDisplay:YES];
	}
	[_sel setIntValue:geo->selected()];
	
bGenericType* tp=gapp->typesMgr()->get(geo->getType());
char	str[256];
	tp->name(str);
	[_typ setCharValue:str];
	sprintf(str,"%ld/%ld",_cur,_arr->count());
	[_cnt setCharValue:str];
}

// ---------------------------------------------------------------------------
//
// -----------
-(void)setKeyEquivalent:(BOOL)on{
    if(on){
        [_frs setKeyEquivalent:_fke];
        [_frs setKeyEquivalentModifierMask:_fkm];
        [_prv setKeyEquivalent:_pke];
        [_prv setKeyEquivalentModifierMask:_pkm];
        [_nxt setKeyEquivalent:_nke];
        [_nxt setKeyEquivalentModifierMask:_nkm];
        [_lst setKeyEquivalent:_lke];
        [_lst setKeyEquivalentModifierMask:_lkm];
    }
    else{
        [_frs setKeyEquivalent:@""];
        [_frs setKeyEquivalentModifierMask:0];
        [_prv setKeyEquivalent:@""];
        [_prv setKeyEquivalentModifierMask:0];
        [_nxt setKeyEquivalent:@""];
        [_nxt setKeyEquivalentModifierMask:0];
        [_lst setKeyEquivalent:@""];
        [_lst setKeyEquivalentModifierMask:0];
    }
}

#pragma mark ---- Intf Externe/Cocoa ----
// ---------------------------------------------------------------------------
// 
// ------------
-(bGenericMacMapApp*)getApp{
	return((bGenericMacMapApp*)_ext->getapp());
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)getParamsInfos:(char*)directory name:(char*)prmName{
	GetSignatureString(_ext,directory);
	sprintf(prmName,"default_fields.xml");
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
FicheWindowController	*controller;
NSAutoreleasePool		*localPool;
	
    localPool=[[NSAutoreleasePool alloc] init];   
    controller=[[FicheWindowController alloc] init];
    [controller setExt:(bStdNSXMap*)ext];
    [localPool release];
    return((void*)controller);
}

// ---------------------------------------------------------------------------
// 
// ------------
void disposeCocoa(const void* instance){
NSAutoreleasePool		*localPool;
FicheWindowController	*mmc=(FicheWindowController*)instance;
	
	if(mmc==NULL){
		return;
	}
	
    localPool=[[NSAutoreleasePool alloc] init];        
	[mmc release];
    [localPool release];
}

// ---------------------------------------------------------------------------
// 
// ------------
void closeCocoa(const void* instance){
NSAutoreleasePool		*localPool;
FicheWindowController	*mmc=(FicheWindowController*)instance;
	
	if(mmc==NULL){
		return;
	}
	
    localPool=[[NSAutoreleasePool alloc] init];        
	[mmc close];
    [localPool release];
}

