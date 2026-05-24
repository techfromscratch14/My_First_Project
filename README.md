# My_First_Project
This project covers the Microcontroller project from scratch

cd D:\GitHub\My_First_Project

rm -r -fo build

mkdir build

cd build

cmake -G Ninja ..

cmake --build .

cmake --build . --target flash
