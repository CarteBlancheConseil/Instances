//----------------------------------------------------------------------------
// File : bvDefPaletteHisto.h
// Project : MacMap
// Purpose : Header file : Histogram vdef class
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
// 09/07/2013 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefPaletteHisto__
#define __bvDefPaletteHisto__

//----------------------------------------------------------------------------

#include <Carbon/Carbon.h>
#include <std_ext/bStdNSPalettevDef.h>

//----------------------------------------------------------------------------

class bvDefPaletteHisto : public bStdNSPalettevDef{
public:		
    bvDefPaletteHisto                       (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bvDefPaletteHisto              (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual bool test						(	bGenericType* tp);
    
    virtual void stl_alloc					(	bool);

    virtual void fld_put					(	int fld){_fld=fld;};


    virtual bool bck_get					(	){return(_bck);};
    virtual void bck_put					(	bool bck){_bck=bck;};

    virtual double* strk_get				(	){return(_stroke);};
    virtual void strk_put					(	double* stroke){
                                                _stroke[0]=stroke[0];
                                                _stroke[1]=stroke[1];
                                                _stroke[2]=stroke[2];
                                                _stroke[3]=stroke[3];
                                                _stroke[4]=stroke[4];};

    virtual double* fill_get				(	){return(_fill);};
    virtual void fill_put					(	double* fill){
                                                _fill[0]=fill[0];
                                                _fill[1]=fill[1];
                                                _fill[2]=fill[2];
                                                _fill[3]=fill[3];
                                                _fill[4]=fill[4];};

    virtual double wdth_get					(	){return(_width);};
    virtual void wdth_put					(	double width){_width=width;};

    virtual bArray&	fields					(	){return(_fields);};

protected:
    virtual void* ccinit					(	);
    
    virtual void stl_free					(	);

    virtual void make						(	);
    virtual bool read						(	);
    virtual bool write						(	);

private:
    bArray				_fields;
    double				_bck;
    double				_width;
    double				_stroke[5];
    double				_fill[5];

};

//----------------------------------------------------------------------------

#endif
