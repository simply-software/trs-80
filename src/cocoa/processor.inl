namespace algorithms
{

    //! \brief Convert integer to Processor (throws EnumCastException)
    template <> inline ::assembly::Processor enum_cast(size_t i)
    {
        if (i >= static_cast<size_t>(::assembly::Processor::NUM_VALUES))
        {
            throw_enum_cast_exception<::assembly::Processor>(i, nullptr);
        }

        return static_cast<::assembly::Processor>(i);
    }


} // namespace assembly
