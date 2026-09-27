#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>


ullong get_string_length(char* string)
{
        const char* moving_string = string;
        while (*moving_string++);
        return moving_string - string - 1;
}


ullong init__token_train(buffer_train* token_train, const ullong token_count, const ullong token_size)
{
        if (token_size == 0)
        {
                return LOWLY_ERROR;
        }

        if (init__buffer_train(token_train, token_count * token_size) == LOWLY_ERROR)
        {
                return LOWLY_ERROR;
        }

        token_train->unit_size = token_size;

        return LOWLY_OK;
}


ullong tokenize__to__token_train(buffer_train* token_train, char* string, ullong(*chopper_callback)(void*, char*, ullong*), ullong* token_count_ptr)
{
        if (token_train == NULL || string == NULL || token_count_ptr == NULL)
        {
                return LOWLY_ERROR;
        }

        const ullong token_size = token_train->unit_size;

        if (token_size == 0)
        {
                return LOWLY_ERROR;
        }

        if (token_train->car_buffer_size % token_size != 0)
        {
                return LOWLY_ERROR;
        }

        void* token = malloc(token_size);

        if (token == NULL)
        {
                return LOWLY_ERROR;
        }

        const ullong string_length = get_string_length(string);

        *token_count_ptr = 0;

        for (ullong string_index = 0; string_index < string_length;)
        {
                if (chopper_callback(token, string, &string_index) == 1)
                {
                        return LOWLY_ERROR;
                }

                if (buffer_train__append_buffer(token_train, token, token_size) == LOWLY_ERROR)
                {
                        return LOWLY_ERROR;
                }

                (*token_count_ptr) ++;
        }

        return LOWLY_OK;
}


void* finalize__token_train_to_array(buffer_train* token_train)
{
        if (token_train == NULL)
        {
                return NULL;
        }

        if (token_train->unit_size == 0)
        {
                return NULL;
        }

        if (token_train->car_buffer_size % token_train->unit_size != 0)
        {
                return NULL;
        }

        return finalize__buffer_train(token_train);
}
