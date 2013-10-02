#include <stdio.h>
#include "CirculerBuffer.h"

int buffer[100];

int main(void)
{
    char buf[80];
    int command;
    int input_num;
    int output_num;

    CirculerBuffer_create(buffer, 30);

    while(1) {
        printf("Please input command > ");
        fflush(stdout);
        fgets(buf, sizeof(buf), stdin);
        sscanf(buf, "%d", &command);
        if (command == 0) {
            printf("Please input data > ");
            fflush(stdout);
            fgets(buf, sizeof(buf), stdin);
            sscanf(buf, "%d", &input_num);

            CirculerBuffer_put(input_num);
        } else {
            output_num = CirculerBuffer_get();

            printf(" data = %d\n", output_num);
        }
    }

	return 0;
}
    

