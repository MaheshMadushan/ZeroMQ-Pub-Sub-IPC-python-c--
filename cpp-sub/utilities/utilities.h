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

#define IPC_CREATE_NEW_OBJECT_OF(class, out) {                                     \
        try {                                                               \
            out = new class;                                                \
        } catch (std::bad_alloc & ba) {                                     \
            printf("new c1 failed: %s\n", ba.what());                       \
            return 1;                                                       \
        }                                                                   \
    }

#ifndef NDEBUG
#define IPC_ASSERT(expression) assert(expression)
#endif

#endif // UTILITIES_H
