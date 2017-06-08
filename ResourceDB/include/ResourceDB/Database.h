/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DATABASE_H
#define RESOURCEDB_DATABASE_H

#include "stdafx.h"

#include "ResourceDB/Catalog.h"
#include "ResourceDB/DBEntry.h"
#include "ResourceDB/db_error.h"

namespace ResourceDB {

	class Database {
	public:
		void AddCatalog(Catalog *catalog);
		void RemoveCatalog(Catalog *catalog);
		DB_ERROR Load(const os_char_t *filename);
		DB_ERROR Load(const os_string_t &filename);
		DB_ERROR Save(const os_char_t *filename) const;
		DB_ERROR Save(const os_string_t &filename) const;
		const Catalog* GetCatalog(uint16_t object_id);
		std::vector<const DBEntry *> Search(const os_char_t *search) const;
		std::vector<const DBEntry *> Search(const os_string_t &search) const;
		std::vector<const DBEntry *> Search(const os_char_t *search, uint16_t catalog_id) const;
		std::vector<const DBEntry *> Search(const os_string_t &search, uint16_t catalog_id) const;
	private:
		std::unordered_map<uint16_t, const Catalog *> catalog_map;
		std::unordered_map<uint16_t, const Catalog *> object_map;
	};
}

#endif // RESOURCEDB_DATABASE_H