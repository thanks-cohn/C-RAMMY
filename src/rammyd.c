
/*
    C-RAMMY v0
    rammyd.c

    FIRST LIVING NODE DAEMON
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define RAMMY_PORT 45454
#define HEARTBEAT_INTERVAL 1

typedef struct
{
    char node_name[64];
    uint64_t total_ram_mb;
    uint64_t free_ram_mb;
    uint64_t uptime_sec;
}
rammy_heartbeat_t;

static uint64_t get_total_ram_mb(void)
{
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp)
        return 0;

    char line[256];
    uint64_t kb = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "MemTotal: %lu kB", &kb) == 1)
        {
            fclose(fp);
            return kb / 1024;
        }
    }

    fclose(fp);

    return 0;
}

static uint64_t get_free_ram_mb(void)
{
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp)
        return 0;

    char line[256];
    uint64_t kb = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "MemAvailable: %lu kB", &kb) == 1)
        {
            fclose(fp);
            return kb / 1024;
        }
    }

    fclose(fp);

    return 0;
}

static uint64_t get_uptime_sec(void)
{
    FILE *fp = fopen("/proc/uptime", "r");
    if (!fp)
        return 0;

    double uptime = 0.0;

    fscanf(fp, "%lf", &uptime);

    fclose(fp);

    return (uint64_t)uptime;
}

int main(void)
{
    int sockfd;

    struct sockaddr_in broadcast_addr;

    int broadcast_enable = 1;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("socket");
        return 1;
    }

    if (setsockopt(
            sockfd,
            SOL_SOCKET,
            SO_BROADCAST,
            &broadcast_enable,
            sizeof(broadcast_enable)) < 0)
    {
        perror("setsockopt");
        return 1;
    }

    memset(&broadcast_addr, 0, sizeof(broadcast_addr));

    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(RAMMY_PORT);
    
const char *target_ip = getenv("RAMMY_BCAST");
if (!target_ip || target_ip[0] == '\0')
    target_ip = "255.255.255.255";

broadcast_addr.sin_addr.s_addr = inet_addr(target_ip);


    char hostname[64];

    gethostname(hostname, sizeof(hostname));

    printf("\n");
    printf("=====================================\n");
    printf("C-RAMMY v0 NODE ONLINE\n");
    printf("=====================================\n");
    printf("Node: %s\n", hostname);
    printf("Broadcast Port: %d\n", RAMMY_PORT);\n    printf("Broadcast Target: %s\n", target_ip);
    printf("=====================================\n");
    printf("\n");

    while (1)
    {
        rammy_heartbeat_t hb;

        memset(&hb, 0, sizeof(hb));

        snprintf(hb.node_name, sizeof(hb.node_name), "%s", hostname);

        hb.total_ram_mb = get_total_ram_mb();
        hb.free_ram_mb = get_free_ram_mb();
        hb.uptime_sec = get_uptime_sec();

        ssize_t sent = sendto(
            sockfd,
            &hb,
            sizeof(hb),
            0,
            (struct sockaddr *)&broadcast_addr,
            sizeof(broadcast_addr));

        if (sent < 0)
        {
            perror("sendto");
        }
        else
        {
            printf(
                "[RAMMY HEARTBEAT] "
                "node=%s "
                "total_ram=%luMB "
                "free_ram=%luMB "
                "uptime=%lus\n",
                hb.node_name,
                hb.total_ram_mb,
                hb.free_ram_mb,
                hb.uptime_sec);
        }

        sleep(HEARTBEAT_INTERVAL);
    }

    close(sockfd);

    return 0;
}
