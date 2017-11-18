/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBWRITER_H
#define RESOURCEDB_DBWRITER_H

#include "stdafx.h"

#include "ResourceDB/DBString.h"
#include "ResourceDB/db_error.h"
#include "ResourceDB/types.h"

namespace ResourceDB {

	/**
		A class to write to a database. This is basically a wrapper of FILE
		and fwrite.

		Both DBReader and DBWriter were created to standardize the process of
		saving and loading the data. See DBReader for reference.
	*/
	class DBWriter {
	public:

		/**
			Default constructor.
		*/
		DBWriter();

		/**
			Opens a database to be written to.

			@param filename the filename of the database.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Open(const os_char_t *filename);

		/**
			Opens a database to be written to.

			@param filename the filename of the database.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Open(const os_string_t &filename);

		/**
			Closes the database stream.
		*/
		void Close();

		/**
			Writes a byte to the database.

			@param ub the byte to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const UInt8 ub);

		/**
			Writes bytes to the database.

			@param src the bytes to write.
			@param num_bytes the number of bytes to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const UInt8 *src, size_t num_bytes);

		/**
			Writes a character to the database.

			@param c the character to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const os_char_t c);

		/**
			Writes a short to the database.

			@param s the short to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const Int16 s);

		/**
			Writes an integer to the database.

			@param i the integer to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const Int32 i);

		/**
			Writes a long to the database.

			@param l the long to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const Int64 l);

		/**
			Writes an unsigned short to the database.

			@param us the unsigned short to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const UInt16 us);

		/**
			Writes an unsigned integer to the database.

			@param ui the unsigned integer to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const UInt32 ui);

		/**
			Writes an unsigned long to the database.

			@param ul the unsigned long to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const UInt64 ul);

		/**
			Writes a DBString to the database.

			@param string the DBString to write.

			@return DB_OK on success, failure otherwise.
		*/
		DB_ERROR Write(const DBString &string);
	private:
		DB_ERROR WriteRaw(const void *src, size_t num_bytes);
		FILE *fp;
	};
}

#endif // RESOURCEDB_DBWRITER_H