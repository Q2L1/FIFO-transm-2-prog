//Дочерний процесс(child.c) :
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#define FIFO_PATH "/tmp/info_fifo"
#define BUFFER_SIZE 100

int main(void) {
    char str1[BUFFER_SIZE];
    int fd_read;

    // Открываем канал для чтения
    fd_read = open(FIFO_PATH, O_RDONLY);
    if (fd_read == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Читаем данные из канала
    ssize_t bytesRead = read(fd_read, str1, sizeof(str1));
    if (bytesRead == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // Закрываем дескриптор чтения
    close(fd_read);

    // Выводим прочитанные данные
    printf("Received message in child process: %.*s\n", (int)bytesRead, str1);

    return 0;
}
