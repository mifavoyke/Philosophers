#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void unix_to_utc_time(long int unix_time) {
    int year = 1970;
    int month, day, hour, minute, second;

    // Days and seconds
    long days = unix_time / 86400;
    long remaining_seconds = unix_time % 86400;

    // Calculate the hour, minute, and second
    hour = remaining_seconds / 3600;
    remaining_seconds %= 3600;
    minute = remaining_seconds / 60;
    second = remaining_seconds % 60;

    // Calculate the year and day of the year
    while (1) {
        int days_in_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 366 : 365;
        if (days < days_in_year) break;
        days -= days_in_year;
        year++;
    }

    // Determine the month and day of the month
    static const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    for (month = 0; month < 12; month++) {
        int dim = days_in_month[month];
        if (month == 1 && leap) dim++; // February in a leap year
        if (days < dim) break;
        days -= dim;
    }
    day = days + 1; // Days are 0-indexed, so add 1 for human-readable format

    // Print result
    printf("UTC Time: %04d-%02d-%02d %02d:%02d:%02d\n", year, month + 1, day, hour, minute, second);
}

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // Use our function to convert to readable UTC time
    unix_to_utc_time(tv.tv_sec);

    return 0;
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

int main()
{
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv,&tz);

    printf("Seconds since 1/1/1970: %lu\n",tv.tv_sec);
    printf("Microseconds: %d\n",tv.tv_usec);
    printf("Minutes west of Greenwich: %d\n",tz.tz_minuteswest);
    printf("Daylight Saving Time adjustment: %d\n",tz.tz_dsttime);

    return(0);
}

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