//----------------------------------------------------------------------------
// File : bGeogGAlong.h
// Project : MacMap
// Purpose : Header file : Along Geog interface class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2006 Carte Blanche Conseil.
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
// 07/11/2006 creation.
// 04/09/2016 cocoa intf.
// 01/11/2016 remove carbon call (edit(windowref,*rect), hide and show)
//----------------------------------------------------------------------------

#ifndef __bGeogGAlong__
#define __bGeogGAlong__

//----------------------------------------------------------------------------

#include <std_ext/bStdGeog.h>

//----------------------------------------------------------------------------

class bGeogGAlong : public bStdGeog {
public:
    bGeogGAlong								(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bGeogGAlong					(	);
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
    bool		_full;
    bool		_strict;
    void*       _ctrlr;
};

//----------------------------------------------------------------------------

#endif
