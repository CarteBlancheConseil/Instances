//----------------------------------------------------------------------------
// File : bXMapBuffer.h
// Project : MacMap
// Purpose : Header file : XMap class, buffer creation
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
// 11/04/2007 creation.
// 30/06/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapBuffer__
#define __bXMapBuffer__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

class bXMapBuffer : public bStdXMap{
public:
    bXMapBuffer								(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapBuffer					(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void open						(	int* flags);
    virtual bool edit						(	void* prm);
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);

    buffer_prm get_data                     (   ){return _prm;};
    void set_data                           (   buffer_prm prm){_prm=prm;};

protected:		
    
private:
    virtual void bufferize					(	);
    virtual void bufferize					(	buffer_prm prm);
    virtual void puts						(	);
    
    buffer_prm	_prm;
};

//----------------------------------------------------------------------------

#endif
