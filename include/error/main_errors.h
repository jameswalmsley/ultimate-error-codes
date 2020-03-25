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

#ifndef MAIN_ERROR_H
#define MAIN_ERROR_H

#define DEF_MAIN_ERROR(code) DEF_ERROR(MODULE_MAIN, code)

#define ERR_NO_MEMORY   DEF_MAIN_ERROR(1)
#define ERR_WRITE_FAIL  DEF_MAIN_ERROR(2)


#ifdef ERROR_USE_TABLES
MODULE_ERRORS(MODULE_MAIN)
{
    DEF_ERR_INFO(ERR_NO_MEMORY,  "Could not allocate memory"),
    DEF_ERR_INFO(ERR_WRITE_FAIL, "Write failed"),
    {0}
};
#endif

#endif

