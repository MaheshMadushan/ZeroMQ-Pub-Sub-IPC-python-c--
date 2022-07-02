#ifndef UTILITIES_H
#define UTILITIES_H

#define IPCPYCPPZMQ_DELETE(p_object)  \
    {                                 \
        if(p_object == ZMQ_NULLPTR){  \
            return;                   \
        }                             \
        delete p_object;              \
        p_object = 0;                 \
    }

#endif // UTILITIES_H
