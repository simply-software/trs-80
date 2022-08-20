#pragma once

#include "processor.h"
#include <bitset>
#include <iosfwd>

///////////////////////////////////////////////////////////////////////////////
//
// \file processor_list.h
//
// \brief A list of processors
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

    //! \brief A list of processors that is easily queryable
    struct ProcessorList
    {
    public:
        //! \brief Construct a empty list
        ProcessorList() = default;

        //! \brief Construct a list of one or more processors
		template <typename... ProcessorT>
        explicit ProcessorList(ProcessorT... processors);

        //! \brief Query if *all* processors are in the list
		template <typename... ProcessorT>
        bool all(ProcessorT... processors) const;

        //! \brief Query if *at least one* processor is in the list
		template <typename... ProcessorT>
        bool any(ProcessorT... processors) const;

        //! brief Query if this one processor is in the list
        bool has(Processor processor) const;

    private:
        using ProcSet = std::bitset<static_cast<int>(Processor::NUM_VALUES)>;

        ProcSet _processors; // List of processors as a bitfield
    };

    //! \brief Output mnemonically, eg "PROC_1|PROc_2"
    std::ostream& operator<<(std::ostream& os, const ProcessorList& p);

} // namespace assembly

#include "processor_list.inl"
