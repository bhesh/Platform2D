/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBENTRY_H
#define RESOURCEDB_DBENTRY_H

#include "stdafx.h"

#include "ResourceDB/DBString.h"
#include "ResourceDB/types.h"

namespace ResourceDB {

	/**
		Defines a database entry object. This class must be extended to write
		or read an object to/from a database.
	*/
	class DBEntry {
	public:

		/**
			Constructs a DBEntry object.

			@param dbscheme_id the id of the DBScheme.
			@param object_id the id of the object.
			@param name the name of the object.
		*/
		DBEntry(UInt16 dbscheme_id = 0, UInt16 object_id = 0,
			const DBString &name = STRING(""));

		/**
			Constructs a DBEntry object.

			@param dbscheme_id the id of the DBScheme.
			@param object_id the id of the object.
			@param name the name of the object.
		*/
		DBEntry(UInt16 dbscheme_id, UInt16 object_id, const os_char_t *name);

		/**
			Constructs a DBEntry object.

			@param dbscheme_id the id of the DBScheme.
			@param object_id the id of the object.
			@param name the name of the object.
		*/
		DBEntry(UInt16 dbscheme_id, UInt16 object_id,
			const os_string_t &name);

		/**
			Sets the DBScheme ID.

			@param dbscheme_id the ID of the DBScheme.
		*/
		void SetDBSchemeId(UInt16 dbscheme_id);

		/**
			Sets the object ID.

			@param object_id the ID of the object.
		*/
		void SetObjectId(UInt16 object_id);

		/**
			Sets the name of the object.

			@param name the name of the object.
		*/
		void SetName(const os_char_t *name);

		/**
			Sets the name of the object.

			@param name the name of the object.
		*/
		void SetName(const os_string_t &name);

		/**
			Sets the name of the object.

			@param name the name of the object.
		*/
		void SetName(const DBString &name);

		/**
			Gets the ID of the DBScheme.

			@return the ID of the DBScheme.
		*/
		UInt16 GetDBSchemeId() const;

		/**
			Gets the ID of the object.

			@return the ID of the object.
		*/
		UInt16 GetObjectId() const;

		/**
			Gets the name of the object.

			@return the name of the object.
		*/
		const DBString& GetName() const;
	private:
		UInt16 object_id;
		UInt16 dbscheme_id;
		DBString name;
	};
}

#endif // RESOURCEDB_DBENTRY_H