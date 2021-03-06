//----------------------------------------------------------------------------
// File : bXMapRasterImport.h
// Project : MacMap
// Purpose : Header file : XMap class, raster imports
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
// 13/12/2006 creation.
// 14/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapRasterImport__
#define __bXMapRasterImport__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

//#define	kXMapRasterImportMessageID				"rasterimport"
#define	kXMapRasterImportInvalidGridErrorID		"GridErr"
#define	kXMapRasterImportIGridNotFoundErrorID	"IGridNotFoundErr"
#define	kXMapRasterImportIGridNotFoundExplID	"IGridNotFoundExpl"
#define	kXMapRasterImportGlobalErrorID          "GlobalErr"
#define	kXMapRasterImportGlobalExplID           "GlobalExpl"

enum{
	kRasterImportKindBotRight	=1,
	kRasterImportKindScale		=2,
	kRasterImportKindTFW		=10,
	kRasterImportKindTAB		=11,
	kRasterImportKindKML		=12,// unused
	kRasterImportKindMMR		=20,// unused
};

//----------------------------------------------------------------------------

class bXMapRasterImport : public bStdXMap{
public:		
    bXMapRasterImport						(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapRasterImport				(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual bool process					(	int msg, 
                                                void* prm);
    virtual bool edit						(	void* prm);
    
    virtual void set_import_type            (   long ik){_ik=ik;};
    virtual long get_import_type            (   ){return _ik;};

    virtual void set_topleft                (   d2dvertex loc){_tl=loc;};
    virtual d2dvertex get_topleft           (   ){return _tl;};

    virtual void set_botright               (   d2dvertex loc){_br=loc;};
    virtual d2dvertex get_botright          (   ){return _br;};

    virtual void set_scale                  (   double scl){_scl=scl;};
    virtual double get_scale                (   ){return _scl;};

protected:
    virtual bool import						(	);
    virtual bool import						(	import_prm* prm);

    virtual bool parse_tfw					(	bStdFile& f);
    virtual bool parse_tab					(	bStdFile& f);
    
private:
    import_prm	_prm;
    
    int			_ik;
    d2dvertex	_tl;
    d2dvertex	_br;
    double		_scl;
    
    double		_xsz;
    double		_ysz;
};

//----------------------------------------------------------------------------

#endif
