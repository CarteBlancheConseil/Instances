//----------------------------------------------------------------------------
// File : bToolCreate.h
// Project : MacMap
// Purpose : Header file : Object creation tool class
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
// 06/05/2005 creation.
// 18/03/2014 Ready for CG geometry	& drawing
// 28/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bToolCreate__
#define __bToolCreate__

//----------------------------------------------------------------------------

#include <tool_lib/bToolNSGeomWithJoin.h>
#include <MacMapSuite/bArray.h>

//----------------------------------------------------------------------------

class bToolCreate : public bToolNSGeomWithJoin{
public:		
	bToolCreate								(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bToolCreate					(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
			
	virtual void open						(	int* flags);
	virtual void idle						(	void* prm);
	virtual void clic						(	CGPoint pt, 
												int count);
	virtual void drag						(	CGPoint pt);
	virtual void update						(	bool global);

	virtual bool set_key					(	int k);
	
	virtual void action						(	int count);

    virtual bool edit						(	void* prm);
    	
	virtual bGenericXMLBaseElement* load	(	);
	bGenericXMLBaseElement* make			(	bArray &arr);
	
    bool get_opn                            (   ){return _opn;};
    void set_opn                            (   bool opn){_opn=opn;};
    
protected:

private:
	void create_multi						(	);
	void create_single						(	);

	bGenericType*	_tp;
	bool			_opn;
};

//----------------------------------------------------------------------------

#endif
