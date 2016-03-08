//----------------------------------------------------------------------------
// File : bXMapMakeConstraints.h
// Project : MacMap
// Purpose : Header file : XMap make constraints class
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
// 22/12/2010 creation.
//----------------------------------------------------------------------------

#ifndef __bXMapMakeConstraints__
#define __bXMapMakeConstraints__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMap.h>
#include <std_ext/bXMapStdIntf.h>
#include <Carbon/Carbon.h>

//----------------------------------------------------------------------------

class bXMapMakeConstraints : public bStdXMap{
	public:		
		bXMapMakeConstraints					(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bXMapMakeConstraints			(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
				
		virtual bool test						(	void* prm);
		virtual bool edit						(	void* prm);
	
		virtual bool process					(	int msg,
													void* prm);
													
		virtual void* get_prm					(	);
		virtual void set_prm					(	const void* prm);
		
		virtual bool do_remove					(	bGenericType* tp,
													long field,
													long constraint);
		virtual bool do_add						(	bGenericType* tp,
													long field,
													long kind,
													void* value);
		virtual bool do_modify					(	bGenericType* tp,
													long field,
													long constraint,
													void* value);
		virtual bool do_make_from_field			(	bGenericType* tp,
													long field,
													long srcfield,
													bool usevalue);
		
//		virtual void do_beep();
			
	protected:
		static int analyse_char					(	void *o, 
													void *prm);
		static int analyse_int					(	void *o, 
													void *prm);
		static int analyse_double				(	void *o, 
													void *prm);
		static int fill_char					(	void *o, 
													void *prm);
		static int fill_int						(	void *o, 
													void *prm);
		static int fill_double					(	void *o, 
													void *prm);
	
	private:
		MakeConstraints_prm	_prm;
};

//----------------------------------------------------------------------------

#endif
