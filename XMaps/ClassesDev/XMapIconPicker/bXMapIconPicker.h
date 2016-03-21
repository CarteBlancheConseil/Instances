//----------------------------------------------------------------------------
// File : bXMapIconPicker.h
// Project : MacMap
// Purpose : Header file : XMap class, icon picker (used by vDefs)
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
// 30/05/2006 creation.
// 08/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapIconPicker__
#define __bXMapIconPicker__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

class bXMapIconPicker : public bStdXMap{
public:
    bXMapIconPicker                         (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapIconPicker                (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual bool edit						(	void* prm);

    virtual bool process					(	int msg,
                                                void* prm);

    virtual void get_infos					(	picker_prm* prm){*prm=_prm;};
    virtual void set_infos					(	picker_prm prm){_prm=prm;};

protected:
    picker_prm	_prm;
    char		_sub[FILENAME_MAX];

private:

};

//----------------------------------------------------------------------------

#endif
