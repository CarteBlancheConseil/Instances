//----------------------------------------------------------------------------
// File : bToolZoom.h
// Project : MacMap
// Purpose : Header file : Zoom tool class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2005 Carte Blanche Conseil.
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
// 05/01/2005 creation.
// 02/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bToolZoom__
#define __bToolZoom__

//----------------------------------------------------------------------------

#include <std_ext/bStdToolNav.h>

//----------------------------------------------------------------------------
typedef struct scale{
	int				idx;
	bool			modified;
	bool			created;
	bool			deleted;
	double			value;
	char			name[256];
	bGenericUnit*	u;
}scale;

//----------------------------------------------------------------------------

class bToolZoom : public bStdToolNav{
public:		
	bToolZoom								(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bToolZoom						(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
	
	virtual void open						(	int* flags);
	virtual void close						(	);
	
	virtual void pop						(	cocoaMenuPrm prm);
	virtual void clic						(	CGPoint pt, 
												int count);
	virtual void update						(	bool global);
	virtual void set_modifiers				(	int k);

    virtual bool edit						(	void* prm);
	
	virtual void pop_tools					(	CGPoint	location,
												WindowRef inWindow);
    bArray&  scales                         (   ){return _scales;};

protected:

private:
	void dump								(	);
	
	CursorRef		_cminus;
	bArray			_scales;
};

//----------------------------------------------------------------------------

#endif
