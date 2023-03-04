///////////////////////////////////////////////////////////////////////////////
//
// \file symbol_name.inl
//
// \brief Holds a symbol name
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Construct from a string type
	template <typename StringType>
	inline SymbolName::SymbolName(const StringType& str) :
		_symbol_name(str)
	{
		// Nothing to do
	}

	//! \brief Get the symbol name as it appears in source code
	inline const std::string& SymbolName::name() const
	{
		return _symbol_name;
	}

	//! \brief Is the symbol the branch-point '!'?
	inline bool SymbolName::is_branch_point() const
	{
		return _symbol_name.length() == 1 && _symbol_name[0] == '!';
	}

	//! \brief Is the symbol the previous-branch-point '<'?
	inline bool SymbolName::is_previous_branch_point() const
	{
		return _symbol_name.length() == 1 && _symbol_name[0] == '<';
	}

	//! \brief Is the symbol the next-branch-point '>'?
	inline bool SymbolName::is_next_branch_point() const
	{
		return _symbol_name.length() == 1 && _symbol_name[0] == '>';
	}

	//! \brief Is the symbol one of the special values '!', '<', or '>'?
	inline bool SymbolName::is_branch_point_symbol_type() const
	{
		return is_branch_point()
			|| is_previous_branch_point()
			|| is_next_branch_point();
	}

} // namespace assembly
