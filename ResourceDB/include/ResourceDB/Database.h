/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DATABASE_H
#define RESOURCEDB_DATABASE_H

#include "stdafx.h"

#include "ResourceDB/DBScheme.h"
#include "ResourceDB/DBEntry.h"
#include "ResourceDB/db_error.h"
#include "ResourceDB/types.h"

namespace ResourceDB {

	class Database {
	public:
		~Database();
		DB_ERROR AddDBScheme(DBScheme *dbscheme);
		DB_ERROR RemoveDBScheme(UInt16 dbscheme_id);
		DB_ERROR GetDBScheme(UInt16 dbscheme_id,
			const DBScheme **ret_dbscheme) const;
		DB_ERROR AddDBEntry(const DBEntry *entry, size_t size);
		DB_ERROR RemoveDBEntry(UInt16 object_id);
		DB_ERROR Load(const os_char_t *filename);
		DB_ERROR Load(const os_string_t &filename);
		DB_ERROR Save(const os_char_t *filename) const;
		DB_ERROR Save(const os_string_t &filename) const;
		DB_ERROR GetDBEntry(UInt16 object_id, const DBEntry **ret_object) const;
		DB_ERROR GetDBEntryDBScheme(UInt16 object_id,
			const DBScheme **ret_dbscheme) const;
		std::vector<const DBEntry *> Search(const os_char_t *search) const;
		std::vector<const DBEntry *> Search(const os_string_t &search) const;
		std::vector<const DBEntry *> Search(const os_char_t *search,
			UInt16 dbscheme_id) const;
		std::vector<const DBEntry *> Search(const os_string_t &search,
			const UInt16 dbscheme_id) const;
	private:
		DB_ERROR InternalAddDBEntry(const DBEntry *entry);
		DB_ERROR ReadHeader(DBReader &in, size_t *num_objects);
		DB_ERROR WriteHeader(DBWriter &out) const;
		std::unordered_map<UInt16, const DBScheme *> dbscheme_map;
		std::unordered_map<UInt16, const DBEntry *> object_map;
	};
}

#endif // RESOURCEDB_DATABASE_H