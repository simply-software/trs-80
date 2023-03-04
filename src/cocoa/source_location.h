#pragma once

#include <cstdlib>
#include <string>

///////////////////////////////////////////////////////////////////////////////
//
// \file source_location.h
//
// \brief Defines a location in the source code -- file and line number.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Holds a file name and line number
	class SourceLocation
	{
		using FileName = std::string;

	public:
		//! \brief Construct from a filename and a 1-based line number
		SourceLocation(const FileName& file_name, uint32_t line_number);

		//! \brief Return the filename, which may contain a (possibly
		//         (relative) path
		const FileName& file() const;

		//! \brief Return the 1-based line number
		uint32_t line_number() const;

	private:
		FileName _file_name;   //!< As seen by the assembler; may be relative
		uint32_t _line_number; //!< 1-based line number
	}; // class SourceLocation

} // namespace assembly

#include "source_location.inl"
