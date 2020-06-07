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

    auto PIXELS = _qrPixelDataForPNGWriter(_qr);
    if (PIXELS.empty())
        return false;

    if (_overwriteExistingFile and fs::exists(_fileName))
        if (!fs::remove(_fileName))
            return false;

    _writePNGfile(PIXELS, _imgSize(_qr));

    return fs::exists(_fileName);
}

std::vector<uint8_t> QrToPng::_qrPixelDataForPNGWriter(const qrcodegen::QrCode &qrData) const {
    std::vector<uint8_t> PIXELS;
    auto qrSize = qrData.getSize();
    if (qrSize > _size)
        return PIXELS; // qrcode doesn't fit

    int qrSizeFitsInMaxImgSizeTimes = _size / qrSize;
    int calculatedModulePixelSize = qrSizeFitsInMaxImgSizeTimes;

    if (calculatedModulePixelSize < _minModulePixelSize)
        return PIXELS; // image would be to small to scan

    const uint8_t blackPixel = 0x00;
    const uint8_t whitePixel = 0xFF;

    /* The below loop transforms the qrData to a vector of RGB8.8.8 for
     * the tinyPNGoutput library. since we probably have requested a larger
     * qr module pixel size we must transform the qrData modules to be larger
     * pixels (than just 1x1). */
    for (int qrModuleAtY = 0; qrModuleAtY < qrSize; qrModuleAtY++) {
        for (int rowY = 0; rowY < qrSizeFitsInMaxImgSizeTimes; ++rowY) {
            for (int qrModuleAtX = 0; qrModuleAtX < qrSize; qrModuleAtX++) {
                for (int rowX = 0; rowX < qrSizeFitsInMaxImgSizeTimes; ++rowX) {
                    for (int i = 0; i < 3; ++i) {
                        if (qrData.getModule(qrModuleAtX, qrModuleAtY)) {
                            PIXELS.push_back(blackPixel);
                        } else {
                            PIXELS.push_back(whitePixel);
                        }
                    }
                }
            }
        }
    }
    return PIXELS;
}

void QrToPng::_writePNGfile(std::vector<uint8_t> PIXELS, uint32_t SIZE) {
    std::ofstream out(_fileName.c_str(), std::ios::binary);
    TinyPngOut pngout(SIZE, SIZE, out);
    pngout.write(PIXELS.data(), static_cast<size_t>(SIZE * SIZE));
}

uint32_t QrToPng::_imgSize(const qrcodegen::QrCode &qrData) const {
    return (_size / qrData.getSize()) * qrData.getSize();
}
