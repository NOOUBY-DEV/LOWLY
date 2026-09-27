#define buffer_trains
#ifdef buffer_trains



#include "../LOWLY.h"


typedef union pointers
{
        char* as_char;
        uchar* as_uchar;
        ullong* as_ullong;
        void* as_void;
}
pointers;

typedef struct buffer_car
{
        uchar* buffer;
        ullong free_index;
        ullong is_free;
        struct buffer_car* next;
        struct buffer_car* prev;
        void* data;
}
buffer_car;

typedef struct buffer_train
{
        buffer_car* head_car;
        buffer_car* current_car;
        ullong car_count;
        ullong car_buffer_size;
        ullong unit_size;
}
buffer_train;


void print_buffer_train(buffer_train* train);

ullong init__buffer_train(buffer_train* train, const ullong buffer_car_size);

ullong free__buffer_train(buffer_train* train);

ullong buffer_train__append_buffer(buffer_train* train, const void* append_buffer, const ullong append_size);

ullong buffer_train__add_car(buffer_train* train);

void* finalize__buffer_train(buffer_train* train);


#endif
