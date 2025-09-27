#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8082
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // 1. Создаем сокет
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    // 2. Заполняем структуру server_address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Преобразуем IP-адрес сервера
    if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
        perror("Ошибка преобразования IP-адреса");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Подключаемся к серверу
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Ошибка подключения к серверу");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    printf("Подключено к серверу %s:%d\n", SERVER_IP, PORT);

    // 4. Обмен сообщениями с сервером
    while (1) {
        // Ввод сообщения пользователем
        printf("Введите сообщение для сервера (или 'exit' для выхода): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Удаляем символ новой строки
        buffer[strcspn(buffer, "\n")] = '\0';

        // Проверяем команду выхода
        if (strcmp(buffer, "exit") == 0) {
            printf("Отключение от сервера...\n");
            break;
        }

        // Отправляем сообщение серверу
        if (send(client_fd, buffer, strlen(buffer), 0) < 0) {
            perror("Ошибка отправки сообщения");
            break;
        }

        // Получаем ответ от сервера
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Сервер отключился.\n");
            break;
        }
        printf("Ответ от сервера: %s\n", buffer);
    }

    // 5. Закрываем сокет
    close(client_fd);

    return 0;
}
