#! /usr/bin/python
import os
import sys
from subprocess import Popen, PIPE
import shlex

output_from_temp_txt = True

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
get_number = lambda name: name.split("_")[1]


def get_in_out_arg(pos_neg):
    filt = lambda ioa: list(sorted(filter(fand(ioa, pos_neg), files)))
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


def check(ins, outs, args, pos=True):

    fail_count = 0

    for in_path, out_path, arg_path in zip(ins, outs, args):
        failed = False
        
        a = []
        if arg_path:
            a = read_file(arg_path)
            a = shlex.split(a)
        i = read_file(in_path)
        o = read_file(out_path)

        process = Popen(["../app.exe", *a], stdout=PIPE)
        (output, _) = process.communicate(input=str.encode(i))
        exit_code = process.wait()
        output = output.decode()
        if output_from_temp_txt:
            output = read_file("./temp.txt")
        
        output = ''.join(list(filter(lambda x: x != "\r", output)))
        o = ''.join(list(filter(lambda x: x != "\r", o)))

        if pos and exit_code != 0:
            failed = True
        if not pos and exit_code == 0:
            failed = True
        if output != o:
            failed = True
        
        fail_count += failed
    
    return fail_count


def main():
    pos_in, pos_out, pos_arg = get_in_out_arg(is_pos)
    neg_in, neg_out, neg_arg = get_in_out_arg(is_neg)
    fails = 0
    fails += check(pos_in, pos_out, pos_arg)
    fails += check(neg_in, neg_out, neg_arg, False)
    print("Tests", "passed" if not fails else "failed")
    if fails:
        print("#failed:", fails)
    exit(fails)


if __name__ == "__main__":
    main()
