from __future__ import print_function
from string import ascii_uppercase as uppercase
import time

from random import randint
from threading import Thread

import zmq
from dump_msg import dump

from random import randint

def main ():

    ctx = zmq.Context.instance()

    # Subscribe to topic "A"
    subscriber = ctx.socket(zmq.SUB)
    subscriber.connect("tcp://localhost:6001")
    subscriber.setsockopt(zmq.SUBSCRIBE, b"A")

    count = 0

    while True:
        try:
            msg = subscriber.recv_multipart()
            dump(msg)
        except zmq.ZMQError or KeyboardInterrupt as e:
            ctx.term()
            if e.errno == zmq.ETERM:
                break           # Interrupted
            else:
                raise
        count += 1


if __name__ == '__main__':
    main()