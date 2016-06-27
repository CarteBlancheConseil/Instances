//----------------------------------------------------------------------------
// File : main.h
// Project : MacMap
// Purpose : Header file : Plugin entry point
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
// 26/08/2005 creation.
//----------------------------------------------------------------------------

#include <mox_intf/bGenericXMLBaseElement.h>
#include <mox_intf/bGenericMacMapApp.h>

//----------------------------------------------------------------------------

#include "bXMLBool.h"
#include "bXMLContainer.h"
#include "bXMLDirectory.h"
#include "bXMLFloat.h"
#include "bXMLFormula.h"
#include "bXMLInt.h"
#include "bXMLName.h"
#include "bXMLObject.h"
#include "bXMLParam.h"
#include "bXMLPath.h"
#include "bXMLSign.h"
#include "bXMLVersion.h"
#include "bXMLClassBound.h"
#include "bXMLClassBoundsArray.h"
#include "bXMLClassField.h"
#include "bXMLClassMax.h"
#include "bXMLClassMin.h"
#include "bXMLClassName.h"
#include "bXMLSort.h"
#include "bXMLAlpha.h"
#include "bXMLBgFill.h"
#include "bXMLBlack.h"
#include "bXMLBlue.h"
#include "bXMLCyan.h"
#include "bXMLFill.h"
#include "bXMLFillPattern.h"
#include "bXMLGreen.h"
#include "bXMLMagenta.h"
#include "bXMLRed.h"
#include "bXMLStroke.h"
#include "bXMLStrokePattern.h"
#include "bXMLYellow.h"
#include "bXMLDBBool.h"
#include "bXMLDBChar.h"
#include "bXMLDBDate.h"
#include "bXMLDBField.h"
#include "bXMLDBFloat.h"
#include "bXMLDBInt.h"
#include "bXMLDBSelKind.h"
#include "bXMLDBTime.h"
#include "bXMLDBType.h"
#include "bXMLDBUseMasked.h"
#include "bXMLColorField8.h"
#include "bXMLColorField16M.h"
#include "bXMLField.h"
#include "bXMLValue.h"
#include "bXMLStrLen.h"
#include "bXMLStrLwr.h"
#include "bXMLStrSntFCUpr.h"
#include "bXMLStrUpr.h"
#include "bXMLStrWrdFCUpr.h"
#include "bXMLArrow.h"
#include "bXMLCentroid.h"
#include "bXMLDecal.h"
#include "bXMLLineTo.h"
#include "bXMLOffsetCoord.h"
#include "bXMLPointJustification.h"
#include "bXMLPolyJustification.h"
#include "bXMLSmooth.h"
#include "bXMLLayer.h"
#include "bXMLLayerArray.h"
#include "bXMLSelectable.h"
#include "bXMLStyle.h"
#include "bXMLType.h"
#include "bXMLView.h"
#include "bXMLVisible.h"
#include "bXMLAnd.h"
#include "bXMLBeginWith.h"
#include "bXMLContain.h"
#include "bXMLDiv.h"
#include "bXMLEndWith.h"
#include "bXMLEqual.h"
#include "bXMLHigher.h"
#include "bXMLHigherOrEqual.h"
#include "bXMLLower.h"
#include "bXMLLowerOrEqual.h"
#include "bXMLMinus.h"
#include "bXMLMult.h"
#include "bXMLNotEqual.h"
#include "bXMLOr.h"
#include "bXMLPlus.h"
#include "bXMLPow.h"
#include "bXMLStrCat.h"
#include "bXMLPass.h"
#include "bXMLPassCount.h"
#include "bXMLAngle.h"
#include "bXMLCap.h"
#include "bXMLCharSpacing.h"
#include "bXMLDash.h"
#include "bXMLFont.h"
#include "bXMLHSize.h"
#include "bXMLImage.h"
#include "bXMLJoin.h"
#include "bXMLLeading.h"
#include "bXMLMiterLimit.h"
#include "bXMLPDFDocument.h"
#include "bXMLPropSize.h"
#include "bXMLPropWidth.h"
#include "bXMLRaster.h"
#include "bXMLSize.h"
#include "bXMLSubStyle.h"
#include "bXMLText.h"
#include "bXMLVSize.h"
#include "bXMLWidth.h"
#include "bXMLWordSpacing.h"
#include "bXMLScaleMax.h"
#include "bXMLScaleMin.h"
#include "bXMLScaleRef.h"
#include "bXMLUnitCoef.h"
#include "bXMLCondition.h"
#include "bXMLGeometry.h"
#include "bXMLGlobals.h"
#include "bXMLRender.h"
#include "bXMLStdGeometry.h"
#include "bXMLStyleIdentification.h"
#include "bXMLStyleRun.h"
#include "bXMLValidity.h"
#include "bXMLCircleStyle.h"
#include "bXMLIconStyle.h"
#include "bXMLPolygonStyle.h"
#include "bXMLPolylineStyle.h"
#include "bXMLRasterStyle.h"
#include "bXMLRectStyle.h"
#include "bXMLTextStyle.h"
#include "bXMLfcalcUser.h"
#include "bXMLfmacroUser.h"
#include "bXMLfvarUser.h"
#include "bXMLSubStyleRun.h"
#include "bXMLSubGlobals.h"
#include "bXMLSubRender.h"
#include "bXMLSubClassBound.h"
#include "bXMLSubClassBoundsArray.h"
#include "bXMLSubClassField.h"
#include "bXMLSubClassName.h"

