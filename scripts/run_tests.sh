for dir in $(ls | grep lab_03)
do
    echo "DIR: $dir:\n"
    bash ./scripts/run_test.sh $dir
done