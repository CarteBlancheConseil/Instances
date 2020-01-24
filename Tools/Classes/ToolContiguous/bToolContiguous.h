//----------------------------------------------------------------------------
// File : bToolContiguous.h
// Project : MacMap
// Purpose : Header file : Contiguous tool class (Select a set of connected lines having same value in a field, usefull for roadmaps). 
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2006 Carte Blanche Conseil.
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
// 07/04/2006 creation.
// 19/03/2014 Ready for CG geometry	& drawing
// 03/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bToolContiguous__
#define __bToolContiguous__

//----------------------------------------------------------------------------

#include <std_ext/bStdToolNav.h>

//----------------------------------------------------------------------------

class bToolContiguous : public bStdToolNav{
public:		
	bToolContiguous							(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bToolContiguous				(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
	
	virtual void close						(	);
	
	virtual void clic						(	CGPoint pt, int count);
	
    virtual bool edit						(	void* prm);

	virtual bGenericXMLBaseElement* load	(	);
	virtual bGenericXMLBaseElement* make	(	bArray& arr);
	virtual void save						(	);
	
    bArray& types                           (	){return _types;};

protected:

private:
	virtual void line_propagate				(	bGenericGeoElement* o);

	virtual bGenericXMLBaseElement* make	(	int tidx);
	virtual void load_type					(	int tidx);

	bArray	_types;
};

//----------------------------------------------------------------------------

#endif
