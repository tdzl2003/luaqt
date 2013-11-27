/****************************************************************************
**
** Copyright (C) 2013 tdzl2003.
** Contact: https://github.com/tdzl2003/luaqt
**
** This file is part of the LuaQt Toolkit source.
**
** This file is licensed at BSD New license.
**
** NOTICE:
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
** POSSIBILITY OF SUCH DAMAGE.** 
**
** read COPYRIGHT.md for more informations.
**
****************************************************************************/

#include <LuaQt/globals.hpp>

#include <QtGui/QPaintDevice>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QStyleOptionGraphicsItem>
#include <QtWidgets/QGraphicsPathItem>
#include <QtWidgets/QGraphicsSimpleTextItem>
#include <QtGui/QMatrix4x4>
#include <QtGui/QTransform>
#include <QtGui/QPainterPath>
#include <QtGui/QRegion>
#include <QtGui/QPen>
#include <QtGui/QCursor>
#include <QtGui/QPolygonF>
#include <QtGui/QTextCursor>
#include <QtGui/QPicture>
#include <QtGui/QPixmap>
#include <QtGui/QBitmap>
#include <QtGui/QTextBlock>
#include <QtCore/QLineF>
#include <QtWidgets/QGraphicsItemGroup>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QGraphicsLayout>
#include <QtWidgets/QItemEditorFactory>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QTreeWidgetItem>
#include <QtCore/QMargins>
#include <QtGui/QDropEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QPagedPaintDevice>
#include <QtGui/QPaintEngine>
#include <QtGui/QBackingStore>
#include <QtWidgets/QScrollerProperties>
#include <QtWidgets/QStyleOption>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QTableWidgetSelectionRange>
#include <QtCore/QLocale>
#include <QtWidgets/QUndoCommand>
#include <QtCore/QAbstractNativeEventFilter>
#include <QtCore/QItemSelection>
#include <QtCore/QByteArray>

#include <QtCore/QFile>
#include <QtCore/QJsonObject>
#include <QtCore/QRegExp>
#include <QtCore/QEasingcurve>

#include <QtGui/QAbstractTextDocumentLayout>
#include <QtGui/QAccessibleBridgePlugin>
#include <QtGui/QAccessiblePlugin>
#include <QtGui/QClipboard>
#include <QtGui/QGuiApplication>
#include <QtGui/QIconEnginePlugin>
#include <QtGui/QImageIOPlugin>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QRegularExpressionValidator>
#include <QtGui/QScreen>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTextDocument>
#include <QtGui/QWindow>
#include <QtGui/QtExtTable>
#include <QtGui/QTextFormat>

namespace LuaQt
{
	template <typename T>
	bool ArgHelperGeneral<T>::CheckArg(lua_State *L, int idx)
	{
		return false;
	}

	template <typename T>
	T ArgHelperGeneral<T>::GetArg(lua_State *L, int idx)
	{
		luaL_error(L, "Not implemented");
		return T();
	}

	template <typename T>
	void ArgHelperGeneral<T>::pushRetVal(lua_State *L, const T& idx)
	{
		luaL_error(L, "Not implemented");
	}

	template <typename T>
	void ArgHelperGeneral<T>::pushRetVal(lua_State *L, T&& idx)
	{
		luaL_error(L, "Not implemented");
	}

	template class Q_DECL_EXPORT ArgHelperGeneral<long*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<unsigned char*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<unsigned char const*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<char*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<char>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QChar>;
	template class Q_DECL_EXPORT ArgHelperGeneral<void const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<bool*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<int*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QAbstractNativeEventFilter*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QItemSelection>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QJsonObject>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QRegExp>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QEasingCurve>;
	template class Q_DECL_EXPORT ArgHelperGeneral<_iobuf *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QByteArray*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPaintDevice*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<enum QFormLayout::ItemRole *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QStyleOptionGraphicsItem const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QMatrix4x4*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsItem const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsRectItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsPixmapItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsPolygonItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsLineItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsItemGroup *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsPathItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsEllipseItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsSimpleTextItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QGraphicsLayout *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTransform>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPainterPath>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPen>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QCursor>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextCursor>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QRegion>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPolygon>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPolygonF>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QLineF>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextBlock>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPicture>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPicture const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPicture *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QBitmap>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPixmap const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QItemEditorFactory>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QItemEditorFactory *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QMargins>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QListWidgetItem const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QListWidgetItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTableWidgetItem const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTableWidgetItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTreeWidgetItem const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTreeWidgetItem *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QDropEvent *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPlatformMenu *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPlatformMenuBar *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QAbstractTextDocumentLayout::PaintContext>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPagedPaintDevice*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPaintEngine*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QScrollerProperties>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QStyleOption*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QSizePolicy>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QLocale>;	
	template class Q_DECL_EXPORT ArgHelperGeneral<QTableWidgetSelectionRange>;	
	template class Q_DECL_EXPORT ArgHelperGeneral<QUndoCommand const *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QUndoCommand *>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QBackingStore *>;

	template class Q_DECL_EXPORT ArgHelperGeneral<QTextObjectInterface*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QAccessibleBridge*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QAccessibleInterface*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QImage>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPlatformNativeInterface*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QCursor*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QIconEngine*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QImageIOHandler*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QSurfaceFormat>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPlatformOffscreenSurface*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPlatformScreen*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QRegularExpression>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QStandardItem*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QStandardItem const*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextCursor*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QAbstractUndoItem*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextOption>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextFormat>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextFrameFormat>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextListFormat>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextTableFormat>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextTableCell>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextDocumentPrivate*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QTextFrameLayoutData*>;
	template class Q_DECL_EXPORT ArgHelperGeneral<QPlatformWindow*>;
}

void Q_DECL_EXPORT QSurface_initMethods(lua_State *L){}
void Q_DECL_EXPORT QGraphicsItem_initMethods(lua_State *L){}
void Q_DECL_EXPORT QGraphicsLayoutItem_initMethods(lua_State *L){}
void Q_DECL_EXPORT QLayoutItem_initMethods(lua_State *L){}
void Q_DECL_EXPORT QPaintDevice_initMethods(lua_State *L){}
