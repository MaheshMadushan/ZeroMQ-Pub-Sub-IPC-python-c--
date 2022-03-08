# Python and C++ IPC with pub-sub model
ZeroMQ IPC with publisher subcriber model to communicate between two applications written in python and c++

```seq

C++/Python \nSubcriber \nprocess->>Python \nPublish \nProcess: Publish
Python \nPublish \nProcess->>C++/Python \nSubcriber \nprocess: Subcribes

```