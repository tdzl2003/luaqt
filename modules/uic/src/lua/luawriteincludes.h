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

#ifndef CPPWRITEINCLUDES_H
#define CPPWRITEINCLUDES_H

#include "../treewalker.h"

#include <QtCore/qhash.h>
#include <QtCore/qmap.h>
#include <QtCore/qset.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE

class QTextStream;
class Driver;
class Uic;

namespace LUA {

struct WriteIncludes : public TreeWalker
{
    WriteIncludes(Uic *uic);

    void acceptUI(DomUI *node);
    void acceptWidget(DomWidget *node);
    void acceptLayout(DomLayout *node);
    void acceptSpacer(DomSpacer *node);
    void acceptProperty(DomProperty *node);
    void acceptWidgetScripts(const DomScripts &, DomWidget *, const DomWidgets &);

//
// custom widgets
//
    void acceptCustomWidgets(DomCustomWidgets *node);
    void acceptCustomWidget(DomCustomWidget *node);

//
// include hints
//
    void acceptIncludes(DomIncludes *node);
    void acceptInclude(DomInclude *node);

    bool scriptsActivated() const { return m_scriptsActivated; }

private:
    void add(const QString &className, bool determineHeader = true);

private:
    typedef QMap<QString, bool> OrderedSet;
    void insertIncludeForClass(const QString &className);
	void insertIncludeForPackage(const QString &packageName);
    void activateScripts();

	void writeHeaders(const OrderedSet &headers);

    const Uic *m_uic;
    QTextStream &m_output;

    QSet<QString> m_knownClasses;
	QSet<QString> m_knownPackages;

    typedef QMap<QString, QString> StringMap;
	StringMap		m_classModule;

	OrderedSet m_requires;


    bool m_scriptsActivated;
    bool m_laidOut;
};

} // namespace CPP

QT_END_NAMESPACE

#endif // CPPWRITEINCLUDES_H
