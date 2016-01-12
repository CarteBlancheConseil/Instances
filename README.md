# Instances

Instances is the repository that contains all externs Xcode project. These projects generate plugins that are used by MacMap.
Externs are plugins that have various functions :
- Calc : functions that return a result (lenght, area...)
- Geog : functions that deals with geographic query (inside, containing...)
- Tool : functions that manage mouse and user interface with the main mapping window (select, zoom, scroll...)
- UserExt : umbrella functions that allows the user to create its own function (calc, macro, script...)
- Var : functions that return a result (π, current date...)
- XBox : functions for palettes windows managment
- XMap : generic functions (spreadsheet, undo/redo...)
- vDef : functions to define the graphical representation of objects


**Compilation :**
You can open each project with Xcode then compile, or use xcodebuild in a terminal window. As plugins are linked to MacMap frameworks, you have to build MacMapSuite.framework, MacMapStats.framework, and internal MacMap frameworks (mox_intf.framework, std_ext.framework...) before building components.

Note: MacMap projects are currently built with Xcode 6 against Mac OS X 10.8 SDK.

**Installation location :**
Plugins are installed in the standard MacMap plugins directory.
