//----------------------------------------------------------------------------
// File : bXMLfcalcUser.h
// Project : MacMap
// Purpose : Header file : user calc tag class, used in formulas
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
// For user calc access, when embeded in user calc
//----------------------------------------------------------------------------
// 06/12/2005 creation.
//----------------------------------------------------------------------------

#ifndef __bXMLfcalcUser__
#define __bXMLfcalcUser__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLCalc.h>

//----------------------------------------------------------------------------

class bfcalcUserElement : public bStdXMLCalc{
	public:		
		bfcalcUserElement						(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bfcalcUserElement				(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);
		virtual bool solve						(	bStdSolver* ctx);
	
	private:
		bGenericXMLFormulaElement*	_root;
};

//----------------------------------------------------------------------------

#endif
