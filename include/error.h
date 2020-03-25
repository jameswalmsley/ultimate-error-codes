/*
 * Ultimate Error Codes
 *
 * Copyright (C) 2013 - 2020 James Walmsley <james@fullfat-fs.co.uk>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * @see README.md
 */

#ifndef _ULTIMATE_ERROR_H_
#define _ULTIMATE_ERROR_H_

#include <stdint.h>
#include <assert.h>

typedef int32_t Error_t;            ///< Main global error type.

#define _ERROR_MASK                 (0xc000ffff)            ///< Mask for comparing errors.
#define _ERR_BIT_MASK               (0x80000000)            ///< Indicates the field is an error (< 0).
#define _ERR_GLOBAL_MASK            (0x40000000)            ///< Indicates generic error space.
#define _ERR_RESOLUTION_MASK        (0x30000000)            ///< Line number resolution. 0..3
#define _ERR_CODE_MASK              (0x000000ff)            ///< Upto 256 error codes / module.
#define _ERR_MODULE_MASK            (0x0000ff00)            ///< Upto 256 modules.
#define _ERR_LINE_MASK              (0x0fff0000)            ///< Upto 61440 lines
#define _ERR_BINS                   ((_ERR_LINE_MASK >> 16) + 1)

/*
 *  Internal macros for setting error fields.
 */
#define _ERR_CODE(code)             (((code   <<  0) & _ERR_CODE_MASK))
#define _ERR_MODULE(module)         (((module <<  8) & _ERR_MODULE_MASK))
#define _ERR_LINE(line)             (((line   << 16) & _ERR_LINE_MASK))
#define _ERR_RESOLUTION(res)        (((res    << 28) & _ERR_RESOLUTION_MASK))

#define _ERR_OFFSET_BITS(res)       ((1 << res) - 1)

#define _ERR_OFF_3(res)             (((_ERR_OFFSET_BITS(res) >> 2) & 1) * (_ERR_BINS << 2))
#define _ERR_OFF_2(res)             (((_ERR_OFFSET_BITS(res) >> 1) & 1) * (_ERR_BINS << 1))
#define _ERR_OFF_1(res)             (((_ERR_OFFSET_BITS(res) >> 0) & 1) * (_ERR_BINS << 0))
#define _ERR_OFF_0(res)             (1)

#define _ERR_OFF_VAL(res)           (_ERR_OFF_0(res) + _ERR_OFF_1(res) + _ERR_OFF_2(res) + _ERR_OFF_3(res))

#define _ERR_RES_3(line)            (3)
#define _ERR_RES_2(line)            ((line < _ERR_OFF_VAL(3) - 1) ? 2 : _ERR_RES_3(line))
#define _ERR_RES_1(line)            ((line < _ERR_OFF_VAL(2) - 1) ? 1 : _ERR_RES_2(line))
#define _ERR_RES_0(line)            ((line < _ERR_OFF_VAL(1) - 1) ? 0 : _ERR_RES_1(line))
#define _ERR_RES_VAL(line)          (_ERR_RES_0(line))

/*
 *  Public macros for working with Error_t codes.
 */
#define IS_ERROR(code)              ((code & _ERR_BIT_MASK))
#define IS_GLOBAL_ERROR(code)       ((code & _ERR_GLOBAL_MASK))
#define GET_ERROR_RESOLUTION(code)  ((code & _ERR_RESOLUTION_MASK) >> 28)
#define GET_ERROR_LINE(code)        (((((code & _ERR_LINE_MASK)    >> 16)) << \
			GET_ERROR_RESOLUTION(code)) \
			+ _ERR_OFF_VAL(GET_ERROR_RESOLUTION(code)) \
			+ _ERR_OFFSET_BITS(GET_ERROR_RESOLUTION(code)))

#define GET_ERROR_MODULE(code)      ((code & _ERR_MODULE_MASK)     >>  8)
#define GET_ERROR_CODE(code)        ((code & _ERR_CODE_MASK)       >>  0)
#define GET_ERROR(code)             (IS_GLOBAL_ERROR(code) ? (code & (_ERROR_MASK & ~_ERR_MODULE_MASK)) : (code & _ERROR_MASK))


/*
 * These structures define the Error table data.
 */
struct _error_code
{
	uint8_t     id;                 ///< Error code.
	const char* name;               ///< Error name e.g. ERR_GENERIC etc.
	const char* description;        ///< Informative error information.
};

struct _error_module
{
	uint8_t     id;                 ///< Unique module identifier.
	const char* name;
	const char* description;
	const struct _error_code* codes;
};

/*
 *  Macros for generating Error information tables.
 */
#ifdef ERROR_USE_TABLES

#define ERR_MODULES                         static const struct _error_module _g_err_modules[] =
#define DEF_ERR_MODULE(name, description)   { name, #name, description, _g_err_codes_##name }
#define MODULE_ERRORS(module)               const struct _error_code _g_err_codes_##module[] =
#define DEF_ERR_INFO(name, description)     { GET_ERROR_CODE(name), #name, description }

#else

#define ERR_MODULES
#define DEF_ERR_MODULE(name, description)
#define MODULE_ERRORS(module)
#define DEF_ERR_INFO(name, description)

#endif

/*
 * Macro used to define an error code for a module.
 */
#define DEF_ERROR(module, code)     (_ERR_BIT_MASK | _ERR_CODE(code) | _ERR_MODULE(module))

/*
 * Include all error codes for each module globally.
 * - Modules can define e.g. ERR_LINE_RESOLUTION individually.
 */
#include "error/modules.h"

/*
 * Macro to "throw" an error.
 * . Where 'throw' means to pin its location.
 */
#define ERROR(code)     (code == 0 ? 0 : (code | ( _ERR_LINE((__LINE__ - (_ERR_OFF_VAL(_ERR_RES_VAL(__LINE__ - 1)) \
					>> _ERR_RES_VAL(__LINE__- 1))))) | _ERR_MODULE(ERR_MODULE) \
					| (_ERR_RESOLUTION(_ERR_RES_VAL(__LINE__- 1))))); \
					static_assert(code == 0 || IS_GLOBAL_ERROR(code) \
							|| (GET_ERROR_MODULE(code) == ERR_MODULE), \
							"Out-of-scope Error 'thrown' (Only use error codes from Global or Local module")

/*
 * Prototypes for pretty error functions.
 */
void printError(Error_t code);
const char* getErrorModuleName(Error_t code);
const char* getErrorModuleDescription(Error_t code);
const char* getErrorName(Error_t code);
const char* getErrorDescription(Error_t code);

#endif

