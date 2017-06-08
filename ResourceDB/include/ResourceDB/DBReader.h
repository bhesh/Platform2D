/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBREADER_H
#define RESOURCEDB_DBREADER_H

#include "stdafx.h"

#include "ResourceDB/DBString.h"
#include "ResourceDB/db_error.h"
#include "ResourceDB/types.h"

namespace ResourceDB {

	class DBReader {
	public:
		DBReader();
		DB_ERROR Open(const os_char_t *filename);
		DB_ERROR Open(const os_string_t &filename);
		long GetFileSize();
		bool AtEnd();
		void Close();
		DB_ERROR Read(UInt8 *dest);
		size_t Read(UInt8 *dest, size_t num_bytes);
		DB_ERROR Read(os_char_t *dest);
		DB_ERROR Read(Int16 *dest);
		DB_ERROR Read(Int32 *dest);
		DB_ERROR Read(Int64 *dest);
		DB_ERROR Read(UInt16 *dest);
		DB_ERROR Read(UInt32 *dest);
		DB_ERROR Read(UInt64 *dest);
		DB_ERROR Read(DBString *string);
	private:
		size_t ReadRaw(void *dest, size_t num_bytes);
		FILE *fp;
		long filesize;
	};
}

#endif // RESOURCEDB_DBREADER_H