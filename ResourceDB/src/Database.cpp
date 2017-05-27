/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "ResourceDB/Database.h"

/**
	Limit the database memory size to 512 MB.
*/
#define MAX_DB_MEM_SIZE (1 << 29)

/**
	Defines the header of the database.
*/
typedef struct _DBHeader {
	uint16_t num_categories;
	uint16_t num_entries;
} DBHeader;

/**
	Defines the categories in the header.
*/
typedef ResourceDB::DBString CategoryEntry;

ResourceDB::Database::Database() {
	next_id = 0;
}

ResourceDB::Database::~Database() {

	// Remove the references
	categories.clear();
	hashmap.clear();
	searchmap.clear();

	// Remove the originals
	items.clear();
}

ResourceDB::DB_ERROR ResourceDB::Database::Load(const os_char_t *filename) {

}

ResourceDB::DB_ERROR ResourceDB::Database::Save(const os_char_t *filename) {

}

ResourceDB::DB_ERROR ResourceDB::Database::AddItem(const DBItem &item,
	uint16_t *ret_id) {

}

ResourceDB::DB_ERROR ResourceDB::Database::DeleteItem(const uint16_t id,
	DBItem *ret_item) {

}

ResourceDB::DB_ERROR ResourceDB::Database::GetItemRef(const uint16_t id,
	DBItem *const &ret_item) {

}

ResourceDB::DB_ERROR ResourceDB::Database::SetItem(const uint16_t id,
	const DBItem &item) {

}

std::vector<const ResourceDB::DBItem&> ResourceDB::Database::Search(
	const os_char_t *search, const os_char_t *category) {

}