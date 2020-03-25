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

#include <stdio.h>

/*
 *  Simply include "error.h" to get all error codes.
 */
#include "error.h"

/*
 *  Define the ERR_MODULE you are working within (a .c file).
 */
#define ERR_MODULE MODULE_EXAMPLE

extern int32_t getNumber(int);

int main()
{
    /*
     * We can define and initialise an Error_t code to no error/success.
     *
     */
    Error_t errcode = ERROR(ERR_NONE);
    printError(errcode);

    errcode = ERR_NONE; // This is equivalent.
    printError(errcode);

    /*
     * All errors are of typeError_t (an int32_t).
     *
     * We "throw" an error with ERROR()
     * - This combines and error reason with its location.
     * - Forming a completely "unique" error code.
     *
     * Any module can "throw" a global error, like ERR_GENERIC.
     */
    errcode = ERROR(ERR_GENERIC);
    printError(errcode);

    /*
     * It is only possible to "throw" errors from the correct module
     * The following statement results in a compiler error.
     */

#if 0
    errcode = ERROR(ERR_NO_MEMORY);
#endif

   /*
    * You can compare error code using GETERROR()
    */
    if(GET_ERROR(errcode) == ERR_GENERIC)
    {
        printf("Encountered ERR_GENERIC,, continuing...\n");
    }

    /*
     * We can receiveError_t codes from other modules.
     *
     * - If we do, we should pass it back up the stack.
     *   (don't replaceError_t from lower in the stack)
     */
    Error_t errval = getNumber(1);
    if(IS_ERROR(errval))
    {
        printError(errval);
    }

    /*
     * The encoding is also compatible with 'negative errors' 'positive values'.
     */
    int32_t val = getNumber(2);
    if(val < 0)
    {
        printError(val);
    }

    /*
     *  ERR_NONE, is the only code that always evaluates to 0.
     */
    return ERR_NONE | ERROR(ERR_NONE);
}

