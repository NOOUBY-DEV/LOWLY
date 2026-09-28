#include "../LOWLY/buffer_trains/buffer_trains.h"
#include <stdio.h>
#include <string.h>


const char* append_string =
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
        "HELLO WORLD I AM VERITY SON IM CRINE |\n"
;


int main()
{
        const ullong string_size = strlen(append_string) + 1;

        buffer_train test_train;

        init__buffer_train(&test_train, 64);

        buffer_train__append_buffer(&test_train, append_string, string_size);

        char* final_string = finalize__buffer_train(&test_train);

        // [print]
        {
                printf("%s\n", final_string);

                printf("final_string size : %lu\n", strlen(final_string) + 1);
        }

        free__buffer_train(&test_train);

        free(final_string);

        return 0;
}
