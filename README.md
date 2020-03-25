```
Ultimate Error Codes

Copyright (C) 2013 - 2020 James Walmsley <james@fullfat-fs.co.uk>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
```


# Ultimate Error Codes

This system allows an entire system to have a global set of error codes.
Any level of a system can emit an Error_t and that can be safely passed
back through to an external user API.

This ensures that errors are detected and emitted at their source.

If an Error_t is encountered it should not be discarded and overwritten
by an Error_t code from a calling function.

* The system can have up to 256 global error codes.
* The system can have up to 256 modules.
* Each module can have up to 256 error codes.

* The encoding space is flexible, i.e. lower line resolution for more modules/errors.
  - 256/256 modules/errors seems reasonable.
  - Once a project has decided on this split, it should not be changed.

In abstract an Error is an abstraction of a cause of an event (reason)
combined with a unique context (location).

This encoding scheme combines these properties.

## Use

All errors are included globally with a simple:

```
#include "error.h"
```

The error headers can be easily packaged and deployed for use in other projects,
allowing them to "pretty" print any errorcodes received.

## Error-Code Space

```
0x80000000  // Top-bit (sign bit) is set - This is an error. (Otherwise a value).
0x40000000  // Global errors have an extra bit set.

0x0000ff00  // The module the error was emitted from.
0x000000ff  // The specific error code.

0x0fff0000  // Line number of emitted error.
0x30000000  // Location resolution bits.
```

## What errors look like?

A module specific error:
```
Error   : 0x80070101
Module  : MODULE_MAIN - main.c:7
Details : ERR_NO_MEMORY - Could not allocate memory
```

A global error.
```
Error   : 0xc01a0301
Module  : MODULE_EXAMPLE - example.c:26
Details : ERR_GENERIC - Generic error
```
Errors should always be printed as a 32-bit hex string.

## Error Location

The error location is inserted into the error code when the error is emitted
using the ERROR() macro.

The ERROR() macro automatically determines the resolution based on the __LINE__ number.

The encoding allows for files with lengths up to 61440 lines.

| Resolution | Binning | Range (Begin) | Range (End) |
| ---------: | ------: | ------------: | ----------: |
|          0 |       1 |             1 |        4096 |
|          1 |       2 |          4097 |       12288 |
|          2 |       4 |         12289 |       28672 |
|          3 |       8 |         28673 |       61440 |

## Testing For Errors

Use the IS_ERROR() macro:

```
Error_t err = uart_init();
if(IS_ERROR(err))
{
  LOGE("Uart initialisation failed\n");
  return err; // Pass the error up!
}
```

Its also perfectly fine to do this:

```
if(err < 0) {}
```

## Comparing Errors

Use the GET_ERROR() macro to check for a specific error:

```
Error_t mmu_error = init_mmu();
if(GET_ERROR(mmu_error) == ERR_MMU_INIT_FAILED)
{
  /* Fatal error cannot continue.*/
  printk("Kernel could not init mmu.");
  for(;;);
}
```

## Error Values

I'd recommend keeping values and errors separate, however its perfectly OK to do:

```
int32_t value = read_adc();
if(IS_ERROR(value))
{
  LOGE("Adc read failed\n");
}

calculateParams(value);
```

Alternatively:

```
int32_t value;
Error_t err = read_adc(&value);
if(IS_ERROR(err))
{
  LOGE("Adc read failed\n");
}

...
```

## Error Info and Tables.

There is a global_errors.h file, to define the global errors:

```
#ifndef GLOBAL_ERRORS_H
#define GLOBAL_ERRORS_H

#define DEF_GLOBAL_ERROR(code) (DEF_ERROR(MODULE_GLOBAL, code) | _ERR_GLOBAL_MASK)

#define ERR_NONE                      (0)
#define ERR_GENERIC   DEF_GLOBAL_ERROR(1)
#define ERR_INVAL     DEF_GLOBAL_ERROR(2)

#ifdef ERROR_USE_TABLES
MODULE_ERRORS(MODULE_GLOBAL)
{
    DEF_ERR_INFO(ERR_GENERIC, "Generic error"),
    DEF_ERR_INFO(ERR_INVAL,   "Invalid parameter/value"),
};
#endif

#endif
```

All other modules define a list of error codes and their description in the same way.

## Defining Error Codes

Single prefix for all error codes:

```
ERR_x_y_z
```

I'd recommend sticking to a convention like:

```
ERR_MYMODULE_CANNOT_COMPUTE // Where MYMODULE namespaces the defines.
```

