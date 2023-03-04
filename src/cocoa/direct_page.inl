///////////////////////////////////////////////////////////////////////////////
//
// \file direct_page.inl
//
// \brief Holds an 8-bit value which represents the most significant byte
//        of a 16-bit address.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Construct from an integer.
	inline DirectPage::DirectPage(uint8_t page) :
		_direct_page(page)
	{
		// Nothing to do
	}

} // namespace assembly
