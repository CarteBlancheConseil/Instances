//----------------------------------------------------------------------------
// File : bXMapSelector.h
// Project : MacMap
// Purpose : Header file : XMap class, selector : selecting objects by database and/or geographic request
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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// See the LICENSE.txt file for more information.
//
//----------------------------------------------------------------------------
// 
//----------------------------------------------------------------------------
// 20/01/2005 creation.
// 29/07/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapSelector__
#define __bXMapSelector__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <mox_intf/bGenericGeog.h>
#include <MacMapSuite/bStdBaseAccessor.h>

//----------------------------------------------------------------------------

enum{
	kXMapSelectorDTSourceField		=0,
	kXMapSelectorDTSourceCalc		=1
};

enum{
	kXMapSelectorSelect				=1,
	kXMapSelectorCreateMacro		=2,
	kXMapSelectorEditMacro			=3
};

#define kXMapSelectorCreateMacroCall	-1

//----------------------------------------------------------------------------

class bXMapSelector : public bStdXMap{
public:
    bXMapSelector							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapSelector					(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void open						(	int* flags);
    virtual bool process					(	int msg, 
                                                void* prm);
    virtual bool test						(	void* prm);
    virtual bool edit						(	void* prm);// Possibilité de passer un XML à éditer, -1 pour une macro
    
    virtual int get_action                  (   ){return _act;};
    virtual bArray& criterions              (   ){return _critarr;};
    
    virtual int get_selwhat                 (   ){return _selwhat;};
    virtual void set_selwhat                (   int selwhat){_selwhat=selwhat;};
    virtual UInt32 get_next                 (   ){return _next;};
    virtual void set_next                   (   UInt32 next){_next=next;};
    virtual bool get_add2cnt                (   ){return _add2cnt;};
    virtual void set_add2cnt                (   bool add2cnt){_add2cnt=add2cnt;};
    virtual int get_add2hdn                 (   ){return _add2hdn;};
    virtual void set_add2hdn                (   int add2hdn){_add2hdn=add2hdn;};
    virtual bool get_use_mask               (   ){return _use_mask;};
    virtual void set_use_mask               (   bool use_mask){_use_mask=use_mask;};
    virtual bGenericType* get_type          (   ){return _tp;};
    virtual void set_type                   (   bGenericType* tp){_tp=tp;};
    virtual bGenericGeog* get_geog          (   ){return _geog;};
    virtual void set_geog                   (   bGenericGeog* geog){_geog=geog;};
    virtual void get_name                   (   char* name){strcpy(name,_name);};
    virtual void set_name                   (   char* name){strcpy(_name,name);};
    
protected:
    void reset                              (	);
    bGenericXMLBaseElement* make			(	char* macro);
    bool parse								(	bGenericXMLBaseElement* root);
    void save_formula						(	);

private:											
    bGenericType*			_tp;
    bArray					_critarr;
    int						_selwhat;
    
    UInt32					_next;
    bool					_add2cnt;
    int						_add2hdn;
    
    bool					_use_mask;
    bGenericGeog*			_geog;
    
    int						_act;		
    bGenericXMLBaseElement*	_root;
    UInt32					_fsgn;
    char					_name[FILENAME_MAX];
    int						_idx;
};

//----------------------------------------------------------------------------

#endif
