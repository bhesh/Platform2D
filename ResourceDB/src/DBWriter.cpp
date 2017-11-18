/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "stdafx.h"

#include "ResourceDB/DBWriter.h"

ResourceDB::DBWriter::DBWriter() {
	fp = nullptr;
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Open(const os_char_t *filename) {
#ifdef _MSC_VER
	_wfopen_s(&fp, filename, STRING("wb"));
#else
	fp = fopen(filename, STRING("wb"));
#endif
	if (!fp)
		return DB_NOFILE;

	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Open(const os_string_t &filename) {
	return Open(filename.c_str());
}

void ResourceDB::DBWriter::Close() {
	if (fp == nullptr)
		return;
	fclose(fp);
	fp = nullptr;
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::WriteRaw(const void *src,
	size_t num_bytes) {
	UInt8 *_src = (UInt8 *)src;
	size_t totalbyteswritten = 0;
	size_t nbytes;
	while (totalbyteswritten < num_bytes) {
		nbytes = fwrite(_src + totalbyteswritten, sizeof(UInt8),
			num_bytes - totalbyteswritten, fp);
		if (nbytes < 0)
			break;
		totalbyteswritten += nbytes;
	}
	if (totalbyteswritten != num_bytes)
		return DB_IOERROR;
	return DB_OK;
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const UInt8 ub) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&ub, sizeof(UInt8));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const UInt8 *src,
	size_t num_bytes) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(src, num_bytes);
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const os_char_t c) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&c, sizeof(os_char_t));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const Int16 s) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&s, sizeof(Int16));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const Int32 i) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&i, sizeof(Int32));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const Int64 l) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&l, sizeof(Int64));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const UInt16 us) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&us, sizeof(UInt16));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const UInt32 ui) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&ui, sizeof(UInt32));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(const UInt64 ul) {
	if (fp == nullptr)
		return DB_IOERROR;
	return WriteRaw(&ul, sizeof(UInt64));
}

ResourceDB::DB_ERROR ResourceDB::DBWriter::Write(
	const DBString &string) {
	if (fp == nullptr)
		return DB_IOERROR;
	size_t size_in_bytes = _DB_STRING_LENGTH * sizeof(os_char_t);
	return WriteRaw(string.GetCString(), size_in_bytes);
}