/* BSD Socket API Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#ifdef __wasi__
#include <wasi_socket_ext.h>
#endif
#include "esp_log.h"
#include "sdkconfig.h"

#if defined(CONFIG_EXAMPLE_IPV4)
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV4_ADDR
#elif defined(CONFIG_EXAMPLE_IPV6)
#define HOST_IP_ADDR CONFIG_EXAMPLE_IPV6_ADDR
#else
#define HOST_IP_ADDR ""
#endif

#define PORT CONFIG_EXAMPLE_PORT

static const char *TAG = "example";
static const char *payload = "Message from ESP32 ";

static void *tcp_client_task(void *pvParameters)
{
    char rx_buffer[128];
    char host_ip[] = HOST_IP_ADDR;
    int addr_family = 0;
    int ip_protocol = 0;
    int errno = 0;

    while (1) {
#if defined(CONFIG_EXAMPLE_IPV4)
        struct sockaddr_in dest_addr;
        inet_pton(AF_INET, host_ip, &dest_addr.sin_addr);
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(PORT);
        addr_family = AF_INET;
        ip_protocol = IPPROTO_IP;
#elif defined(CONFIG_EXAMPLE_IPV6)
        struct sockaddr_in6 dest_addr = { 0 };
        inet_pton(AF_INET6, host_ip, &dest_addr.sin6_addr);
        dest_addr.sin6_family = AF_INET6;
        dest_addr.sin6_port = htons(PORT);
        addr_family = AF_INET6;
        ip_protocol = IPPROTO_IPV6;
#endif
        int sock =  socket(addr_family, SOCK_STREAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, PORT);

#if defined(CONFIG_EXAMPLE_SOCKET_REUSEADDR) || \
    defined(CONFIG_EXAMPLE_SOCKET_REUSEPORT) || \
    defined(CONFIG_EXAMPLE_SOCKET_SNDBUF) || \
    defined(CONFIG_EXAMPLE_SOCKET_RCVBUF)
        int optval = 1;
        socklen_t optlen = sizeof(int);

#if defined(CONFIG_EXAMPLE_SOCKET_REUSEADDR)
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, optlen)) {
            ESP_LOGE(TAG, "Socket unable to set SO_REUSEADDR: errno %d", errno);
            break;
        }

        if (getsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, &optlen)) {
            ESP_LOGE(TAG, "Socket unable to get SO_REUSEADDR: errno %d", errno);
            break;
        }
#endif

#if defined(CONFIG_EXAMPLE_SOCKET_REUSEPORT)
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &optval, optlen)) {
            ESP_LOGE(TAG, "Socket unable to set SO_REUSEPORT: errno %d", errno);
            break;
        }

        if (getsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &optval, &optlen)) {
            ESP_LOGE(TAG, "Socket unable to get SO_REUSEPORT: errno %d", errno);
            break;
        }
#endif

#if defined(CONFIG_EXAMPLE_SOCKET_SNDBUF)
        optval = 744;
        if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &optval, optlen)) {
            ESP_LOGE(TAG, "Socket unable to set SO_SNDBUF: errno %d", errno);
            break;
        }

        if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &optval, &optlen)) {
            ESP_LOGE(TAG, "Socket unable to get SO_SNDBUF: errno %d", errno);
            break;
        }
#endif

#if defined(CONFIG_EXAMPLE_SOCKET_RCVBUF)
        optval = 744;
        if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &optval, optlen)) {
            ESP_LOGE(TAG, "Socket unable to set SO_RCVBUF: errno %d", errno);
            break;
        }

        if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &optval, &optlen)) {
            ESP_LOGE(TAG, "Socket unable to get SO_RCVBUF: errno %d", errno);
            break;
        }
#endif

#endif

        int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in6));
        if (err != 0) {
            ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Successfully connected");

#if defined(CONFIG_EXAMPLE_SOCKET_SOCKNAME)
        struct sockaddr_in  local_addr;
        socklen_t           local_addr_size = sizeof(local_addr);
        if (getsockname(sock, (struct sockaddr *)&local_addr, &local_addr_size)) {
            ESP_LOGE(TAG, "Socket unable to get the local address: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Successfully getsockname %04x %d", local_addr.sin_addr.s_addr, local_addr.sin_port);
#endif

#if defined(CONFIG_EXAMPLE_SOCKET_PEERNAME)
        struct sockaddr_in  remote_addr;
        socklen_t           remote_addr_size = sizeof(remote_addr);
        if (getpeername(sock, (struct sockaddr *)&remote_addr, &remote_addr_size)) {
            ESP_LOGE(TAG, "Socket unable to get the remote address: errno %d", errno);
            break;
        }
        ESP_LOGI(TAG, "Successfully getpeername %04x %d", remote_addr.sin_addr.s_addr, remote_addr.sin_port);
#endif

        while (1) {
            int err = send(sock, payload, strlen(payload), 0);
            if (err < 0) {
                ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
                break;
            }

            int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
            // Error occurred during receiving
            if (len < 0) {
                ESP_LOGE(TAG, "recv failed: errno %d", errno);
                break;
            }
            // Data received
            else {
                rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
                ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
                ESP_LOGI(TAG, "%s", rx_buffer);
            }

        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }

    return NULL;
}

int
main(int argc, char *argv[])
{
    pthread_t t;
    int res;

    res = pthread_create(&t, NULL, tcp_client_task, NULL);
    assert(res == 0);

    res = pthread_join(t, NULL);
    assert(res == 0);

    return res;
}