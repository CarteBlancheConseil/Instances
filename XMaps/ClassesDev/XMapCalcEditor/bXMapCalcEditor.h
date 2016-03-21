//----------------------------------------------------------------------------
// File : bXMapCalcEditor.h
// Project : MacMap
// Purpose : Header file : XMap class, MapCalculator editor
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
// 03/05/2007 creation.
// 16/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapCalcEditor__
#define __bXMapCalcEditor__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <xmap_lib/bXMapCalcCell.h>

//----------------------------------------------------------------------------

class bXMapCalcEditor : public bStdXMap{
public:		
    bXMapCalcEditor							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapCalcEditor				(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool edit						(	void* prm);// Possibilité de passer un XML à éditer
    
    virtual bool wd_event					(	EventRef evt, 
                                                WindowRef wd);
    virtual void wd_init					(	WindowRef wd);
    
    virtual bXMapCalcCell* get_root         (   ){return _root;};
    virtual void set_root                   (   bXMapCalcCell* root){_root=root;};

    virtual void get_name                   (   char* name){strcpy(name,_name);};
    virtual void set_name                   (   char* name){strcpy(_name,name);};

    virtual int get_kind                    (   ){return _fknd;};
    virtual void set_kind                   (   int kind){_fknd=kind;};

protected:
    bool save_action						(	);
    bool parse								(	bGenericXMLBaseElement* root);

private:
    bXMapCalcCell*  _root;
    char            _name[FILENAME_MAX];
    UInt32          _fknd;
    UInt32          _fsgn;
    bool            _new;
    int             _idx;
};

//----------------------------------------------------------------------------

#endif
