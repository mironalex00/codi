#include "files.h"
#include "assert.h"

File* get_file_contents(const char* filepath)
{
	File file {};
	FILE* result = fopen(filepath, "rt");
	assert(result);
	//TODO; Seguir los metodos
	return nullptr;
}

File* read_json_file(const char* filepath, const char* output, char** error_msg)
{
	return nullptr;
}
