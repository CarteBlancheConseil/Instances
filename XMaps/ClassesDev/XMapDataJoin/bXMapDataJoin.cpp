//----------------------------------------------------------------------------
// File : bXMapDataJoin.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, data join from DBF, text, csv, ... file
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
// 29/06/2006 creation.
// 11/02/2015 NAV to NS transformation.
// 03/03/2016 Cocoa Intf.
//----------------------------------------------------------------------------

#include "bXMapDataJoin.h"
#include "CocoaStuff.h"

#include <mox_intf/bEventLog.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/mm_errors.h>
#include <mox_intf/bStdAlert.h>
#include <mox_intf/NSOpenSavePanelWrappers.h>

#include <MacMapSuite/MacMapSuiteCPP.h>

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapDataJoin	::bXMapDataJoin(bGenericXMLBaseElement* elt, 
								bGenericMacMapApp* gapp, 
								CFBundleRef bndl) 
				:bStdXMap(elt,gapp,bndl)
				,_cols(sizeof(datajoin_act)){
	setclassname("datajoin2");
                    
char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapDataJoin::~bXMapDataJoin(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapDataJoin::create(bGenericXMLBaseElement* elt){
	return(new bXMapDataJoin(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
// 
// ------------
void bXMapDataJoin::open(int* flags){
	bStdXMap::open(flags);
	_tpi=1;
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapDataJoin::test(void* prm){
    return(_gapp->typesMgr()->count()>0);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapDataJoin::process(int msg, void* prm){
	switch(msg){
		case kExtProcessCallFromIntf:
            join(false);
			break;
		case kExtProcessCallWithParams:
			break;
		case kExtProcessCallWithXMLTree:
			break;
		default:
			break;
	}
	return(true);
}

// ---------------------------------------------------------------------------
// 
// ------------
bool bXMapDataJoin::edit(void* prm){
_bTrace_("bXMapDataJoin::edit",false);
int             status;
char            name[FILENAME_MAX];
char            ext[FILENAME_MAX];
char            path[SHRT_MAX];
char            msg[__MESSAGE_STRING_LENGTH_MAX__];
const char*		nsft[4]={"TXT","CSV","DBF","MMT"};
const char**	pnsft=nsft;
    
    if(NSGetFilePath(pnsft,
                     4,
                     cNSUTF8StringEncoding,
                     false,
                     NULL,
                     path)==cNSCancelButton){
_te_("user canceled");
        return(true);
    }
    splitPath(path,path,name);
char	*bf=strrchr(name,'.');
    if(bf){
        bf++;
        strcpy(ext,bf);
    }
int	sign=ext2sign(ext);
_tm_(path);
_tm_(name);
_tm_(ext);
_tm_(sign);
    
    if(sign==0){
_te_("unsupported format");
        b_error_string(error_num(0,kXMapDataJoinUnsupportedFormatErr),msg,getbundle());
        bAlertStop(msg,"");
        return(true);
    }
    status=0;
    _tbl=wtbl_alloc(sign,
                    path,
                    name,
                    false,
                    _gapp->document()->dist_resolution(),
                    _gapp->document()->srid(),
                    &status);
    if(!_tbl){
_te_("table not allocated");
        b_error_string(error_num(0,kXMapDataJoinOpenErr),msg,getbundle());
        bAlertStop(msg,"");
        return(true);
    }
    if(status<0){
_te_("wtbl_alloc failed with "+status);
        b_error_string(error_num(0,kXMapDataJoinOpenErr),msg,getbundle());
        bAlertStop(msg,"");
        wtbl_free(_tbl);
        _tbl=NULL;
        return(true);
    }
    /**/	
    strcpy(_tpth,path);
    strcpy(_tnam,name);
    /**/
    
    populate_act();
    
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    else{
        delete _tbl;
        _tbl=NULL;
        _cols.reset();
    }
    return true;
}

// ---------------------------------------------------------------------------
// 
// -----------
void bXMapDataJoin::set_type_index(int tpi){
    _tpi=tpi;
    populate_act();
}

// ---------------------------------------------------------------------------
// 
// -----------
void bXMapDataJoin::populate_act(){
    _cols.reset();
    
bGenericType*	tp=_gapp->typesMgr()->get(_tpi);
wbase			bse=tp->fields();
char			name[256];
datajoin_act	action;
bool			srch=false;
    
    for(int i=1;i<=_tbl->CountFields();i++){
        _tbl->FieldName(i,name);
        action.fidx=bse->get_index(name);
        if(action.fidx<kOBJ_Vertices_){
            action.fidx=0;// Do not fill std hidden fields
        }
        if(action.fidx){
            if(srch){
                action.k=kDataJoinActionCreate;
            }
            else{
                action.k=kDataJoinActionSearch;
                srch=true;
            }
        }
        else{
            action.k=kDataJoinActionCreate;
        }
        _cols.add(&action);
    }
}

// ---------------------------------------------------------------------------
// 
// -----------
void bXMapDataJoin::join(bool mode){
_bTrace_("bXMapDataJoin::join(bool)",false);

bEventLog       log(_gapp,this);
char            msg[__ERROR_STRING_LENGTH_MAX__];
datajoin_act	action;
bGenericType*	tp=_gapp->typesMgr()->get(_tpi);
wbase			bse=tp->fields();
long			i,x=0;
    
// Buffer alloc and key search
    for(i=1;i<=_cols.count();i++){
        _cols.get(i,&action);
        if(action.k==kDataJoinActionSearch){
            x=i;
            break;
        }
    }
_tm_(x);
    
    if(x>0){
_tm_("field "+action.fidx);
        if(bse->add_dyn(_tpth,_tnam,x,action.fidx)){
            b_error_string(error_num(0,kXMapDataJoinKeyNotDefinedErr),msg,getbundle());
bAlertStop	alrt(msg,"",mode);
        }
    }
    else{
        b_error_string(error_num(0,kXMapDataJoinKeyNotDefinedErr),msg,getbundle());
bAlertStop	alrt(msg,"",mode);
    }
    
    log.close();
    _cols.reset();
    wtbl_free(_tbl);
    _tbl=NULL;	
}

