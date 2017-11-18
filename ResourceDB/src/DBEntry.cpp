/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "stdafx.h"

#include "ResourceDB/DBEntry.h"

ResourceDB::DBEntry::DBEntry(UInt16 dbscheme_id, UInt16 object_id,
	const DBString &name) {
	this->dbscheme_id = dbscheme_id;
	this->object_id = object_id;
	this->name = name;
}

ResourceDB::DBEntry::DBEntry(UInt16 dbscheme_id, UInt16 object_id,
	const os_char_t *name) :
	DBEntry(dbscheme_id, object_id, DBString(name)) {}

ResourceDB::DBEntry::DBEntry(UInt16 dbscheme_id, UInt16 object_id,
	const os_string_t &name) :
	DBEntry(dbscheme_id, object_id, DBString(name)) {}

void ResourceDB::DBEntry::SetDBSchemeId(UInt16 dbscheme_id) {
	this->dbscheme_id = dbscheme_id;
}

void ResourceDB::DBEntry::SetObjectId(UInt16 object_id) {
	this->object_id = object_id;
}

void ResourceDB::DBEntry::SetName(const os_char_t *name) {
	this->name = name;
}

void ResourceDB::DBEntry::SetName(const os_string_t &name) {
	this->name = name;
}

void ResourceDB::DBEntry::SetName(const DBString &name) {
	this->name = name;
}

ResourceDB::UInt16 ResourceDB::DBEntry::GetDBSchemeId() const {
	return dbscheme_id;
}

ResourceDB::UInt16 ResourceDB::DBEntry::GetObjectId() const {
	return object_id;
}

const ResourceDB::DBString& ResourceDB::DBEntry::GetName() const {
	return name;
}