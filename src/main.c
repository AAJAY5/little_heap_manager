#include <stdio.h>
#include "little_heap_mngr.h"

void *ptr_malloc_test = NULL;
void *ptr_calloc_test = NULL;

int main()
{
	printf("littel heap manager demo example.\r\n");
	
	printf("1. Allocating heap 100 bytes using LTL_MALLOC...");
	ptr_malloc_test = LTL_MALLOC(100);
	if (ptr_malloc_test)
	{
		printf("[Success]\r\n");
		printf("  -> Checking allocated size: %llu\r\n", LTL_ALLOCED_SIZE(ptr_malloc_test));
		printf("  -> Heap usage now: %llu\r\n", LTL_HEAP_USAGE());
	}
	else
	{
		printf("[Failed]\r\n");
	}

	printf("2. Allocating heap 2*100 bytes using LTL_CALLOC...");
	ptr_calloc_test = LTL_CALLOC(2, 100);
	if (ptr_calloc_test)
	{
		printf("[Success]\r\n");
		printf("  -> Checking allocated size: %llu\r\n", LTL_ALLOCED_SIZE(ptr_calloc_test));
		printf("  -> Heap usage now: %llu\r\n", LTL_HEAP_USAGE());
	}
	else
	{
		printf("[Failed]\r\n");
	}

	printf("3. Releasing memory...\r\n");
	printf("  -> Heap usage before: %llu\r\n", LTL_HEAP_USAGE());
	LTL_FREE(ptr_calloc_test);
	LTL_FREE(ptr_malloc_test);
	printf("  -> Heap usage now   : %llu\r\n", LTL_HEAP_USAGE());

	return (0);
}