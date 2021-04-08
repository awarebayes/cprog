cd $1
mkdir func_tests
cd func_tests

touch readme.md

for i in $(seq 1 $2)
do
    if ! [ -f "pos_$(printf "%02d" "$i")_in.txt" ]
    then
        touch "pos_$(printf "%02d" "$i")_in.txt"
    fi
    if ! [ -f "pos_$(printf "%02d" "$i")_out.txt" ]
    then

        touch "pos_$(printf "%02d" "$i")_out.txt"
    fi
done;

for i in $(seq 1 $3)
do
    if ! [ -f "neg_$(printf "%02d" "$i")_in.txt" ]
    then
        touch "neg_$(printf "%02d" "$i")_in.txt"
    fi
    if ! [ -f  "neg_$(printf "%02d" "$i")_out.txt" ]
    then
        touch "neg_$(printf "%02d" "$i")_out.txt"
    fi
done;
