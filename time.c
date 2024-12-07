#include <stdio.h>
#include <sys/time.h>

int main()
{
	struct timeval tv;
	long long timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("%lld\n", timestamp);
	return (0);
}

// int main()
// {
//     struct timeval tv;
//     struct tm *local_time = localtime(&tv.tv_sec);

//     gettimeofday(&tv, NULL); // Get current time in seconds and microseconds
//     // Convert seconds part to local time
//     // Print local time
//     printf("Local time: %04d-%02d-%02d %02d:%02d:%02d\n",
//            local_time->tm_year + 1900, // tm_year is years since 1900
//            local_time->tm_mon + 1,     // tm_mon is months since January (0-11)
//            local_time->tm_mday,
//            local_time->tm_hour,
//            local_time->tm_min,
//            local_time->tm_sec);

//     return (0);
// }

// int main()
// {
//     struct timeval tv;
//     struct timezone tz;

//     gettimeofday(&tv,&tz);

//     printf("Seconds since 1/1/1970: %lu\n",tv.tv_sec);
//     printf("Microseconds: %d\n",tv.tv_usec);
//     printf("Minutes west of Greenwich: %d\n",tz.tz_minuteswest);
//     printf("Daylight Saving Time adjustment: %d\n",tz.tz_dsttime);

//     return(0);
// }

// int main()
// {
//     struct timeval tv;
//     struct timezone tz;
//     struct tm *today;
//     int zone;

//     gettimeofday(&tv, &tz);
//     /* get time details */
//     today = localtime(&tv.tv_sec);
//     printf("It's %d:%0d:%0d.%d\n",
//            today->tm_hour,
//            today->tm_min,
//            today->tm_sec,
//            tv.tv_usec);
//     /* set time zone value to hours, not minutes */
//     zone = tz.tz_minuteswest / 60;
//     /* calculate for zones east of GMT */
//     if (zone > 12)
//         zone -= 24;
//     printf("Time zone: GMT %+d\n", zone);
//     printf("Daylight Saving Time adjustment: %d\n", tz.tz_dsttime);

//     return (0);
// }