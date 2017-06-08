/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_CATALOG_H
#define RESOURCEDB_CATALOG_H

#include "stdafx.h"

#include "ResourceDB/DBEntry.h"
#include "ResourceDB/db_error.h"

namespace ResourceDB {

	class Catalog {
	public:
		const uint16_t catalog_id;
		const os_char_t *catalog_name;
		virtual DB_ERROR LoadEntry(std::istream &istream);
		virtual DB_ERROR StoreEntry(std::ostream &ostream) const;
		virtual std::vector<const DBEntry *> Search(const os_char_t *search) const;
		virtual std::vector<const DBEntry *> Search(const os_string_t &search) const;
	};
}

#endif // RESOURCEDB_CATALOG_H