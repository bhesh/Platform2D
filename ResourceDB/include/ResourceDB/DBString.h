/**
	Copyright 2017 Brian Hession. All rights reserved.
*/

#ifndef RESOURCEDB_DBSTRING_H
#define RESOURCEDB_DBSTRING_H

#include "stdafx.h"

#include "ResourceDB/db_error.h"

#ifndef DB_STRING_LENGTH
#define _DB_STRING_LENGTH 128
#else
#define _DB_STRING_LENGTH DB_STRING_LENGTH - 1
#endif

namespace ResourceDB {

	/**
		Defines a static sized string that integrates well with the database.
		Only DBString's can be written to or read from the database. The string
		is capped at whatever @c DB_STRING_LENGTH is defined to. This value
		defaults to 128 characters. To change this, the library must be
		recompiled with a new string length.
	*/
	class DBString {
	public:

		/**
			Constructs an empty DBString.
		*/
		DBString();

		/**
			Constructs a DBString with the value in @c string. If @c string
			is longer than DB_STRING_LENGTH, it will be capped to fit.

			@param string the string to copy into DBString.
		*/
		DBString(const os_char_t *string); 

		/**
			Constructs a DBString with the value in @c string. If @c string
			is longer than DB_STRING_LENGTH, it will be capped to fit.

			@param string the string to copy into DBString.
		*/
		DBString(const os_string_t &string); 

		/**
			Constructs a DBString with the value in @c string. If @c string
			is longer than DB_STRING_LENGTH, it will be capped to fit.

			@param string the string to copy into DBString.
		*/
		DBString(const DBString &string);

		/**
			Returns the current length of the string, excluding the null 
			character.

			@return the length of the string.
		*/
		size_t Length() const;

		/**
			Returns the max length the string can be, excluding the null
			character.

			@return the max possible length of the string.
		*/
		size_t MaxLength() const;

		/**
			Retuns the DBString as an array of characters. On Windows, this
			will be an array of wchar_t. Elsewhere, it will be an array of
			char.

			@return the array of characters.
		*/
		const os_char_t* GetCString() const;

		/**
			Overloads the = operator to assign the value of the string
			represented by @c string. If @c string is longer than
			DB_STRING_LENGTH, it will be capped to fit.

			@param string the string to copy from.
		*/
		void operator =(const os_char_t *string);

		/**
			Overloads the = operator to assign the value of the string
			represented by @c string. If @c string is longer than
			DB_STRING_LENGTH, it will be capped to fit.

			@param string the string to copy from.
		*/
		void operator =(const os_string_t &string);

		/**
			Overloads the = operator to assign the value of the string
			represented by @c string. If @c string is longer than
			DB_STRING_LENGTH, it will be capped to fit.

			@param string the string to copy from.
		*/
		void operator =(const DBString &string);

		/**
			Appends a character to the end of the DBString. If the string is
			already at max size, this function will do nothing.

			@param c the character to append.
		*/
		void operator +=(os_char_t c);

		/**
			Appends a short to the end of the DBString. If the string reaches
			max size, the numerical values copied will be capped.

			@param s the short to append.
		*/
		void operator +=(short s);

		/**
			Appends an integer to the end of the DBString. If the string reaches
			max size, the numerical values copied will be capped.

			@param i the integer to append.
		*/
		void operator +=(int i);

		/**
			Appends a long to the end of the DBString. If the string reaches
			max size, the numerical values copied will be capped.

			@param l the long to append.
		*/
		void operator +=(long l);

		/**
			Appends a float to the end of the DBString. If the string reaches
			max size, the numerical values copied will be capped.

			@param f the float to append.
		*/
		void operator +=(float f);

		/**
			Appends a double to the end of the DBString. If the string reaches
			max size, the numerical values copied will be capped.

			@param d the double to append.
		*/
		void operator +=(double d);

		/**
			Appends an unsigned character to the end of the DBString. If the
			string reaches max size, the numerical values copied will be capped.

			@param uc the unsigned character to append.
		*/
		void operator +=(unsigned char uc);

		/**
			Appends an unsigned short to the end of the DBString. If the string
			reaches max size, the numerical values copied will be capped.

			@param us the unsigned short to append.
		*/
		void operator +=(unsigned short us);

		/**
			Appends an unsigned integer to the end of the DBString. If the
			string reaches max size, the numerical values copied will be capped.

			@param ui the unsigned integer to append.
		*/
		void operator +=(unsigned int ui);

		/**
			Appends an unsigned long to the end of the DBString. If the string
			reaches max size, the numerical values copied will be capped.

			@param ul the unsigned long to append.
		*/
		void operator +=(unsigned long ul);

		/**
			Appends a string to the end of the DBString. If the string reaches
			max size, the copied string will be capped.

			@param string the string to append.
		*/
		void operator +=(const os_char_t *string);

		/**
			Appends a string to the end of the DBString. If the string reaches
			max size, the copied string will be capped.

			@param string the string to append.
		*/
		void operator +=(const os_string_t &string);

		/**
			Appends a string to the end of the DBString. If the string reaches
			max size, the copied string will be capped.

			@param string the string to append.
		*/
		void operator +=(const DBString &string);
	private:
		os_char_t value[_DB_STRING_LENGTH];
		size_t size;
	};

	/**
		Concatenates a DBString and a character. On windows, it will be a
		@c wchar_t. Elsewhere, it will be a @c char.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the character to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, os_char_t right);

	/**
		Concatenates a DBString and a short.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the short to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, short right);

	/**
		Concatenates a DBString and an integer.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the integer to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, int right);

	/**
		Concatenates a DBString and a long.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the long to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, long right);

	/**
		Concatenates a DBString and a float.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the float to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, float right);

	/**
		Concatenates a DBString and a double.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the double to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, double right);

	/**
		Concatenates a DBString and an unsigned byte.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the unsigned byte to the end of the DBString, it
		would be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, unsigned char right);

	/**
		Concatenates a DBString and an unsigned short.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the unsigned short to the end of the DBString, it
		would be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, unsigned short right);

	/**
		Concatenates a DBString and an unsigned integer.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the unsigned integer to the end of the DBString, it
		would be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, unsigned int right);

	/**
		Concatenates a DBString and an unsigned long.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the unsigned long to the end of the DBString, it
		would be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, unsigned long right);

	/**
		Concatenates a DBString and a string.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the string to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, const os_char_t *right);

	/**
		Concatenates a DBString and a string.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the string to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, const os_string_t &right);

	/**
		Concatenates a DBString and a string.

		@b NOTE: This function will create a new DBString object. If the end
		result is to append the string to the end of the DBString, it would
		be more appropriate to use += as the values are directly written.

		@return a new DBString with the values concatenated.
	*/
	DBString operator +(const DBString &left, const DBString &right);

	/**
		Outputs the DBString to an ostream. On Windows, it will use a wostream.
		Elsewhere, it will use a ostream.
	*/
	os_ostream_t& operator <<(os_ostream_t &ostream, const DBString &string);
}

#endif // RESOURCEDB_DBSTRING_H
