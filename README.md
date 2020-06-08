# C++ QR to PNG

A bridge between two great libraries, [QR-Code-Generator][1] and [Tiny-PNG-Out][2].

![qr code example][3]
 
The QR-Code-Generator library by Project Nayuki for C++ gives you an easy, fast and 
correct way to generate QR codes. However, you get just a data structure, showing 
that data is up to you. An example is provided to print the code to a terminal, 
but not to create and actual image file. For Java, there is an example provided 
which writes a PNG file, but not for C++. 

The author of the library also has another C++ library, [Tiny-PNG-Out][2]. 
It is correct up until 700 megapixel PNG files, which I hope your QR code never hits.

I've written a class which bridges the two together, allowing you to both generate
the QR code and write it to a PNG file, scaled up to be as readable as possible.

## Size, scaled up?

A QR code consists out of modules, otherwise known as the black and white dots. 
The library gives you a data structure where each dot is either a 1 or 0, (black/white).
The size of the total QR code is also provided.

It is up to you to scale those up to bigger pixels if required. Since we're writing
it to a PNG file using the Tiny PNG Out library, we could just pass the qr data
and size, (width/height) and be done with it. That would result in a small, probably
unscanable image: 

![small qr code][4]

The PNG library needs a `vector` of RGB 8.8.8 pixels. That's just the HTML colour scheme 
you already know (#FF0000 for red) but in a vector. If we wanted a brown code, we'd make 
the black dots `0x8B, 0x45, 0x14` instead of `0x00, 0x00, 0x00`: 

![brown][5]

To make sure the code is readable, I calculate how many times the code fits inside the
requested image size. If the QR code reports that it's size is 23, that means,
in the context of our png library, we must write 23 modules as one row of pixels,
then start a new row. But if you've requested a 600x600px image, that would be way
too small.

Therefore the modules are scaled up to the size of the image. So if you've requested
a 90x90px image and the qr code reports a size of 29, it will fit inside 90px three 
times. The resulting image will be 87x87px with a qr module size of 3 (each black/white
dot being 3 pixels tall/wide).

You can provide a minimal module pixel size. If you want to encode a small code but want
the pixels to be, lets say, at least 2 pixels wide for better scanability, you can ask
the class. If it is able to scale up, it will write the file, otherwise it will return false.


## Build instructions

Clone this git repository. You get both projects included.

    git clone bla
    cd bla
    
Create a build folder:

    mkdir build
    cd build
    
Run CMake:

    cmake ..
    
Run Make:

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

However, the built version of this program is not very usefull, it's about the code itself.

### Examples

In `src/main.cpp` you will find 4 examples on how to use the class. Here is 
one example:

    auto exampleQrPng1 = QrToPng("example1.png", 300, 3, "https://raymii.org", true, qrcodegen::QrCode::Ecc::MEDIUM);
    exampleQrPng1.writeToPNG()  
    
Which results in the below image as `example1.png`:

![qr code example][3]       


### Licenses:

QrToPng:

    Copyright © 2020 Remy van Elst (https://raymii.org)
    License: GNU GPLv3

QR Code generator:

    https://github.com/nayuki/QR-Code-generator
    Copyright © 2020 Project Nayuki. (MIT License)
    https://www.nayuki.io/page/qr-code-generator-library

Tiny PNG Out:

    https://www.nayuki.io/page/tiny-png-output
    GPL v3 or LGPL v3
    
Licenses are also includes in the `libs/` folders.
    
[1]: https://www.nayuki.io/page/qr-code-generator-library
[2]: https://www.nayuki.io/page/tiny-png-output
[3]: example1.png
[4]: example2.png
[5]: brown.png