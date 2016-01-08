//----------------------------------------------------------------------------
// File : CocoaStuff.h
// Project : MacMap
// Purpose : Header file : Cocoa C wrappers
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
// 19/06/2008 creation.
//----------------------------------------------------------------------------

#ifndef __CocoaStuff__
#define __CocoaStuff__

//----------------------------------------------------------------------------

#import "bXMapMakeConstraints.h"

//----------------------------------------------------------------------------
// Pour test suite à bug quand on surclasse à partir de bStdNSAppModalWindowController.
// Dans ce cas, l'appel d'une IBAction vers la classe C++ bXMapMakeConstraint ne
// pas. La référence à la classe de _ext semble perdue et pointe donc vers 
// bGenericExt, ce qui provoque le crash.
// Pourtant le pointeur _ext vers l'instance contient la bonne addresse.
// Pas trouvé non plus d'action qui aurait pu écraser une partie de l'instance.
// Problème dans le linker ?

#define	_MCAsSubClasser_ 0

//----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------

#if _MCAsSubClasser_
void	runCocoaAppModal	(	bGenericExt* ext,
#else
void	runCocoaAppModal	(	bXMapMakeConstraints* ext,
#endif
								long* code);

//----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

//----------------------------------------------------------------------------

#endif
