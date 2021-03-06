//----------------------------------------------------------------------------
// File : bToolShape.h
// Project : MacMap
// Purpose : Header file : Rectangles and ovals objects creation tool class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2007 Carte Blanche Conseil.
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
// 18/06/2007 creation.
// 18/03/2014 Ready for CG geometry	& drawing
// 24/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bToolShape__
#define __bToolShape__

//----------------------------------------------------------------------------

#include <std_ext/bStdToolGeom.h>

//----------------------------------------------------------------------------

enum{
	kShapeRect			=1,
	kShapeCircle		=2
};

//----------------------------------------------------------------------------

class bToolShape : public bStdToolGeom{
public:		
	bToolShape								(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bToolShape						(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
			
	virtual void open						(	int* flags);
	virtual void clic						(	CGPoint pt, 
												int count);
	virtual void end_clic					(	);		
	virtual void update						(	bool global);
	virtual void drag						(	CGPoint pt);
    
    virtual bool edit						(	void* prm);

	virtual bGenericXMLBaseElement* load	(	);
	virtual bGenericXMLBaseElement* make	(	bArray &arr);

    bool get_ctr                            (   ){return _ctr;};
    void set_ctr                            (   bool ctr){_ctr=ctr;};
    bool get_opn                            (   ){return _opn;};
    void set_opn                            (   bool opn){_opn=opn;};
    char get_cm                             (   ){return _cm;};
    void set_cm                             (   char cm){_cm=cm;};
    
protected:

private:
	virtual void create_rect				(	);
	virtual void create_circle				(	);
	virtual void report						(	);

	bGenericType*	_tp;
	bool			_ctr;
	bool			_opn;
	char			_cm;
};

//----------------------------------------------------------------------------

#endif
