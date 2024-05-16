#include "felt_string.h"

size_t
felt_str_len(char* str) {
	size_t len = 0;
	for (size_t i = 0; str[i] != '\0'; i++) {
		len++;
	}
	return len;
}

char *
felt_str_dup(char* str) {
	size_t len = felt_str_len(str);
	char *new_str = felt_calloc(len + 1, sizeof(char));
	for (size_t i = 0; i < len; i++) {
		new_str[i] = str[i];
	}
	new_str[len] = '\0';
	return new_str;
}

char *
felt_str_chr(char *str, char chr, size_t len) {
	for (size_t i = 0; i < len; i++) {
		if (str[i] == chr) {
			return &str[i];
		}
	}
	return NULL;
}

char *
felt_find_str_in_str_arr(char **arr, char *str) {
	for (size_t i = 0; arr[i] != NULL; i++) {
		if (felt_str_same(arr[i], str)) {
			return arr[i];
		}
	}
	return NULL;
}

bool
felt_is_substr_at_addr(char* addr, char* substr) {
	for (size_t i = 0; i < felt_str_len(substr); i++) {
		if (substr[i] != addr[i]) {
			return false;
		}
	}
	return true;
}

bool
felt_str_same(char *str, char *cmp) {
	if (!str || !cmp)
		return false;
	if (str[0] != cmp[0])
		return false;
	for (size_t i = 1; str[i - 1] != '\0'; i++) {
		if(str[i] != cmp[i])
			return false;
	}
	return true;
}

char *
felt_new_str_stdin(void) {
	const size_t buff_len = 256;
	char *input = felt_calloc(buff_len, sizeof(char));
	char *end = NULL;
	while (!(end = felt_str_chr(input, '\n', buff_len))) {
		input = fgets(input, buff_len, stdin);
	}
	*end = '\0';
	return input;
}

char **
felt_new_str_arr_split(char *str, char *delim) {
	size_t num_toks = 1;
	for (size_t i = 0; i < felt_str_len(str); i++) {
		if (felt_is_substr_at_addr(&str[i], delim)) {
			num_toks++;
			i += felt_str_len(delim) - 1;
		}
	}
	char **output = felt_calloc(num_toks + 1, sizeof(char *));
	output[num_toks] = NULL;

	char* start = str;
	char* end = str;
	for (size_t i = 0; i < num_toks; i++) {
		while (!felt_is_substr_at_addr(end, delim) && *end != '\0') {
			end++;
		}
		size_t tok_len = (size_t)(end - start);
		output[i] = felt_calloc(tok_len + 1, sizeof(char));
		for (size_t j = 0; j < tok_len; j++) {
			output[i][j] = *start;
			start++;
		}
		output[i][tok_len] = '\0';
		start = end + felt_str_len(delim);
		end = start;
	}

	return output;
}

void
felt_free_split_str(char **split_str) {
	for (size_t i = 0; split_str[i] != NULL; i++) {
		free(split_str[i]);
	}
	free(split_str);
	return;
}