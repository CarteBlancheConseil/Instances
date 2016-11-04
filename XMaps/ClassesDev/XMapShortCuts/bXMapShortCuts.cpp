//----------------------------------------------------------------------------
// File : bXMapShortCuts.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, shortcuts management
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
// 15/03/2010 creation.
// 29/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapShortCuts.h"
#include "CocoaStuff.h"

#include <mox_intf/ext_utils.h>
#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/Carb_Utils.h>
#include <mox_intf/endian.h>

#include <std_ext/bStdUserExt.h>

#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
//
// -----------
static int comp_shortcutkey(const void* a, const void* b){
//_bTrace_("comp_shortcutkey",false);
shortcut_prm* ga=(shortcut_prm*)a;
shortcut_prm* gb=(shortcut_prm*)b;

//_tm_("("+(int)ga->modi+";"+(int)ga->key+")>("+(int)gb->modi+";"+(int)gb->key+")");
    if(ga->modi>gb->modi){
        return(1);
    }
    if(ga->modi<gb->modi){
        return(-1);
    }
    
    if(ga->key>gb->key){
        return(1);
    }
    if(ga->key<gb->key){
        return(-1);
    }
    
    return(0);
}

// ---------------------------------------------------------------------------
//
// -----------
static int comp_shortcutcode(const void* a, const void* b){
//_bTrace_("comp_shortcutcode",false);
shortcut_prm* ga=(shortcut_prm*)a;
shortcut_prm* gb=(shortcut_prm*)b;
    
//_tm_("("+(int)ga->modi+";"+ga->code+")>("+(int)gb->modi+";"+gb->code+")");
    if(ga->modi>gb->modi){
        return(1);
    }
    if(ga->modi<gb->modi){
        return(-1);
    }
    
    if(ga->code>gb->code){
        return(1);
    }
    if(ga->code<gb->code){
        return(-1);
    }
    
    return(0);
}

// ---------------------------------------------------------------------------
//
// -----------
static int comp_shortcutxtrn(const void* a, const void* b){
shortcut_prm* ga=(shortcut_prm*)a;
shortcut_prm* gb=(shortcut_prm*)b;
    
    if(ga->xtrn>gb->xtrn){
        return(1);
    }
    if(ga->xtrn<gb->xtrn){
        return(-1);
    }
    
    return(0);
}

// ---------------------------------------------------------------------------
//
// -----------
static int comp_shortcutname(const void* a, const void* b){
shortcut_prm* ga=(shortcut_prm*)a;
shortcut_prm* gb=(shortcut_prm*)b;
    return(strcmp(ga->name,gb->name));
}


// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapShortCuts  ::bXMapShortCuts(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                : bStdXMap(elt,gapp,bndl)
                ,_xmap(sizeof(shortcut_prm))
                ,_xbox(sizeof(shortcut_prm))
                ,_macr(sizeof(shortcut_prm))
                ,_scrp(sizeof(shortcut_prm)){
	setclassname("shortcuts");
    set_flags(kXMapNeedIdle+kXMapNeedEvents);
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapShortCuts::~bXMapShortCuts(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapShortCuts::create(bGenericXMLBaseElement* elt){
	return(new bXMapShortCuts(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapShortCuts::open(int* flags){
    bStdXMap::open(flags);
    _call=0;
    _first=false;
// read params
    read_p();
// parse menus shortcuts
    scan_read_menu(AcquireRootMenu());
// write menus shortcuts
    scan_write_menu(AcquireRootMenu());
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapShortCuts::event(EventRef evt){
bool	res=false;
    if(!_first){
// Don't use events before init
        return(false);
    }
    
UInt32			clss=GetEventClass(evt);
UInt32			kind=GetEventKind(evt);
UInt32			modi;
UInt32			key;
UInt32			xtrn;
bool			inmenu;
bArray*			arr;
bGenericEvent*	mevt;
bGenericExt*	ext;
bArray*			exts;
bGenericExtMgr*	mgr;
user_ext_data	edt;
    
    if(clss==kEventClassMacMap){
        switch(kind){
            case kEventMacMapDataBase:
                arr=_gapp->eventMgr()->events();
                for(long i=1;i<=arr->count();i++){
                    arr->get(i,&mevt);
                    if(mevt->kind()!=kEventKindUserExt){
                        continue;
                    }
                    
                    for(int j=1;j<=mevt->elements()->count();j++){
                        mevt->elements()->get(j,&ext);
                        if(ext->getsubclass()==kXMLSubClassExtMacro){
                            exts=&_macr;
                            mgr=_gapp->macroMgr();
                            ext->process(kExtProcessCallGetData,&edt);
                        }
                        else if(ext->getsubclass()==kXMLSubClassExtScript){
                            exts=&_scrp;
                            mgr=_gapp->scriptMgr();
                            ext->process(kExtProcessCallGetData,&edt);
                        }
                        else{
                            continue;
                        }
                        
                        switch(mevt->action()){
                            case kEventActionCreate:
                                add_ext(*exts,mgr,edt.sign);
                                break;
                            case kEventActionModify:
                                modify_ext(*exts,mgr,edt.sign);
                                break;
                            case kEventActionDestroy:
                                remove_ext(*exts,mgr,edt.sign);
                                break;
                        }
                    }
                    
                }
                break;
            default:
                break;
        }
    }
    else if(clss==kEventClassKeyboard){
        switch(kind){
            case kEventRawKeyDown:
                GetEventParameter(evt,kEventParamKeyCode,typeUInt32,NULL,sizeof(UInt32),NULL,&key);
                GetEventParameter(evt,kEventParamKeyModifiers,typeUInt32,NULL,sizeof(UInt32),NULL,&modi);
                xtrn=scan_array(_xmap,0,key,modi,&inmenu);
                if((xtrn)&&(!inmenu)){
                    _call=xtrn;
                    break;
                }
                xtrn=scan_array(_xbox,0,key,modi,&inmenu);
                if((xtrn)&&(!inmenu)){
                    _call=xtrn;
                    break;
                }
                xtrn=scan_array(_scrp,0,key,modi,&inmenu);
                if((xtrn)&&(!inmenu)){
                    _call=xtrn;
                    break;
                }
                xtrn=scan_array(_macr,0,key,modi,&inmenu);
                if((xtrn)&&(!inmenu)){
                    _call=xtrn;
                    break;
                }
                break;
            default:
                break;
        }
    }
    return(res);
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapShortCuts::idle(void* prm){
    if(_first){
// Inited
        if(_call!=0){
            SendCommandToApplication(_call);
            _call=0;
        }
        return;
    }
    
// Init, must be done at first idle call after loading plugins
bArray	xmap(_xmap);
bArray	xbox(_xbox);
bArray	scrp(_scrp);
bArray	macr(_macr);
    
    _xmap.reset();
    _xbox.reset();
    _scrp.reset();
    _macr.reset();
    
    xmap.sort(comp_shortcutxtrn);
    xbox.sort(comp_shortcutxtrn);
    scrp.sort(comp_shortcutxtrn);
    macr.sort(comp_shortcutxtrn);
    
    _first=true;
int			k;
    for(long i=1;i<=_gapp->xmapMgr()->count();i++){
shortcut_prm	p={0,0,0,0,false};
        p.xtrn=_gapp->xmapMgr()->ext_signature(i);
        k=xmap.search(&p,comp_shortcutxtrn);
        if(k){
            xmap.get(k,&p);
        }
        _gapp->xmapMgr()->ext_name(i,p.name);
        _xmap.add(&p);
    }
    for(long i=1;i<=_gapp->xboxMgr()->count();i++){
shortcut_prm	p={0,0,0,0,false};
        p.xtrn=_gapp->xboxMgr()->ext_signature(i);
        k=xbox.search(&p,comp_shortcutxtrn);
        if(k){
            xbox.get(k,&p);
        }
        _gapp->xboxMgr()->ext_name(i,p.name);
        _xbox.add(&p);
    }
    for(long i=1;i<=_gapp->scriptMgr()->count();i++){
shortcut_prm	p={0,0,0,0,false};
        p.xtrn=_gapp->scriptMgr()->ext_signature(i);
        k=scrp.search(&p,comp_shortcutxtrn);
        if(k){
            scrp.get(k,&p);
        }
        _gapp->scriptMgr()->ext_name(i,p.name);
        _scrp.add(&p);
    }
    for(long i=1;i<=_gapp->macroMgr()->count();i++){
shortcut_prm	p={0,0,0,0,false};
        p.xtrn=_gapp->macroMgr()->ext_signature(i);
        k=macr.search(&p,comp_shortcutxtrn);
        if(k){
            macr.get(k,&p);
        }
        _gapp->macroMgr()->ext_name(i,p.name);
        _macr.add(&p);
    }
    
    _xmap.sort(comp_shortcutkey);
    _xbox.sort(comp_shortcutkey);
    _scrp.sort(comp_shortcutkey);
    _macr.sort(comp_shortcutkey);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapShortCuts::process(int msg, void* prm){
_bTrace_("bXMapShortCuts::process()",true);
shortcut_prm*	p;
int				k;
    
    switch(msg){
        case kExtProcessCallFromIntf:
            // Done in edit
            break;
        case kExtProcessCallWithParams:			
            // Not necessary
            break;
        case kExtProcessCallWithXMLTree:
            // Not necessary
            break;
        case kExtProcessCallGetData:
            p=(shortcut_prm*)prm;
            _xmap.setsorted(false);
            k=_xmap.search(p,comp_shortcutxtrn);
            if(k){
                _xmap.get(k,p);
                _xmap.setsorted(true);
                break;
            }
            _xbox.setsorted(false);
            k=_xbox.search(p,comp_shortcutxtrn);
            if(k){
                _xbox.get(k,p);
                _xbox.setsorted(true);
                break;
            }
            _scrp.setsorted(false);
            k=_scrp.search(p,comp_shortcutxtrn);
            if(k){
                _scrp.get(k,p);
                _scrp.setsorted(true);
                break;
            }
            _macr.setsorted(false);
            k=_macr.search(p,comp_shortcutxtrn);
            if(k){
                _macr.get(k,p);
                _macr.setsorted(true);
                break;
            }
            break;
        case kExtProcessCallSetData:			
            // Pas autorisé
            break;
        default:
            break;
    }	
    return(true);
}

// ---------------------------------------------------------------------------
// 
// -----------
bool bXMapShortCuts::edit(void* prm){
_bTrace_("bXMapShortCuts::edit()",true);
long    result=0;
    
    _xmap.sort(comp_shortcutname);
    _xbox.sort(comp_shortcutname);
    _scrp.sort(comp_shortcutname);
    _macr.sort(comp_shortcutname);
    
    _xmap.setsorted(false);
    _xbox.setsorted(false);
    _scrp.setsorted(false);
    _macr.setsorted(false);
    
    runCocoaAppModal(this,&result);

    if(result>0){
        _xmap.sort(comp_shortcutkey);
        _xbox.sort(comp_shortcutkey);
        _scrp.sort(comp_shortcutkey);
        _macr.sort(comp_shortcutkey);
        write_p();
        scan_write_menu(AcquireRootMenu());
    }
    else{
// User canceled, reload from params and menus
        _xmap.reset();
        _xbox.reset();
        _scrp.reset();
        _macr.reset();
        read_p();
        scan_read_menu(AcquireRootMenu());
        _first=false;
    }
    return(process(kExtProcessCallFromIntf,prm));
}

// ---------------------------------------------------------------------------
//
// -----------
void bXMapShortCuts::scan_read_menu(MenuRef mnu){
MenuRef			chld;
shortcut_prm	p={0,0,0,0,true};
UInt8			ui8;
UInt16			ui16;
int				k;
    
    for(MenuItemIndex i=1;i<=CountMenuItems(mnu);i++){
        GetMenuItemHierarchicalMenu(mnu,i,&chld);
        if(chld){
            scan_read_menu(chld);
        }
        else{
            GetMenuItemCommandID(mnu,i,&p.xtrn);
            if(p.xtrn==0){
                continue;
            }
            k=_xmap.search(&p,comp_shortcutxtrn);
            if(!k){
                k=_xbox.search(&p,comp_shortcutxtrn);
            }
            if(!k){
                k=_macr.search(&p,comp_shortcutxtrn);
            }
            if(!k){
                k=_scrp.search(&p,comp_shortcutxtrn);
            }
            
            if(!k){
                GetMenuItemCommandKey(mnu,i,true,&ui16);
                p.key=ui16;
                GetMenuItemCommandKey(mnu,i,false,&ui16);
                p.code=ui16;
                GetMenuItemModifiers(mnu,i,&ui8);
                p.modi=0;
                if(ui8&kMenuShiftModifier){
                    p.modi|=shiftKey;
                }
                if(ui8&kMenuControlModifier){
                    p.modi|=controlKey;
                }
                if(ui8&kMenuOptionModifier){
                    p.modi|=optionKey;
                }
                if(!(ui8&kMenuNoCommandModifier)){
                    p.modi|=cmdKey;
                }
                
                if(	((p.modi)&&(p.key))		||
                    ((p.modi)&&(p.code))	){
                    if(_gapp->xmapMgr()->ext_index(p.xtrn)){
#ifdef __LITTLE_ENDIAN__
                        LBSwapWord(&p.xtrn,sizeof(UInt32));
#endif
                        _xmap.add(&p);
                    }
                    else if(_gapp->xboxMgr()->ext_index(p.xtrn)){
#ifdef __LITTLE_ENDIAN__
                        LBSwapWord(&p.xtrn,sizeof(UInt32));
#endif
                        _xbox.add(&p);
                    }
                    else if(_gapp->scriptMgr()->ext_index(p.xtrn)){
#ifdef __LITTLE_ENDIAN__
                        LBSwapWord(&p.xtrn,sizeof(UInt32));
#endif
                        _scrp.add(&p);
                    }
                    else if(_gapp->macroMgr()->ext_index(p.xtrn)){
#ifdef __LITTLE_ENDIAN__
                        LBSwapWord(&p.xtrn,sizeof(UInt32));
#endif
                        _macr.add(&p);
                    }
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// => Pb : don't work
// -----------
void bXMapShortCuts::scan_write_menu(MenuRef mnu){
MenuRef		chld;
UInt8		ui8;
UInt16		ui16;
int			k;
bArray*		arr=NULL;
    
    for(MenuItemIndex i=1;i<=CountMenuItems(mnu);i++){
        GetMenuItemHierarchicalMenu(mnu,i,&chld);
        if(chld){
            scan_write_menu(chld);
        }
        else{
            shortcut_prm	p={0,0,0,0,false};
            GetMenuItemCommandID(mnu,i,&p.xtrn);
            if(p.xtrn==0){
                continue;
            }
            
#ifdef __LITTLE_ENDIAN__
            LBSwapWord(&p.xtrn,sizeof(UInt32));
#endif
            k=_xmap.search(&p,comp_shortcutxtrn);
            if(!k){
                k=_xbox.search(&p,comp_shortcutxtrn);
                if(!k){
                    k=_macr.search(&p,comp_shortcutxtrn);
                    if(!k){
                        k=_scrp.search(&p,comp_shortcutxtrn);
                        if(k){
                            arr=&_scrp;
                        }
                    }
                    else{
                        arr=&_macr;
                    }
                }
                else{
                    arr=&_xbox;
                }
            }
            else{
                arr=&_xmap;
            }
            
            if(!arr){
                continue;
            }
            
            arr->get(k,&p);
            
            if(p.inmenu){
                continue;
            }
            
            if(	((p.modi)&&(p.key))		||
                ((p.modi)&&(p.code))	){
                //ui16=p.key;
                //SetMenuItemCommandKey(mnu,i,true,ui16);
                ui16=p.code;
                SetMenuItemCommandKey(mnu,i,false,ui16);
                ui8=0;
                
                if((p.modi&shiftKey)!=0){
                    ui8|=kMenuShiftModifier;
                }
                if((p.modi&controlKey)!=0){
                    ui8|=kMenuControlModifier;
                }
                if((p.modi&optionKey)!=0){
                    ui8|=optionKey;
                }
                if(!((p.modi&cmdKey)!=0)){
                    ui8|=kMenuNoCommandModifier;
                }
                
                SetMenuItemModifiers(mnu,i,ui8);
            }
            
        }
    }
}

// ---------------------------------------------------------------------------
// 
// -----------
UInt32 bXMapShortCuts::scan_array(bArray& arr, char code, UInt32 key, UInt32 modi, bool* inmenu){
//_bTrace_("bXMapShortCuts::scan_array",true);
//_tm_((int)key+":"+(int)modi);
//
shortcut_prm	p;
    p.key=key;
    p.code=code;
    p.modi=modi;
    p.xtrn=-1;
    (*inmenu)=false;
    
long	k=0;
    if(code!=0){
        k=arr.search(&p,comp_shortcutcode);
    }
    if(k<=0){
        k=arr.search(&p,comp_shortcutkey);
    }
    if(k){
        arr.get(k,&p);
        (*inmenu)=p.inmenu;
#ifdef __LITTLE_ENDIAN__
        LBSwapWord(&p.xtrn,sizeof(UInt32));
#endif
    }
    else{
//_tw_("not found");
        p.xtrn=0;
    }
//_tm_("inmenu="+(*inmenu));
    
    return(p.xtrn);
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapShortCuts::read_p(){
    read_p("xmaps",_xmap);
    read_p("xmapboxes",_xbox);
    read_p("scripts",_scrp);
    read_p("macros",_macr);
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapShortCuts::write_p(){
    write_p("xmaps",_xmap);
    write_p("xmapboxes",_xbox);
    write_p("scripts",_scrp);
    write_p("macros",_macr);
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapShortCuts::read_p(const char* name, bArray& arr){
_bTrace_("bXMapShortCuts::read_p",false);
UInt32					sign=GetSignature(this);
bGenericXMLBaseElement* root=NULL;
bGenericXMLBaseElement* elt=NULL;
bGenericXMLBaseElement* chld=NULL;
bool					b=_gapp->document()->readTree(&root,sign,(char*)name);
char					val[_values_length_max_];
shortcut_prm			shrt;
    
    if((!b)||(!root)){
        write_p(name,arr);
        return;
    }
    if((!b)||(!root)){
_tw_("((!b)||(!root)) for "+name);
        return;
    }
    
    for(long i=2;i<=root->countelements();i++){
        elt=root->getelement(i);
        
        chld=elt->getelement(1);
        chld->getvalue(val);
        shrt.xtrn=(*(UInt32*)val);
        
        chld=elt->getelement(2);
        chld->getvalue(val);
        shrt.modi=atoi(val);
        
        chld=elt->getelement(3);
        chld->getvalue(val);
        shrt.key=atoi(val);
        
        chld=elt->getelement(4);
        chld->getvalue(val);
        shrt.code=val[0];
        
        shrt.inmenu=false;
        
        arr.add(&shrt);
    }
    _gapp->classMgr()->ReleaseXMLInstance(root);
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapShortCuts::write_p(const char* name, bArray& arr){
bGenericXMLBaseElement* root=make_p(arr);
    if(!root){
        return;
    }
UInt32	sign=GetSignature(this);
    if(!_gapp->document()->writeTree(root,sign,(char*)name)){
        return;
    }
    _gapp->classMgr()->ReleaseXMLInstance(root);
}

// ---------------------------------------------------------------------------
//
// ------------
bGenericXMLBaseElement* bXMapShortCuts::make_p(bArray& arr){
bArray			xml(sizeof(xmlelt));
char			val[_values_length_max_];
shortcut_prm	shrt;
    
    add_cdesc(xml,0,"param","");
    add_cdesc(xml,1,"version","3.0.0");
    for(long i=1;i<=arr.count();i++){
        arr.get(i,&shrt);
        if((!shrt.inmenu)&&(shrt.key)){
            add_cdesc(xml,1,"param","");
            sprintf(val,"%.4s",(char*)&shrt.xtrn);
            add_cdesc(xml,2,"sign",val);
            add_idesc(xml,2,"int",shrt.modi);
            add_idesc(xml,2,"int",shrt.key);
            val[1]=0;
            val[0]=shrt.code;
            add_cdesc(xml,2,"string",val);
        }
    }
bGenericXMLBaseElement*	root=_gapp->classMgr()->ParseXMLDescriptors(&xml);
    free_descs(xml);
    return(root);
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapShortCuts::add_ext(bArray& arr,
                             bGenericExtMgr* mgr,
                             UInt32 sgn){
shortcut_prm	p={sgn,0,0,0,false,""};
#ifdef __LITTLE_ENDIAN__
    LBSwapWord(&sgn,sizeof(UInt32));
#endif
int			k=mgr->ext_index(sgn);
#ifdef __LITTLE_ENDIAN__
    LBSwapWord(&sgn,sizeof(UInt32));
#endif
    if(k){
        mgr->ext_name(k,p.name);
        arr.add(&p);
        arr.sort(comp_shortcutxtrn);
    }
}

// ---------------------------------------------------------------------------
//
// ------------
void bXMapShortCuts::modify_ext(bArray& arr,
                                bGenericExtMgr* mgr,
                                UInt32 sgn){
shortcut_prm    p={sgn,0,0,0,false};
long            k=arr.search(&p,comp_shortcutxtrn);
    if(k){
        arr.get(k,&p);
        mgr->ext_name(k,p.name);
        arr.put(k,&p);
        arr.setsorted(true);
    }	
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapShortCuts::remove_ext(bArray& arr,
                                bGenericExtMgr* mgr,
                                UInt32 sgn){
shortcut_prm	p={sgn,0,0,0,false};
long            k=arr.search(&p,comp_shortcutxtrn);
    if(k){
        arr.rmv(k);
        arr.setsorted(true);
    }	
}
