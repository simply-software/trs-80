//////////////////////////////////////////////////////////////////////////////
//
// \file character_case.inl
//
// \brief Enum for upper/lower case
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

	namespace detail
	{

		std::string _format_chars(
			std::string text,
			CharCase    char_case
		);

	} // namespace detail


	//! \brief Convert the case of all characters in a string
    template <typename FmtSpec = DefaultCharCaseTraits> inline
    std::string char_case(const std::string& text)
	{
		return detail::_format_chars(
			text,
			FmtSpec::Case
		);
	}

} // namespace format
