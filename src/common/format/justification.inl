//////////////////////////////////////////////////////////////////////////////
//
// \file justification.inl
//
// \brief Formats the incoming text string according to justification and
//        field width
//
//////////////////////////////////////////////////////////////////////////////

namespace format
{

	namespace detail
	{

		//! \brief Function that actually does the justification.
		std::string do_justify(
			std::string   text_to_justify,
			Justification justification,
			size_t		  field_width,
			char		  fill_char
		);

	}


	//! \brief Pad the input string with a fill character
	//
	//         If the FieldWidth is larger than the input string
	//         width, then enough FillChars are added to the
	//         left and/or right of the input string so as to
	//         make the resulting string exactly FieldWidth
	//         characters wide.  If the input string is larger
	//         than the field width already, then the input
	//         string is returned unmodified.
	template <typename JustificationTraits> inline
	std::string justify(const std::string& text_to_justify)
	{
		return JustificationTraits::FieldWidth == 0 ?
			text_to_justify :
			detail::do_justify(
				text_to_justify,
				JustificationTraits::Justify,
				JustificationTraits::FieldWidth,
				JustificationTraits::FillChar
			);
	}

} // namespace format
