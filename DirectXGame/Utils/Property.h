#pragma once

#define PROPERTY(t, n)                                                          \
    __declspec(property(put = property__set_##n, get = property__get_##n)) t n; \
    typedef t property__tmp_type_##n
#define R_PROPERTY(t, n)                               \
    __declspec(property(get = property__get_##n)) t n; \
    typedef t property__tmp_type_##n
#define W_PROPERTY(t, n)                               \
    __declspec(property(put = property__set_##n)) t n; \
    typedef t property__tmp_type_##n
#define GET(n) property__tmp_type_##n property__get_##n()
#define SET(n) void property__set_##n(const property__tmp_type_##n &value)

