/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "stdafx.h"

#include "ResourceDB/Database.h"

/**
	Limit the database memory size to 512 MB.
*/
#define MAX_DB_SIZE (1 << 29)

/**
	Define special headers
*/
#define DB_HEADER_ID 0x3456789a

ResourceDB::Database::~Database() {
	DB_ERROR err;
	auto it = object_map.begin();
	for (size_t i = 0; i < object_map.size() && it != object_map.end(); ++i) {
		const DBScheme *dbscheme;
		err = GetDBEntryDBScheme(it->first, &dbscheme);
		if (err == DB_OK)
			dbscheme->Deallocate(it->second);
		else
			delete it->second;
		++it;
	}
	object_map.clear();
	dbscheme_map.clear();
}

ResourceDB::DB_ERROR ResourceDB::Database::AddDBScheme(DBScheme *dbscheme) {
	UInt16 dbscheme_id = dbscheme->GetDBSchemeId();
	auto it = dbscheme_map.find(dbscheme_id);
	if (it != dbscheme_map.end())
		return DB_DUPENTRY;
	dbscheme_map[dbscheme_id] = dbscheme;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::RemoveDBScheme(UInt16 dbscheme_id) {
	auto it = dbscheme_map.find(dbscheme_id);
	if (it == dbscheme_map.end())
		return DB_NOENTRY;
	dbscheme_map.erase(dbscheme_id);
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::GetDBScheme(UInt16 dbscheme_id, 
	const DBScheme **ret_dbscheme) const {
	auto it = dbscheme_map.find(dbscheme_id);
	if (it == dbscheme_map.end())
		return DB_NOENTRY;
	*ret_dbscheme = it->second;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::InternalAddDBEntry(
	const DBEntry *entry) {
	UInt16 object_id = entry->GetObjectId();
	auto it = object_map.find(object_id);
	if (it != object_map.end())
		return DB_DUPENTRY;
	object_map[object_id] = entry;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::AddDBEntry(const DBEntry *entry,
	size_t size) {
	DB_ERROR err;
	const DBScheme *dbscheme;
	err = GetDBScheme(entry->GetDBSchemeId(), &dbscheme);
	if (err != DB_OK)
		return DB_INVAL;
	DBEntry *object = dbscheme->Allocate();
	if (object == nullptr)
		return DB_NOMEM;
	memcpy(object, entry, size);
	err = InternalAddDBEntry(object);
	if (err != DB_OK) {
		dbscheme->Deallocate(object);
		return DB_DUPENTRY;
	}
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::RemoveDBEntry(UInt16 object_id) {
	auto it = object_map.find(object_id);
	if (it == object_map.end())
		return DB_NOENTRY;
	object_map.erase(object_id);
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::ReadHeader(DBReader &in,
	size_t *num_objects) {
	DB_ERROR err;

	// Read in the DB_HEADER_ID
	UInt32 db_id;
	err = in.Read(&db_id);
	if (err != DB_OK)
		return err;
	if (db_id != DB_HEADER_ID)
		return DB_INVAL;

	// Read in number of schemes
	size_t num_dbschemes;
	err = in.Read(&num_dbschemes);
	if (err != DB_OK)
		return err;
	if (num_dbschemes != dbscheme_map.size())
		return DB_INVAL;

	// Read in number of objects
	size_t _num_objects;
	err = in.Read(&_num_objects);
	if (err != DB_OK)
		return err;
	*num_objects = _num_objects;

	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::WriteHeader(DBWriter &out) const {
	DB_ERROR err;

	// Write DB_HEADER_ID
	err = out.Write((UInt32)DB_HEADER_ID);
	if (err != DB_OK)
		return err;

	// Write number of schemes
	size_t num_dbschemes = dbscheme_map.size();
	err = out.Write(num_dbschemes);
	if (err != DB_OK)
		return err;

	// Write number of entries
	size_t num_objects = object_map.size();
	err = out.Write(num_objects);
	if (err != DB_OK)
		return err;

	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::Load(const os_char_t *filename) {
	DB_ERROR err;
	DBReader in;

	// Open the database
	err = in.Open(filename);
	if (err != DB_OK)
		return err;

	// Check DB size
	if (in.GetFileSize() > MAX_DB_SIZE) {
		in.Close();
		return DB_TOOBIG;
	}

	// Read in the header
	size_t num_objects;
	err = ReadHeader(in, &num_objects);
	if (err != DB_OK) {
		in.Close();
		return err;
	}

	// Read in all entries
	for (size_t i = 0; i < num_objects; ++i) {
		UInt16 object_id;
		err = in.Read(&object_id);
		if (err != DB_OK) {
			in.Close();
			return err;
		}
		UInt16 dbscheme_id;
		err = in.Read(&dbscheme_id);
		if (err != DB_OK) {
			in.Close();
			return err;
		}
		DBString name;
		err = in.Read(&name);
		if (err != DB_OK) {
			in.Close();
			return err;
		}

		// Get DBScheme
		const DBScheme *dbscheme;
		err = GetDBScheme(dbscheme_id, &dbscheme);
		if (err != DB_OK) {
			in.Close();
			return err;
		}

		// Load the object
		DBEntry *object = dbscheme->Allocate();
		if (object == nullptr) {
			in.Close();
			return DB_NOMEM;
		}
		object->SetObjectId(object_id);
		object->SetName(name);
		err = dbscheme->Load(in, object);
		if (err != DB_OK) {
			dbscheme->Deallocate(object);
			in.Close();
			return err;
		}

		// Add object to map
		err = InternalAddDBEntry(object);
		if (err != DB_OK) {
			dbscheme->Deallocate(object);
			in.Close();
			return err;
		}
	}
	
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::Load(const os_string_t &filename) {
	return Load(filename.c_str());
}

ResourceDB::DB_ERROR ResourceDB::Database::Save(
	const os_char_t *filename) const {
	DB_ERROR err;
	DBWriter out;

	// Open the database
	err = out.Open(filename);
	if (err != DB_OK)
		return err;

	// Write the header
	err = WriteHeader(out);
	if (err != DB_OK) {
		out.Close();
		return err;
	}

	// Write each object
	auto it = object_map.begin();
	for (size_t i = 0; i < object_map.size() && it != object_map.end(); ++i) {

		// Grab the DBScheme
		const DBScheme *dbscheme;
		err = GetDBScheme(it->second->GetDBSchemeId(), &dbscheme);
		if (err != DB_OK) {
			out.Close();
			return DB_INVAL;
		}

		// Write the object to the database
		const DBEntry *object = it->second;
		err = out.Write(object->GetObjectId());
		if (err != DB_OK) {
			out.Close();
			return err;
		}
		err = out.Write(object->GetDBSchemeId());
		if (err != DB_OK) {
			out.Close();
			return err;
		}
		err = out.Write(object->GetName());
		if (err != DB_OK) {
			out.Close();
			return err;
		}

		// Store DBEntry
		err = dbscheme->Store(out, object);
		if (err != DB_OK) {
			out.Close();
			return err;
		}

		// Next object
		++it;
	}

	// If there are more entries, throw an error
	if (it != object_map.end()) {
		out.Close();
		return DB_INVAL;
	}

	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::Save(
	const os_string_t &filename) const {
	return Save(filename.c_str());
}

ResourceDB::DB_ERROR ResourceDB::Database::GetDBEntry(UInt16 object_id,
	const DBEntry **ret_object) const {
	auto obj_it = object_map.find(object_id);
	if (obj_it == object_map.end())
		return DB_NOENTRY;
	*ret_object = obj_it->second;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::Database::GetDBEntryDBScheme(UInt16 object_id,
	const DBScheme **ret_dbscheme) const {
	DB_ERROR err;

	const DBEntry *object;
	err = GetDBEntry(object_id, &object);
	if (err != DB_OK)
		return err;

	UInt16 dbscheme_id = object->GetDBSchemeId();
	const DBScheme *dbscheme;
	err = GetDBScheme(dbscheme_id, &dbscheme);
	if (err != DB_OK)
		return err;

	*ret_dbscheme = dbscheme;
	return DB_OK;
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_char_t *search) const {
	return Search(os_string_t(search));
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_string_t &search) const {
	std::vector<const DBEntry *> results;
	auto it = object_map.begin();
	for (size_t i = 0; i < object_map.size() && it != object_map.end(); ++i) {
		os_string_t name = it->second->GetName().GetCString();
		size_t found = name.find(search);
		if (found != os_string_t::npos)
			results.push_back(it->second);
		++it;
	}
	return results;
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_char_t *search, UInt16 dbscheme_id) const {
	return Search(os_string_t(search), dbscheme_id);
}

std::vector<const ResourceDB::DBEntry *> ResourceDB::Database::Search(
	const os_string_t &search, UInt16 dbscheme_id) const {
	std::vector<const DBEntry *> results;
	auto it = object_map.begin();
	for (size_t i = 0; i < object_map.size() && it != object_map.end(); ++i) {
		if (it->second->GetDBSchemeId() != dbscheme_id)
			continue;
		os_string_t name = it->second->GetName().GetCString();
		size_t found = name.find(search);
		if (found != os_string_t::npos)
			results.push_back(it->second);
		++it;
	}
	return results;
}