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
#define MAX_BACKLOG 5

void handle_client(int client_sock_fd)
{
    ssize_t recv_rc = -1;
    ssize_t send_rc = -1;
    const char CLOSE_WORD[] = "!quit";
    const size_t CLOSE_WORD_LEN = 5;
    int should_close = 0;
    int rc = -1;
    char *p_buffer = NULL;

    while (1) {
        // Reset buffer
        if (p_buffer)
            free(p_buffer);
        p_buffer = calloc(1, MAX_BUFFER_SIZE + 1);
        check_mem(p_buffer);

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
        if (should_close)
            break;

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

    rc = close(client_sock_fd);
    check(rc == 0, "Failed to close client socket.");

    printf("A client disconnected.\n");

// fallthrough
error:
    if (p_buffer)
        free(p_buffer);
}

int main(int argc, char *argv[])
{
    // Declare variables
    int server_sock_fd = -1;
    int client_sock_fd = -1;
    int rc = -1;
    int given_addr = -1;
    int given_port = -1;
    struct sockaddr_in addr;
    socklen_t addr_len = 0;
    pid_t fork_rc = -1;
    int should_reuse_addr = 1;

    // Exit early if incorrect CLI args given
    check(
        argc == 3,
        "USAGE: %s <IPv4 Address> <Port>",
        argv[0]
    );

    // Update some variables using the CLI args for the
    // IP Address and port
    given_addr = inet_addr(argv[1]);
    check(given_addr != -1, "Invalid IPv4 Address given.");

    given_port = atoi((const char *)argv[2]);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(given_port),
    addr.sin_addr.s_addr = given_addr;
    addr_len = (socklen_t)(sizeof(addr) + sizeof(struct in_addr));

    // Create a socket
    server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    check(server_sock_fd != -1, "Error creating socket.");

    // Set socket options to reuse abandoned IP addresses and ports
    rc = setsockopt(
        server_sock_fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &should_reuse_addr,
        sizeof(should_reuse_addr)
    );
    check(rc == 0, "Failed to set server socket options.");

    // Bind the socket
    rc = bind(server_sock_fd, (struct sockaddr *)&addr, addr_len);
    check(rc == 0, "Failed to bind socket.");

    printf(
        "> %s running at %s:%i\n",
        argv[0],
        argv[1],
        given_port
    );

    // Listen to connections on the socket
    rc = listen(server_sock_fd, MAX_BACKLOG);
    check(rc == 0, "Failed to listen on socket.");

    while (1) {
        // Accept connections to the socket
        client_sock_fd = accept(
            server_sock_fd,
            (struct sockaddr *)&addr,
            &addr_len
        );
        check(
            client_sock_fd > -1,
            "Failed to accept a connection to the server."
        );

        printf("A client connected.\n");

        fork_rc = fork();

        if (fork_rc == 0) {
            // Client process
            rc = close(server_sock_fd);
            check(rc == 0, "Failed to close server socket.");

            handle_client(client_sock_fd);
            exit(0);
        } else {
            // Server process
            rc = close(client_sock_fd);
            check(rc == 0, "Failed to close client socket.");
        }
    }

    // Clean up
    rc = close(server_sock_fd);
    check(rc == 0, "Failed to close server socket.");

    return 0;

error:
    if (fork_rc != 0) {
        // Server process
        printf("%s crashed due to an error.\n", argv[0]);
    }
    return -1;
}
