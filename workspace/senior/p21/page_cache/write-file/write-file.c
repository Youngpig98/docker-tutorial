#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE 1024  // 数据块的大小

int main() {
    FILE* file = fopen("/mnt/data.txt", "wb");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return 1;
    }

    char data[BLOCK_SIZE];  // 数据块

    sleep(60);

    memset(data, 0, BLOCK_SIZE);

    long long totalSize = 0;  // 累计写入的数据大小

    while (totalSize < 100 * 1024 * 1024) {
        size_t blockSize = sizeof(data);  // 数据块的大小

        size_t bytesWritten = fwrite(data, 1, blockSize, file);
        if (bytesWritten < blockSize) {
            printf("写入文件时发生错误。\n");
            break;
        }

        totalSize += bytesWritten;
    }

    fclose(file);

    sleep(1000000);

    return 0;
}

