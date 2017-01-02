//----------------------------------------------------------------------------
// File : main.cpp
// Project : MacMap
// Purpose : C++ source file : Plugin entry point
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
// 09/02/2006 creation.
//----------------------------------------------------------------------------

#include "main.h"
#include <MacMapSuite/bTrace.h>

// ---------------------------------------------------------------------------
// 
// ------------
void init(bGenericXMLBaseElement **elt,bGenericMacMapApp* gapp, CFBundleRef bndl){
_bTrace_("XMLDictionnary::init",true);
	(*elt)=new bBoolElement(NULL,gapp,bndl);

bGenericXMLBaseElement*	chld;
	
	chld=new bContainerElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDirectoryElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFloatElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bIntElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bObjectElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bNameElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
    chld=new bAlternativeNameElement(*elt,gapp,bndl);
    gapp->classMgr()->AddXMLClass(chld);
	chld=new bParamElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPathElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSignElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bVersionElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bClassBoundElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bClassBoundsArrayElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bClassFieldElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bClassMaxElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bClassMinElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bClassNameElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSortElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bAlphaElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bBackElement(*elt,gapp,bndl);// Pour compatibilité
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bBlackElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bBlueElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bCyanElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFillElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFillPatternElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bGreenElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bMagentaElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bRedElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrokeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrokePatternElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bYellowElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBBoolElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBCharElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBDateElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBFieldElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBFloatElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBIntElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBSelKindElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBTimeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBTypeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBUseMaskedElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bColorField8Element(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bColorField16MElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bv160ColorFieldElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFieldElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bValueElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrLenElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrLwrElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrSntFCUprElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrUprElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrWrdFCUprElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bArrowElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bCentroidElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDecalElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLineToElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bOffsetCoordElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPointJustificationElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPolyJustificationElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSmoothElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLayerElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLayerArrayElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSelectableElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bTypeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bViewElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bVisibleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bAndElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bBeginWithElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bContainElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDivElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bEndWithElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bEqualElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFormulaElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bHigherElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bHigherOrEqualElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLowerElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLowerOrEqualElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bMinusElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bMultElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bNotEqualElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bOrElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPlusElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPowElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStrCatElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPassElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPassCountElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bAngleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bCapElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bCharSpacingElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDashElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFontElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bHSizeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bImageElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bJoinElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLeadingElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bMiterLimitElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPDFDocumentElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPropSizeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPropWidthElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bRasterElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSizeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bTextElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bVSizeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bWidthElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bWordSpacingElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bScaleMaxElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bScaleMinElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bScaleRefElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bUnitCoefElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bConditionElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bGeometryElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bGlobalsElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bRenderElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStdGeometryElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStyleIdentificationElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStyleRunElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bValidityElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bCircleStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bIconStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPolygonStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPolylineStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bRasterStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bRectStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bTextStyleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bfcalcUserElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bfmacroUserElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bfvarUserElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubStyleRunElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubGlobalsElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubRenderElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubClassBoundElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubClassBoundsArrayElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubClassFieldElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSubClassNameElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bFactElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bCeilElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bCosElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bExpElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFloorElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bInvElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLnElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLogElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bNotElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bRoundElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSinElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSqrElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bTanElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSqrtElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bAverageElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bFirstElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLastElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bMaxElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bMinElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bMedianElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bProductElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSingleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStdDeviationElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bSumElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bVarianceElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bModuloElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bXOrElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bShiftXElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bShiftYElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bLegibleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bStartAngleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bEndAngleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPropAngleElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPropColorElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bScriptElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bStringElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bVirtualLayerElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bDBQuestionElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	
	chld=new bDBSetNextElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBAddToContrastElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bDBAddToMaskedElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bScreenGeometryElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPrintAreaGeometryElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bWMSRasterElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	
	chld=new bBoxPosElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bfCastElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new biCastElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bBgFillElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bBgStrokeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bBgWidthMajElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bBgHeightMajElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bBgWidthElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bRoundedRadiusElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bBgShiftXElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bBgShiftYElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	

	chld=new bPropHSizeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bPropVSizeElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	
	chld=new bHSizeJustificationElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);
	chld=new bVSizeJustificationElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bNthCharElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bTextRptJustificationElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);

	chld=new bGoogleMapElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	
	chld=new bTMSRasterElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	

	chld=new bPerpendicularLineElement(*elt,gapp,bndl);
	gapp->classMgr()->AddXMLClass(chld);	

    chld=new bCollectionElement(*elt,gapp,bndl);
    gapp->classMgr()->AddXMLClass(chld);
    chld=new bObjectSetElement(*elt,gapp,bndl);
    gapp->classMgr()->AddXMLClass(chld);

    chld=new bVertexGeometryElement(*elt,gapp,bndl);
    gapp->classMgr()->AddXMLClass(chld);
}

// ---------------------------------------------------------------------------
// 
// ------------
void destroy(bGenericXMLBaseElement *elt){
_bTrace_("XMLDictionnary::destroy",true);
	delete (bStdXMLBaseElement*)(void*)elt;
}
