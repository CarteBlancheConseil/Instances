//----------------------------------------------------------------------------
// File : bXMapShortCuts.h
// Project : MacMap
// Purpose : Header file : XMap class, shortcuts management
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
// 15/03/2010 creation.
// 29/02/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapShortCuts__
#define __bXMapShortCuts__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

class bXMapShortCuts : public bStdXMap{
public:		
    bXMapShortCuts                          (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapShortCuts                 (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual void open						(	int* flags);
    virtual bool event						(	EventRef evt);
    virtual void idle						(	void* prm);

    virtual bool edit						(	void* prm);

    virtual bool process                    (	int msg,
                                                void* prm);


    bArray& getxmap                         (   ){return _xmap;};
    bArray& getxbox                         (   ){return _xbox;};
    bArray& getmacr                         (   ){return _macr;};
    bArray& getscrp                         (   ){return _scrp;};
    
    UInt32 scan_array                       (	bArray& arr,
                                                char code,
                                                UInt32 key,
                                                UInt32 modi,
                                                bool* inmenu);
protected:
    void scan_read_menu						(	MenuRef mnu);
    void scan_write_menu					(	MenuRef mnu);
    void read_p								(	);
    void write_p							(	);
    
    void read_p								(	const char* name,
                                                bArray& arr);
    void write_p							(	const char* name,
                                                bArray& arr);
    
    bGenericXMLBaseElement* make_p			(	bArray& arr);
    
    
    void add_ext							(	bArray& arr,
                                                bGenericExtMgr* mgr,
                                                UInt32 sgn);
    void modify_ext							(	bArray& arr,
                                                bGenericExtMgr* mgr,
                                                UInt32 sgn);
    void remove_ext							(	bArray& arr,
                                                bGenericExtMgr* mgr,
                                                UInt32 sgn);

    
private:
    bArray	_xmap;
    bArray	_xbox;
    bArray	_macr;
    bArray	_scrp;
    bool	_first;
    UInt32	_call;
};

//----------------------------------------------------------------------------

#endif
