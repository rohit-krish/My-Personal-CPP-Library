## MyLIb (My Personal C++ Lib)

### How to create a shared lib(dynamic lib)
```
cd /usr/lib/mylib
g++ -shared -o ./lib/libtileIt.so -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui ./src/tileIt.cpp
```

### build & run test.cpp

```
g++ -o test test.cpp -Iinclude -Llib -ltileIt `pkg-config --cflags --libs opencv4`
```
```
export LD_LIBRARY_PATH="/usr/lib/mylib/lib:$LD_LIBRARY_PATH"
```
```
./test
```

for conveniency we can use pkg-config to specify the cflags and libs of our script automatically, rather than manually typing it.

so create a .pc file similer to the file i provided here (mylib.pc) & copy it to /usr/lib/pkgconfig/

```
sudo cp mylib.pc /usr/lib/pkgconfig/
```

now we can use pkg-config to extract cflags and libs
```
g++ -o test test.cpp `pkg-config --cflags --libs mylib opencv4`; ./test
```
