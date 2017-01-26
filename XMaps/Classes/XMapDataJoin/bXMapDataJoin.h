//----------------------------------------------------------------------------
// File : bXMapDataJoin.h
// Project : MacMap
// Purpose : Header file : XMap class, data join from DBF, text, csv, ... file
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
// 29/06/2006 creation.
// 11/02/2015 NAV to NS transformation.
// 03/03/2016 Cocoa Intf.
//----------------------------------------------------------------------------

#ifndef __bXMapDataJoin__
#define __bXMapDataJoin__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

enum{
	kXMapDataJoinNoErr,
	kXMapDataJoinUnsupportedFormatErr,
	kXMapDataJoinOpenErr,
	kXMapDataJoinKeyNotDefinedErr,
	kXMapDataJoinNoDataToFillErr,
	kXMapDataJoinNoObjectErr,
	kXMapDataJoinNotUniqueErr
};

#define	kXMapDataJoinMessageID		"DataJoin"
#define	kXMapDataJoinLineNumberID   "LineNumber"
#define	kXMapDataJoinErrorsOccursID	"ErrorsOccurs"
#define	kXMapDataJoinReadLogID		"ReadLog"
#define	kXMapDataJoinReadContinueID	"Continue"

//----------------------------------------------------------------------------

class bXMapDataJoin : public bStdXMap{
public:
    bXMapDataJoin							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapDataJoin                  (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);

    virtual void open						(	int* flags);
    virtual bool test						(	void* prm);
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool edit						(	void* prm);
    
    virtual bStdTable* table                (   ){return _tbl;};
    virtual bArray& actions                 (   ){return _cols;};
    virtual int get_type_index              (   ){return _tpi;};
    virtual void set_type_index             (   int tpi);

protected:
    virtual void populate_act				(	);
    virtual void join						(	bool mode);
            
private:    
    bArray			_cols;
    int				_tpi;
    bStdTable*		_tbl;
    char			_tpth[PATH_MAX];
    char			_tnam[FILENAME_MAX];
};

//----------------------------------------------------------------------------

#endif
