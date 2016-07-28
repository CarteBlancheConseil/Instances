//----------------------------------------------------------------------------
// File : bXMapTranslation.h
// Project : MacMap
// Purpose : Header file : XMap class, translate selected geometries in x and y
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
// 19/10/2005 creation.
// 22/07/2016 cocoa intf.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapTranslation__
#define __bXMapTranslation__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

class bXMapTranslation : public bStdXMap{
public:
    bXMapTranslation						(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp,
                                                CFBundleRef bndl);
    virtual ~bXMapTranslation				(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual void open						(	int* flags);
    virtual bool process					(	int msg, 
                                                void* prm);
    virtual bool test						(	void* prm);
    virtual bool edit						(	void* prm);
    
    translation_prm get_data                (   ){return _prm;};
    void set_data                           (   translation_prm prm){_prm=prm;};

protected:
    
private:
    virtual bool translation_with_offset	(	);
    virtual bool translation_with_offset	(	double dx, 
                                                double dy);
    virtual bool translation_to_coord		(	);
    virtual bool translation_to_coord		(	double x, 
                                                double y);
    
    translation_prm	_prm;
};

//----------------------------------------------------------------------------

#endif
