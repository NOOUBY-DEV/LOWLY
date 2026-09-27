#define tokenizer
#ifdef tokenizer


#include "../buffer_trains/buffer_trains.h"


ullong get_string_length(char* string);

ullong init__token_train(buffer_train* token_train, ullong token_count, ullong token_size);

ullong tokenize__to__token_train(buffer_train* token_train, char* string, ullong(*chopper_callback)(void*, char*, ullong*), ullong* token_count_ptr);

void* finalize__token_train_to_array(buffer_train* token_train);


#endif
