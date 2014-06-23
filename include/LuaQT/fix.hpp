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

#pragma once

#include <LuaQT/globals.hpp>

// fix of some special class
#include <QtCore/QProcess>
#include <QtWidgets/qgraphicseffect.h>
#include <QtWidgets/qmenu.h>
#include <QtWidgets/qmenubar.h>
#include <QtGui/QWindow>
#include <QtGui/QTextObject>
#include <QtGui/QScreen>
#include <QtGui/QOffscreenSurface>
#include <QtGui/QGuiApplication>
#include <QtCore\qfileinfo.h>
#include <QtGui\QTextCursor>
#include <QtGui\QBackingStore>
#include <QtNetwork\QNetworkAccessManager>
#include <QtNetwork\QHostAddress>
namespace LuaQt{
	template <>
	struct is_qobject_ptr<QGraphicsEffectSource*>
		: public std::tr1::false_type
	{
	};

	template <>
	struct is_qobject_ptr<QPlatformMenu*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<QFileInfoPrivate*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<QTextCursorPrivate*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<QTextDocumentPrivate*>
		: public std::tr1::false_type
	{
	};
	

	template <>
	struct is_qobject_ptr<QPlatformMenuBar*>
		: public std::tr1::false_type
	{
	};

	template <>
	struct is_qobject_ptr<_PROCESS_INFORMATION*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<QPlatformSurface*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<const sockaddr *>
		: public std::tr1::false_type
	{
	};
	
	template <>
	struct is_qobject_ptr<QPlatformPixmap*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<QPlatformBackingStore*>
		: public std::tr1::false_type
	{
	};
	
	template <>
	struct is_qobject_ptr<QPlatformWindow*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<QAuthenticator*>
		: public std::tr1::false_type
	{
	};
	
	template <>
	struct is_qobject_ptr<const QTextDocumentPrivate*>
		: public std::tr1::false_type
	{
	};
	template <>
	struct is_qobject_ptr<QTextEngine*>
		: public std::tr1::false_type
	{
	};
		
	template <>
	struct is_qobject_ptr<QPlatformScreen*>
		: public std::tr1::false_type
	{
	};

	template <>
	struct is_qobject_ptr<QPlatformOffscreenSurface*>
		: public std::tr1::false_type
	{
	};

	template <>
	struct is_qobject_ptr<QPlatformNativeInterface*>
		: public std::tr1::false_type
	{
	};
}
