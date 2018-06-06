// This file is part of Asteria.
// Copyleft 2018, LH_Mouse. All wrongs reserved.

#include "precompiled.hpp"
#include "expression_node.hpp"
#include "utilities.hpp"

namespace Asteria {

Expression_node::Expression_node(Expression_node &&) noexcept = default;
Expression_node & Expression_node::operator=(Expression_node &&) noexcept = default;
Expression_node::~Expression_node() = default;

const char * get_operator_name(Expression_node::Operator op) noexcept {
	switch(op){
	case Expression_node::operator_postfix_inc:
		return "postfix increment";
	case Expression_node::operator_postfix_dec:
		return "postfix decrement";
	case Expression_node::operator_postfix_at:
		return "subscripting";
	case Expression_node::operator_prefix_pos:
		return "unary plus";
	case Expression_node::operator_prefix_neg:
		return "negation";
	case Expression_node::operator_prefix_notb:
		return "bitwise not";
	case Expression_node::operator_prefix_notl:
		return "logical not";
	case Expression_node::operator_prefix_inc:
		return "prefix increment";
	case Expression_node::operator_prefix_dec:
		return "prefix decrement";
	case Expression_node::operator_infix_cmp_eq:
		return "equality comparison";
	case Expression_node::operator_infix_cmp_ne:
		return "inequality comparison";
	case Expression_node::operator_infix_cmp_lt:
		return "less-than comparison";
	case Expression_node::operator_infix_cmp_gt:
		return "greater-than comparison";
	case Expression_node::operator_infix_cmp_lte:
		return "less-than-or-equal comparison";
	case Expression_node::operator_infix_cmp_gte:
		return "greater-than-or-equal comparison";
	case Expression_node::operator_infix_add:
		return "addition";
	case Expression_node::operator_infix_sub:
		return "subtraction";
	case Expression_node::operator_infix_mul:
		return "multiplication";
	case Expression_node::operator_infix_div:
		return "division";
	case Expression_node::operator_infix_mod:
		return "modulo";
	case Expression_node::operator_infix_sll:
		return "logical left shift";
	case Expression_node::operator_infix_sla:
		return "arithmetic left shift";
	case Expression_node::operator_infix_srl:
		return "logical right shift";
	case Expression_node::operator_infix_sra:
		return "arithmetic right shift";
	case Expression_node::operator_infix_andb:
		return "bitwise and";
	case Expression_node::operator_infix_orb:
		return "bitwise or";
	case Expression_node::operator_infix_xorb:
		return "bitwise xor";
	case Expression_node::operator_infix_assign:
		return "assginment";
	default:
		ASTERIA_DEBUG_LOG("Unknown operator enumeration `", op, "`. This is probably a bug, please report.");
		return "<unknown>";
	}
}

}
