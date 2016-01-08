//----------------------------------------------------------------------------
// File : XMapFicheCell.mm
// Project : MacMap
// Purpose : Objective C++ source file : XMap fiche (i.e. card) cell
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
// 15/04/2014 creation.
//----------------------------------------------------------------------------


#import "XMapFicheCell.h"
#import <mox_intf/bCoreTextInfo.h>
#import <mox_intf/bEventLog.h>
#import <mox_intf/NSUIUtils.h>
#import <mox_intf/NSContextualMenuWrappers.h>
#import <mox_intf/bGenericCalc.h>

#import <MacMapSuite/bTrace.h>
#import "FicheWindowController.h"

// ---------------------------------------------------------------------------
// 
// -----------
#define _XOFFSET_				3.0
#define _YOFFSET_				0.5
#define _RADIUS_				3.0
#define _LINEWIDTH_				0.5
#define _NAMEBACKCOLORNORMAL_	[NSColor lightGrayColor]
#define _NAMEBACKCOLORHILITED_	[NSColor darkGrayColor]
#define _VALUEBACKCOLOR_		[NSColor whiteColor]
#define _STROKECOLOR_			[NSColor blackColor]
#define	kXMapFicheMessageID		"fiche"

// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFicheCell

// ---------------------------------------------------------------------------
// 
// -----------
static bGenericMacMapApp*	_gapp;
static bGenericGeoElement*	_geo;
static bGenericType*		_gtp;
static const char			_font[256]={"Geneva"};
//static NSString*			_font=@"Geneva";

static CGFloat				_font_size=12;
static CGFloat				_std_height=16;

static NSMutableDictionary*	_strAttr=NULL;


// ---------------------------------------------------------------------------
// 
// -----------
-(void)calcFrame:(NSPoint)o{
char	name[512];
int		l,k;
	
	_gtp->fields()->get_name(_field,name);
	_gtp->fields()->get_len(_field,&l);
	_gtp->fields()->get_kind(_field,&k);
	if(k==_ivxs2){
		l=2*_kDoubleLen;
	}
	
{
bCoreTextInfo	ti(_font, 
				   _font_size, 
				   0, 
				   0, 
				   0, 
				   name);
	_name_area=NSMakeRect(o.x,o.y,ti.textWidth()+6.0,_std_height);
}	
	for(k=0;k<l;k++){
		name[k]='W';
	}
	name[k]=0;
	
{
bCoreTextInfo	ti(_font, 
				   _font_size, 
				   0, 
				   0, 
				   0, 
				   name);
	_value_area=NSMakeRect(_name_area.origin.x+_name_area.size.width,_name_area.origin.y,ti.textWidth()+6.0,_name_area.size.height);
}
	_frame=NSUnionRect(_name_area,_value_area);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)initWithPoint:(NSPoint)point 
	   application:(bGenericMacMapApp*)gapp 
			  type:(bGenericType*)typ 
			 field:(long)fld{
	_gapp=gapp;
	_gtp=typ;
	
	if(_strAttr==NULL){
		_strAttr = [NSMutableDictionary dictionary];
		[_strAttr setObject:[NSFont fontWithName:@"Geneva" size:_font_size] forKey:NSFontAttributeName];
		[_strAttr setObject:[NSColor blackColor] forKey:NSForegroundColorAttributeName];
		[_strAttr retain];
	}
	
    if(self=[super init]) {
		_field=fld;
		_fieldId=_gtp->fields()->get_id(_field);
		_current=false;
		[self calcFrame:point];
    }
    return self;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)dealloc{
    [super dealloc];
}

