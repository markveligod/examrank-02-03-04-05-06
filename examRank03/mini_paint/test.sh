gcc mini.c -o nooriginal -Wall -Wextra -Werror -lm
gcc mini.c -o original -Wall -Wextra -Werror -lm
echo ""
echo "TEST - <ex_1>"
echo "NO original"
./nooriginal ./test/ex_1
echo "Original"
./original ./test/ex_1
echo ""
echo "TEST - <ex_2>"
echo "NO original"
./nooriginal ./test/ex_2
echo "Original"
./original ./test/ex_2
echo ""
echo "TEST - <NULL>"
echo "NO original"
./nooriginal
echo "Original"
./original
echo ""
echo "TEST - <Error file>"
echo "NO original"
./nooriginal ./test/ex
echo "Original"
./original ./test/ex
rm nooriginal
rm original
