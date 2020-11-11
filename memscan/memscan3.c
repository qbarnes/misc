/*
 * Check for the maximum amount of memory usable.
 *
 * Measure read memory performance at intervals.
 *
 * Would prefer to use clock_gettime(CLOCK_MONOTONIC, ...), but
 * DJGPP doesn't support it.  Use flaky gettimeofday() instead.
 *
 * Running original memscan.exe under MS-DOS produces beeps, I'd
 * assume when hitting an out-of-memory condition.  Let's avoid
 * those as much as possible in this version.
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*
 * Find maximum amount of malloc'able memory.
 */

size_t
find_upper(size_t start)
{
	char	*p;
	size_t	prev_memsz = 0, cur_memsz = start;

	do {
		printf("."); fflush(stdout);
		if ((p = malloc(cur_memsz))) {
			free(p);
			prev_memsz = cur_memsz;
			cur_memsz *= 1.05;
		}
	} while (p);
	printf("*\n"); fflush(stdout);

	return prev_memsz;
}


int
timeval_le(const struct timeval *t1, const struct timeval *t2)
{
	if (t1->tv_sec < t2->tv_sec)
		return 1;
	if (t1->tv_sec == t2->tv_sec && t1->tv_usec <= t2->tv_usec)
		return 1;
	return 0;
}


size_t
touch_mem(volatile char *p, size_t ps, const struct timeval *until)
{
	struct timeval	now;
	size_t	touches = 0;

	gettimeofday(&now, NULL);

	while (timeval_le(&now, until))
	{
		p[(size_t)(drand48() * ps)];
		++touches;
		gettimeofday(&now, NULL);
	}

	return touches;
}


int
main(int argc, char **argv)
{
	unsigned int	interval = 8;
	unsigned int	duration = 5;

	switch (argc) {
	case 3:
		duration = strtol(argv[2], NULL, 0);
		/* FALLTHRU */
	case 2:
		interval = strtol(argv[1], NULL, 0);
		break;
	case 1:
		break;
	default:
		fprintf(stderr, "Usage: %s [[duration] interval]\n", argv[0]);
		break;
	}

	size_t	upper = find_upper(262144);
	char	*p;

	if (!(p = malloc(upper))) {
		fprintf(stderr, "Malloc for upper of %llu failed.",
			(unsigned long long)upper);
		return 1;
	}

	printf("Upper limit is %llu KiB.\n", (unsigned long long)upper / 1024);

	size_t	touches;

	for (int pass = 0; pass <= interval; ++pass) {
		struct timeval	until;

		gettimeofday(&until, NULL);
		until.tv_sec += duration;

		touches = touch_mem(p, upper * pass / interval, &until);

		printf("Interval %d: %llu touches/sec.\n", pass,
			(unsigned long long)touches / duration);
	}

	free(p);

	return 0;
}
