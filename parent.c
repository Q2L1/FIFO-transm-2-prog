//Организовать передачу информации через FIFO от одного процесса другому (родственники). Каждый процесс запускает свою программу.
//Родительский процесс (parent.c):
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define FIFO_PATH "/tmp/info_fifo"
#define BUFFER_SIZE 100

int main(void) {
    char str[] = "Hello from parent process";
    int fd_write;

    // Создаем именованный канал (FIFO)
    mkfifo(FIFO_PATH, 0666);

    // Запускаем дочерний процесс
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid > 0) {
        // Родительский процесс

        // Открываем канал для записи
        fd_write = open(FIFO_PATH, O_WRONLY);
        if (fd_write == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Пишем данные в канал
        write(fd_write, str, sizeof(str));

        // Закрываем дескриптор записи
        close(fd_write);

        // Ждем завершения дочернего процесса
        wait(NULL);
    }
    else {
        // Дочерний процесс

        // Запускаем свою программу (например, с помощью exec)
        execlp("./child", "./child", NULL);
    }

    // Удаляем FIFO
    unlink(FIFO_PATH);

    return 0;
}
