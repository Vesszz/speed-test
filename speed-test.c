#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// created by zxcwn

#define TEXT "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum rhoncus."
#define TEXT_LEN strlen(TEXT)
#define RESET "\033[0m"
#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

#define BACKSPACE_ASCII_CODE 127
#define SPACE_ASCII_CODE 32
#define SPACE_SYMBOL '_'

unsigned long long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(){
	printf("%s%s%s\n", BLACK, TEXT, RESET);
	system("stty -icanon -echo");
	unsigned long long current_time_ms = get_current_time_ms();
	char inp_char;
	unsigned int success = 0;
	for (int i = 0; i < TEXT_LEN; ++i) {
		inp_char = getchar();
		if (inp_char == BACKSPACE_ASCII_CODE) {
			--i;
		}
		else if (inp_char == TEXT[i]) {
			if (inp_char == SPACE_ASCII_CODE) {
				printf("%s%c%s", GREEN, SPACE_SYMBOL, RESET);
			}
			else {
				printf("%s%c%s", GREEN, inp_char, RESET);
			}
			success++;
		}
		else {
			if (inp_char == SPACE_ASCII_CODE) {
				printf("%s%c%s", RED, SPACE_SYMBOL, RESET);
			}
			else {
				printf("%s%c%s", RED, inp_char, RESET);
			}
		}
	}
	unsigned long long time_after_sleep = get_current_time_ms();
	printf("\n%s%d%s/%s%lu\n%s", GREEN, success, BLACK, RED, TEXT_LEN - success, RESET);
	printf("%sLetters per minute: %f%s\n", BLACK, ((60.0 * success) / ((time_after_sleep - current_time_ms) / 1000.0)), RESET);
	printf("%sWords per minute: %f%s\n", BLACK, ((60.0 * success / 6.0) / ((time_after_sleep - current_time_ms) / 1000.0)), RESET);
	system("stty icanon echo");
}
