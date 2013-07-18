/****************************************************************************
**
** Copyright (C) 2013 tdzl2003.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the tools applications of the LuaQt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MOCREADER_GLOBAL_H
#define MOCREADER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MOCREADER_LIB
# define MOCREADER_EXPORT Q_DECL_EXPORT
#else
# define MOCREADER_EXPORT Q_DECL_IMPORT
#endif

#endif // MOCREADER_GLOBAL_H
