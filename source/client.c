/*
 * client.c
 *
 *  Created on: 2022年10月22日
 *      Author: brian1009
 */

#include "client.h"
#include <stdio.h>
#include <string.h>
#include "fsl_debug_console.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"

#define SERVER_IP "192.168.137.72"
#define SERVER_PORT 5000

void add_item(int item_id) {
    unsigned char path[32];
    sprintf(path, "/add/%d", item_id);
    send_request(path);
}

void remove_item(int item_id) {
    unsigned char path[32];
    sprintf(path, "/remove/%d", item_id);
    send_request(path);
}

void send_request(const char path[]) {
    int ret, len;
    unsigned char buf[256];

    // create socket
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        PRINTF("socket() failed\n");
        goto exit;
    }

    // fill in server info
    uint32_t converted_addr;
    struct sockaddr_in server_addr;
    inet_pton(AF_INET, SERVER_IP, &converted_addr);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = converted_addr;
    server_addr.sin_port = htons(SERVER_PORT);

    // connect to server
    if (connect(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        PRINTF("connect() failed\n");
        goto exit;
    }

    // send request
    len = sprintf((char*) buf, "GET %s HTTP/1.1\r\n\r\n", path);
    while ((ret = write(server_fd, buf, len)) <= 0) {
        if (ret != 0) {
            PRINTF("write() failed\n");
            goto exit;
        }
    }

    // read response
    do {
        len = sizeof(buf) - 1;
        memset(buf, 0, sizeof(buf));
        if (read(server_fd, buf, len) <= 0)
            break;
    } while (1);

exit:
    close(server_fd);
}
