#include "luawritecontroller.h"
#include "..\uic.h"
#include "..\ui4.h"
#include "..\option.h"
#include "..\driver.h"
#include <fstream>
#pragma comment(lib, "jsoncpp.lib")
#include "json/json.h"
using namespace LUA;
WriteController::WriteController(Uic *uic) :
    m_uic(uic),
    m_driver(uic->driver()),
    out(uic->cl_output()),
    m_option(uic->option()),
	m_indent("\t")
{
	
}

void WriteController::acceptUI(DomUI *node)
{
	QString qualifiedClassName = node->elementClass() + m_option.postfix;
	QString className = qualifiedClassName;
	QString varName = m_driver->findOrInsertWidget(node->elementWidget());
    QString widgetClassName = node->elementWidget()->attributeClass();

	out << "local LuaQtHelper = require(\"LuaQtHelper\")\n";
	out << "local LuaQt = require(\"LuaQt\")\n";

	//includes
	
	//class declertion
	out << "local ui_" << varName << " = require(\"ui_" << varName << "\")\n";
	out << "\n";
	out << "local " << varName << " = {\n";
	out << m_indent << "className = \"" << className << "\",\n";
	out << m_indent << "superClass = "<< widgetClassName << " ,\n";
	out << "}\n";
	out << "\n";

	out << "local function new" << varName << "(mo, parent)\n";
	out << m_indent  << "local self = "<<widgetClassName<<".newExtended(mo, parent)\n";
	out << m_indent  << "self.ui = ui_" << varName << ".setupUi(self)\n";
	out << m_indent  << "return self\n";
	out << "end\n";
	out << "\n";
	out << "LuaQtHelper.addConstructor( " << varName << ", {\"QWidget*\"}, new"<<varName <<")\n";
	//out << "local ui_" << className << " = {}\n";
	acceptWidget(node->elementWidget());
	acceptConnections(node->elementConnections());

	//WriteInitialization(m_uic).acceptUI(node);
	out<< varName<< " = LuaQtHelper.defineQtClass("<<varName<<") "<< "\n";
	out << "return " << className << "\n";
}
bool WriteController::Recursive_Slot(QString& qstrfilename, DomConnection* connection)
{
	qstrfilename += ".json";
	qstrfilename.insert(0,"..\\tmp\\");
	char *pch;
	QByteArray ba = qstrfilename.toLatin1(); 
	pch=ba.data();
	std::ifstream ifs;
	ifs.open(pch);
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		ifs.close();
		return false;
	}
	int j = 0;
	const Json::Value arrayslotList = root["slotList"];
	QString qstrelementSlot = connection->elementSlot();
	for(j = 0;j < arrayslotList.size();j++)
	{
		Json::Value valslotList = root["slotList"][j];
		std::string strSlot = valslotList["name"].asString();  
		QString qstrSlot = QString::fromStdString(strSlot);
		if(qstrelementSlot.indexOf(qstrSlot) != -1)
		{
			break;
		}
		else
		{
		}
	}
	if(j == arrayslotList.size())
	{
		int k = 0;
		const Json::Value arraysuperclass = root["superclassList"];
		for(k = 0;k < arraysuperclass.size();k++)
		{
			Json::Value valsuperclass = root["superclassList"][k];
			std::string strsuperclass = valsuperclass["name"].asString(); 
			QString qstrsuperclass = QString::fromStdString(strsuperclass);
			if(Recursive_Slot(qstrsuperclass,connection) == false)
			{
			}
			else
			{
				break;
			}
		}
		if(k == arraysuperclass.size())
		{
			ifs.close();
			return false;
		}
		else
		{
			ifs.close();
			return true;
		}
	}
	else
	{
		ifs.close();
		return true;
	}
	ifs.close(); 
}
QString WriteController::findDeclaration(const QString &name)
{
	const QString normalized = Driver::normalizedName(name);

    if (DomWidget *widget = m_driver->widgetByName(normalized))
        return m_driver->findOrInsertWidget(widget);
    if (DomAction *action = m_driver->actionByName(normalized))
        return m_driver->findOrInsertAction(action);
    if (const DomButtonGroup *group = m_driver->findButtonGroup(normalized))
        return m_driver->findOrInsertButtonGroup(group);
    return QString();
}
void WriteController::acceptWidget( DomWidget*  widget)
{
	const QString className = widget->attributeClass();
	const QString varName = m_driver->findOrInsertWidget(widget);
	m_multiMap.insert(className,varName);
	QList<DomWidget*> childWidget = widget->elementWidget();
	for( int i = 0; i<childWidget.size();i++)
	{
		acceptWidget(childWidget[i]);
	}
}
void WriteController::acceptConnections(DomConnections *connections)
{
	for (int i=0; i<connections->elementConnection().size(); ++i)
	{
		DomConnection *connection = connections->elementConnection().at(i);
		const QString receiver = findDeclaration(connection->elementReceiver());
		if(m_multiMap.key(receiver) != "")
		{
			QString qstrfilename = m_multiMap.key(receiver);
			if(Recursive_Slot(qstrfilename,connection) == false)
			{
				const QString receiver = findDeclaration(connection->elementReceiver());
				const QString sender = findDeclaration(connection->elementSender());
				if (sender.isEmpty() || receiver.isEmpty())
					return;
				QString slot =  connection->elementSlot() ;
				int pos = slot.lastIndexOf("(");
				if(pos>=0) slot =  slot.mid(0,pos);
				out << "LuaQtHelper.addSlot(" << receiver << ", \"void\", \"" <<slot << "\", {}, function(self)\n";
				//out << m_indent << "local " << connection->elementSlot() << " = require(\"cl_" << connection->elementSlot() << "\").new()\n";
				//out << m_indent << connection->elementSlot() << ":show();\n";
				out << "end)\n";
			}
			else
			{
			}
		}
	
	}
}
