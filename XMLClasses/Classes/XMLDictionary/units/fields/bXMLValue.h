//----------------------------------------------------------------------------
// File : bXMLValue.h
// Project : MacMap
// Purpose : Header file : value tag class, used in styles
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
// 22/10/2003 creation.
//----------------------------------------------------------------------------

#ifndef __XMLVALUECLASSE__
#define __XMLVALUECLASSE__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLValueElement.h>

//----------------------------------------------------------------------------

class bValueElement : public bStdXMLValueElement {
	public:
		bValueElement 							(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bValueElement  				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
				
		virtual void getvalue					(	bGenericGeoElement* geo, 
													char* value);
 		virtual void getvalue					(	bGenericGeoElement* geo, 
													bool* value);
 		virtual void getvalue					(	bGenericGeoElement* geo, 
													int* value);
 		virtual void getvalue					(	bGenericGeoElement* geo, 
													double* value);
};

//----------------------------------------------------------------------------

#endif
