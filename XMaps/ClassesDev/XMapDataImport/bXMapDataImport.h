//----------------------------------------------------------------------------
// File : bXMapDataImport.h
// Project : MacMap
// Purpose : Header file : XMap class, fills objects data from DBF, text, csv, ... file
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
// 25/10/2007 creation.
// 11/02/2015 NAV to NS transformation.
// 02/03/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapDataImport__
#define __bXMapDataImport__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

enum{
	kXMapDataImportNoErr,
	kXMapDataImportUnsupportedFormatErr,
	kXMapDataImportOpenErr,
	kXMapDataImportKeyNotDefinedErr,
	kXMapDataImportNoDataToFillErr,
	kXMapDataImportNoObjectErr,
	kXMapDataImportNotUniqueErr
};

#define	kXMapDataImportMessageID		"DataImport"
#define	kXMapDataImportLineNumberID		"LineNumber"
#define	kXMapDataImportErrorsOccursID	"ErrorsOccurs"
#define	kXMapDataImportReadLogID		"ReadLog"
#define	kXMapDataImportReadContinueID	"Continue"

//----------------------------------------------------------------------------

typedef	int	(*compProc)(const void*,const void*);

//----------------------------------------------------------------------------

class bXMapDataImport : public bStdXMap{
public:
    bXMapDataImport							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapDataImport                (	);
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
    virtual bool get_use_masked             (   ){return _use_msk;};
    virtual void set_use_masked             (   bool b){_use_msk=b;};
    virtual bool get_unique                 (   ){return _unique;};
    virtual void set_unique                 (   bool b){_unique=b;};

protected:
    virtual void populate_act				(	);
    virtual void parse_tree					(	);
    virtual void join						(	);
    virtual void join						(	datajoin_prm* prm,
                                                bool mode);
    virtual int add_fields					(	datajoin_prm* prm);
            
private:
    compProc		_comp;
    
    bArray			_cols;
    int				_tpi;
    bool			_use_msk;
    bool			_unique;
		
    bStdTable*		_tbl;
    bStdFile*		_report;
};

//----------------------------------------------------------------------------

#endif
