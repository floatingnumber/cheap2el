/*
 * Copyright 2010 sakamoto.gsyc.3s@gmail.com
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * cheap2el : COFF Object file functions
 *
 * $Id$
 */

#include "cheap2el.h"
#include <windows.h>

// {{{ cheap2el_coff_obj_map_from_memory()

PCHEAP2EL_COFF_OBJ
cheap2el_coff_obj_map_from_memory(
        LPVOID lpvMemoryBuffer,
        CHEAP2EL_ERROR_CODE *err
        )
{
    PCHEAP2EL_COFF_OBJ coff = NULL;
    PIMAGE_FILE_HEADER file_header = NULL;
    DWORD dwptr1, dwptr2;

    if (NULL == lpvMemoryBuffer) {
        *err = CHEAP2EL_EC_LACK_OF_MEMORY_BUFFER;
        return NULL;
    }

    coff = GlobalAlloc(GMEM_ZEROINIT, sizeof(CHEAP2EL_COFF_OBJ));
    if (NULL == coff) {
        *err = CHEAP2EL_EC_MEMORY_ALLOC;
        return NULL;
    }

    coff->dwBase = (DWORD)lpvMemoryBuffer;
    file_header = (PIMAGE_FILE_HEADER)lpvMemoryBuffer;
    coff->fileHeader = file_header;
    dwptr1 = coff->dwBase + sizeof(IMAGE_FILE_HEADER);
    coff->sectionHeaders = (PIMAGE_SECTION_HEADER)dwptr1;
    if (file_header->PointerToSymbolTable) {
        dwptr1 = coff->dwBase + file_header->PointerToSymbolTable;
        coff->symbolTable = (PIMAGE_SYMBOL)dwptr1;
    }
    return coff;
}

// }}}
// {{{ cheap2el_coff_obj_enumerate_relocations()

int
cheap2el_coff_obj_enumerate_relocations(
        PCHEAP2EL_COFF_OBJ coff,
        PIMAGE_SECTION_HEADER sect,
        CHEAP2EL_COFF_OBJ_ENUM_RELOCATION_CALLBACK cb,
        LPVOID lpApplicationData
        )
{
    int result = 0;
    PIMAGE_RELOCATION reloc = NULL;
    DWORD dwptr = 0;

    if (NULL == cb) {
        return 0;
    }

    dwptr = coff->dwBase + sect->PointerToRelocations;
    reloc = (PIMAGE_RELOCATION)dwptr;
    for (result = 0;
            result != sect->NumberOfRelocations;
            result++, reloc++) {
        if (NULL != cb && 
                cb(coff, sect, reloc, result, lpApplicationData)) {
            result++;
            break;
        }
    }
    return result;
}

// }}}
