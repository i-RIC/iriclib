import os

def remove(fname):
    if not os.path.exists(fname):
        return
    os.remove(fname)

def verify_log(msg, result):
    ret_str = '[NG]'
    if result: 
        ret_str = '[OK]'

    print('{0} {1}'.format(msg, ret_str))
