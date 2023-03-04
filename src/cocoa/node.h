#pragma once

#include "label.h"
#include "source_line.h"

///////////////////////////////////////////////////////////////////////////////
//
// \file node.h
//
// \brief Base class for ASN nodes
//
///////////////////////////////////////////////////////////////////////////////

namespace assembly
{

	//! \brief Base class for all ASN node types
	class Node
	{
	public:
		explicit Node(const SourceLine& source_line);

		Node(const SourceLine& source_line, const Label& label);

		bool has_label() const;

		Label label() const;

	private:
		SourceLine _source_line;
		Label _label;
	};

		DECLARE_RECOGNIZE_METHOD(recognize_instruction, InstructionNode);

		DECLARE_RECOGNIZE_METHOD(recognize_title_directive, TitleNode);

		DECLARE_RECOGNIZE_METHOD(recognize_proc_directive, ProcNode);

		DECLARE_RECOGNIZE_METHOD(recognize_struct_directive, StructNode);

		DECLARE_RECOGNIZE_METHOD(recognize_union_directive, UnionNode);

		DECLARE_RECOGNIZE_METHOD(recognize_setdp_directive, SetDPNode);

		DECLARE_RECOGNIZE_METHOD(recognize_org_align_even_odd_directive, AlignNode);

		DECLARE_RECOGNIZE_METHOD(recognize_data_directive, DataNode);

		DECLARE_RECOGNIZE_METHOD(recognize_equ_set_directive, EquNode);

		DECLARE_RECOGNIZE_METHOD(recognize_endu_ends_endn_end_directive, EndBlockNode);

		DECLARE_RECOGNIZE_METHOD(recognize_namespace_directive, NamespaceNode);

		DECLARE_RECOGNIZE_METHOD(recognize_include_directive, IncludeNode);

		DECLARE_RECOGNIZE_METHOD(recognize_includebin_directive, IncludeBinaryNode);

		DECLARE_RECOGNIZE_METHOD(recognize_call_directive, CallNode);

	private:
	}; // class Node

} // namespace assembly
