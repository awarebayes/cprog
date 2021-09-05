import os
from subprocess import Popen, PIPE
import shlex

files = os.listdir(os.getcwd())

def match_name(index, word):
    return lambda name: name.split("_")[index] == word

def fand(f1, f2):
    return lambda *args: f1(*args) and f2(*args)

is_in =  match_name(-1, "in.txt")
is_arg = match_name(-1, "arg.txt")
is_out = match_name(-1, "out.txt") 
is_pos = match_name(0, "pos")
is_neg = match_name(0, "neg")
has_args = any(filter(is_arg, files))

def get_in_out_arg(pos_neg):
    filt = lambda ioa:  list(sorted(filter(fand(ioa, pos_neg), files)))
    ins, outs, args = map(filt, [is_in, is_out, is_arg])
    if not args:
        args = [None for _ in ins]
    return ins, outs, args

def read_file(relpath):
    f = open(f"./{relpath}", "r")
    s = f.read()
    f.close()
    return s

def check(ins, outs, args):
    for in_path, out_path, arg_path in zip(ins, outs, args):
        a = []
        if a:
            a = read_file(arg_path)
            a = shlex.split(a)
        i = read_file(in_path)
        o = read_file(out_path)

        process = Popen(["../main", *a], stdout=PIPE)
        (output, err) = process.communicate(input=str.encode(i))
        exit_code = process.wait()
        print("test", pos_in)
        print(output, err, exit_code)

pos_in, pos_out, pos_arg = get_in_out_arg(is_pos)
neg_in, neg_out, neg_arg = get_in_out_arg(is_neg)
check(pos_in, pos_out, pos_arg)
