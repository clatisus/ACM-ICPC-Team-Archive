g++ -std=c++14 data.cpp -o data.out
g++ -std=c++14 std.cpp -o std.out

while true; do
    ./data.out > data.txt
    ./std.out < data.txt > std.txt
    ./a.out < data.txt > a.txt
    if diff std.txt a.txt; then
        echo AC
    else
        echo WA
        exit 0
    fi
done
