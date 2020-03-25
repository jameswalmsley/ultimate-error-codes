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

#ifndef GLOBAL_ERRORS_H
#define GLOBAL_ERRORS_H

#define DEF_GLOBAL_ERROR(code) (DEF_ERROR(MODULE_GLOBAL, code) | _ERR_GLOBAL_MASK)

#define ERR_NONE                        (0)
#define ERR_GENERIC     DEF_GLOBAL_ERROR(1)
#define ERR_INVAL       DEF_GLOBAL_ERROR(2)

#ifdef ERROR_USE_TABLES
MODULE_ERRORS(MODULE_GLOBAL)
{
    DEF_ERR_INFO(ERR_NONE,    "No Error / Success"),
    DEF_ERR_INFO(ERR_GENERIC, "Generic error"),
    DEF_ERR_INFO(ERR_INVAL,   "Invalid parameter/value"),
    {0}
};
#endif

#endif

