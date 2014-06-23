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

#include "luawriteincludes.h"
#include "../driver.h"
#include "../ui4.h"
#include "../uic.h"
#include "../databaseinfo.h"

#include <QtCore/qdebug.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qtextstream.h>

#include <stdio.h>

QT_BEGIN_NAMESPACE

enum { debugWriteIncludes = 0 };
enum { warnHeaderGeneration = 0 };

struct ClassInfoEntry
{
    const char *klass;
    const char *module;
    const char *header;
};

static const ClassInfoEntry qclass_lib_map[] = {
#define QT_CLASS_LIB(klass, module, header) { #klass, #module, #header },
#include "../qclass_lib_map.h"

#undef QT_CLASS_LIB
};

namespace LUA {

WriteIncludes::WriteIncludes(Uic *uic)
    : m_uic(uic), m_output(uic->output()), m_scriptsActivated(false), m_laidOut(false)
{
    const QString namespaceDelimiter = QLatin1String("::");
    const ClassInfoEntry *classLibEnd = qclass_lib_map + sizeof(qclass_lib_map)/sizeof(ClassInfoEntry);
    for (const ClassInfoEntry *it = qclass_lib_map; it < classLibEnd;  ++it) {
        const QString klass = QLatin1String(it->klass);
        const QString module = QLatin1String(it->module);
        QLatin1String header = QLatin1String(it->header);
		m_classModule.insert(klass, module);
    }
}

void WriteIncludes::acceptUI(DomUI *node)
{
    m_scriptsActivated = false;
    m_laidOut = false;
    m_knownClasses.clear();
	m_knownPackages.clear();

    if (node->elementIncludes())
        acceptIncludes(node->elementIncludes());

    if (node->elementCustomWidgets())
        TreeWalker::acceptCustomWidgets(node->elementCustomWidgets());

    add(QLatin1String("QApplication"));
    add(QLatin1String("QVariant"));
    add(QLatin1String("QAction"));

    add(QLatin1String("QButtonGroup")); // ### only if it is really necessary
    add(QLatin1String("QHeaderView"));

	add(QLatin1String("QFont"));

    TreeWalker::acceptUI(node);
	
	m_output << "local bit = require(\"bit\");\n";

    writeHeaders(m_requires);

    m_output << QLatin1Char('\n');
}

void WriteIncludes::acceptWidget(DomWidget *node)
{
    if (debugWriteIncludes)
        fprintf(stderr, "%s '%s'\n", Q_FUNC_INFO, qPrintable(node->attributeClass()));

    add(node->attributeClass());
    TreeWalker::acceptWidget(node);
}

void WriteIncludes::acceptLayout(DomLayout *node)
{
    add(node->attributeClass());
    m_laidOut = true;
    TreeWalker::acceptLayout(node);
}

void WriteIncludes::acceptSpacer(DomSpacer *node)
{
    add(QLatin1String("QSpacerItem"));
    TreeWalker::acceptSpacer(node);
}

void WriteIncludes::acceptProperty(DomProperty *node)
{
    TreeWalker::acceptProperty(node);
}

void WriteIncludes::insertIncludeForClass(const QString &className)
{
    if (debugWriteIncludes)
        fprintf(stderr, "%s %s\n", Q_FUNC_INFO, qPrintable(className));


    // Known class
    const StringMap::const_iterator it = m_classModule.constFind(className);
    if (it != m_classModule.constEnd()) {
        insertIncludeForPackage(it.value());
        return;
    }

	//TODO: Unknown class
	fprintf(stderr, "Unknown class: %s\n", qPrintable(className));
}

void WriteIncludes::add(const QString &className, bool determineHeader)
{
    if (debugWriteIncludes)
        fprintf(stderr, "%s %s \n", Q_FUNC_INFO, qPrintable(className));

    if (className.isEmpty() || m_knownClasses.contains(className))
        return;

    m_knownClasses.insert(className);

    if (!m_laidOut && m_uic->customWidgetsInfo()->extends(className, QLatin1String("QToolBox")))
        add(QLatin1String("QLayout")); // spacing property of QToolBox)

    if (className == QLatin1String("Line")) { // ### hmm, deprecate me!
        add(QLatin1String("QFrame"));
        return;
    }

    if (determineHeader)
        insertIncludeForClass(className);
}

void WriteIncludes::acceptCustomWidget(DomCustomWidget *node)
{
    const QString className = node->elementClass();
    if (className.isEmpty())
        return;

    if (const DomScript *domScript = node->elementScript())
        if (!domScript->text().isEmpty())
            activateScripts();

    if (!node->elementHeader() || node->elementHeader()->text().isEmpty()) {
        add(className, false); // no header specified
    } else {
        add(className, true);
    }
}

void WriteIncludes::acceptCustomWidgets(DomCustomWidgets *node)
{
    Q_UNUSED(node);
}

void WriteIncludes::acceptIncludes(DomIncludes *node)
{
    TreeWalker::acceptIncludes(node);
}

void WriteIncludes::acceptInclude(DomInclude *node)
{
}

void WriteIncludes::insertIncludeForPackage(const QString &packageName)
{
	if (m_knownPackages.contains(packageName)) {
		return;
	}
    if (debugWriteIncludes)
        fprintf(stderr, "%s %s\n", Q_FUNC_INFO, qPrintable(packageName));

	m_knownPackages.insert(packageName);

    m_requires.insert(packageName, false);
}

void WriteIncludes::writeHeaders(const OrderedSet &headers)
{
	const OrderedSet::const_iterator cend = headers.constEnd();
    for (OrderedSet::const_iterator sit = headers.constBegin(); sit != cend; ++sit) {
		const QString header = sit.key();
        if (!header.trimmed().isEmpty()) {
            m_output << "require(\"" << header << "\")\n";
        }
    }
}

void WriteIncludes::acceptWidgetScripts(const DomScripts &scripts, DomWidget *, const  DomWidgets &)
{
    if (!scripts.empty()) {
        activateScripts();
    }
}

void WriteIncludes::activateScripts()
{
    if (!m_scriptsActivated) {
        add(QLatin1String("QScriptEngine"));
        add(QLatin1String("QDebug"));
        m_scriptsActivated = true;
    }
}
} // namespace LUA

QT_END_NAMESPACE
