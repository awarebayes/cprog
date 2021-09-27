#! /usr/bin/python
import os
import sys
from subprocess import Popen, PIPE
import shlex
import difflib as dl

os.chdir(sys.argv[1] + "/func_tests/")
files = os.listdir(os.getcwd())


def match_name(index, word):
    return lambda name: name.split("_")[index] == word


def fand(f1, f2):
    return lambda *args: f1(*args) and f2(*args)


is_in = match_name(-1, "in.txt")
is_arg = match_name(-1, "args.txt")
is_out = match_name(-1, "out.txt")
is_pos = match_name(0, "pos")
is_neg = match_name(0, "neg")
has_args = any(filter(is_arg, files))
def get_number(name): return name.split("_")[1]


def get_in_out_arg(pos_neg):
    def filt(ioa): return list(sorted(filter(fand(ioa, pos_neg), files)))
    ins, outs, args = map(filt, [is_in, is_out, is_arg])
    if not args:
        args = [None for _ in ins]
    return ins, outs, args


def read_file(relpath):
    with open(f"./{relpath}", "r") as f:
        s = f.read()
    return s


def write_to_file(relpath, s):
    with open(f"./{relpath}", "w") as f:
        f.write(s)


def check(ins, outs, args):

    for in_path, out_path, arg_path in zip(ins, outs, args):
        a = []
        if arg_path:
            a = read_file(arg_path)
            a = shlex.split(a)
        i = read_file(in_path)

        process = Popen(["valgrind", "--leak-check=yes",
                         "-q", "../app.exe", *a], stdout=PIPE)
        (output, err) = process.communicate(input=str.encode(i))
        exit_code = process.wait()
        output = output.decode()
        output = ''.join(list(filter(lambda x: x != "\r", output)))
        print(in_path)
        if output:
            print("Valgrind found an error!")
            print(in_path)
            print(output)
            print("--------")


def main():
    pos_in, pos_out, pos_arg = get_in_out_arg(is_pos)
    neg_in, neg_out, neg_arg = get_in_out_arg(is_neg)
    check(pos_in, pos_out, pos_arg)
    check(neg_in, neg_out, neg_arg)


if __name__ == "__main__":
    main()
