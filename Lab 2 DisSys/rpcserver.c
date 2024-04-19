#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <rpc/rpc.h>

#define BUFFER_SIZE 1024

bool_t transfer_file_svc(string *filename, opaque *file_data, struct svc_req *rqstp) {
    FILE *received_file = fopen(*filename, "w");
    if (received_file == NULL) {
        perror("File open error");
        return FALSE;
    }

    fwrite(file_data->data_val, 1, file_data->data_len, received_file);
    fclose(received_file);
    return TRUE;
}
