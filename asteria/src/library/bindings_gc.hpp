// This file is part of Asteria.
// Copyleft 2018 - 2019, LH_Mouse. All wrongs reserved.

#ifndef ASTERIA_LIBRARY_BINDINGS_GC_HPP_
#define ASTERIA_LIBRARY_BINDINGS_GC_HPP_

#include "../fwd.hpp"

namespace Asteria {

extern Iopt std_gc_tracked_count(Global& global, Ival generation);
extern Iopt std_gc_get_threshold(Global& global, Ival generation);
extern Iopt std_gc_set_threshold(Global& global, Ival generation, Ival threshold);
extern Ival std_gc_collect(Global& global, Iopt generation_limit);

// Create an object that is to be referenced as `std.gc`.
extern void create_bindings_gc(Oval& result, API_Version version);

}  // namespace Asteria

#endif
