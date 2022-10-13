#include <message_f.hpp>


// free function - shouldn't be a member function - read https://stackoverflow.com/questions/2298242/callback-functions-in-c
void free_data_buffer_fn(void *data, void *hint)
{
    IPC_ASSERT(data == NULL);
    IPC_DELETE(data);
}

message_f::message_f(void *data)
{
    IPC_ASSERT(data != NULL);
    this->message = new zmq::message_t(data,sizeof(data),free_data_buffer_fn,ZMQ_NULLPTR);
}

message_f::~message_f()
{
    IPC_DELETE(this->message);
}

