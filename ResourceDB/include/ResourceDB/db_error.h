/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DB_ERROR_H
#define RESOURCEDB_DB_ERROR_H

#include "stdafx.h"

namespace ResourceDB {
	enum DB_ERROR {
		DB_OK = 0,
		DB_NOFILE,
		DB_IOERROR,
		DB_NOENTRY,
		DB_NOMEM,
		DB_FULL,
	};
}

#endif // RESOURCEDB_DB_ERROR_H