///////////////////////////////////////////////////////////////////////////////
//
// \file label.inl
//
// \brief Holds a label
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Holds a symbol and its address
	class Label
	{
	public:
		//! \brief Construct from a name and address
	inline Label::Label(const SymbolName& symbol, LogicalMemoryAddress address) :
		_symbol_name(symbol),
		_address(address)
	{
		// Nothing to do
	}

	//! \brief Get the symbol name as it appears in source code
	inline const SymbolName& Label::symbol_name() const
	{
		return _symbol_name;
	}

	//! \brief Get the address that the symbol refers to
	inline LogicalMemoryAddress Label::address() const
	{
		return _address;
	}

} // namespace assembly
