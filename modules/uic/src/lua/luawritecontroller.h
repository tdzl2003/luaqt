#ifndef luawritecontroller_h
#define luawritecontroller_h
#include "../treewalker.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>
QT_BEGIN_NAMESPACE
class QTextStream;
class Driver;
class Uic;

struct Option;

namespace LUA {
	struct WriteController : public TreeWalker
{
    WriteController(Uic *uic);

	void acceptConnections(DomConnections *connection);

    void acceptUI(DomUI *node);
	void acceptWidget( DomWidget*  widget);//node->elementWidget()
	bool Recursive_Slot(QString&, DomConnection*);

	QString findDeclaration(const QString &name);

    QMultiMap<QString,QString> m_multiMap;
	//include 
	//class declertion
	//slot
	

    //void acceptActionGroup(DomActionGroup *node);
    //void acceptAction(DomAction *node);
    //void acceptButtonGroup(const DomButtonGroup *buttonGroup);

private:
	QLatin1String m_indent;
    Uic *m_uic;
    Driver *m_driver;
    QTextStream &out;
    const Option &m_option;
};
}
QT_END_NAMESPACE

#endif