//----------------------------------------------------------------------------
// File : bvDefVirtualWMSStyle.h
// Project : MacMap
// Purpose : Header file : WMS vdef style class
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
// 13/07/2013 creation.
//----------------------------------------------------------------------------

#ifndef __bvDefVirtualWMSStyle__
#define __bvDefVirtualWMSStyle__

//----------------------------------------------------------------------------

#include <vdef_lib/bvDefVirtualStyle.h>
#include <MacMapSuite/WMSCapabilitiesParser.h>

//----------------------------------------------------------------------------

class bvDefVirtualWMSStyle : public bvDefVirtualStyle{
public:
	bvDefVirtualWMSStyle			(	bGenericMacMapApp* gapp);
	virtual ~bvDefVirtualWMSStyle	(	);
	
	virtual bool load				(	bGenericXMLBaseElement* root);
	virtual bool dump				(	bArray& arr, 
										int indent);
	
    char	_url[1024];
    bool    _https;
    char	_usr[1024];
    char	_pwd[1024];
	char	_layer[256];
	char	_style[256];
	char	_fmt[256];
	int		_srs;
	double	_alpha;
	
protected:													
	void	parse_url				(	);
	
private:
	
};

//----------------------------------------------------------------------------

#endif
