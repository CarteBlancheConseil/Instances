//----------------------------------------------------------------------------
// File : bXMLfcalcUpdtTime.h
// Project : MacMap
// Purpose : Header file : Calc modification time formula class. Return object's modification time.
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
// 20/02/2007 creation.
//----------------------------------------------------------------------------

#ifndef __bXMLfcalcUpdtTime__
#define __bXMLfcalcUpdtTime__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLCalc.h>

//----------------------------------------------------------------------------

class bfcalcUpdtTimeElement : public bStdXMLCalc{
	public:		
		bfcalcUpdtTimeElement					(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bfcalcUpdtTimeElement			(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual bool solve						(	bStdSolver* ctx);
};

//----------------------------------------------------------------------------

#endif
