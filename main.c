#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include "server.h"

int fLen(char data[]) {
    int len = 0;
    for (int i = 0; data[i] != NULL; ++i) {
        len++;
    }
    return len;
}

int numberOfDigits(int number) {
    int result = 1;
    for (int i = number; number > 9; number /= 10) {
        result++;
    }
    return result;
}

void fFetchAll(int client_socket) {

    int len, j, k = 0, numberOfDataLines = 0;
    char msg[5000] = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\nContent-Type: text/html\nContent-Length: ";
    char data[5000]={0}, newData[5000]={0}, ch, numberToChar[4]={0};
    len = fLen(msg);

    FILE *file;
    file = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\add.csv", "r");
    for (int j = 0; (ch = fgetc(file)) != EOF; j++) {
        data[j] = ch;
    }
    fclose(file);

    for (int i = 0; data[i] != NULL; ++i) {
        if (data[i] == 10) {
            numberOfDataLines++;
        }
    }

    if (fLen(data) == 1)
        numberOfDataLines = 0;

    int i, lenData;
    lenData = fLen(data);
    if (numberOfDataLines != 0)
        newData[0] = '[';
    i = 1;

    for (int l = 0; l < numberOfDataLines; l++) {
        newData[i] = '[';
        newData[i + 1] = '"';
        newData[i + 2] = data[k];
        newData[i + 3] = data[k + 1];
        newData[i + 4] = data[k + 2];
        newData[i + 5] = '"';
        newData[i + 6] = ',';
        newData[i + 7] = '"';
        newData[i + 8] = data[k + 4];
        newData[i + 9] = '"';
        newData[i + 10] = ',';
        newData[i + 11] = '"';
        newData[i + 12] = data[k + 6];
        newData[i + 13] = data[k + 7];
        newData[i + 14] = data[k + 8];
        newData[i + 15] = data[k + 9];
        newData[i + 16] = data[k + 10];
        newData[i + 17] = data[k + 11];
        newData[i + 18] = data[k + 12];
        newData[i + 19] = data[k + 13];
        newData[i + 20] = '"';
        newData[i + 21] = ',';
        newData[i + 22] = '"';
        newData[i + 23] = data[k + 15];
        newData[i + 24] = '"';
        newData[i + 25] = ',';
        newData[i + 26] = '"';
        for (j = 0; data[k + j + 17] != 10; ++j) {
            newData[i + 27 + j] = data[k + j + 17];
        }
        newData[i + 27 + j] = '"';
        newData[i + 28 + j] = ']';
        newData[i + 29 + j] = ',';
        if (data[k + j + 18] == EOF && data[k + j + 17] == EOF && data[k + j + 19] == EOF && data[k + j + 16] == EOF &&
            data[k + j + 20] == EOF)
            break;
        i += 30 + j;
        k += 18 + j;
        if (lenData + 17 > !i)
            lenData += 17;
    }
    newData[i - 1] = ']';
    newData[i] = '\0';


    int leanTest = fLen(newData);
    for (int i = numberOfDigits(fLen(newData)) - 1; 0 <= i; i--) {
        numberToChar[i] = leanTest % 10 + '0';
        leanTest /= 10;
    }
    if (numberOfDataLines == 0)
        numberToChar[0] = '0';
    strcat(msg, numberToChar);
    msg[len + numberOfDigits(fLen(newData))] = 10;
    msg[len + numberOfDigits(fLen(newData)) + 1] = 10;
    if (numberOfDataLines != 0)
        strcat(msg, newData);
    respond(client_socket, msg);

    puts(msg);
}


void fAdd(char buffer[], int client_socket) {
    char oldData[512] = {0}, data[512] = {0}, newData[512] = {0};
    int counter = 0, i = 0, j = 0;
    char ch = NULL;

    FILE *oldFile;
    oldFile = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\add.csv", "r");
    for (j = 0; (ch = fgetc(oldFile)) != EOF; j++) {
        oldData[j] = ch;
    }
    fclose(oldFile);

    strcpy(newData, oldData);
    int end = fLen(oldData) + 1;
    newData[end] = NULL;

    counter = i;
    data[0] = buffer[21];
    data[1] = buffer[22];
    data[2] = buffer[23];
    data[3] = ',';
    data[4] = buffer[36];
    data[5] = ',';
    data[6] = buffer[43];
    data[7] = buffer[44];
    data[8] = buffer[45];
    data[9] = buffer[46];
    data[10] = buffer[47];
    data[11] = buffer[48];
    data[12] = buffer[49];
    data[13] = buffer[50];
    data[14] = ',';
    data[15] = '0';
    data[16] = ',';

    counter += 17;
    int counterOfDiscription = 1;
    for (j = 64; counterOfDiscription == 1; ++j) {
        if (buffer[j + 1] == ' ' && buffer[j + 2] == 'H' && buffer[j + 3] == 'T' && buffer[j + 4] == 'T' &&
            buffer[j + 5] == 'P')
            counterOfDiscription = 0;
        data[i + 17] = buffer[i + 64];
        i++;
    }
    data[i + 17] = 10;
    data[i + 18] = NULL;

    strcat(newData, data);

    FILE *newFile;
    newFile = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\add.csv", "w");
    fputs(newData, newFile);
    fclose(newFile);
    char msg[1024] = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\nContent-Type: text/html\nContent-Length: 13\n\nrecord added!";
    puts(msg);
    respond(client_socket, msg);
}

