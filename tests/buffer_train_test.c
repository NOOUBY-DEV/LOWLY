#include "../LOWLY/buffer_trains/buffer_trains.h"


#include <stdio.h>
#include <string.h>


int main()
{
        buffer_train test_train;

        init__buffer_train(&test_train, 64);

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
        ;

        ullong string_size = strlen(append_string) + 1;

        printf("string_size : %llu\n", string_size);

        buffer_train__append_buffer(&test_train, append_string, string_size);

        char* final_string = finalize__buffer_train(&test_train);

        printf("%s\n", final_string);

        free__buffer_train(&test_train);

        free(final_string);

        return 0;
}
