#include "Utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


Result Screen::ExportFrame(const char* file_path) {
    unsigned char* test;
    if (stbi_write_png(file_path, screenWidth_const, screenHeight_const, 3, convertFrameToUnsignedChar(), screenWidth_const * 3) != 0) {
        std::cout << "Frame saved successfully to " << file_path << "\n";
        return Result::SUCCESS;
    } else {
        std::cerr << "error: failed to save the frame to " << file_path << "\n";
        return Result::FAIL;
    }
}
