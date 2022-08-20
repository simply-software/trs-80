///////////////////////////////////////////////////////////////////////////////
//
// \file exception.inl
//
// \brief Base class for all exceptions thrown by the assembler.
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Return the error message
	inline const char* Exception::what() const noexcept
	{
		return _error_buffer.c_str();
	}


	//! \brief Construct the DerivedExceptionType from the given
	//!        arguments and throw the exception.
	template <typename DerivedExceptionType, typename... Args> inline
	void throw_(Args&&... args)
	{
		DerivedExceptionType exc(std::forward<Args>(args)...);
		// FIXME: construct the error message
		throw exc;
	}

} // namespace assembly
