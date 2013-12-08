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

#include "luawritedeclaration.h"
//#include "luawriteicondeclaration.h"
#include "luawriteinitialization.h"
//#include "luawriteiconinitialization.h"
//#include "luaextractimages.h"
#include "../driver.h"
#include "../ui4.h"
#include "../uic.h"
#include "../databaseinfo.h"
#include "../customwidgetsinfo.h"

#include <QtCore/qtextstream.h>
#include <QtCore/qdebug.h>

QT_BEGIN_NAMESPACE

namespace LUA {

WriteDeclaration::WriteDeclaration(Uic *uic)  :
    m_uic(uic),
    m_driver(uic->driver()),
    out(uic->output()),
    m_option(uic->option())
{
}

void WriteDeclaration::acceptUI(DomUI *node)
{
	QString qualifiedClassName = node->elementClass() + m_option.postfix;
	QString className = qualifiedClassName;

	QString varName = m_driver->findOrInsertWidget(node->elementWidget());
    QString widgetClassName = node->elementWidget()->attributeClass();

	out << "local ui_" << className << " = {}\n";

	TreeWalker::acceptWidget(node->elementWidget());

	WriteInitialization(m_uic).acceptUI(node);

	out << "return ui_" << className << "\n";

}

void WriteDeclaration::acceptWidget(DomWidget *node)
{
    TreeWalker::acceptWidget(node);
}

void WriteDeclaration::acceptSpacer(DomSpacer *node)
{
     TreeWalker::acceptSpacer(node);
}

void WriteDeclaration::acceptLayout(DomLayout *node)
{
    TreeWalker::acceptLayout(node);
}

void WriteDeclaration::acceptActionGroup(DomActionGroup *node)
{
    TreeWalker::acceptActionGroup(node);
}

void WriteDeclaration::acceptAction(DomAction *node)
{
    TreeWalker::acceptAction(node);
}

void WriteDeclaration::acceptButtonGroup(const DomButtonGroup *buttonGroup)
{
    TreeWalker::acceptButtonGroup(buttonGroup);
}

} // namespace CPP

QT_END_NAMESPACE
