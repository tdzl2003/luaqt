#pragma once

#include <LuaQT/globals.hpp>

// fix of some special class
#include <QtWidgets\qgraphicseffect.h>
#include <QtWidgets\qmenu.h>
#include <QtWidgets\qmenubar.h>
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
	struct is_qobject_ptr<QPlatformMenuBar*>
		: public std::tr1::false_type
	{
	};
}
