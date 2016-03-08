//----------------------------------------------------------------------------
// File : bXMapDBDefVal.h
// Project : MacMap
// Purpose : Header file : XMap default values class, sets standard fields default values
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
// 16/03/2007 creation.
// 11/02/2016 coca intf.
//----------------------------------------------------------------------------

#ifndef __bXMapDBDefVal__
#define __bXMapDBDefVal__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bXMapDBDefVal : public bStdXMap{
public:
    bXMapDBDefVal                           (	bGenericXMLBaseElement* elt,
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl);
    virtual ~bXMapDBDefVal                  (	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
            
    virtual bool test						(	void* prm);
    virtual bool edit						(	void* prm);

    virtual bool process					(	int msg,
                                                void* prm);

    virtual int modify                      (	bGenericType* tp,
                                                long field,
                                                long cidx,
                                                const char* value);
protected:

private:

};

//----------------------------------------------------------------------------

#endif
