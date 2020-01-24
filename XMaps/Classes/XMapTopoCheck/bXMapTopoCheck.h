//----------------------------------------------------------------------------
// File : bXMapTopoCheck.h
// Project : MacMap
// Purpose : Header file : XMap class, network topology check
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
// 16/11/2006 creation.
// 08/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapTopoCheck__
#define __bXMapTopoCheck__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

#define kXMapTopoCheckConfig		"topocheck_config"

//----------------------------------------------------------------------------

class bXMapTopoCheck : public bStdXMap{
public:
    bXMapTopoCheck							(	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp,
                                                CFBundleRef bndl);
    virtual ~bXMapTopoCheck					(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void open						(	int* flags);
    virtual void close						(	);
    virtual bool edit						(	void* prm);
    virtual bool nsevent                    (	void* nsevt);
    virtual bool process					(	int msg,
                                                void* prm);

    virtual bArray& types					(   ){return _types;};

protected:
    virtual void check_events				(	);
    virtual void process_objects			(	bArray& objects);
    
    virtual void read_p						(	);
    virtual void write_p					(	);
    virtual bGenericXMLBaseElement* make_p	(	);
    
private:
    bArray			_types;
    topocheck_prm	_prm;
};

//----------------------------------------------------------------------------

#endif
