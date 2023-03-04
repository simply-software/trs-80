///////////////////////////////////////////////////////////////////////////////
//
// \file logical_memory_address.inl
//
// \brief Holds a 16-bit TRS-80 logical memory address
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Holds a memory address
	class LogicalMemoryAddress
	{
	public:
		//! \brief Construct from an integer.
	inline LogicalMemoryAddress::LogicalMemoryAddress(uint16_t address) :
		_memory_address(address)
	{
		// Nothing to do
	}

	//! \brief Is the address null?
	bool LogicalMemoryAddress::is_null() const
	{
		return _memory_address;
	}

	//! \brief Obtain the direct page that contains this address
	DirectPage LogicalMemoryAddress::direct_page() const
	{
		return DirectPage(_memory_address >> 8);
	}

} // namespace assembly
