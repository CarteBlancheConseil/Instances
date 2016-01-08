//----------------------------------------------------------------------------
// File : bXMapPaint.h
// Project : MacMap
// Purpose : Header file : XMap paint class
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
// 20/08/2015 creation.
//----------------------------------------------------------------------------
// SCRIPT_COMPATIBLE
//----------------------------------------------------------------------------

#ifndef __bXMapPaint__
#define __bXMapPaint__

//----------------------------------------------------------------------------

#include <std_ext/bStdNSXMap.h>
#include <std_ext/bXMapStdIntf.h>

//----------------------------------------------------------------------------

class bXMapPaint : public bStdNSXMap{
public:		
	bXMapPaint								(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bXMapPaint						(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
	
    virtual bool process					(	int msg,
                                                void* prm);
	virtual bool edit						(	void* prm);

    virtual bool paint						(	int c,
                                                bool dummy);

protected:
	virtual void* ccinit					(	);
	
    virtual bool paint						(	int c);
    virtual void puts						(	);

private:

};

//----------------------------------------------------------------------------

#endif
