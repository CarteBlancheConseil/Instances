//----------------------------------------------------------------------------
// File : bXMapVarEditor.h
// Project : MacMap
// Purpose : Header file : Constants editor class
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
// 16/05/2007 creation.
// 04/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapVarEditor__
#define __bXMapVarEditor__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bXMapVarEditor : public bStdXMap{
public:
    bXMapVarEditor                          (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapVarEditor                 (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual bool edit						(	void* prm);

    virtual bool process					(	int msg,
                                                void* prm);

    virtual void get_infos                  (	char* name,
                                                char* value,
                                                UInt32* kind);
    virtual void set_infos                  (	const char* name,
                                                const char* value,
                                                UInt32 kind);

protected:
    bool save_action						(	);
    bool parse								(	bGenericXMLBaseElement* root);

private:
    char					_name[FILENAME_MAX];
    char					_value[_values_length_max_];
    UInt32					_fknd;
    UInt32					_fsgn;
    bool					_new;
    int						_idx;

};

//----------------------------------------------------------------------------

#endif
