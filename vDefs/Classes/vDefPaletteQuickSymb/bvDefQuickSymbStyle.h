//----------------------------------------------------------------------------
// File : bvDefQuickSymbStyle.h
// Project : MacMap
// Purpose : Header file : Symbols vdef style class
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
// 26/06/2012 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefQuickSymbStyle__
#define __bvDefQuickSymbStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefPaletteQuickStyle.h>

//----------------------------------------------------------------------------

class bvDefQuickSymbStyle : public bvDefPaletteQuickStyle{
	public:
		bvDefQuickSymbStyle				(	bGenericMacMapApp* gapp,
											bGenericType* gtp,
											int clss);
		virtual ~bvDefQuickSymbStyle	(	);
		
		virtual bool load				(	bGenericXMLBaseElement* root);
		virtual bool dump				(	bArray& arr, 
											int indent);
											
		double		_h;
		int			_fh;
		double		_v;
		int			_fv;
		double		_a;
		int			_fa;
		char		_smb[256];
		int			_fsmb;
		double		_alpha;
		int			_falpha;
		static bool	_centro;
	
	protected:													
	
	private:
	
};

//----------------------------------------------------------------------------

#endif
