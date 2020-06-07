# C++ QR to PNG

A bridge between two great libraries, [QR-Code-Generator][1] and [Tiny-PNG-Out][2].

![qr code example][3]
 
The QR-Code-Generator library for C++ gives you an easy, fast and correct way to 
generate QR codes. However, you get just a data structure, showing that data is up
to you. An example is provided to print the code to a terminal, but not to create 
and actual image file. 

The author of the library also has another C++ library, [Tiny-PNG-Out][2]. 
It is correct up until 700 megapixel PNG files, which I hope your QR code never hits.

I've written a class which bridges the two together, allowing you to both generate
the QR code and write it to a PNG file. 

## Size?

A QR code consists out of modules, otherwise known as the black and white dots. 
The library gives you a data structure where each dot is either a 1 or 0, (black/white).
The size of the total QR code is also provided.

It is up to you to scale those up to bigger pixels if required. 

## Build instructions

- Clone this git repository. You get both projects included.

    git clone bla
    cd bla
    
- Create a build folder:
    
    mkdir build
    cd build
    
- Run CMake:

    cmake ..
    
- Run Make:

    make all

The binary which writes example files is located in the `src/` folder:

    src/qr-to-png 
   
Running it should generate 3 example QR codes:

    /home/remy/Repo/cpp-qr-to-png/cmake-build-debug/src/qr-to-png
    Writing Example QR code 1 (normal) to example1.png with text: 'https://raymii.org', size: 300x300, qr module pixel size: 3. 
    Success!
    Writing Example QR code 2 (tiny) to example2.png with text: 'https://raymii.org', size: 40x40, qr module pixel size: 1. 
    Success!
    Writing Example QR code 3 (huge) to example3.png with text: 'https://raymii.org', size: 1080x1080, qr module pixel size: 20. 
    Success!
    
![qr code example][3]       


[1]: https://www.nayuki.io/page/qr-code-generator-library
[2]: https://www.nayuki.io/page/tiny-png-output
[3]: example1.png