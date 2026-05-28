#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <time.h>

#define RAMMY_PORT 45454
#define MAX_NODES 128
#define NODE_TIMEOUT_SEC 5

typedef struct {
    char node_name[64];
    uint64_t total_ram_mb;
    uint64_t free_ram_mb;
    uint64_t uptime_sec;
} rammy_heartbeat_t;

typedef struct {
    char node_name[64];
    char ip[64];
    uint64_t total_ram_mb;
    uint64_t free_ram_mb;
    uint64_t uptime_sec;
    time_t last_seen;
} rammy_node_t;

static rammy_node_t nodes[MAX_NODES];
static int node_count = 0;

static int find_node(const char *name, const char *ip) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].node_name, name) == 0 && strcmp(nodes[i].ip, ip) == 0)
            return i;
    }
    return -1;
}

static void update_node(const rammy_heartbeat_t *hb, const char *ip) {
    int idx = find_node(hb->node_name, ip);

    if (idx < 0) {
        if (node_count >= MAX_NODES) {
            fprintf(stderr, "[RAMMY WARN] node table full\n");
            return;
        }

        idx = node_count++;
        memset(&nodes[idx], 0, sizeof(nodes[idx]));
        strncpy(nodes[idx].node_name, hb->node_name, sizeof(nodes[idx].node_name) - 1);
        strncpy(nodes[idx].ip, ip, sizeof(nodes[idx].ip) - 1);

        printf("[RAMMY JOIN] node=%s ip=%s\n", hb->node_name, ip);
    }

    nodes[idx].total_ram_mb = hb->total_ram_mb;
    nodes[idx].free_ram_mb = hb->free_ram_mb;
    nodes[idx].uptime_sec = hb->uptime_sec;
    nodes[idx].last_seen = time(NULL);
}

static void print_fabric(void) {
    uint64_t total_ram = 0;
    uint64_t free_ram = 0;
    int alive = 0;
    time_t now = time(NULL);

    printf("\033[2J\033[H");
    printf("C-RAMMY v0 FABRIC VIEW\n");
    printf("----------------------\n");

    for (int i = 0; i < node_count; i++) {
        int age = (int)(now - nodes[i].last_seen);
        int is_alive = age <= NODE_TIMEOUT_SEC;

        if (is_alive) {
            alive++;
            total_ram += nodes[i].total_ram_mb;
            free_ram += nodes[i].free_ram_mb;
        }

        printf("%s node=%s ip=%s total=%luMB free=%luMB uptime=%lus last_seen=%ds\n",
               is_alive ? "[ALIVE]" : "[DEAD] ",
               nodes[i].node_name,
               nodes[i].ip,
               nodes[i].total_ram_mb,
               nodes[i].free_ram_mb,
               nodes[i].uptime_sec,
               age);
    }

    printf("----------------------\n");
    printf("nodes_alive=%d\n", alive);
    printf("pooled_total_ram=%luMB\n", total_ram);
    printf("pooled_free_ram=%luMB\n", free_ram);
    printf("----------------------\n");
}

int main(void) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        close(sockfd);
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(RAMMY_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(sockfd);
        return 1;
    }

    printf("C-RAMMY v0 FABRIC LISTENER ONLINE port=%d\n", RAMMY_PORT);

    time_t last_print = 0;

    while (1) {
        fd_set readfds;
        struct timeval tv;

        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        tv.tv_sec = 1;
        tv.tv_usec = 0;

        int ready = select(sockfd + 1, &readfds, NULL, NULL, &tv);

        if (ready < 0) {
            perror("select");
            break;
        }

        if (ready > 0 && FD_ISSET(sockfd, &readfds)) {
            rammy_heartbeat_t hb;
            struct sockaddr_in sender;
            socklen_t sender_len = sizeof(sender);

            ssize_t received = recvfrom(sockfd, &hb, sizeof(hb), 0,
                                        (struct sockaddr *)&sender, &sender_len);

            if (received == sizeof(hb)) {
                char ip[64];
                inet_ntop(AF_INET, &sender.sin_addr, ip, sizeof(ip));
                update_node(&hb, ip);
            }
        }

        time_t now = time(NULL);
        if (now != last_print) {
            print_fabric();
            last_print = now;
        }
    }

    close(sockfd);
    return 0;
}
