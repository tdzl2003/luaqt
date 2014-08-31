luaQt
=====

Lua(JIT) wrapper for QT

News
----

Lua-Qt Meta language's sample was at [here](https://github.com/tdzl2003/luaqt/blob/master/test/testwidget/loginwindow-ml/LoginWindow.lua)

Please let me know what do you think about it.

Any question/review/suggesting about luaqt will be good for me&luaqt.

contact me with:

QQ: 402740419

E-mail: tdzl2003@gmail.com

Prerequisites(Windows)
----------------------

1. Install Visual Studio (2010 or higher). The freely downloadable [Express Edition](http://www.microsoft.com/Express/VC/) works just fine.

    Currently, only 2013 was tested. Other versions should also work.

2. Download and install [Qt](http://qt-project.org/downloads).

    Currently, only 5.3.1 was tested. Other versions should also work.

3. Download and build [luajit](http://luajit.org/download.html). Follow [this guide](http://luajit.org/install.html#windows).

    Any versions higher than 2.0.0 should work.


Install
-------

1. Add luajit src directory(eg C:\LuaJIT-2.0.3\src) to THREE environment variables: `PATH`, `INCLUDE`, `LIB`

2. Set environment variable `QT_HOME` as home directory of Qt SDK(Not Qt installation directory)(eg, C:\Qt\Qt5.3.1\5.3\msvc2013_opengl)

3. Add both Qt SDK bin directory(eg C:\Qt\Qt5.3.1\5.3\msvc2013_opengl\bin) and Qt Creator bin directory(eg C:\Qt\Qt5.3.1\Tools\QtCreator\bin\) to enviroment variable `PATH`

4. Run `Developer Command Prompt` for Visual Studio

5. Goto luaqt directory and run `msvcbuild.bat`

```
cd C:\luaqt
msvcbuild
```

6. Get your libraries from luaqt\bin, or add it to `PATH`

