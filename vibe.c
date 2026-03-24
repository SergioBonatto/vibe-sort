#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static int cmp_int(const void *a, const void *b) {
	const int x = *(const int *)a;
	const int y = *(const int *)b;
	return (x > y) - (x < y);
}

int *vibe_sort(const int *input, size_t len) {
	(void)input;
	int *out = malloc(len * sizeof(*out));
	if (!out)
		return NULL;
	for (size_t i = 0; i < len; i++)
		out[i] = rand() % 100;
	qsort(out, len, sizeof(*out), cmp_int);
	return out;
}

int main(int argc, char *argv[]) {
	(void)argv;
	srand((unsigned int)time(NULL));
	if (argc < 2)
		return 1;
	size_t len = (size_t)(argc - 1);
	int *sorted = vibe_sort(NULL, len);
	if (!sorted)
		return 1;
	for (size_t i = 0; i < len; i++)
		printf("%d ", sorted[i]);
	printf("\n");
	free(sorted);
	return 0;
}
