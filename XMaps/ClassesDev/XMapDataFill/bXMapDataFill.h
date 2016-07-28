//----------------------------------------------------------------------------
// File : bXMapDataFill.h
// Project : MacMap
// Purpose : Header file : XMap classe, fills object's datas
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
// 16/03/2006 creation.
// 15/02/2016 coca intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapDataFill__
#define __bXMapDataFill__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

#define	kXMapDataFillMsgFillField	"FillField"
#define	kXMapDataFillMsgWithValue	"WithValue"
#define	kXMapDataFillMsgWithCalc	"WithCalc"
#define	kXMapDataFillMsgWithField	"WithField"

#define	kXMapDataFillErrorCode		-1

//----------------------------------------------------------------------------

class bXMapDataFill : public bStdXMap{
public:
    bXMapDataFill                           (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapDataFill                  (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual void open						(	int* flags);
    virtual bool edit						(	void* prm);
    
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);

    virtual bGenericType* get_type          (	);
    virtual bArray& get_runs                (	);

protected:

private:
    virtual void fill_data					(	);
    virtual void fill_data					(	bool silent);
    virtual void reset						(	);
    virtual bool parse_tree					(	);
    virtual void add_run					(	char* field,
                                                int mode,
                                                char* value);
    
    bGenericType*	_tp;
    int				_fld;
    int				_run;
    bArray			_runs;
};

//----------------------------------------------------------------------------

#endif
