#include "netlink_listener.h"
#include "visca_ctrl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define NETLINK_VISCA 31
#define MAX_PAYLOAD 32

static void netlink_read_cb(struct aeEventLoop *el, int fd, void *clientData, int mask) {
    struct nlmsghdr *nlh = (struct nlmsghdr*) malloc(NLMSG_SPACE(MAX_PAYLOAD));
    if (!nlh) return;

    struct iovec iov = { .iov_base = nlh, .iov_len = NLMSG_SPACE(MAX_PAYLOAD) };
    struct sockaddr_nl sa;
    struct msghdr msg = { 
        .msg_name = &sa, .msg_namelen = sizeof(sa),
        .msg_iov = &iov, .msg_iovlen = 1 
    };

    ssize_t len = recvmsg(fd, &msg, 0);
    if (len < 0) {
        perror("netlink recvmsg");
        free(nlh);
        return;
    }

    int data_len = nlh->nlmsg_len - NLMSG_HDRLEN;
    unsigned char *data = (unsigned char *)NLMSG_DATA(nlh);

    if (data_len == 1) {
        if (data[0] == 0x01) {
            printf("[Netlink] Recv: MIPI ON\n");
            visca_ctrl_set_mipi(1);
        } else if (data[0] == 0x00) {
            printf("[Netlink] Recv: MIPI OFF\n");
            visca_ctrl_set_mipi(0);
        }
    }

    free(nlh);
}

int start_netlink_listener(aeEventLoop *el) {
    int fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_VISCA);
    if (fd < 0) {
        perror("netlink socket");
        return -1;
    }

    struct sockaddr_nl src_addr;
    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = 0; 
    
    if (bind(fd, (struct sockaddr *)&src_addr, sizeof(src_addr)) < 0) {
        perror("netlink bind");
        close(fd);
        return -1;
    }

    int group = 1;
    setsockopt(fd, SOL_NETLINK, NETLINK_ADD_MEMBERSHIP, &group, sizeof(group));

    if (aeCreateFileEvent(el, fd, AE_READABLE, netlink_read_cb, NULL) == AE_ERR) {
        printf("Failed to register netlink event\n");
        close(fd);
        return -1;
    }

    printf("Netlink listener started on fd %d\n", fd);
    return fd;
}