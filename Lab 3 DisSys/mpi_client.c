#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        fprintf(stderr, "This program requires exactly 2 processes.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    if (rank == 0) {
        
        char buffer[BUFFER_SIZE];
        FILE *file_to_send = fopen("file_to_send.txt", "r");
        if (file_to_send == NULL) {
            perror("File open error");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        int bytes_read;
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file_to_send)) > 0) {
            MPI_Send(buffer, bytes_read, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        }

        fclose(file_to_send);
        printf("File sent successfully.\n");
    } else {
        
    }

    MPI_Finalize();
    return 0;
}
