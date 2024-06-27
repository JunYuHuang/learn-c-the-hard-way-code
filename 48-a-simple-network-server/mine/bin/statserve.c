#include <stdlib.h>
#include <sys/select.h>
#include <stdio.h>
#include <dbg.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    // Declare variables
    int server_sock_fd = -1;
    int client_sock_fd = -1;
    int rc = -1;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(7899),
        .sin_addr.s_addr = htonl(INADDR_LOOPBACK)
    };
    socklen_t addr_len = (socklen_t)sizeof(struct sockaddr_in);
    char *p_buffer = NULL;
    ssize_t recv_rc = -1;
    ssize_t send_rc = -1;
    const char CLOSE_WORD[] = "!quit";
    const size_t CLOSE_WORD_LEN = 5;
    int should_close = 0;

    // Create a socket
    server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(server_sock_fd != -1, "Error creating socket.");

    // Bind the socket
    rc = bind(server_sock_fd, (struct sockaddr *)&addr, addr_len);
    check(rc == 0, "Failed to bind socket.");

    // Listen to connections on the socket
    rc = listen(server_sock_fd, 5);
    check(rc == 0, "Failed to listen on socket.");

    // Accept connections to the socket
    client_sock_fd = accept(
        server_sock_fd,
        (struct sockaddr *)&addr,
        &addr_len
    );
    check(
        client_sock_fd > -1,
        "Failed to accept connections on socket."
    );

    while (1) {
        // Reset the buffer
        if (p_buffer)
            free(p_buffer);
        p_buffer = calloc(1, MAX_BUFFER_SIZE + 1);

        // Receive sent msg from client socket
        recv_rc = recv(
            client_sock_fd,
            (void *)p_buffer,
            (size_t)MAX_BUFFER_SIZE,
            0
        );
        check(
            recv_rc != -1, "Failed to receive client socket message."
        );

        // Close the connection on a keyword
        should_close = strncmp(
            (const char *)p_buffer,
            (const char *)&CLOSE_WORD,
            CLOSE_WORD_LEN
        ) == 0 ? 1 : 0;
        if (should_close) break;

        // Send client-sent msg back to client socket
        send_rc = send(
            client_sock_fd,
            (void *)p_buffer,
            strnlen((const char *)p_buffer, (size_t)MAX_BUFFER_SIZE),
            0
        );
        check(
            send_rc != -1, "Failed to send message to client socket."
        );
    }

    // Clean up
    if (p_buffer)
        free(p_buffer);

    rc = close(server_sock_fd);
    check(rc == 0, "Failed to close server socket.");

    rc = close(client_sock_fd);
    check(rc == 0, "Failed to close client socket.");

    printf("statserve ran OK.\n");

    return 0;

error:
    if (p_buffer)
        free(p_buffer);
    return -1;
}
