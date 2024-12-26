#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define BUFFER_SIZE 256

HANDLE open_port(const char *device, unsigned long baud_rate, unsigned char bit_size, unsigned char parity)
{
    HANDLE port = CreateFileA(device, GENERIC_READ | GENERIC_WRITE, 0, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (port == INVALID_HANDLE_VALUE)
    {
        return INVALID_HANDLE_VALUE;
    }

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutConstant = 50;

    SetCommTimeouts(port, &timeouts);

    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    dcb.BaudRate = baud_rate;
    dcb.ByteSize = bit_size;
    dcb.Parity = parity;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(port, &dcb);

    return port;
}

int uart_transmit(HANDLE port, unsigned char *TX_buf, unsigned int TX_buf_len)
{
    DWORD writtenbytes;
    WriteFile(port, TX_buf, TX_buf_len, &writtenbytes, NULL);
    return writtenbytes == TX_buf_len ? 0 : -1;
}

int uart_receive(HANDLE port, unsigned char *RX_buf, unsigned int RX_buf_len)
{
    DWORD readbytes;
    ReadFile(port, RX_buf, RX_buf_len, &readbytes, NULL);
    return readbytes;
}

void display_menu()
{
    printf("\n");
    printf("=============================================\n");
    printf("              CHON LUA MOI                  \n");
    printf("=============================================\n");
    printf("1. Cai dat chu ky lay mau\n");
    printf("2. Cai dat chu ky quang cao cho BLE\n");
    printf("3. Lay thong tin nhiet do va do am\n");
    printf("0. Thoat\n");
    printf("=============================================\n");
    printf("Vui long chon lua chon cua ban: ");
}

int main()
{
    const char *device = "\\\\.\\COM18";
    unsigned long baud_rate = 115200;
    unsigned char bit_size = 8;
    unsigned char parity = 0;

    HANDLE port = open_port(device, baud_rate, bit_size, parity);
    if (port == INVALID_HANDLE_VALUE)
    {
        printf("Khong the mo cong\n");
        return -1;
    }

    char command[BUFFER_SIZE];
    char response[BUFFER_SIZE] = {0};
    int choice;

    do
    {
        system("cls");
        display_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            printf("Nhap gia tri chu ky lay mau: ");
            int sample_period;
            scanf("%d", &sample_period);
            getchar();

            sprintf(command, "1%d", sample_period);
            command[strcspn(command, "\n")] = 0;
            strcat(command, "\r");

            if (uart_transmit(port, (unsigned char *)command, strlen(command)) != 0)
            {
                printf("Gui that bai\n");
            }
            else
            {
                printf("Gui thanh cong: %s\n", command);
            }
            getch();
            break;
        }

        case 2:
        {
            printf("Nhap gia tri chu ky quang ba: ");
            int adv_period;
            scanf("%d", &adv_period);
            getchar();

            sprintf(command, "2%d", adv_period);
            command[strcspn(command, "\n")] = 0;
            strcat(command, "\r");

            if (uart_transmit(port, (unsigned char *)command, strlen(command)) != 0)
            {
                printf("Gui that bai\n");
            }
            else
            {
                printf("Gui thanh cong: %s\n", command);
            }
            getch();
            break;
        }

        case 3:
        {
            sprintf(command, "3");
            strcat(command, "\r");

            if (uart_transmit(port, (unsigned char *)command, strlen(command)) != 0)
            {
                printf("Gui that bai\n");
            }
            else
            {
                printf("Gui thanh cong: %s\n", command);
            }

            int bytes_read = uart_receive(port, (unsigned char *)response, BUFFER_SIZE - 1);
            if (bytes_read > 0)
            {
                response[bytes_read] = '\0';
                printf("Nhan duoc phan hoi:\n\n %s\n", response);
            }
            else
            {
                printf("Khong nhan duoc phan hoi.\n");
            }
            getch();
            break;
        }

        case 0:
            printf("Dang thoat chuong trinh...\n");
            break;

        default:
            printf("Lua chon khong hop le! Vui long chon lai.\n");
            getch();
        }
    } while (choice != 0);

    CloseHandle(port);
    return 0;
}
