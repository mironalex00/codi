#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#pragma region Definitions
typedef enum {
    READ_OK = 0,
    READ_ERR_FILE_NOT_EXISTS = -1,
    READ_ERR_MEM = -2,
    READ_ERR_TOO_LARGE = 1,
    READ_ERR_OPEN = 2,
    READ_ERR_PARSE = 3,
    READ_ERR_INVALID = 4
} ReadStatus;
typedef struct {
    ReadStatus status;
    const char* name;
    const char* content;
    size_t size;
} File;
#pragma endregion

#pragma region Functions
File* get_file_contents(const char* filepath);
File* read_json_file(const char* filepath, const char* output, char** error_msg);
#pragma endregion