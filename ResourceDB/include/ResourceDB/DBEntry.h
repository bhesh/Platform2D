/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBENTRY_H
#define RESOURCEDB_DBENTRY_H

#include "stdafx.h"

namespace ResourceDB {

	class DBEntry {
	public:
		DBEntry(uint16_t catalog_id, uint16_t object_id, const os_char_t *name);
		DBEntry(uint16_t catalog_id, uint16_t object_id, const os_string_t &name);
		DBEntry(uint16_t catalog_id, uint16_t object_id);
		void SetName(const os_char_t *name);
		void SetName(const os_string_t &name);
		uint16_t GetCatalogId() const;
		uint16_t GetObjectId() const;
		const os_string_t& GetName() const;
	private:
		uint16_t object_id;
		uint16_t catalog_id;
		os_string_t name;
	};
}

#endif // RESOURCEDB_DBENTRY_H