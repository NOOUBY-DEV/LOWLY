#include "../LOWLY/tokenizer/tokenizer.h"
#include <stdio.h>

enum token_types
{
        EENIE,
        MEENIE,
        MINEY,
        MO,
        UNKOWN
};

typedef struct text_to_token_type
{
        char* text;
        ullong token_type;
}
text_to_token_type;


text_to_token_type text_to_token_type_list[] =
{
        {"eenie", EENIE},
        {"meenie", MEENIE},
        {"miney", MINEY},
        {"mo", MO},
        {NULL, UNKOWN}
};

typedef struct test_token
{
        char* position;
        ullong length;
        ullong type;
        ullong value;
        void* data;
}
test_token;


ullong chopper_callback(void* raw_token, char* string, ullong* string_index_ptr);


void print_token_types(test_token* tokens, const ullong token_count)
{
        printf("token count : %llu \n", token_count);

        for (ullong token_index = 0; token_index < token_count; token_index ++)
        {
                ullong type = tokens[token_index].type;

                printf("|%s| \n", text_to_token_type_list[type].text);
        }
}


int main()
{
        buffer_train token_train;

        init__token_train(&token_train, 3, sizeof(test_token));

        ullong token_count;

        char* text = "eenie  meenie miney mo  eenie miney mo meenie";

        tokenize__to__token_train(&token_train, text, chopper_callback, &token_count);

        test_token* final_tokens = finalize__token_train_to_array(&token_train);

        print_token_types(final_tokens, token_count);

        free_buffer_train(&token_train);
}

ullong chopper_callback(void* raw_token, char* string, ullong* string_index_ptr)
{
        test_token* token = raw_token;

        ullong string_index = *string_index_ptr;

        while (string[string_index] == ' ' || string[string_index] == '\t' || string[string_index] == '\n')
        {
                string_index++;
        }

        if (string[string_index] == '\0')
        {
                return 1;
        }

        for (ullong i = 0; text_to_token_type_list[i].text != NULL; i++)
        {
                text_to_token_type* candidate = &text_to_token_type_list[i];
                ullong match_len = 0;
                ullong matched = 1;

                while (candidate->text[match_len] != '\0')
                {
                        char a = string[string_index + match_len];
                        char b = candidate->text[match_len];

                        if (a != b)
                        {
                                matched = 0;
                                break;
                        }

                        match_len++;
                }

                        if (matched)
                        {
                                token->type = candidate->token_type;
                                token->length = match_len;

                                *string_index_ptr = string_index + match_len;

                                return 0;
                        }
        }

        return 1;
}
