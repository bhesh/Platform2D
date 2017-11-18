/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBREADER_H
#define RESOURCEDB_DBREADER_H

#include "stdafx.h"

#include "ResourceDB/DBString.h"
#include "ResourceDB/db_error.h"
#include "ResourceDB/types.h"

namespace ResourceDB {

	/**
		A class to read from a database. This is basically a wrapper of FILE
		and fread.

		Both DBReader and DBWriter were created to standardize the process of
		saving and loading the data. See DBWriter for reference.
	*/
	class DBReader {
	public:

		/**
			Default constructor.
		*/
		DBReader();

		/**
			Opens the database for reading.

			@param filename the filename of the database.

			@return DB_OK on success, an error otherwise.
		*/
		DB_ERROR Open(const os_char_t *filename);

		/**
			Opens the database for reading.

			@param filename the filename of the database.

			@return DB_OK on success, an error otherwise.
		*/
		DB_ERROR Open(const os_string_t &filename);

		/**
			Returns the size of the database in bytes.

			@return the size of the database in bytes.
		*/
		long GetFileSize();

		/**
			Returns true if the database stream has hit the end of the file.

			@b NOTE: An unsuccessful read must be made for this to return true.

			@return if the stream has hit the end of the file.
		*/
		bool AtEnd();

		/**
			Closes the database.
		*/
		void Close();

		/**
			Reads a byte from the database.

			@param dest where the byte will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(UInt8 *dest);

		/**
			Reads bytes from the database.

			@param dest where the bytes will be read to. @c dest must be
			allocated prior to calling this function.
			@param num_bytes the number of bytes to read.

			@return DB_OK on success, error otherwise.
		*/
		size_t Read(UInt8 *dest, size_t num_bytes);

		/**
			Reads a character from the database.

			@param dest where the character will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(os_char_t *dest);

		/**
			Reads a short from the database.

			@param dest where the short will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(Int16 *dest);

		/**
			Reads an integer from the database.

			@param dest where the integer will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(Int32 *dest);

		/**
			Reads a long from the database.

			@param dest where the long will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(Int64 *dest);

		/**
			Reads an unsigned short from the database.

			@param dest where the unsigned short will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(UInt16 *dest);

		/**
			Reads an unsigned integer from the database.

			@param dest where the unsigned integer will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(UInt32 *dest);

		/**
			Reads an unsigned long from the database.

			@param dest where the unsigned long will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(UInt64 *dest);

		/**
			Reads a DBString from the database.

			@param string where the DBString will be read to.

			@return DB_OK on success, error otherwise.
		*/
		DB_ERROR Read(DBString *string);
	private:
		size_t ReadRaw(void *dest, size_t num_bytes);
		FILE *fp;
		long filesize;
	};
}

#endif // RESOURCEDB_DBREADER_H