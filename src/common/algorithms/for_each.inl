//////////////////////////////////////////////////////////////////////////////
//
// \file for_each.inl
//
// \brief Implementation of "for_each" algorithm
//
//////////////////////////////////////////////////////////////////////////////

namespace algorithms
{

    template <typename... ValueTypes, typename UnaryFn> inline
    void for_each(UnaryFn&& fn, ValueTypes... values)
    {
        (fn(values), ...);
    }

} // namespace algorithms
