#ifndef UTILITIES_H
#define UTILITIES_H

#define IPC_DELETE(p_object)  \
    {                                 \
        if(p_object == ZMQ_NULLPTR){  \
            return;                   \
        }                             \
        delete p_object;              \
        p_object = 0;                 \
    }

#ifndef NDEBUG
#define IPC_ASSERT(expression) assert(expression)
#endif
#endif // UTILITIES_H
