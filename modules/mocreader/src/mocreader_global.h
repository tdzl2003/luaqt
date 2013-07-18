#ifndef MOCREADER_GLOBAL_H
#define MOCREADER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MOCREADER_LIB
# define MOCREADER_EXPORT Q_DECL_EXPORT
#else
# define MOCREADER_EXPORT Q_DECL_IMPORT
#endif

#endif // MOCREADER_GLOBAL_H
