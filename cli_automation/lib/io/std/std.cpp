#include "./std.h"

#pragma region Print base methods
static void ps_printf(FILE* s, const char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	size_t fmt_len = strlen(fmt) + 1;
	wchar_t* wfmt = (wchar_t*)malloc(fmt_len * sizeof(wchar_t));
	if (!wfmt) return;
	#ifdef WIN_OS
		#if defined(UNICODE) || defined(_UNICODE)
			if(_setmode(_fileno(stdout), _O_U16TEXT) == -1)
			{
				fprintf(stderr, "Error: Could not set stdout to UTF-8 \n");
				#ifdef DEBUG
				exit(EXIT_FAILURE);
				#endif
			}
			if (_setmode(_fileno(stderr), _O_U16TEXT) == -1)
			{
				fprintf(stderr, "Error: Could not set stderr to UTF-8 \n");
				#ifdef DEBUG
				exit(EXIT_FAILURE);
				#endif
			}
		#endif
	#else
		setlocale(LC_ALL, "en_US.UTF-8");
	#endif
	mbstowcs(wfmt, fmt, fmt_len);
	for (wchar_t* p = wfmt; *p; p++) {
		if (*p == L'%' && *(p + 1) == L's') {
			*p = L'%';
			*(p + 1) = L'h';
			*(p + 2) = L's';
			p++;
		}
	}
	vfwprintf(s, wfmt, args);
	va_end(args);
	free(wfmt);
}
static void print_f(const char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	ps_printf(stdout, fmt, args );
	va_end(args);
}
static void print_ferr(const char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	ps_printf(stderr, fmt, args);
	va_end(args);
}
static void print_ln(const char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	print_f(concat(fmt, "\n"), args);
	va_end(args);
}
static void print_lnerr(const char* fmt, ...)
{
	va_list args; va_start(args, fmt);
	print_ferr(concat(fmt, "\n"), args);
	va_end(args);
}
#pragma endregion

#pragma region Objects
const SystemType System = {
	.out = { print_f, print_ln },
	.err = { print_ferr, print_lnerr }
};
#pragma endregion