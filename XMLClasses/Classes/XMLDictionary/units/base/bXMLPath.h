//----------------------------------------------------------------------------
// File : bXMLPath.h
// Project : MacMap
// Purpose : Header file : simple path tag class, used in params
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
// 12/01/2004 creation.
//----------------------------------------------------------------------------

#ifndef __XMLPATH__
#define __XMLPATH__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLBaseElement.h>

//----------------------------------------------------------------------------

class bPathElement : public bStdXMLBaseElement{
public:
    bPathElement 							(	bGenericXMLBaseElement* elt, 
                                                bGenericMacMapApp* gapp, 
                                                CFBundleRef bndl );
    virtual ~bPathElement  					(	);
    virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);

    virtual void getvalue					(	char* value);
    virtual void setvalue					(	char* value);
private:
    bool	_docrel;
};

//----------------------------------------------------------------------------

#endif