// ---------------------------------------------------------------------------
// 
// -----------
+(void)setObject:(bGenericGeoElement*)geo{
    _geo=geo;
    return;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)setFrame:(NSRect)rect{
CGFloat dx=rect.origin.x-_frame.origin.x;
CGFloat dy=rect.origin.y-_frame.origin.y;

	_name_area=NSOffsetRect(_name_area,dx,dy);
	_value_area=NSOffsetRect(_value_area,dx,dy);
    _frame=rect;
    return;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(NSRect)frame{
    return _frame;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)setCurrent:(BOOL)flg{
	_current=flg;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)current{
	return _current;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)fieldIndex{
	return _field;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)name:(char*)buffer{
	_gtp->fields()->get_name(_field,buffer);
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellNoKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
- (void)drawRect:(NSRect)rect{	
	if([self current]){
		[_NAMEBACKCOLORHILITED_ set];
	}
	else{
		[_NAMEBACKCOLORNORMAL_ set];
	}
	
NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:_frame xRadius:_RADIUS_ yRadius:_RADIUS_];
    [path fill];
	
	[_VALUEBACKCOLOR_ set];
	path = [NSBezierPath bezierPathWithRoundedRect:_value_area xRadius:_RADIUS_ yRadius:_RADIUS_];
    [path fill];

	path = [NSBezierPath bezierPathWithRoundedRect:_frame xRadius:_RADIUS_ yRadius:_RADIUS_];
	[[NSColor blackColor] setStroke];
	[path setLineWidth:_LINEWIDTH_];
	[path stroke];
	
char		name[256];
NSString*	nstr;
		
	_gtp->fields()->get_name(_field,name);
	nstr=[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
	[nstr drawAtPoint:NSMakePoint(_name_area.origin.x+_XOFFSET_,_name_area.origin.y+_YOFFSET_) withAttributes:_strAttr];
	
	_geo->getValue(_field,name);
	nstr=[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
	//nstr=NSStringFromRect(_frame);
	[nstr drawAtPoint:NSMakePoint(_value_area.origin.x+_XOFFSET_,_value_area.origin.y+_YOFFSET_) withAttributes:_strAttr];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)mouse:(NSEvent*)evt inView:(NSView*)view{
	if(NSPointInRect([view convertPoint:[evt locationInWindow] fromView:nil],_value_area)){
		[view scrollRectToVisible:_frame];
		return YES;
	}
	return NO;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)rightMouse:(NSEvent*)evt inView:(NSView*)view{
	if(NSPointInRect([view convertPoint:[evt locationInWindow] fromView:nil],_value_area)){
		[view scrollRectToVisible:_frame];
long			n=_gapp->calcMgr()->count();
menuitem_desc*	desc=new menuitem_desc[n];		
		
		for(long i=1;i<=_gapp->calcMgr()->count();i++){
			_gapp->calcMgr()->ext_name(i,desc[i-1].name);
			desc[i-1].checked=false;
			desc[i-1].disabled=false;
            desc[i-1].index=0;
		}

CGPoint	location=NSPointToCGPoint([view convertPointToBase:_value_area.origin]);
long which=popUpContextMenuWithCGPointAndNSWindow(location,
												  [view window],
												  desc,
												  n);
		delete desc;
		
		if(which>0){
bGenericCalc*	clc=(bGenericCalc*)(void*)_gapp->calcMgr()->get(which);
bStdDBValue*	val=clc->solve(_geo);
char			cval[1024]="";
int				ival,k;
double			dval;
bool			b=false;
			
			if(FieldInView(_gapp,_gtp,_field)){
				_geo->inval(_field);
			}
			
CFBundleRef	bndl=CFBundleGetBundleWithIdentifier(CFSTR("com.cbconseil.xmapfiche"));
bEventLog	log(_gapp,
				bndl,
				kXMapFicheMessageID,
				GetSignatureFromBundle(bndl));

			_gtp->fields()->get_kind(_field,&k);
			switch(k){
				case _bool:
				case _int:
					val->get(&ival);
					b=_geo->setValue(_field,ival);
					break;
				case _double:
				case _date:
				case _time:
					val->get(&dval);
					b=_geo->setValue(_field,dval);
					break;
				case _char:
					val->get(&cval);
					b=_geo->setValue(_field,cval);
					break;
			}
			log.close();
			if(!b){
				NSBeep();
			}
			delete val;
			
			if(FieldInView(_gapp,_gtp,_field)){
				_geo->inval(_field);
			}		
		}
		return YES;
	}
	return NO;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)key:(NSEvent*)evt inView:(NSView*)view{
	[view scrollRectToVisible:_frame];
	
	switch([evt keyCode]){
		case kVK_Tab:
		case kVK_Delete:
		case kVK_Escape:
		case kVK_Home:
		case kVK_PageUp:
		case kVK_ForwardDelete:
		case kVK_End:
		case kVK_PageDown:
		case kVK_LeftArrow:
		case kVK_RightArrow:
		case kVK_DownArrow:
		case kVK_UpArrow:
			return NO;
			break;
	}
	
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)abort{
	return NO;
}

// ---------------------------------------------------------------------------
// 
// -----------
@end


// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFicheCheckBoxCell

// ---------------------------------------------------------------------------
// 
// -----------
-(void)calcFrame:(NSPoint)o{
char	name[512];
int		l,k;
	
	_gtp->fields()->get_name(_field,name);
	_gtp->fields()->get_len(_field,&l);
	_gtp->fields()->get_kind(_field,&k);
	if(k==_ivxs2){
		l=2*_kDoubleLen;
	}
	
{
	bCoreTextInfo	ti(_font, 
					   _font_size, 
					   0, 
					   0, 
					   0, 
					   name);
	_name_area=NSMakeRect(o.x,o.y,ti.textWidth()+6.0,_std_height);
}	
	
	_value_area=NSMakeRect(_name_area.origin.x+_name_area.size.width,_name_area.origin.y,_std_height,_name_area.size.height);
	_frame=NSUnionRect(_name_area,_value_area);
}

// ---------------------------------------------------------------------------
// 
// -----------
- (void)drawRect:(NSRect)rect{	
	if([self current]){
		[_NAMEBACKCOLORHILITED_ set];
	}
	else{
		[_NAMEBACKCOLORNORMAL_ set];
	}

NSBezierPath *path = [NSBezierPath bezierPathWithRoundedRect:_frame xRadius:_RADIUS_ yRadius:_RADIUS_];
    [path fill];
	
	[_VALUEBACKCOLOR_ set];
	path = [NSBezierPath bezierPathWithRoundedRect:_value_area xRadius:_RADIUS_ yRadius:_RADIUS_];
    [path fill];
	
	path = [NSBezierPath bezierPathWithRoundedRect:_frame xRadius:_RADIUS_ yRadius:_RADIUS_];
	[_STROKECOLOR_ setStroke];
	[path setLineWidth:_LINEWIDTH_];
	[path stroke];
	
char		name[256];
NSString*	nstr;
	
	_gtp->fields()->get_name(_field,name);
	nstr=[NSString stringWithCString:name encoding:NSMacOSRomanStringEncoding];
	[nstr drawAtPoint:NSMakePoint(_name_area.origin.x+_XOFFSET_,_name_area.origin.y+_YOFFSET_) withAttributes:_strAttr];
	
int	val;
	_geo->getValue(_field,&val);
	path = [NSBezierPath bezierPathWithOvalInRect:NSInsetRect(_value_area,3.0,3.0)];
	[_STROKECOLOR_ setStroke];
	[path setLineWidth:_LINEWIDTH_];
	[path stroke];		
	if(val){
		path = [NSBezierPath bezierPathWithOvalInRect:NSInsetRect(_value_area,5.0,5.0)];
		[_NAMEBACKCOLORHILITED_ setFill];
		[path fill];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellCheckBoxKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)mouse:(NSEvent*)evt inView:(NSView*)view{
	if(![super mouse:evt inView:view]){
		return NO;
	}
	[self assign];
	[view setNeedsDisplayInRect:_frame];
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)key:(NSEvent*)evt inView:(NSView*)view{
	if(![super key:evt inView:view]){
		return NO;
	}
unsigned short k=[evt keyCode];
	if((k==kVK_Return)||(k==kVK_ANSI_KeypadEnter)){
		[self assign];
		[view setNeedsDisplayInRect:_frame];
	}
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)assign{
int	val;
	_geo->getValue(_field,&val);
	val=!val;
	
	if(FieldInView(_gapp,_gtp,_field)){
		_geo->inval(_field);
	}	
CFBundleRef	bndl=CFBundleGetBundleWithIdentifier(CFSTR("com.cbconseil.xmapfiche"));
bEventLog	log(_gapp,
				bndl,
				kXMapFicheMessageID,
				GetSignatureFromBundle(bndl));	
	_geo->setValue(_field,&val);
	log.close();
	if(FieldInView(_gapp,_gtp,_field)){
		_geo->inval(_field);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
@end

// ---------------------------------------------------------------------------
// Subclasser for keyDown catching
// -----------
@implementation XMapFicheCoordListCellTableView

// ---------------------------------------------------------------------------
// 
// ------------
-(void)keyDown:(NSEvent*)event{	
	if(([event keyCode]!=kVK_Return)&&
	   ([event keyCode]!=kVK_ANSI_KeypadEnter)){
		[super keyDown:event];
	}
	else{
XMapFicheCoordListCell*	cell=[self delegate];
		[cell assign];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
@end

// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFicheCoordListCell

// ---------------------------------------------------------------------------
// 
// -----------
-(id)initWithPoint:(NSPoint)point 
	   application:(bGenericMacMapApp*)gapp 
			  type:(bGenericType*)typ 
			 field:(long)fld{
    if(self=[super initWithPoint:point application:gapp type:typ field:fld]){
		_vxs=NULL;
		_scl=NULL;
		_tbl=NULL;
		_clx=NULL;
		_cly=NULL;
    }
    return self;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)setCurrent:(BOOL)flg{
	[super setCurrent:flg];
	if((flg==NO)&&(_scl!=nil)){
		[self abort];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)drawRect:(NSRect)rect{	
	[super drawRect:rect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellCoordListKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)mouse:(NSEvent*)evt inView:(NSView*)view{
	if(![super mouse:evt inView:view]){
		if(_scl!=NULL){
			[self abort];
		}
		return NO;
	}
	[self editInit:view];
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)rightMouse:(NSEvent*)evt inView:(NSView*)view{
	if(NSPointInRect([view convertPoint:[evt locationInWindow] fromView:nil],_value_area)){
		[view scrollRectToVisible:_frame];
		return YES;
	}
	return NO;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)key:(NSEvent*)evt inView:(NSView*)view{
	_parent=view;
	_responder=[[view window] firstResponder];
	if(_scl){
		switch([evt keyCode]){
			case kVK_Escape:
				[self abort];
				break;
		}
	}
	else{
		if(![super key:evt inView:view]){
			return NO;
		}
		[self editInit:view];		
	}
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)abort{
	if(_scl!=NULL){
		[_scl removeFromSuperview];
		[_scl release];
		[_tbl release];
		[_clx release];
		[_cly release];
		ivs_free(_vxs);
		
		_scl=NULL;
		_tbl=NULL;
		_clx=NULL;
		_cly=NULL;
		_vxs=NULL;

        [((FicheWindowController*)[[_parent window] windowController]) setKeyEquivalent:YES];
		[[_parent window] makeFirstResponder:_responder];

		return YES;
	}
	return NO;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)editInit:(NSView*)view{
    [((FicheWindowController*)[[view window] windowController]) setKeyEquivalent:NO];
	_parent=view;
	_responder=[[view window] firstResponder];
	
	if(_scl==NULL){
		if(_field==kOBJ_Vertices_){
			_geo->getVertices(&_vxs);
			ivs2ivs(_vxs,&_vxs);
		}
		else{
			_geo->getValue(_field,&_vxs);
		}
		
NSRect	bnds=_value_area;
		bnds.size.height+=100;
		if(bnds.size.width>400){
			bnds.size.width=400;
		}
		
// create a table view and a scroll view
		_scl=[[NSScrollView alloc] initWithFrame:bnds];
		bnds.size.height-=16;
		bnds.origin.x=bnds.origin.y=0;
		bnds=NSInsetRect(bnds,2.0,2.0);
		
		_tbl=[[XMapFicheCoordListCellTableView alloc] initWithFrame:bnds];
// create columns for our table
		_clx=[[NSTableColumn alloc] initWithIdentifier:@"X"];
		_cly=[[NSTableColumn alloc] initWithIdentifier:@"Y"];

CGFloat	wdt=(bnds.size.width-16)/2.0;
		
		[_clx setWidth:wdt];
		[_clx setMinWidth:wdt];
		[_clx setMaxWidth:wdt];
		
		[_cly setWidth:wdt];
		[_cly setMinWidth:wdt];
		[_cly setMaxWidth:wdt];
		
// generally you want to add at least one column to the table view.
		[_tbl addTableColumn:_clx];
		[_tbl addTableColumn:_cly];
		[_tbl setDelegate:self];
		[_tbl setDataSource:self];
		[_tbl reloadData];
		
// embed the table view in the scroll view, and add the scroll view
// to our window.
		[_scl setDocumentView:_tbl];
		[_scl setHasVerticalScroller:YES];
		[view addSubview:_scl];
		
		[[view window] makeFirstResponder:_tbl];

		[[_clx headerCell] setStringValue:@"X"];
		[[_cly headerCell] setStringValue:@"Y"];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)assign{
	if(FieldInView(_gapp,_gtp,_field)){
		_geo->inval(_field);
	}		
CFBundleRef	bndl=CFBundleGetBundleWithIdentifier(CFSTR("com.cbconseil.xmapfiche"));
bEventLog	log(_gapp,
				bndl,
				kXMapFicheMessageID,
				GetSignatureFromBundle(bndl));
	if((_gtp->kind()==kBaseKindPolygon)	||
	   (_gtp->kind()==kBaseKindRaster)	){
		ivs_closegeom(_vxs);
	}
	if(_field==kOBJ_Vertices_){
		_geo->setVertices(_vxs);
	}
	else{
		_geo->setValue(_field,&_vxs);
	}
	log.close();
	[self abort];
	if(FieldInView(_gapp,_gtp,_field)){
		_geo->inval(_field);
	}		
}

// ---------------------------------------------------------------------------
// 
// -----------
-(NSInteger)numberOfRowsInTableView:(NSTableView*)aTableView{
	if(_vxs){
		return _vxs->nv;
	}
	return 0;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(id)			tableView:(NSTableView*)aTableView 
objectValueForTableColumn:(NSTableColumn*)aTableColumn 
					row:(NSInteger)rowIndex{
NSString*	identifier=[aTableColumn identifier];
NSString*	value;
d2dvertex	vx;
	
	if(_vxs){
		_gapp->locConverter()->convert(&vx,&_vxs->vx.vx2[rowIndex]);
		if(identifier==@"X"){
			value=[[NSString alloc] initWithFormat:@"%.*f",_gapp->document()->dist_pref_digits(),vx.x];		
		}
		else if(identifier==@"Y"){
			value=[[NSString alloc] initWithFormat:@"%.*f",_gapp->document()->dist_pref_digits(),vx.y];				
		}
		else{
			value=@"####";
		}
	}
	else{
		value=@"????";
	}
	return value;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)	tableView:(NSTableView *)aTableView
   setObjectValue:(id)anObject
   forTableColumn:(NSTableColumn*)aTableColumn
			  row:(NSInteger)rowIndex{
NSString*	identifier=[aTableColumn identifier];
d2dvertex	vx;

	if(_vxs){
		_gapp->locConverter()->convert(&vx,&_vxs->vx.vx2[rowIndex]);
		if(identifier==@"X"){
			vx.x=[anObject doubleValue];		
		}
		else if(identifier==@"Y"){
			vx.y=[anObject doubleValue];		
		}
		_gapp->locConverter()->convert(&_vxs->vx.vx2[rowIndex],&vx);
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
@end

// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFicheEditTextCell

// ---------------------------------------------------------------------------
// 
// -----------
-(id)initWithPoint:(NSPoint)point 
	   application:(bGenericMacMapApp*)gapp 
			  type:(bGenericType*)typ 
			 field:(long)fld{
    if(self=[super initWithPoint:point application:gapp type:typ field:fld]){
		_fld=NULL;
    }
    return self;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)setCurrent:(BOOL)flg{
	[super setCurrent:flg];
	if((flg==NO)&&(_fld!=nil)){
		[self abort];
	}
}

// ---------------------------------------------------------------------------
// 
// -----------
- (void)drawRect:(NSRect)rect{	
	[super drawRect:rect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellEditKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)mouse:(NSEvent*)evt 
	  inView:(NSView*)view{
	_parent=view;
    _responder=[[view window] firstResponder];
	if(![super mouse:evt inView:view]){
		if(_fld!=NULL){
//			[_fld removeFromSuperview];
//			[_fld release];
			[self assign:self];
			_fld=NULL;
		}
		return NO;
	}
	[self editInit:view];
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)key:(NSEvent*)evt inView:(NSView*)view{
	_parent=view;
	_responder=[[view window] firstResponder];
	if(![super key:evt inView:view]){
		return NO;
	}
	[self editInit:view];
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)abort{
	if(_fld!=NULL){
		[_fld removeFromSuperview];
		[_fld release];
		_fld=NULL;

        [((FicheWindowController*)[[_parent window] windowController]) setKeyEquivalent:YES];
		[[_parent window] makeFirstResponder:_responder];
		return YES;
	}
	return NO;
}

// ---------------------------------------------------------------------------
// 
// ------------
-(void)editInit:(NSView*)view{
    [((FicheWindowController*)[[view window] windowController]) setKeyEquivalent:NO];
	_parent=view;
	_responder=[[view window] firstResponder];
	if(_fld==NULL){
NSRect	frame=NSInsetRect(_value_area,-3.0,-3.0);
		if(frame.size.width>300){
			frame.size.width=300;
		}
		_fld=[[NSTextField alloc] initWithFrame:frame];
		[view addSubview:_fld];
		[[view window] makeFirstResponder:_fld];
		[_fld setTarget:self];
		[_fld setAction:@selector(assign:)];

char	str[1024]="";
		_geo->getValue(_field,str);
		[_fld setCharValue:str];
	}
}

// ---------------------------------------------------------------------------
// 
// ------------
-(IBAction)assign:(id)sender{
	if(FieldInView(_gapp,_gtp,_field)){
		_geo->inval(_field);
	}		
char			str[1024]="";
NSString*		nsstr=[_fld stringValue];
	[nsstr getCString:str maxLength:sizeof(str)-1 encoding:NSMacOSRomanStringEncoding];
CFBundleRef	bndl=CFBundleGetBundleWithIdentifier(CFSTR("com.cbconseil.xmapfiche"));
bEventLog	log(_gapp,
				bndl,
				kXMapFicheMessageID,
				GetSignatureFromBundle(bndl));
	_geo->setValue(_field,str);
	log.close();
	[_fld removeFromSuperview];
	[_fld release];
	_fld=NULL;
    [((FicheWindowController*)[[_parent window] windowController]) setKeyEquivalent:YES];
	[[_parent window] makeFirstResponder:_responder];
//    [[_parent window] makeKeyAndOrderFront:_parent];
	if(FieldInView(_gapp,_gtp,_field)){
		_geo->inval(_field);
	}		
}

// ---------------------------------------------------------------------------
// 
// -----------
@end


// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFichePopupCell

// ---------------------------------------------------------------------------
// 
// -----------
- (void)drawRect:(NSRect)rect{	
	[super drawRect:rect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellPopupKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)mouse:(NSEvent*)evt inView:(NSView*)view{
	if(![super mouse:evt inView:view]){
		return NO;
	}
	[self pop:view];
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)key:(NSEvent*)evt inView:(NSView*)view{
	if(![super key:evt inView:view]){
		return NO;
	}
	[self pop:view];
	return YES;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(void)pop:(NSView*)view{
long			i,idx,n=_gtp->fields()->count_constraints(_field);
menuitem_desc*	desc=new menuitem_desc[n];
int				k,d,ck,fk;
char			cval[256];
int				ival;
double			dval;
	
	_gtp->fields()->get_kind(_field,&k);
	_gtp->fields()->get_decs(_field,&d);
	ck=_gtp->fields()->get_constraints_kind(_field);
	fk=k;
	if((ck!=k)&&(ck!=_bit)){
		k=_char;
	}
	else if((ck!=k)&&(ck==_bit)){
		k=_bit;
	}
	
	switch(k){
		case _bool:
		case _int:
			_geo->getValue(_field,&ival);
			idx=_gtp->fields()->get_constraint_index(_field,&ival);
			for(i=1;i<=n;i++){
				_gtp->fields()->get_constraint(_field,i,&ival);
				sprintf(desc[i-1].name," %d",ival);	
				desc[i-1].checked=(i==idx);
				desc[i-1].disabled=false;
                desc[i-1].index=0;
			}
			break;
		case _double:
			_geo->getValue(_field,&dval);
			idx=_gtp->fields()->get_constraint_index(_field,&dval);
			for(i=1;i<=n;i++){
				_gtp->fields()->get_constraint(_field,i,&dval);
				sprintf(desc[i-1].name," %.*f",d,dval);
				desc[i-1].checked=(i==idx);
				desc[i-1].disabled=false;
                desc[i-1].index=0;
			}
			break;
		case _char:
			_geo->getValue(_field,cval);
			idx=_gtp->fields()->get_constraint_index(_field,cval);
			for(i=1;i<=n;i++){
				_gtp->fields()->get_constraint(_field,i,desc[i-1].name);
				desc[i-1].checked=(i==idx);
				desc[i-1].disabled=false;
                desc[i-1].index=0;
			}
			break;
		case _bit:
			if(fk==_char){
				_geo->getValue(_field,cval);
				if(strlen(cval)<n){
					for(int j=strlen(cval);j<n;j++){
						strcat(cval,"0");
					}				
				}
				for(i=1;i<=n;i++){
					_gtp->fields()->get_constraint(_field,i,desc[i-1].name);
					desc[i-1].checked=(cval[i-1]!='0');
					desc[i-1].disabled=false;
                    desc[i-1].index=0;
				}
			}
			else if(fk==_int){
				_geo->getValue(_field,&ival);
				for(i=1;i<=n;i++){
					_gtp->fields()->get_constraint(_field,i,desc[i-1].name);
					desc[i-1].checked=btst(ival,i-1);
					desc[i-1].disabled=false;
                    desc[i-1].index=0;
				}
			}
			break;
	}
	
CGPoint	location=NSPointToCGPoint([view convertPointToBase:_value_area.origin]);
	
long which=popUpContextMenuWithCGPointAndNSWindow(location,
												  [view window],
												  desc,
												  n);
	delete desc;
	
	if(which>0){
bool b;	
		if(FieldInView(_gapp,_gtp,_field)){
			_geo->inval(_field);
		}		
CFBundleRef	bndl=CFBundleGetBundleWithIdentifier(CFSTR("com.cbconseil.xmapfiche"));
bEventLog	log(_gapp,
				bndl,
				kXMapFicheMessageID,
				GetSignatureFromBundle(bndl));
		if(ck!=fk){
			if(ck==_bit){
				if(fk==_int){
					_geo->getValue(_field,&ival);
					if(btst(ival,which-1)){
						bclr(ival,which-1);
					}
					else{
						bset(ival,which-1);
					}
					b=_geo->setValue(_field,ival);
				}
				else if(fk==_char){
					_geo->getValue(_field,cval);
					if(strlen(cval)<n){
						for(int j=strlen(cval);j<n;j++){
							strcat(cval,"0");
						}
					}
					if(cval[which-1]=='0'){
						cval[which-1]='1';
					}
					else{
						cval[which-1]='0';
					}
					b=_geo->setValue(_field,cval);				
				}				
			}
			else{
				b=_geo->setValue(_field,(int)which);
			}
		}
		else switch(ck){
			case _bool:
			case _int:
				_gtp->fields()->get_constraint(_field,which,&ival);
				b=_geo->setValue(_field,ival);
				break;
			case _double:
			case _date:
			case _time:
				_gtp->fields()->get_constraint(_field,which,&dval);
				b=_geo->setValue(_field,dval);
				break;
			case _char:
				_gtp->fields()->get_constraint(_field,which,cval);
				b=_geo->setValue(_field,cval);
				break;
		}
		if(!b){
			NSBeep();
		}
		else{
			[view setNeedsDisplayInRect:_frame];
		}
		log.close();
		if(FieldInView(_gapp,_gtp,_field)){
			_geo->inval(_field);
		}		
	}	
}

// ---------------------------------------------------------------------------
// 
// -----------
@end


// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFicheStaticTextCell

// ---------------------------------------------------------------------------
// 
// -----------
- (void)drawRect:(NSRect)rect{	
	[super drawRect:rect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellStaticKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
-(BOOL)rightMouse:(NSEvent*)evt inView:(NSView*)view{
	if(NSPointInRect([view convertPoint:[evt locationInWindow] fromView:nil],_value_area)){
		[view scrollRectToVisible:_frame];
		return YES;
	}
	return NO;
}

// ---------------------------------------------------------------------------
// 
// -----------
@end


// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFicheListCell

// ---------------------------------------------------------------------------
// 
// -----------
- (void)drawRect:(NSRect)rect{	
	[super drawRect:rect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellListKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
@end


// ---------------------------------------------------------------------------
// 
// -----------
@implementation XMapFicheImageCell

// ---------------------------------------------------------------------------
// 
// -----------
- (void)drawRect:(NSRect)rect{	
	[super drawRect:rect];
}

// ---------------------------------------------------------------------------
// 
// -----------
-(long)kind{
	return kCellImageKind;
}

// ---------------------------------------------------------------------------
// 
// -----------
@end

