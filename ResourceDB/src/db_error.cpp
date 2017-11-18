/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "stdafx.h"

#include "ResourceDB/db_error.h"

os_ostream_t& ResourceDB::operator<<(os_ostream_t &out, DB_ERROR errorcode) {
	switch (errorcode) {
	case DB_OK:
		out << STRING("OK");
		break;
	case DB_INVAL:
		out << STRING("Invalid");
		break;
	case DB_NOFILE:
		out << STRING("No file");
		break;
	case DB_IOERROR:
		out << STRING("IO Error");
		break;
	case DB_NOENTRY:
		out << STRING("No entry");
		break;
	case DB_DUPENTRY:
		out << STRING("Duplicate entry");
		break;
	case DB_NOMEM:
		out << STRING("No memory");
		break;
	case DB_FULL:
		out << STRING("Database is full");
		break;
	case DB_TOOBIG:
		out << STRING("Too big");
		break;
	}
	return out;
}
