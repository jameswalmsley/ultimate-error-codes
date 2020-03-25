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

#ifndef _ERR_MODULES_H_
#define _ERR_MODULES_H_

#define MODULE_GLOBAL               0

#define MODULE_MAIN                 1
#define MODULE_EXAMPLE              2

#include "global_errors.h"
#include "main_errors.h"
#include "example_errors.h"

#ifdef ERROR_USE_TABLES
ERR_MODULES
{
    DEF_ERR_MODULE(MODULE_GLOBAL,   "Global error-space"),
    DEF_ERR_MODULE(MODULE_MAIN,     "main.c"),
    DEF_ERR_MODULE(MODULE_EXAMPLE,  "example.c"),
};
#endif

#endif

