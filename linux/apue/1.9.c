
/* USAGE: Print user ID and group ID */

/* The user ID of root or superuser is 0 */
/* If a process has superuser privileges,
 * most file permission check are bypassed. */
/* Some OS functions are restricted to the superuser. */

/* GROUP:
 * There is also a group file that maps group names
 * into numeric group IDs. /etc/group */

/* In addition to the group ID specified in /etc/passwd for a login name,
 * most UNIX systems allow a user to belong to additional groups.
 * for example: BSD allowed a user to belong to up to 16 additional groups.
 * These supplementary groups are got at login time by reading /etc/group */
#include "apue.h"
int main()
{
    /* print the user id and group id of this process */
    printf("uid = %d, gid = %d\n", getuid(), getgid());
    exit(0);
}
