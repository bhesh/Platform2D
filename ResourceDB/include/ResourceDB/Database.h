/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "stdafx.h"

#ifndef DB_STRING_SIZE
#define _DB_STRING_SIZE 128
#else
#define _DB_STRING_SIZE DB_STRING_SIZE
#endif

namespace ResourceDB {

	enum DB_ERROR {
		DB_OK = 0,
		DB_IOERROR,
		DB_NOENTRY,
		DB_NOMEM,
		DB_FULL,
	};

	typedef struct _DBKey {
		uint16_t db_id;
		uint16_t db_key;
	} DBKey;

	typedef struct _DBString {
		os_char_t value[_DB_STRING_SIZE];
	} DBString;

	class DBItem {
	public:
		virtual DBKey GetId() const;
		virtual const DBString GetName() const;
		virtual const DBItemLoader* GetLoader() const;
	};

	class DBItemLoader {
	public:
		const uint16_t unique_id = 0;
		virtual DB_ERROR Load(std::istream &istream) = 0;
		virtual DB_ERROR Store(std::ostream &istream) const = 0;
	};

	class DatabaseScheme {
	public:
		void AddLoader(const DBItemLoader &loader);
		void RemoveLoader(const DBItemLoader &loader);
		const std::vector<DBItemLoader&> GetLoaders() const;
	private:
		std::vector<DBItemLoader&> loaders;
	};

	class Database {
	public:
	};
}