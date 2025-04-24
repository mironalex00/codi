#pragma once

#pragma region Enum definitions
typedef enum {
	JSON_NULL,
	JSON_BOOL,
	JSON_NUMBER,
	JSON_STRING,
	JSON_ARRAY,
	JSON_OBJECT
} JsonType;
#pragma endregion

#pragma region Struct definitions

#pragma endregion

#pragma region Function definitions
typedef struct JsonValue JsonValue;
typedef struct {
	char* key;
	JsonValue* value;
} JsonMember;
#pragma endregion