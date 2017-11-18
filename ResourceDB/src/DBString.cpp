/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#include "stdafx.h"

#include "ResourceDB/DBString.h"

ResourceDB::DBString::DBString() {
	size = 0;
	value[size] = 0;
}

ResourceDB::DBString::DBString(const os_char_t *string) {
	*this = string;
}

ResourceDB::DBString::DBString(const os_string_t &string) {
	size_t csize = string.length();
	if (csize > _DB_STRING_LENGTH)
		csize = _DB_STRING_LENGTH;
	memcpy(value, string.c_str(), csize * sizeof(os_char_t));
	size = csize;
	value[size] = 0;
}

ResourceDB::DBString::DBString(const DBString &string) {
	size_t csize = string.Length();
	memcpy(value, string.GetCString(), csize * sizeof(os_char_t));
	size = csize;
	value[size] = 0;
}

size_t ResourceDB::DBString::Length() const {
	return size;
}

size_t ResourceDB::DBString::MaxLength() const {
	return _DB_STRING_LENGTH;
}

const os_char_t* ResourceDB::DBString::GetCString() const {
	return value;
}

void ResourceDB::DBString::operator =(const os_char_t *string) {
#ifdef _MSC_VER
	size_t csize = wcsnlen_s(string, _DB_STRING_LENGTH);
#else
	size_t csize = strnlen(string, _DB_STRING_LENGTH - size);
#endif
	memcpy(value, string, csize * sizeof(os_char_t));
	size = csize;
	value[size] = 0;
}

void ResourceDB::DBString::operator =(const os_string_t &string) {
	size_t csize = string.length();
	if (csize > _DB_STRING_LENGTH)
		csize = _DB_STRING_LENGTH;
	memcpy(value, string.c_str(), csize * sizeof(os_char_t));
	size = csize;
	value[size] = 0;
}

void ResourceDB::DBString::operator =(const ResourceDB::DBString &string) {
	size_t csize = string.Length();
	memcpy(value, string.GetCString(), csize * sizeof(os_char_t));
	size = csize;
	value[size] = 0;
}

void ResourceDB::DBString::operator +=(os_char_t c) {
	if (size >= _DB_STRING_LENGTH)
		return;
	value[size] = c;
	++size;
	value[size] = 0;
}

void ResourceDB::DBString::operator +=(short s) {
#ifdef _MSC_VER
	*this += std::to_wstring(s);
#else
	*this += std::to_string(s);
#endif
}

void ResourceDB::DBString::operator +=(int i) {
#ifdef _MSC_VER
	*this += std::to_wstring(i);
#else
	*this += std::to_string(i);
#endif
}

void ResourceDB::DBString::operator +=(long l) {
#ifdef _MSC_VER
	*this += std::to_wstring(l);
#else
	*this += std::to_string(l);
#endif
}

void ResourceDB::DBString::operator +=(float f) {
#ifdef _MSC_VER
	*this += std::to_wstring(f);
#else
	*this += std::to_string(f);
#endif
}

void ResourceDB::DBString::operator +=(double d) {
#ifdef _MSC_VER
	*this += std::to_wstring(d);
#else
	*this += std::to_string(d);
#endif
}

void ResourceDB::DBString::operator +=(unsigned char uc) {
#ifdef _MSC_VER
	*this += std::to_wstring(uc);
#else
	*this += std::to_string(uc);
#endif
}

void ResourceDB::DBString::operator +=(unsigned short us) {
#ifdef _MSC_VER
	*this += std::to_wstring(us);
#else
	*this += std::to_string(us);
#endif
}

void ResourceDB::DBString::operator +=(unsigned int ui) {
#ifdef _MSC_VER
	*this += std::to_wstring(ui);
#else
	*this += std::to_string(ui);
#endif
}

void ResourceDB::DBString::operator +=(unsigned long ul) {
#ifdef _MSC_VER
	*this += std::to_wstring(ul);
#else
	*this += std::to_string(ul);
#endif
}

void ResourceDB::DBString::operator +=(const os_char_t *string) {
	if (size >= _DB_STRING_LENGTH)
		return;
#ifdef _MSC_VER
	size_t csize = wcsnlen_s(string, _DB_STRING_LENGTH);
#else
	size_t csize = strnlen(string, _DB_STRING_LENGTH - size);
#endif
	memcpy(value + size, string, csize * sizeof(os_char_t));
	size += csize;
	value[size] = 0;
}

void ResourceDB::DBString::operator +=(const os_string_t &string) {
	if (size >= _DB_STRING_LENGTH)
		return;
	size_t csize = string.length();
	if (size + csize > _DB_STRING_LENGTH)
		csize = _DB_STRING_LENGTH - size;
	memcpy(value + size, string.c_str(), csize * sizeof(os_char_t));
	size += csize;
	value[size] = 0;
}

void ResourceDB::DBString::operator +=(const ResourceDB::DBString &string) {
	if (size >= _DB_STRING_LENGTH)
		return;
	size_t csize = string.Length();
	if (size + csize > _DB_STRING_LENGTH)
		csize = _DB_STRING_LENGTH - size;
	memcpy(value + size, string.GetCString(), csize * sizeof(os_char_t));
	size += csize;
	value[size] = 0;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	os_char_t right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, short right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, int right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, long right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, float right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	double right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	unsigned char right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	unsigned short right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	unsigned int right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	unsigned long right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	const os_char_t *right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left, 
	const os_string_t &right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

ResourceDB::DBString ResourceDB::operator +(const ResourceDB::DBString &left,
	const ResourceDB::DBString &right) {
	ResourceDB::DBString ret = left;
	ret += right;
	return ret;
}

os_ostream_t& ResourceDB::operator <<(os_ostream_t &ostream, 
	const ResourceDB::DBString &string) {
	ostream << string.GetCString();
	return ostream;
}