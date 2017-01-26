//----------------------------------------------------------------------------
// File : bGeogGNearest.h
// Project : MacMap
// Purpose : Header file : Nearest Geog interface class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2008 Carte Blanche Conseil.
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
// 03/12/2008 creation.
// 06/09/2016 cocoa intf.
// 01/11/2016 remove carbon call (edit(windowref,*rect), hide and show)
//----------------------------------------------------------------------------

#ifndef __bGeogGNearest__
#define __bGeogGNearest__

//----------------------------------------------------------------------------

#include <std_ext/bStdGeog.h>

//----------------------------------------------------------------------------

class bGeogGNearest : public bStdGeog {
public:
    bGeogGNearest							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bGeogGNearest					(	);
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
    long    _val;
    void*   _ctrlr;
};

//----------------------------------------------------------------------------

#endif
