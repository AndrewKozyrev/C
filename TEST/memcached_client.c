/*
 * Memcached client
 * Author: A.B. Kozyrev
 *
 *
 * Command-line args:
 * -s -- set function
 * -g -- get function
 * -d -- delete key function
 * -h -- print help and exit
 */


/*
 *  System headers
 */
#include <libmemcached/memcached.h>
#include <stdio.h>
#include <string.h>

/*
 *  Function definition
 */
int getparam(int, char**);
memcached_return_t setData(char*, char*, int);
char* getData(char *key);
memcached_return_t deleteData(char*);
int help();


/*
 *  Global variables
 */
memcached_st *memc;
memcached_return_t rc;


int main(int argc, char **argv) {
  //memcached_servers_parse (char *server_strings);
  memcached_server_st *servers = NULL;
  memc = memcached_create(NULL);
  servers = memcached_server_list_append(servers, "localhost", 11211, &rc);
  rc = memcached_server_push(memc, servers);

  if (rc != MEMCACHED_SUCCESS)
    {
        fprintf(stderr, "Couldn't add server: %s\n", memcached_strerror(memc, rc));
    }

  if (getparam(argc, argv) == 1) { exit(1); }

  return 0;
}

int getparam(int argc, char **argv)
{
    if ( argc != 2 || argv[1][0] != '-' ) {
        help();
        return 1;
    }

    char opt;
    opt = argv[1][1];

    switch(opt) {
        case 's':
            printf("Set function: \nEnter key: ");
            char key[1000];
            scanf("%s", key);
            printf("Enter value: ");
            char value[1000];
            scanf("%s", value);
            printf("Enter expiration time: ");
            int time;
            scanf("%d", &time);
            rc = setData(key, value, time);
            break;
        case 'g':
            printf("Get function: \nEnter key: ");
            scanf("%s", key);
            getData(key);
            break;
        case 'd':
            printf("Delete function: \nEnter key: ");
            scanf("%s", key);
            rc = deleteData(key);
            break;
        case 'h':
            help();
            return 1;
            break;
        default:
            help();
            return 1;
            break;
    }

    return 0;
}



memcached_return_t setData(char *key, char *value, int time)
{
    rc = memcached_set(memc, key, strlen(key), value, strlen(value), (time_t)time, (uint32_t)0);

    if (rc == MEMCACHED_SUCCESS)
        fprintf(stderr, "Key stored successfully\n");
    else
        fprintf(stderr, "Couldn't store key: %s\n", memcached_strerror(memc, rc));

    return rc;
}

char* getData(char *key)
{
    char *retval;
    size_t value_length;
    uint32_t flags;
    retval = memcached_get(memc, key, strlen(key), &value_length, &flags, &rc);

    if (rc == MEMCACHED_SUCCESS) {
        printf("Value: %s\n", retval);
        free(retval);
    }
    else {
        fprintf(stderr, "Couldn't retrieve key: %s\n", memcached_strerror(memc, rc));
    }
}

memcached_return_t deleteData(char *key)
{
    rc = memcached_delete(memc, key, strlen(key), (time_t)0);

    if (rc == MEMCACHED_SUCCESS) {
        fprintf(stderr, "Key deleted successfully\n");
    }
    else {
        fprintf(stderr, "Couldn't delete key: %s\n", memcached_strerror(memc, rc));
    }

    return rc;
}


// Help
int help()
{
    printf("\nMemcached client for C\n\n");
    printf("Command-line args:\n");
    printf("-s -- set (key, value) pair\n");
    printf("-g -- get data from server\n");
    printf("-d -- delete data from server\n");
    printf("-h -- print help and exit\n\n");
    printf("Synopsis:\n");
    printf("memclient -s[g][d][h]\n\n");
    return 0;
}
