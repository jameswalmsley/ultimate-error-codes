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

#ifndef EXAMPLE_ERROR_H
#define EXAMPLE_ERROR_H

#define DEF_EXAMPLE_ERROR(code) DEF_ERROR(MODULE_EXAMPLE, code)

#define ERR_EXAMPLE_1_FAIL  DEF_EXAMPLE_ERROR(1)
#define ERR_EXAMPLE_2_FAIL  DEF_EXAMPLE_ERROR(2)


#ifdef ERROR_USE_TABLES
MODULE_ERRORS(MODULE_EXAMPLE)
{
    DEF_ERR_INFO(ERR_EXAMPLE_1_FAIL, "Example 1 failure."),
    DEF_ERR_INFO(ERR_EXAMPLE_2_FAIL, "Example 2 failure."),
    {0}
};
#endif

#endif

