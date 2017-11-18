/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "stdafx.h"

#include "ResourceDB/DBScheme.h"

ResourceDB::DBScheme::DBScheme(const UInt16 dbscheme_id, const DBString &name) {
	this->dbscheme_id = dbscheme_id;
	this->name = name;
}

ResourceDB::DBScheme::DBScheme(const UInt16 dbscheme_id, const os_char_t *name)
	: DBScheme(dbscheme_id, DBString(name)) {}

ResourceDB::DBScheme::DBScheme(const UInt16 dbscheme_id, const os_string_t &name)
	: DBScheme(dbscheme_id, DBString(name)) {}

void ResourceDB::DBScheme::SetDBSchemeId(const UInt16 dbscheme_id) {
	this->dbscheme_id = dbscheme_id;
}

void ResourceDB::DBScheme::SetName(const DBString &name) {
	this->name = name;
}

ResourceDB::UInt16 ResourceDB::DBScheme::GetDBSchemeId() const {
	return dbscheme_id;
}

const ResourceDB::DBString& ResourceDB::DBScheme::GetName() const {
	return name;
}