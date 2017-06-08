/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "ResourceDB/Database.h"

/**
	Limit the database memory size to 512 MB.
*/
#define MAX_DB_MEM_SIZE (1 << 29)

void ResourceDB::Database::AddCatalog(Catalog *catalog) {
	catalog_map[catalog->catalog_id] = catalog;
}

void ResourceDB::Database::RemoveCatalog(Catalog *catalog) {
	catalog_map.erase(catalog->catalog_id);
}

ResourceDB::DB_ERROR ResourceDB::Database::Load(const os_char_t *filename) {
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::Load(const os_string_t &filename) {
	return Load(filename.c_str());
}

ResourceDB::DB_ERROR ResourceDB::Database::Save(const os_char_t *filename) const {
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::Save(const os_string_t &filename) const {
	return Save(filename.c_str());
}

const ResourceDB::Catalog* ResourceDB::Database::GetCatalog(uint16_t object_id) {
	return object_map[object_id];
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_char_t *search) const {
	return Search(os_string_t(search));
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_string_t &search) const {
	std::vector<const DBEntry *> results;
	for (auto const entry : catalog_map) {
		std::vector<const DBEntry *> nresults = entry.second->Search(search);
		results.insert(results.end(), nresults.begin(), nresults.end());
	}
	return results;
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_char_t *search, uint16_t catalog_id) const {
	return Search(os_string_t(search), catalog_id);
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_string_t &search, uint16_t catalog_id) const {
	const Catalog *catalog = catalog_map.at(catalog_id);
	return catalog->Search(search);
}