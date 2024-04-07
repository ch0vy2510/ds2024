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

    char buffer[BUFFER_SIZE];
    FILE *received_file;

    if (rank == 0) {
        
        received_file = fopen("received_file.txt", "w");
        if (received_file == NULL) {
            perror("File open error");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }

        MPI_Status status;
        int bytes_received;

        
        while (1) {
            MPI_Recv(buffer, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_CHAR, &bytes_received);

            if (bytes_received <= 0) break;

            fwrite(buffer, 1, bytes_received, received_file);
        }

        fclose(received_file);
        printf("File received successfully.\n");
    } else {
        
    }

    MPI_Finalize();
    return 0;
}
