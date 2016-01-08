//----------------------------------------------------------------------------
// File : bCalcCCrtDate.h
// Project : MacMap
// Purpose : Header file : Calc creation date interface class
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
// 01/03/2007 creation.
//----------------------------------------------------------------------------

#ifndef __bCalcCCrtDate__
#define __bCalcCCrtDate__

//----------------------------------------------------------------------------

#include <std_ext/bStdCalc.h>

//----------------------------------------------------------------------------

class bCalcCCrtDate : public bStdCalc{
	public:		
		bCalcCCrtDate							(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl);
		virtual ~bCalcCCrtDate					(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);

		virtual void open						(	int* flags);
		virtual void close						(	);
		virtual int kind						(	);
		
	protected:
		virtual void write						(	bStdDBValue* val);

	private:
};

//----------------------------------------------------------------------------

#endif
