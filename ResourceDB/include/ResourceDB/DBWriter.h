/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBWRITER_H
#define RESOURCEDB_DBWRITER_H

#include "stdafx.h"

#include "ResourceDB/DBString.h"
#include "ResourceDB/db_error.h"
#include "ResourceDB/types.h"

namespace ResourceDB {

	class DBWriter {
	public:
		DBWriter();
		DB_ERROR Open(const os_char_t *filename);
		DB_ERROR Open(const os_string_t &filename);
		void Close();
		DB_ERROR Write(const UInt8 ub);
		DB_ERROR Write(const UInt8 *src, size_t num_bytes);
		DB_ERROR Write(const os_char_t c);
		DB_ERROR Write(const Int16 s);
		DB_ERROR Write(const Int32 i);
		DB_ERROR Write(const Int64 l);
		DB_ERROR Write(const UInt16 us);
		DB_ERROR Write(const UInt32 ui);
		DB_ERROR Write(const UInt64 ul);
		DB_ERROR Write(const DBString &string);
	private:
		DB_ERROR WriteRaw(const void *src, size_t num_bytes);
		FILE *fp;
	};
}

#endif // RESOURCEDB_DBWRITER_H