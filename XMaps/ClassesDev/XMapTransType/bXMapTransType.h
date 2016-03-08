//----------------------------------------------------------------------------
// File : bXMapTransType.h
// Project : MacMap
// Purpose : Header file : XMap class, type transfert (i.e. transfering selected objects from one type to another)
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
// 20/10/2005 creation.
// 15/02/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapTransType__
#define __bXMapTransType__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

typedef struct fieldindex{
    int				idx;
    void*			val;
}fieldindex;

//----------------------------------------------------------------------------

class bXMapTransType : public bStdXMap{
public:
    bXMapTransType                          (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapTransType                 (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual void open						(	int* flags);
    virtual bool edit						(	void* prm);
    
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);

    virtual void set_infos                  (	transtype_prm   prm);
    virtual void get_infos                  (	transtype_prm*   prm);

protected:

private:
    virtual void transtype					(	);
    virtual void transtype					(	bool dummy);
    virtual void transtype					(	transtype_prm* p);
    virtual void field_create				(	transtype_prm* p,
                                                bGenericType* from_type);
    virtual fieldindex* field_index			(	transtype_prm* p,
                                                bGenericType* from_type);
    virtual void kill_objects				(	bArray* a);
    
    transtype_prm	_prm;

};

//----------------------------------------------------------------------------

#endif