void fDelete(char buffer[], int client_socket) {
    int i = 0, j = 0, k = 0, len;
    char id[4]={0}, data[1024]={0}, newData[1024]={0}, ch;

    id[0] = buffer[24];
    id[1] = buffer[25];
    id[2] = buffer[26];
    id[3] = '\0';
    FILE *oldFile;
    oldFile = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\add.csv", "r");
    for (i = 0; (ch = fgetc(oldFile)) != EOF; i++) {
        data[i] = ch;
    }
    fclose(oldFile);
    len = fLen(data);

    for (i = 0; i < len; ++i) {
        if (id[0] == data[i] && id[1] == data[i + 1] && id[2] == data[i + 2]) {
            for (j = 0; j < i; j++) {
                newData[j] = data[j];
            }
            k = j;
            j++;

            while (data[j] != 10 && j != len)
                j++;
            j++;
            if (j == len || j == len - 1 || j == len + 1)
                break;

            while (j < len) {
                newData[k] = data[j];
                j++;
                k++;

            }

            newData[k - 1] = 10;
            newData[k] = NULL;
        }
    }

    FILE *newFile;
    newFile = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\add.csv", "w");
    fputs(newData, newFile);
    fclose(newFile);
    char msg[1024] = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\nContent-Type: text/html\nContent-Length: 15\n\nrecord deleted!";
    puts(msg);
    respond(client_socket, msg);
}

void fEdit(char buffer[], int client_socket) {
    int i = 0, id[3]={0}, len;
    char ch, data[256]={0};

    FILE *oldFile;
    oldFile = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\add.csv", "r");
    for (i = 0; (ch = fgetc(oldFile)) != EOF; i++) {
        data[i] = ch;
    }
    fclose(oldFile);
    len = i;

    id[0] = buffer[22];
    id[1] = buffer[23];
    id[2] = buffer[24];

    for (i = 0; i < len; i++) {
        if (id[0] == data[i] && id[1] == data[i + 1] && id[2] == data[i + 2]) {
            data[i + 15] = buffer[40];
        }
    }
    FILE *newFile;
    newFile = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\add.csv", "w");
    fputs(data, newFile);
    fclose(newFile);

    char msg[1024] = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\nContent-Type: text/html\nContent-Length: 14\n\nrecord edited!";
    puts(msg);
    respond(client_socket, msg);
}

void mainPage(int client_socket) {
    char *frontHtml;
    frontHtml = malloc(12624 * sizeof(char));
    FILE *file;
    file = fopen("C:\\Users\\lotfian.a\\CLionProjects\\untitled4\\front.html", "r");
    char ch;
    for (int i = 0; (ch = fgetc(file)) != EOF; i++) {
        frontHtml[i] = ch;
    }
    fclose(file);
    char msg[50000] = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\nContent-Type: text/html\nContent-Lengh: ";
    msg[86] = fLen(frontHtml);
    msg[87] = 10;
    msg[88] = 10;
    strcpy(msg + 89, frontHtml);
    respond(client_socket, msg);

}

void command(char buffer[], int client_socket) {
    if (buffer[5] == ' ')
        mainPage(client_socket);
    if (buffer[14] == 'f')
        fFetchAll(client_socket);
    if (buffer[14] == 'a')
        fAdd(buffer, client_socket);
    if (buffer[14] == 'd')
        fDelete(buffer, client_socket);
    if (buffer[14] == 'e')
        fEdit(buffer, client_socket);
}

int main(int argc, char const *argv[]) {

#if defined(_WIN32) || defined(_WIN64)
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("\nError: This shity windows socket subsytsem could not be initialized. Error Code: %d. Exiting..\n",
               WSAGetLastError());
        exit(1);
    }
#endif

    int sockid, client_socket;
    struct sockaddr_in address;
    int address_size = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_port = htons(16985);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    char buffer[1024] = {0};

    sockid = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (bind(sockid, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockid, 3) == -1) {
        perror("listening error");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((client_socket = accept(sockid, (struct sockaddr *) &address, &address_size)) == -1) {
            perror("accepting new socket failed");
            exit(EXIT_FAILURE);
        }
        recv(client_socket, buffer, 1023, 0);
        puts(buffer);

        command(buffer, client_socket);

    }
    return 0;
}