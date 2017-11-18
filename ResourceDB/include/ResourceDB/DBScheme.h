/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBSCHEME_H
#define RESOURCEDB_DBSCHEME_H

#include "stdafx.h"

#include "ResourceDB/DBEntry.h"
#include "ResourceDB/DBReader.h"
#include "ResourceDB/DBString.h"
#include "ResourceDB/DBWriter.h"
#include "ResourceDB/db_error.h"
#include "ResourceDB/types.h"

namespace ResourceDB {

	/**
		Defines a scheme for an object in the database. This defines how to 
		load and store objects. Types of objects should extend this class.
	*/
	class DBScheme {
	public:

		/**
			Constructs a DBScheme.

			@param dbscheme_id the ID of the DBScheme.
			@param name the name of the DBScheme.
		*/
		DBScheme(const UInt16 dbscheme_id = 0, const DBString &name = STRING(""));

		/**
			Constructs a DBScheme.

			@param dbscheme_id the ID of the DBScheme.
			@param name the name of the DBScheme.
		*/
		DBScheme(const UInt16 dbscheme_id, const os_char_t *name);

		/**
			Constructs a DBScheme.

			@param dbscheme_id the ID of the DBScheme.
			@param name the name of the DBScheme.
		*/
		DBScheme(const UInt16 dbscheme_id, const os_string_t &name);

		/**
			Sets the ID of the DBScheme.

			@param dbscheme_id the ID of the DBScheme.
		*/
		void SetDBSchemeId(const UInt16 dbscheme_id);

		/**
			Sets the name of the DBScheme.

			@param name the name of the DBScheme.
		*/
		void SetName(const DBString &name);

		/**
			Gets the ID of the DBScheme.

			@return the ID of the DBScheme.
		*/
		UInt16 GetDBSchemeId() const;

		/**
			Gets the name of the DBScheme.

			@return the name of the DBScheme.
		*/
		const DBString& GetName() const;

		/**
			Allocates the DBEntry object.

			@return the allocated DBEntry.
		*/
		virtual DBEntry* Allocate() const = 0;

		/**
			Deallocates the DBEntry object.

			@param object the object in memory to deallocate.
		*/
		virtual void Deallocate(const DBEntry *object) const = 0;

		/**
			Loads an object from the database according to this scheme.

			@param in the DBReader to read from.
			@param ret_entry the returned DBEntry object.

			@return DB_OK on success, failure otherwise.
		*/
		virtual DB_ERROR Load(DBReader &in, DBEntry *object) const = 0;

		/**
			Stores an object in the database according to this scheme.

			@param out the DBWriter to write to.
			@param object_id the ID of the object to write.

			@return DB_OK on success, failure otherwise.
		*/
		virtual DB_ERROR Store(DBWriter &out, const DBEntry *object) const = 0;
	private:
		UInt16 dbscheme_id;
		DBString name;
	};
}

#endif // RESOURCEDB_DBSCHEME_H