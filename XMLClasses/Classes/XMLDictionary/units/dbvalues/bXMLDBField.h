//----------------------------------------------------------------------------
// File : bXMLDBField.h
// Project : MacMap
// Purpose : Header file : database field tag class, used in solvers
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
// 09/03/2004 creation.
//----------------------------------------------------------------------------

#ifndef __bDBFieldElement__
#define __bDBFieldElement__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLDBField.h>

//----------------------------------------------------------------------------

typedef void (*io_proc)	(	bGenericGeoElement*,
							int,
							bStdDBValue*);

//----------------------------------------------------------------------------

class bDBFieldElement : public bStdXMLDBField{

	public:
		bDBFieldElement 						(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bDBFieldElement  				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);
		virtual bool solve						(	bStdSolver* ctx);
		virtual void reset						(	bStdSolver* ctx);
		
	private:
		static void	io_int						(	bGenericGeoElement* o,
													int idx,
													bStdDBValue* v);
		static void	io_dbl						(	bGenericGeoElement* o,
													int idx,
													bStdDBValue* v);
		static void	io_chr						(	bGenericGeoElement* o,
													int idx,
													bStdDBValue* v);
																										
		int				_idx;
		int				_kind;
		bCharDBValue	_crv;
		bBoolDBValue	_blv;
		bIntDBValue		_itv;
		bDoubleDBValue	_dbv;
		bDateDBValue	_dtv;
		bTimeDBValue	_tmv;
		io_proc			_io;
};
									
//----------------------------------------------------------------------------

#endif
