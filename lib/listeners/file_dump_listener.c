#include "hawktracer/listeners/file_dump_listener.h"

#include "internal/mutex.h"

inline static void
_ht_file_dump_listener_flush(void* listener)
{
    HT_FileDumpListener* fd_listener = (HT_FileDumpListener*) listener;

    fwrite(fd_listener->buffer.data, sizeof(HT_Byte), fd_listener->buffer.usage, fd_listener->p_file);
    fd_listener->buffer.usage = 0;
}

HT_Boolean
ht_file_dump_listener_init(HT_FileDumpListener* listener, const char* filename, size_t buffer_size)
{
    listener->p_file = fopen(filename, "wb");
    if (listener->p_file == NULL)
    {
        return HT_FALSE;
    }

    listener->mtx = ht_mutex_create();

    ht_listener_buffer_init(&listener->buffer, buffer_size);

    return HT_TRUE;
}

void
ht_file_dump_listener_deinit(HT_FileDumpListener* listener)
{
    if (listener->p_file != NULL)
    {
        ht_mutex_lock(listener->mtx);
        _ht_file_dump_listener_flush(listener);
        ht_listener_buffer_deinit(&listener->buffer);
        fclose(listener->p_file);
        listener->p_file = NULL;
        ht_mutex_unlock(listener->mtx);
        ht_mutex_destroy(listener->mtx);
    }
}

void
ht_file_dump_listener_callback(TEventPtr events, size_t size, HT_Boolean serialized, void* user_data)
{
    HT_FileDumpListener* listener = (HT_FileDumpListener*)user_data;

    ht_mutex_lock(listener->mtx);

    if (serialized)
    {
        ht_listener_buffer_process_serialized_events(&listener->buffer, events, size, _ht_file_dump_listener_flush, listener);
    }
    else
    {
        ht_listener_buffer_process_unserialized_events(&listener->buffer, events, size, _ht_file_dump_listener_flush, listener);
    }

    ht_mutex_unlock(listener->mtx);
}
