//----------------------------------------------------------------------------
// File : bXMapSelectorCriterion.h
// Project : MacMap
// Purpose : Header file : XMap selector utility (selection criterion)
// Author : Benoit Ogier, benoit.ogier@macmap.com
//
// Copyright (C) 2005 Carte Blanche Conseil.
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
// 20/01/2005 creation.
//----------------------------------------------------------------------------

#ifndef __bXMapSelectorCriterion__
#define __bXMapSelectorCriterion__

//----------------------------------------------------------------------------

#include <mox_intf/bGenericMacMapApp.h>
#include <mox_intf/bGenericType.h>
#include <mox_intf/bGenericGeog.h>
#include <mox_intf/bGenericXMLBaseElement.h>
#include <MacMapSuite/bArray.h>

//----------------------------------------------------------------------------

#define kEqualElement			1000//'oeql'
#define kNotEqualElement		1001//'oneq'
#define kLowerElement			1002//'olwr'
#define kLowerOrEqualElement	1003//'olwe'
#define kHigherElement			1004//'ohgr'
#define kHigherOrEqualElement	1005//'ohge'
#define kContainElement			1006//'ocnt'
#define kBeginWithElement		1007//'obeg'
#define kEndWithElement			1008//'oend'

#define kDBFieldElement			2000//'vfld'

#define kAndElement             3000
#define kOrElement              3001
#define kXOrElement             3002

//----------------------------------------------------------------------------

class bXMapSelectorCriterion{
public:
    bXMapSelectorCriterion				(	bGenericMacMapApp* gapp,
                                            int targetsign,
                                            char* targetvalue,
                                            int targetkind,
                                            int opsgn,
                                            char* val,
                                            bool* succed,
                                            int cntop);
    virtual ~bXMapSelectorCriterion		(	);
    virtual int get_id					(	){return _id;};
    virtual int get_cntop				(	){return _cntop;};
    virtual bool make					(	bArray* l,
                                            int indent,
                                            CFBundleRef bndl);
    virtual CFStringRef	get_string		(	CFBundleRef bndl,
                                            bool last);
    
    static bool parse					(	bGenericXMLBaseElement* root, 
                                            void* prm,
                                            int indent);
protected:
    
private:
    static bGenericMacMapApp* _gapp;
    static long _cid;
    int         _id;
    int         _cntop;
    int         _tgsign;
    char*       _tgname;
    char*       _tgvalue;
    char*       _opname;
    char*       _valname;
    char*       _valvalue;
};

//----------------------------------------------------------------------------

typedef struct parse_prm{
	bArray*					stack;
		
	bGenericType*			tp;
	int						selwhat;
	bool					use_mask;
	
	UInt32					next;
	bool					add2cnt;
	int						add2hdn;

	bGenericGeog*			geog;
		
//	int						cid;
	int						targetsign;
	char					targetvalue[_values_length_max_];
	int						targetkind;
	int						opsgn;
	char					val[_values_length_max_];
    
    int						cntop;
    
    bArray*					stackop;

}parse_prm;

//----------------------------------------------------------------------------

#endif
