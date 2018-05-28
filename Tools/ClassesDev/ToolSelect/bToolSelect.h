//----------------------------------------------------------------------------
// File : bToolSelect.h
// Project : MacMap
// Purpose : Header file : Select tool class
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2004 Carte Blanche Conseil.
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
// 27/12/2004 creation.
// 17/06/2011 CGGeometry OK.
// 18/03/2014 Ready for CG geometry	& drawing
// 28/02/2017 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bToolSelect__
#define __bToolSelect__

//----------------------------------------------------------------------------

#include <std_ext/bStdToolNav.h>

//----------------------------------------------------------------------------

enum{
	kSelectDragRect			=1,
	kSelectDragCircle		=2,
	kSelectDragPoly			=3
};

typedef struct TypeRec{
    bool	swp;
    bool	sbd;
}TypeRec;

//----------------------------------------------------------------------------

class bToolSelect : public bStdToolNav{
public:		
	bToolSelect								(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bToolSelect					(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
	
	virtual void open						(	int* flags);
	virtual void close						(	);
	
	virtual void activate					(	);
	virtual void deactivate					(	);
	virtual void pop						(	cocoaMenuPrm prm);
	virtual void clic						(	CGPoint pt, 
												int count);
	virtual void end_clic					(	);
	virtual void update						(	bool global);
	virtual void set_modifiers				(	int k);

	virtual bool set_key					(	int k);
	
    virtual bool edit						(	void* prm);

    virtual void action						(	int count);

    virtual bGenericXMLBaseElement* load	(	);
	virtual bGenericXMLBaseElement* make	(	bArray& arr);
	
    bArray&  types                          (   ){return _types;};
    bool get_pt_all_obj                     (   ){return _pt_all_obj;};
    void set_pt_all_obj                     (   bool pt_all_obj){_pt_all_obj=pt_all_obj;};
    bool get_pt_all_typ                     (   ){return _pt_all_typ;};
    void set_pt_all_typ                     (   bool pt_all_typ){_pt_all_typ=pt_all_typ;};
    bool get_full_include                   (   ){return _full_include;};
    void set_full_include                   (   bool full_include){_full_include=full_include;};
    bool get_poly_angle                     (   ){return _poly_angle;};
    void set_poly_angle                     (   bool poly_angle){_poly_angle=poly_angle;};

protected:

private:
	virtual void rect_select				(	);
	virtual void circle_select				(	);
	virtual void polygon_select				(	);
	virtual void point_select				(	);
	virtual void report						(	);
	virtual void toggle						(	bArray* input, 
												bArray* handled);
	virtual void reset_handled				(	bArray* handled);
		
	CursorRef		_ctoggle;
	bool			_pt_all_obj;
	bool			_pt_all_typ;
	bool			_full_include;
	bool			_poly_angle;
	bArray			_types;
};

//----------------------------------------------------------------------------

#endif
