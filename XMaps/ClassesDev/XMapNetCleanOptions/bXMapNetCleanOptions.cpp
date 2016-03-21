//----------------------------------------------------------------------------
// File : bXMapNetCleanOptions.cpp
// Project : MacMap
// Purpose : C++ source file : XMap class, network cleaning options
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
// 08/11/2006 creation.
// 08/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#include "bXMapNetCleanOptions.h"
#include "CocoaStuff.h"

#include <mox_intf/xmldesc_utils.h>
#include <mox_intf/mm_messages.h>
#include <mox_intf/Carb_Utils.h>
#include <mox_intf/bStdAlert.h>
#include <mox_intf/ext_utils.h>
#include <mox_intf/bEventLog.h>
#include <mox_intf/bStdWait.h>

#include <MacMapSuite/bTrace.h>
#include <MacMapSuite/bArray.h>
#include <MacMapSuite/vx_measure.h>

// ---------------------------------------------------------------------------
//
// ------------
typedef struct nc_prm{
    bArray*		arr;
    double		d;
    i2dvertex	vx;
}nc_prm;

typedef struct it_prm{
    bGenericType*			tp;
    bGenericGeoIterator*	it;
    int						field;
}it_prm;

typedef struct init_prm{
    int						field;
    bProgressWait*			wt;
}init_prm;

//bool				to=false;

// ---------------------------------------------------------------------------
//
// ------------
int		all_objects		(	void *o,
                            void *prm);
int		dst_point		(	void *o,
                            void *prm);
int		dst_edge		(	void *o,
                            void *prm);
int		dst_edge_end	(	void *o,
                            void *prm);
int		init_ctl		(	void *o,
                            void *prm);
int		check_one_node	(	void *o,
                            void *prm);
int		check_one_edge	(	void *o,
                            void *prm);
void	set_net_flag	(	bGenericGeoElement*	o,
                            int fld,
                            int flg);

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bXMapNetCleanOptions	::bXMapNetCleanOptions(bGenericXMLBaseElement* elt, bGenericMacMapApp* gapp, CFBundleRef bndl)
                :bStdXMap(elt,gapp,bndl){
    setclassname("netcleanoptions2");

char	name[FILENAME_MAX];
GetName(this,name);
(void)_gapp->menuMgr()->add_item(kMenuMgrMenuPalettesID,name,GetSignature(this));
}

// ---------------------------------------------------------------------------
// Destructeur
// -----------
bXMapNetCleanOptions::~bXMapNetCleanOptions(){
}

// ---------------------------------------------------------------------------
// Constructeur
// ------------
bGenericXMLBaseElement* bXMapNetCleanOptions::create(bGenericXMLBaseElement* elt){
    return(new bXMapNetCleanOptions(elt,_gapp,elt->getbundle()));
}

// ---------------------------------------------------------------------------
//
// -----------
bool bXMapNetCleanOptions::edit(void* prm){
_bTrace_("bXMapNetCleanOptions::edit()",true);
long    result=0;
    runCocoaAppModal(this,&result);
    if(result>0){
        return(process(kExtProcessCallFromIntf,prm));
    }
    return false;
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapNetCleanOptions::process(int msg, void* prm){
_bTrace_("bXMapNetCleanOptions::process",true);
    switch(msg){
        case kExtProcessCallFromIntf:
            break;
        case kExtProcessCallWithParams:
            break;
        case kExtProcessCallWithXMLTree:
            break;
        case kExtProcessCallGetData:
            break;
        case kExtProcessCallSetData:
            break;
        default:
            return(false);
    }
    return(true);
}

// ---------------------------------------------------------------------------
//
// ------------
bool bXMapNetCleanOptions::test(void* prm){
    return(_gapp->typesMgr()->count()>2);
}
