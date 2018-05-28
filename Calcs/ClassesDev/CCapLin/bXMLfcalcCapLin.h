//----------------------------------------------------------------------------
// File : bXMLfcalcCapLin.h
// Project : MacMap
// Purpose : Header file : Calc CapLin formula class. Return angle between start and end point of a line.
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2017 Carte Blanche Conseil.
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
// 28/04/2017 creation.
//----------------------------------------------------------------------------

#ifndef __bXMLfcalcCapLin__
#define __bXMLfcalcCapLin__

//----------------------------------------------------------------------------

#include <std_ext/bStdXMLCalc.h>

//----------------------------------------------------------------------------

class bfcalcCapLinElement : public bStdXMLCalc{
	public:		
		bfcalcCapLinElement					(	bGenericXMLBaseElement* elt, 
													bGenericMacMapApp* gapp, 
													CFBundleRef bndl );
		virtual ~bfcalcCapLinElement			(	);
		virtual bGenericXMLBaseElement* create	(	bGenericXMLBaseElement* elt);
		
		virtual void init						(	void* ctx);
		virtual bool solve						(	bStdSolver* ctx);
			
	private:
};

//----------------------------------------------------------------------------

#endif
