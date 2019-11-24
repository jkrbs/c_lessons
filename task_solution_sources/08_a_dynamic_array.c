#include <stdlib.h>
#include <string.h>

struct darray {
    int* buffer; // the dynamic buffer
    size_t element_count; // the current number of elements
    size_t capacity; // the amount of elements the buffer can hold
} darray;

int darray_init(struct darray* arr, size_t initial_capacity)
{
    arr->buffer = (int*)malloc(initial_capacity);
    arr->element_count = 0;
    arr->capacity = initial_capacity;
    if (!arr->buffer) return 1;
    return 0;
}
int darray_get(struct darray* arr, size_t index)
{
    return arr->buffer[index];
}
void darray_set(struct darray* arr, size_t index, int value)
{
    arr->buffer[index] = value;
}
int darray_append(struct darray* arr, int value)
{
    if (arr->element_count == arr->capacity) {
        arr->capacity *= 2;
        int* new_buffer = (int*)malloc(arr->capacity * sizeof(int));
        if (!new_buffer) return 1;
        memcpy(new_buffer, arr->buffer, arr->element_count * sizeof(int));
        free(arr->buffer);
        arr->buffer = new_buffer;
    }
    arr->buffer[arr->element_count] = value;
    arr->element_count++;
    return 0;
}
int darray_insert(struct darray* arr, size_t index, int value)
{
    if (arr->element_count == arr->capacity) {
        arr->capacity *= 2;
        int* new_buffer = (int*)malloc(arr->capacity * sizeof(int));
        if (!new_buffer) return 1;
        memcpy(new_buffer, arr->buffer, index * sizeof(int));
        new_buffer[index] = value;
        memcpy(
            new_buffer + index + 1, arr->buffer + index,
            (arr->element_count - index) * sizeof(int));
        free(arr->buffer);
        arr->buffer = new_buffer;
    }
    else {
        memmove(
            arr->buffer + index + 1, arr->buffer + index,
            (arr->element_count - index) * sizeof(int));
        arr->buffer[index] = value;
    }
    arr->element_count++;
    return 0;
}
void darray_erase(struct darray* arr, size_t index)
{
    memmove(
        arr->buffer + index, arr->buffer + index + 1,
        (arr->element_count - index) * sizeof(int));
    arr->element_count--;
}
void darray_fin(struct darray* arr)
{
    free(arr->buffer);
}
