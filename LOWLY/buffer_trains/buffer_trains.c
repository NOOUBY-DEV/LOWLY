#include "buffer_trains.h"
#include <stdlib.h>


#define CAST_TO_UCHAR(POINTER) ((uchar*)POINTER)


ullong init__buffer_train(buffer_train* train, const ullong buffer_car_size)
{
        if (train == NULL)
        {
                return LOWLY_ERROR;
        }

        if (buffer_car_size == 0)
        {
                return LOWLY_ERROR;
        }

        train->car_buffer_size = buffer_car_size;

        // [create head car and link]
        {
                buffer_car* head_car = malloc(sizeof(buffer_car));

                if (head_car == NULL)
                {
                        return LOWLY_ERROR;
                }

                head_car->buffer = malloc(buffer_car_size);

                if (head_car->buffer == NULL)
                {
                        return LOWLY_ERROR;
                }

                head_car->prev = NULL;
                head_car->next = NULL;
                head_car->is_free = TRUE;
                head_car->free_index = 0;

                train->head_car = head_car;
                train->current_car = head_car;
                train->car_count = 1;
        }

        return LOWLY_OK;
}


ullong free__buffer_train(buffer_train* train)
{
        if (train == NULL)
        {
                return LOWLY_ERROR;
        }

        buffer_car* current_car = train->head_car;

        while (current_car)
        {
                buffer_car* next_car = current_car->next;

                free(current_car->buffer);
                free(current_car);

                current_car = next_car;
        }

        return LOWLY_OK;
}


ullong buffer_train__add_car(buffer_train* train)
{
        train->current_car->is_free = FALSE;

        // [create new car]
        {
                buffer_car* new_car = malloc(sizeof(buffer_car));

                if (new_car == NULL)
                {
                        return LOWLY_ERROR;
                }

                new_car->buffer = malloc(train->car_buffer_size);

                if (new_car->buffer == NULL)
                {
                        return LOWLY_ERROR;
                }

                new_car->is_free = TRUE;
                new_car->free_index = 0;
                new_car->prev = train->current_car;
                new_car->next = NULL;

                train->current_car->next = new_car;
                train->current_car = new_car;
                train->car_count ++;
        }

        return LOWLY_OK;
}


ullong buffer_train__append_buffer(buffer_train* train, const void* append_buffer, const ullong append_size)
{
        if (append_buffer == NULL || append_size == 0)
        {
                return LOWLY_ERROR;
        }

        for (ullong buffer_index = 0; buffer_index < append_size; buffer_index ++)
        {
                if (train->current_car->free_index >= train->car_buffer_size)
                {
                        if (buffer_train__add_car(train) == LOWLY_ERROR)
                        {
                                return LOWLY_ERROR;
                        }
                }

                buffer_car* current_car = train->current_car;

                current_car->buffer[current_car->free_index] = CAST_TO_UCHAR(append_buffer)[buffer_index];

                current_car->free_index ++;
        }

        return LOWLY_OK;
}


void* finalize__buffer_train(buffer_train* train)
{
        if (train == NULL)
        {
                return NULL;
        }

        if (train->car_count == 0 || train->car_buffer_size == 0)
        {
                return NULL;
        }

        uchar* buffer;

        // [allocate final buffer and set]
        {
                const ullong total_length = (train->car_count - 1) * train->car_buffer_size + train->current_car->free_index;

                buffer = malloc(total_length);

                if (buffer == NULL)
                {
                        return NULL;
                }
        }

        buffer_car* current_car = train->head_car;

        for (ullong buffer_index = 0; current_car; )
        {
                for (ullong car_buffer_index = 0; car_buffer_index < current_car->free_index; car_buffer_index ++, buffer_index ++)
                {
                        buffer[buffer_index] = current_car->buffer[car_buffer_index];
                }

                current_car = current_car->next;
        }

        return buffer;
}


void print_buffer_train(buffer_train* train)
{
        buffer_car* current_car = train->head_car;

        while (current_car)
        {
                for (ullong buffer_index = 0; buffer_index < train->car_buffer_size; buffer_index ++)
                {
                        printf("%c", current_car->buffer[buffer_index]);
                }

                current_car = current_car->next;

                printf("\n-------------\n[SWITCH CAR!]\n-------------\n");
        }
}
