//
// Created by remy on 02-06-20.
//

#include "QrToPng.h"

QrToPng::QrToPng(std::string fileName, int imgSize, int minModulePixelSize, std::string text,
                 bool overwriteExistingFile, qrcodegen::QrCode::Ecc ecc) :
        _fileName(std::move(fileName)), _size(imgSize), _minModulePixelSize(minModulePixelSize), _text(std::move(text)),
        _overwriteExistingFile(overwriteExistingFile), _ecc(ecc) {
}

bool QrToPng::writeToPNG() {
    /* text is required */
    if (_text.empty())
        return false;


    if (!_overwriteExistingFile and fs::exists(_fileName))
        return false;

    auto _qr = qrcodegen::QrCode::encodeText("", _ecc);
    try {
        _qr = qrcodegen::QrCode::encodeText(_text.c_str(), _ecc);
    }
    catch (const std::length_error &e) {
        std::cerr << "Failed to generate QR code, too much data. Decrease _ecc, enlarge size or give less text." << std::endl;
        std::cerr << "e.what(): " << e.what() << std::endl;
        return false;
    }

    if (_overwriteExistingFile and fs::exists(_fileName))
        if (!fs::copy_file(_fileName, _fileName + ".tmp", fs::copy_options::overwrite_existing))
            return false;

    auto result = _writeToPNG(_qr);

    if (result)
        fs::remove(_fileName + ".tmp");

    return result;

}

bool QrToPng::_writeToPNG(const qrcodegen::QrCode &qrData) const {
    std::ofstream out(_fileName.c_str(), std::ios::binary);
    TinyPngOut pngout(_imgSize(qrData), _imgSize(qrData), out);

    auto qrSize = qrData.getSize();
    if (qrSize > _size)
        return false; // qrcode doesn't fit

    int qrSizeFitsInMaxImgSizeTimes = _size / qrSize;
    int calculatedModulePixelSize = qrSizeFitsInMaxImgSizeTimes;

    if (calculatedModulePixelSize < _minModulePixelSize)
        return false; // image would be to small to scan

    std::vector<uint8_t> tmpData;
    const uint8_t blackPixel = 0x00;
    const uint8_t whitePixel = 0xFF;

    /* The below loop converts the qrData to RGB8.8.8 pixels and writes it with
     * the tinyPNGoutput library. since we probably have requested a larger
     * qr module pixel size we must transform the qrData modules to be larger
     * pixels (than just 1x1). */
    for (int qrModuleAtY = 0; qrModuleAtY < qrSize; qrModuleAtY++) {
        for (int rowY = 0; rowY < qrSizeFitsInMaxImgSizeTimes; ++rowY) {
            for (int qrModuleAtX = 0; qrModuleAtX < qrSize; qrModuleAtX++) {
                for (int rowX = 0; rowX < qrSizeFitsInMaxImgSizeTimes; ++rowX) {
                    if (qrData.getModule(qrModuleAtX, qrModuleAtY)) {
                        // insert saves us a for loop or 3 times the same line.
                        tmpData.insert(tmpData.end(), {blackPixel, blackPixel, blackPixel});
                    } else {
                        tmpData.insert(tmpData.end(), {whitePixel, whitePixel, whitePixel});
                    }
                }
                pngout.write(tmpData.data(), static_cast<size_t>(tmpData.size()/3));
                tmpData.clear();
            }
        }
    }
    return fs::exists(_fileName);
}


uint32_t QrToPng::_imgSize(const qrcodegen::QrCode &qrData) const {
    return (_size / qrData.getSize()) * qrData.getSize();
}
