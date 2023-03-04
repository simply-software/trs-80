///////////////////////////////////////////////////////////////////////////////
//
// \file source_location.inl
//
// \brief Defines a location in the source code -- file and line number.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Construct from a filename and a 1-based line number
	inline SourceLocation::SourceLocation(
		const FileName& file_name,
		uint32_t line_number
	) : _file_name(file_name),
	    _line_number(line_number)
	{
		// Nothing to do
	}

	//! \brief Return the filename, which may contain a (possibly
	//         (relative) path
	inline const SourceLocation::FileName& SourceLocation::file() const
	{
		return _file_name;
	}

	//! \brief Return the 1-based line number
	inline uint32_t SourceLocation::line_number() const
	{
		return _line_number;
	}

} // namespace assembly
