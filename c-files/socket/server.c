#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8082
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[BUFFER_SIZE];
    int opt = 1;

    // 1. Создаем сокет
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }

    // 2. Настраиваем опции сокета
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("Ошибка настройки сокета");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Заполняем структуру server_address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // 4. Привязываем сокет к адресу
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Ошибка привязки сокета");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 5. Переводим сокет в режим прослушивания
    if (listen(server_fd, 10) < 0) {
        perror("Ошибка listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Сервер запущен. Ожидание подключений на порту %d...\n", PORT);

    // 6. Принимаем входящие подключения
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
        perror("Ошибка accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Новое соединение от клиента: %s:%d\n",
           inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // 7. Обрабатываем данные от клиента
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Клиент отключился.\n");
            break;
        }

        printf("Сообщение от клиента: %s\n", buffer);

        // Отправляем ответ клиенту
        char *response = "Сообщение получено\n";
        send(client_fd, response, strlen(response), 0);
    }

    // 8. Закрываем сокеты
    close(client_fd);
    close(server_fd);

    return 0;
}
