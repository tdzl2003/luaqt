@echo off

REM Create temp directory and build two modules.
if not exist make mkdir make
cd make


echo Build module "mocreader".
if not exist mocreader mkdir mocreader
cd mocreader

qmake.exe ..\..\modules\mocreader\build\mocreader\mocreader.pro -r
jom

cd ..

echo Build module "uic".
if not exist uic mkdir uic
cd uic

qmake.exe ..\..\modules\uic\build\uic\uic.pro -r
jom

cd ..

cd ..

if not exist bin mkdir bin
copy make\mocreader\release\mocreader.dll bin\
copy make\uic\release\uic.dll bin\

set LUA_CPATH=./bin/?.dll
set LUA_PATH=./?.lua;./modules/path/?.lua;./third_party/json/?.lua

REM Parse header files.

luajit ./tools/mocparser/main.lua

REM Generate code.
 
luajit ./tools/codegen/main.lua ./tools/codegen/config.json

cd make
if not exists Root mkdir Root
cd Root

qmake ..\..\build\qtpro\Root.pro -r
jom

cd ..
cd ..
REM Copying code
copy make\Root\LuaQt\release\LuaQt.dll bin\
copy make\Root\QtCore\release\QtCore.dll bin\
copy make\Root\QtGui\release\QtGui.dll bin\
copy make\Root\QtWidgets\release\QtWidgets.dll bin\

echo Done.
