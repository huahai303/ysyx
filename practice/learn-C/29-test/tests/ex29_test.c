#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

typedef int (*lib_function)(const char *data);

void run_test(void *lib, const char *func_name, const char *data)
{
		lib_function func = (lib_function)dlsym(lib,func_name);
		if(func == NULL)
		{
				printf("[FAIL] could not find the function: %s",func_name);
				return;
		}
		int rc = func(data);
		if(rc == 0)
				printf("[PASS] %s: %s\n",func_name, data);
		else
				printf("[FAIL] %s: %s\n",func_name, data);

}
int main()
{

    void *lib = dlopen("./build/libex29.so", RTLD_NOW);
    check(lib != NULL, "Failed to open the library libex29.so: %s",dlerror());

    run_test(lib, "print_a_message","hello world");
		run_test(lib, "uppercase","hello world");
		run_test(lib, "lowercase","HELLO WORLD");
    int rc = dlclose(lib);
    check(rc == 0, "Failed to close libex29.so");

    return 0;

error:
    return 1;
}
