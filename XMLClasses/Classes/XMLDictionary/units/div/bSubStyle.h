//----------------------------------------------------------------------------
// File : bSubStyle.h
// Project : MacMap
// Purpose : Header file : substyle class, used in complex styles
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
// 17/04/2007 creation.
//----------------------------------------------------------------------------

#ifndef __bSubStyle__
#define __bSubStyle__

//----------------------------------------------------------------------------

#include <mox_intf/bGenericStyle.h>
#include <mox_intf/bGenericGeoElement.h>
#include <MacMapSuite/bArray.h>
#include <mox_intf/bGenericXMLBaseElement.h>
#include <mox_intf/bGenericXMLRenderingElement.h>
#include <mox_intf/bGenericGraphicContext.h>

//----------------------------------------------------------------------------

class bSubStyle : public bGenericStyle{
public:
	bSubStyle 									(	); 
	virtual ~bSubStyle   						(	);

// Accès librairie XML
	virtual void setidentification				(	void *elt);
	virtual void setglobals						(	void *elt);
	virtual void setcondition					(	void *elt);
	
	virtual void setdrawingmethod				(	int k);
	virtual void setclassfield					(	const char *name);
	virtual void setpasscount					(	int n);
	virtual void setscaleref					(	double d);
	virtual void setunitcoef					(	double d);
	virtual void setsortkind					(	int k);
	virtual void addclassbound					(	double d);
	virtual void addclassname					(	const char* name);
	
	virtual void addstylerun					(	void *elt);
	virtual void setrunvalidity					(	void *elt);
	virtual void setrunrender					(	void *elt);
	virtual void setrungeometry					(	void *elt);
	
	virtual void setrunscalemin					(	double d);
	virtual void setrunscalemax					(	double d);
	virtual void setrunclassmin					(	long idx);
	virtual void setrunclassmax					(	long idx);
	virtual void setrunpass						(	long idx);
	
	virtual void settype						(	const char *name);
	virtual void setname						(	const char *name);
	virtual void setvisible						(	bool vis);
	virtual void setselectable					(	bool sel);
	virtual void setroot						(	void *elt);
	virtual void setlayer						(	void *elt);

	virtual void setmargin						(	int margin);
	
// Accès noyau/externes		
	virtual void setbounds						(	ivx_rect* bounds);
	virtual void setcontext						(	bGenericGraphicContext* ctx);
				
	virtual void draw							(	bStdWait& wt);
	virtual void draw							(	bGenericGeoElement* o);
	virtual void rect							(	bGenericGeoElement* o, 
													CGRect* bounds);
	virtual bGenericGraphicContext*
	get_context_for_object						(	bGenericGeoElement* o, 
													int pass,
													bool render);
	virtual bGenericGraphicContext*
	get_context_for_class						(	int clss, 
													int pass,
													bool render);
	
	virtual bGenericType* gettype				(	);
	virtual char* getname						(	);
	virtual bool visible						(	);
	virtual bool selectable						(	);

	virtual int getdrawingmethod				(	);
	virtual char* getclassfield					(	);
	virtual int getpasscount					(	);
	virtual double getscaleref					(	);
	virtual double getunitcoef					(	);
	virtual int getsortkind						(	);
	virtual int getclasscount					(	);
	virtual double getclassbound				(	int idx);
	virtual char* getclassname					(	int idx);
	virtual void set_curclass					(	int idx);
	virtual int get_curclass					(	);
	
	virtual int getmargin						(	);
	
	virtual void report							(	);

	virtual bArray* objsinrect					(	CGRect* cgr, 
													bool strict);
	virtual bArray* objsincircle				(	CGRect* cgr, 
													bool strict);
	virtual bArray* objsinpath					(	CGPoint* cgp, 
													int nb, 
													bool strict);
	virtual bArray* objsatpoint					(	CGPoint* cgp, 
													bool all);
		
	virtual bGenericXMLBaseElement* root		(	);
	virtual void get_styleruns					(	bArray& arr,
													bGenericGeoElement* o,
													double scale,
													int pass);

	virtual bool symb							(	CGContextRef ctx,
													CGRect cgr){return(false);};
	virtual bool legend_size					(	CGSize* sz){return(false);};
	virtual bool legend							(	CGContextRef ctx,
													CGPoint origin){return(false);};

// Privé				
	virtual void settype						(	bGenericType* tp);
	virtual int findclass						(	double val);
			

protected:
				
private:
	bGenericType*			_tp;
	char*					_fieldname;
	int						_fieldindex;
	double					_minbound;
	double					_maxbound;		
	bArray					_valbounds;
	bArray					_styleruns;
	bGenericGraphicContext*	_ctx;
	bGenericXMLBaseElement*	_root;
	int						_curclass;
};

//----------------------------------------------------------------------------

#endif
