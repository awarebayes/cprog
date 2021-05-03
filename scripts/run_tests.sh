for dir in $(ls | grep lab_04)
do
    echo "DIR: $dir:\n"
    bash ./scripts/run_test.sh $dir
done