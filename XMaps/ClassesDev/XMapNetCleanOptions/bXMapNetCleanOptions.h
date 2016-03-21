//----------------------------------------------------------------------------
// File : bXMapNetCleanOptions.h
// Project : MacMap
// Purpose : Header file : XMap class, network cleaning options
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
// 08/11/2006 creation.
// 08/03/2016 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bXMapNetCleanOptions__
#define __bXMapNetCleanOptions__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bXMapNetCleanOptions : public bStdXMap{
public:
    bXMapNetCleanOptions					(	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp,
                                                CFBundleRef bndl);
    virtual ~bXMapNetCleanOptions			(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
    
    virtual bool edit						(	void* prm);
    virtual bool process					(	int msg,
                                                void* prm);
    virtual bool test						(	void* prm);
    
protected:
    
private:
    netcleancfg_prm	_prm;
};

//----------------------------------------------------------------------------

#endif
