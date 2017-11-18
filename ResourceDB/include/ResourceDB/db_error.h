/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DB_ERROR_H
#define RESOURCEDB_DB_ERROR_H

#include "stdafx.h"

namespace ResourceDB {

	/**
		A list of database errors.
	*/
	enum DB_ERROR {

		/**
			Everything was ok.
		*/
		DB_OK = 0,

		/**
			Invalid database file.
		*/
		DB_INVAL,

		/**
			No filename found.
		*/
		DB_NOFILE,

		/**
			An I/O error occurred.
		*/
		DB_IOERROR,

		/**
			No entry matching that ID.
		*/
		DB_NOENTRY,

		/**
			Duplicate entry
		*/
		DB_DUPENTRY,

		/**
			Not enough memory.
		*/
		DB_NOMEM,

		/**
			The database is full.
		*/
		DB_FULL,

		/**
			The database is too big.
		*/
		DB_TOOBIG,
	};

	os_ostream_t& operator<<(os_ostream_t &out, const DB_ERROR errorcode);
}

#endif // RESOURCEDB_DB_ERROR_H