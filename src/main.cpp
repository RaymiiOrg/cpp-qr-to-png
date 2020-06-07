//
// Created by remy on 07-06-20.
//
#include "QrToPng.h"

int main() {

    std::string qrText = "https://raymii.org";
    std::string fileName = "example1.png";

    int imgSize = 300;
    int minModulePixelSize = 3;
    auto exampleQrPng1 = QrToPng(fileName, imgSize, minModulePixelSize, qrText, true, qrcodegen::QrCode::Ecc::MEDIUM);

    std::cout << "Writing Example QR code 1 (normal) to " << fileName << " with text: '" << qrText << "', size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng1.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;

    fileName = "example2.png";
    imgSize = 40;
    minModulePixelSize = 1;
    auto exampleQrPng2 = QrToPng(fileName, imgSize, minModulePixelSize, qrText, true, qrcodegen::QrCode::Ecc::LOW);
    std::cout << "Writing Example QR code 2 (tiny) to " << fileName << " with text: '" << qrText << "', size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng2.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;


    fileName = "example3.png";
    imgSize = 1080;
    minModulePixelSize = 20;
    auto exampleQrPng3 = QrToPng(fileName, imgSize, minModulePixelSize, qrText, true, qrcodegen::QrCode::Ecc::HIGH);
    std::cout << "Writing Example QR code 3 (huge) to " << fileName << " with text: '" << qrText << "', size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng3.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;


    qrText = "The most merciful thing in the world, I think, is the inability of the human mind to correlate all its contents. We live on a placid island of ignorance in the midst of black seas of infinity, and it was not meant that we should voyage far. The sciences, each straining in its own direction, have hitherto harmed us little; but some day the piecing together of dissociated knowledge will open up such terrifying vistas of reality, and of our frightful position therein, that we shall either go mad from the revelation or flee from the deadly light into the peace and safety of a new dark age.\n"
             "Theosophists have guessed at the awesome grandeur of the cosmic cycle wherein our world and human race form transient incidents. They have hinted at strange survivals in terms which would freeze the blood if not masked by a bland optimism. But it is not from them that there came the single glimpse of forbidden aeons which chills me when I think of it and maddens me when I dream of it. That glimpse, like all dread glimpses of truth, flashed out from an accidental piecing together of separated things—in this case an old newspaper item and the notes of a dead professor.";

    fileName = "example4.png";
    imgSize = 1024;
    minModulePixelSize = 1;
    auto exampleQrPng4 = QrToPng(fileName, imgSize, minModulePixelSize, qrText, true, qrcodegen::QrCode::Ecc::HIGH);
    std::cout << "Writing Example QR code 3 (enormous) to " << fileName << " with cthulu, size: " <<
              imgSize << "x" << imgSize << ", qr module pixel size: " << minModulePixelSize << ". " << std::endl;
    if (exampleQrPng4.writeToPNG())
        std::cout << "Success!" << std::endl;
    else
        std::cerr << "Failure..." << std::endl;

    return 0;
}