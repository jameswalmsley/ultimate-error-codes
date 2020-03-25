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

/* Define ERROR_USE_TABLES to generate error string tables in this object. */
#define ERROR_USE_TABLES

#include <stdio.h>
#include "error.h"

static const struct _error_module* getErrorModuleEntry(Error_t code)
{
    for (size_t i = 0; i < sizeof(_g_err_modules) / sizeof(struct _error_module); i++)
    {
        const struct _error_module* module = &_g_err_modules[i];
        if (GET_ERROR_MODULE(code) == module->id)
        {
            return module;
        }
    }

    return NULL;
}

const char* getErrorModuleName(Error_t code)
{
    const struct _error_module* module = getErrorModuleEntry(code);
    if (!module)
    {
        return "UNDEFINED_MODULE";
    }

    return module->name;
}

const char* getErrorModuleDescription(Error_t code)
{
    const struct _error_module* module = getErrorModuleEntry(code);
    if (!module)
    {
        return "";
    }

    return module->description;
}

const struct _error_code* getErrorCodeEntry(Error_t code)
{
    if (!IS_ERROR(code) && code != ERR_NONE)
    {
        return NULL;
    }

    const struct _error_module* module = getErrorModuleEntry(code);
    if (IS_GLOBAL_ERROR(code))
    {
        module = getErrorModuleEntry(0);
    }

    if (!module)
    {
        return NULL;
    }

    const struct _error_code* entry = module->codes;
    while (!(entry->id == 0 && entry->name == NULL && entry->description == NULL))
    {
        if (entry->id == GET_ERROR_CODE(code))
        {
            return entry;
        }
        entry++;
    }

    return NULL;
}

const char* getErrorName(Error_t code)
{
    const struct _error_code* entry = getErrorCodeEntry(code);
    if (entry)
    {
        return entry->name;
    }

    return "UNDEFINED_ERROR";
}

const char* getErrorDescription(Error_t code)
{
    const struct _error_code* entry = getErrorCodeEntry(code);
    if (entry)
    {
        return entry->description;
    }

    return "";
}

void fprintError(FILE* fp, Error_t code)
{
    fprintf(fp, "***** ::\n");
    fprintf(fp, "Error   : 0x%08x\n", code);
    fprintf(fp,
            "Module  : %s - %s:%d\n",
            getErrorModuleName(code),
            getErrorModuleDescription(code),
            GET_ERROR_LINE(code));

    fprintf(fp, "Details : %s - %s\n", getErrorName(code), getErrorDescription(code));
    fprintf(fp, "*****\n\n");
}

void printError(Error_t code)
{
    fprintError(stderr, code);
}

