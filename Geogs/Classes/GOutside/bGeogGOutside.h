//----------------------------------------------------------------------------
// File : bGeogGOutside.h
// Project : MacMap
// Purpose : Header file : Outside Geog interface class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2005 Carte Blanche Conseil.
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
// Outside with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 28/01/2005 creation.
// 06/09/2016 cocoa intf.
// 01/11/2016 remove carbon call (edit(windowref,*rect), hide and show)
//----------------------------------------------------------------------------

#ifndef __bGeogGOutside__
#define __bGeogGOutside__

//----------------------------------------------------------------------------

#include <std_ext/bStdGeog.h>

//----------------------------------------------------------------------------

class bGeogGOutside : public bStdGeog {
public:
    bGeogGOutside							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bGeogGOutside					(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);

    virtual void open						(	int* flags);
    virtual void close						(	);

    virtual bool edit						(	void* nsview);
    virtual void end_edit					(	);

    virtual void get_params					(	bArray* arr,
                                                int indent);
    virtual void put_params					(	bGenericXMLBaseElement* root);

protected:

private:
    bool    _full;
    bool    _strict;
    void*   _ctrlr;
};

//----------------------------------------------------------------------------

#endif
