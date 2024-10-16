#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// created by zxcwn

char *keywords[32] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

#define TEXT_LEN 1
#define TEXT "123"
#define RESET "\033[0m"
#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

#define BACKSPACE_ASCII_CODE 127
#define SPACE_ASCII_CODE 32
#define SPACE_SYMBOL '_'
#define SPACE ' '

unsigned long long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(){
	int words_quanitity;
	printf("%sEnter the quanitity: %s", BLACK, RESET);
	scanf("%d", &words_quanitity);
	char string_words[words_quanitity*8];
	srand(get_current_time_ms());
	for (int word_number = 0; word_number < words_quanitity; ++word_number) {
		int random_word_number = abs(rand()) % 32;
		strcat(string_words, keywords[random_word_number]);
		strcat(string_words, " ");
	}
	string_words[(signed int)strlen(string_words) - 1] = '\0';
	printf("%s%s%s", BLACK, string_words, RESET);
	system("stty -icanon -echo");
	unsigned long long current_time_ms = get_current_time_ms();
	char inp_char;
	unsigned int success = 0;
	for (int i = -1; i < (signed int)strlen(string_words); ++i) {
		inp_char = getchar();
		if (inp_char == BACKSPACE_ASCII_CODE) {
			--i;
		}
		else if (inp_char == string_words[i]) {
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
	printf("\n%s%d%s/%s%lu\n%s", GREEN, success, BLACK, RED, (signed int)strlen(string_words) - success, RESET);
	printf("%sLetters per minute: %f%s\n", BLACK, ((60.0 * success) / ((time_after_sleep - current_time_ms) / 1000.0)), RESET);
	printf("%sWords per minute: %f%s\n", BLACK, ((60.0 * success / 6.0) / ((time_after_sleep - current_time_ms) / 1000.0)), RESET);
	system("stty icanon echo");
}
