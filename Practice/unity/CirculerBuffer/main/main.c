#include <stdio.h>
#include "CirculerBuffer.h"

int buffer[100];

void get_number(const char *mess, int *num);

int main(void)
{
    char buf[80];
    int command;
    int input_num;
    int output_num;

    CirculerBuffer_create(buffer, 30);

    while(1) {
        get_number("Please input command > ", &command);
        if (command == 0) {
            get_number("Please input data > ", &input_num);

            CirculerBuffer_put(input_num);
        } else {
            output_num = CirculerBuffer_get();

            printf(" data = %d\n", output_num);
        }
    }

	return 0;
}
    
void get_number(const char *mess, int *num)
{
    char buf[80];

    printf(mess);
    fflush(stdout);
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", num);
}
