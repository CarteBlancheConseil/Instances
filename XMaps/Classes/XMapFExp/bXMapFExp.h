//----------------------------------------------------------------------------
// File : bXMapFExp.h
// Project : MacMap
// Purpose : Header file : XMap classe, export format and projection
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
// 08/06/2007 creation.
// 23/02/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapFExp__
#define __bXMapFExp__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

#define	kXMapFExpMessageID		"fmtexp"
#define	kXMapFExpStdParamID		"std_format.xml"

// ---------------------------------------------------------------------------

class type_p{
public:
    type_p					(	bGenericType*	tp);
    virtual ~type_p			(	);
    
    virtual bool load		(	bGenericMacMapApp* gapp);
    virtual bool dump		(	bGenericMacMapApp* gapp);
    
    static bool read_proc	(	bGenericXMLBaseElement* elt,
                                void* prm,
                                int indent);
    
    bGenericType* 		_tp;
    bArray				_flds;
};

//----------------------------------------------------------------------------

class bXMapFExp : public bStdXMap{
public:
    bXMapFExp                               (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapFExp                      (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual void open						(	int* flags);
    virtual bool edit						(	void* prm);
    
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);

    void get								(	int tp,
                                                bArray* arr,
                                                int* srid);
    void set								(	int tp,
                                                bArray* arr,
                                                int srid);
    virtual void read_p						(	);
    virtual void write_p					(	);
    virtual bGenericXMLBaseElement*	make_p	(	);
    virtual bool parse						(	);

protected:

private:
    int _srid;
};

//----------------------------------------------------------------------------

#endif