#include "bXMLFact.h"
#include "bXMLCeil.h"
#include "bXMLCos.h"
#include "bXMLExp.h"
#include "bXMLFloor.h"
#include "bXMLInv.h"
#include "bXMLLn.h"
#include "bXMLLog.h"
#include "bXMLNot.h"
#include "bXMLRound.h"
#include "bXMLSin.h"
#include "bXMLSqr.h"
#include "bXMLTan.h"
#include "bXMLSqrt.h"

#include "bXMLAverage.h"
#include "bXMLFirst.h"
#include "bXMLLast.h"
#include "bXMLMax.h"
#include "bXMLMedian.h"
#include "bXMLMin.h"
#include "bXMLProduct.h"
#include "bXMLSingle.h"
#include "bXMLStdDeviation.h"
#include "bXMLSum.h"
#include "bXMLVariance.h"

#include "bXMLModulo.h"
#include "bXMLXOr.h"

#include "bXMLShiftX.h"
#include "bXMLShiftY.h"
#include "bXMLLegible.h"

#include "bXMLStartAngle.h"
#include "bXMLEndAngle.h"
#include "bXMLPropAngle.h"
#include "bXMLPropColor.h"

#include "bXMLScript.h"
#include "bXMLString.h"

#include "bXMLVirtualLayer.h"

#include "bXMLDBQuestion.h"
#include "bXMLDBSetNext.h"
#include "bXMLDBAddToContrast.h"
#include "bXMLDBAddToMasked.h"

#include "bXMLScreenGeometry.h"
#include "bXMLPrintAreaGeometry.h"
#include "bXMLWMSRaster.h"

#include "bXMLBoxPos.h"

#include "bXMLfCast.h"
#include "bXMLiCast.h"

#include "bXMLBgStroke.h"
#include "bXMLBgWidthMaj.h"
#include "bXMLBgHeightMaj.h"
#include "bXMLBgWidth.h"
#include "bXMLRoundedRadius.h"
#include "bXMLBgShiftX.h"
#include "bXMLBgShiftY.h"

#include "bXMLPropHVSize.h"
#include "bXMLHVSizeJustification.h"

#include "bXMLNthChar.h"
#include "bXMLTextRptJustification.h"

#include "bXMLGoogleMap.h"
#include "bXMLTMSRaster.h"

#include "bXMLPerpendicularLine.h"

#include "bXMLCollection.h"
#include "bXMLObjectSet.h"

#include "bXMLVertexGeometry.h"

//----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//----------------------------------------------------------------------------

void init		(	bGenericXMLBaseElement **elt,
					bGenericMacMapApp* gapp, 
					CFBundleRef bndl);
void destroy	(	bGenericXMLBaseElement *elt);

//----------------------------------------------------------------------------
								
#ifdef __cplusplus
}
#endif

//----------------------------------------------------------------------------
