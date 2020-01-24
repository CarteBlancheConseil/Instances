//----------------------------------------------------------------------------
// File : bToolInfo.h
// Project : MacMap
// Purpose : Header file : Object info tooltip class (show a set of field when mouse is over objects)
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
// 07/01/2005 creation.
// 18/03/2014 Ready for CG geometry	& drawing
// 24/03/2017 cocoa intf.
//----------------------------------------------------------------------------

#ifndef __bToolInfo__
#define __bToolInfo__

//----------------------------------------------------------------------------

#include <std_ext/bStdToolNav.h>

//----------------------------------------------------------------------------

class bToolInfo : public bStdToolNav{
public:		
	bToolInfo								(	bGenericXMLBaseElement* elt, 
												bGenericMacMapApp* gapp, 
												CFBundleRef bndl);
	virtual ~bToolInfo						(	);
	virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
	
	virtual void open						(	int* flags);
	virtual void close						(	);

	virtual void clic						(	CGPoint pt, 
												int count);		
	virtual void update						(	bool global);

    virtual bool edit						(	void* prm);

	virtual bGenericXMLBaseElement* load	(	);
	virtual bGenericXMLBaseElement* make	(	bArray& arr);
	virtual void save						(	);

    bArray& fields                          (   ){return _fields;};
    bool get_show_type                      (   ){return _show_type;};
    void set_show_type                      (   bool show_type){_show_type=show_type;};
    int get_index							(	int tpidx,
                                                int fid);
    
protected:

private:
	void init_draw							(	);
	void draw								(	);
	void check_bounds						(	);
	bGenericXMLBaseElement* make			(	int tidx);
	virtual void load_type					(	int tidx);
	bGenericXMLBaseElement* find_type		(	bGenericXMLBaseElement* root, 
												double id);
		
	CursorRef		_cleft;
	bool			_cleft_on;
	CGFloat			_wd_width;
	CGFloat			_wd_height;
	bool			_show_type;
    bArray			_fields;
};

//----------------------------------------------------------------------------

typedef struct fld{
	int		fid;
	int		idx;
	char	name[256];
	char	value[256];
}fld;

//----------------------------------------------------------------------------

class bToolInfoParams  : public bGraphicParams {
public:
	bToolInfoParams				(	bGenericXMLBaseElement* root, 
									bGenericMacMapApp* gapp,
									CFBundleRef bndl);
	
	virtual ~bToolInfoParams	(	);
	
	virtual bool update			(	bArray& arr, 
									long indent);
	
	virtual void applyFont		(	CGContextRef ctx);
	
	virtual void setFont		(	const char* fnt);
	virtual void setFontSize	(	float sz);
	virtual void setFontFill	(	const float* clr);
	virtual void setRadius		(	float rad);
	
	virtual const char* font	(	){return _fnt;};
	virtual CGFloat fontSize	(	){return _fnt_sz;};
	virtual CGFloat radius		(	){return _radius;};

protected:
	virtual void parse          (	bGenericXMLBaseElement* root,
                                    bGenericMacMapApp* gapp);
	
	char	_fnt[256];
	CGFloat	_fnt_sz;
	CGFloat _fnt_fill[4];
	CGFloat _radius;

private:
	
};

//----------------------------------------------------------------------------

#endif
