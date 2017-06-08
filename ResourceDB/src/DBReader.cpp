/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "ResourceDB/DBReader.h"

ResourceDB::DBReader::DBReader() {
	fp = nullptr;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Open(const os_char_t *filename) {

	// Open the file
#ifdef _MSC_VER
	_wfopen_s(&fp, filename, STRING("rb"));
#else
	fp = fopen(filename, STRING("rb"));
#endif
	if (!fp)
		return DB_NOFILE;

	// Get the file size
    int retval = fseek(fp, 0, SEEK_END);
    if (retval != 0)
        return DB_IOERROR;
    filesize = ftell(fp);

	// Reset the fp position
	retval = fseek(fp, 0, SEEK_SET);
	if (retval != 0)
		return DB_IOERROR;

	return DB_OK;
}

long ResourceDB::DBReader::GetFileSize() {
	if (fp == nullptr)
		return -1;
	return filesize;
}

bool ResourceDB::DBReader::AtEnd() {
	if (fp == nullptr)
		return false;
	return feof(fp);
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Open(const os_string_t &filename) {
	return Open(filename.c_str());
}

void ResourceDB::DBReader::Close() {
	if (fp == nullptr)
		return;
	fclose(fp);
	fp = nullptr;
}

size_t ResourceDB::DBReader::ReadRaw(void *dest, size_t num_bytes) {
	UInt8 *_dest = (UInt8 *)dest;
	size_t totalbytesread = 0;
	size_t nbytes;
	while (totalbytesread < num_bytes) {
		nbytes = fread(_dest + totalbytesread, sizeof(UInt8), 
			num_bytes - totalbytesread, fp);
		if (nbytes < 0)
			break;
		totalbytesread += nbytes;
	}
	return totalbytesread;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(UInt8 *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(UInt8));
	if (bytesRead != sizeof(UInt8))
		return DB_IOERROR;
	return DB_OK;
}

size_t ResourceDB::DBReader::Read(UInt8 *dest,
	size_t num_bytes) {
	if (fp == nullptr)
		return DB_IOERROR;
	return ReadRaw(dest, num_bytes);
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(os_char_t *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(os_char_t));
	if (bytesRead != sizeof(os_char_t))
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(Int16 *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(Int16));
	if (bytesRead != sizeof(Int16))
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(Int32 *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(Int32));
	if (bytesRead != sizeof(Int32))
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(Int64 *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(Int64));
	if (bytesRead != sizeof(Int64))
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(UInt16 *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(UInt16));
	if (bytesRead != sizeof(UInt16))
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(UInt32 *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(UInt32));
	if (bytesRead != sizeof(UInt32))
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(UInt64 *dest) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t bytesRead = ReadRaw(dest, sizeof(UInt64));
	if (bytesRead != sizeof(UInt64))
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBReader::Read(DBString *string) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t size_in_bytes = _DB_STRING_LENGTH * sizeof(os_char_t);
	os_char_t *tmp_str = new os_char_t[_DB_STRING_LENGTH];
	size_t bytesRead = ReadRaw(tmp_str, size_in_bytes);
	if (bytesRead != size_in_bytes) {
		delete[] tmp_str;
		return DB_IOERROR;
	}
	*string = tmp_str;
	delete[] tmp_str;
	return DB_OK;
}