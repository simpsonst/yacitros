# Name

Yet Another C Interface To RISC OS

# Purpose

I wrote this for several, not altogether sound, reasons:

* I had Easy C, which was buggy, and didn't like OSLib very much.

* I wanted my own desktop abstraction.

* I wanted to generate Drawfiles from C.

I don't regard it as a particularly good production, but I'm releasing it because I've used it, and I've released other code which uses it and which other folk might actually want to compile.

# To Do

* Use `Font_ScanString` instead of `Font_StringBBox` in `font/op.c`.

* Define a `wimp_redrawtitle` op to use the Nested WIMP's (3.80+) extension of `ForceRedraw`:

  ```
  SYS "Wimp_ForceRedraw",window_handle%,&4B534154,3
  ```

  See also [http://www.vigay.com/inet/acorn/nested.html](nested-wimp docs).

* `win_settitle` should use the nested wimp call, if detected.

* Support nested `Wimp_OpenWindow`.

* Support other Nested-WIMP calls.

* Deprecate headers in favour of cswis.

* `src/desktop/mode.c`: Are the pointer casts safe?

* Rename `<riscos/desktop/*.h>` to `<yacitros/desktop/*.h>`.

* Rename `<riscos/vector/*.h>` to `<yacitros/vector/*.h>`.

* Alter `desktop/label.c` so that a standard entry in the message file, such as `charset`, could specify the charset.
  As the file is loaded, iconv could convert to the native charset.

* Allow a template to be localized by going through all its text labels and replacing them with a look-up into a label file.
