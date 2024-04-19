#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <rpc/rpc.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    CLIENT *client;
    char *server;
    char *filename;
    FILE *file_to_send;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s hostname filename\n", argv[0]);
        exit(1);
    }

    server = argv[1];
    filename = argv[2];
    file_to_send = fopen(filename, "r");
    if (file_to_send == NULL) {
        perror("File open error");
        exit(1);
    }

    client = clnt_create(server, FILE_TRANSFER, FILE_TRANSFER_VERSION, "tcp");
    if (client == NULL) {
        clnt_pcreateerror(server);
        exit(1);
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file_to_send)) > 0) {
        opaque file_data;
        file_data.data_len = bytes_read;
        file_data.data_val = buffer;
        if (!transfer_file_1(&filename, &file_data, client)) {
            fprintf(stderr, "Error sending file.\n");
            exit(1);
        }
    }

    fclose(file_to_send);
    clnt_destroy(client);
    printf("File sent successfully.\n");

    return 0;
}
