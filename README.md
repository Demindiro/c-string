C Strings
=========

A library for manipulating length-prefixes strings.


Why use length-prefixed strings instead of just null-terminated strings?
------------------------------------------------------------------------

There are two major advantages:

- **Speed**: knowing how long a string is makes it much easier to predict how
  large a buffer should be, avoiding a lot of `realloc`s.
- **Simplicty**: There is no need to constantly check for a null terminator,
  nor is there any need to always use `strlen`: just use the `len` member
  of `string`or `string_t`.

The only disadvantage is an extra 8 bytes of memory used - whcich is negligible
considering how much RAM most devices have nowadays.


FAQ
---

Or well, questions I assume will be asked :P

### Why both null-terminated and length-prefixed?
Having null-terminated strings allows the use of ANSI C functions directly
without having to go through the hassle of converting back and forth.

### Why both `string_t` and `string`?
Using `string_t` may be faster in some edge cases because it is stack-allocated
and doesn't use `malloc` and `free`. However, it is only recommended to use it
to solve significant bottlenecks.
