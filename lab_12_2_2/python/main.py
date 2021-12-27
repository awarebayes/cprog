import arr as arrlib

while True:
    print(
        "type 'exit' to exit\n"
        "type 'fib' to get first n fibonacci numbers\n"
        "type 'entries' to get indices of first entries of a number in an array\n"
    )
    inp = input("Choice: ")
    if inp == 'exit':
        break
    elif inp == 'fib':
        n = int(input("Input your n: "))
        if n <= 0:
            print("n should be positive")
            continue
        else:
            print(arrlib.fib_arr(n))
    elif inp == 'entries':
        inp = input("Enter your array split by spaces: ")
        arr = list(map(int, inp.split()))
        print(arrlib.entries(arr))
    else:
        continue
exit(0)
