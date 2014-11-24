#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <cmath>

#include <sndfile.h>
#include <wand/MagickWand.h>

using namespace std;


char* inAudioFile;
char* outImageFile;

long imageWidth = 1477;
long imageHeight = 67;


class Color {
public:
    unsigned char red, green, blue, alpha;
    double dRed, dGreen, dBlue, dAlpha;
    Color() {
        red = green = blue = alpha = 0;
        uc2d();
    }
    Color(unsigned char _red, unsigned char _green, unsigned char _blue, unsigned char _alpha = 255) {
        red = _red;
        green = _green;
        blue = _blue;
        alpha = _alpha;
        uc2d();
    }
    void uc2d() {
        dRed = red / (double)(UCHAR_MAX);
        dGreen = green / (double)(UCHAR_MAX);
        dBlue = blue / (double)(UCHAR_MAX);
        dAlpha = alpha / (double)(UCHAR_MAX);
    }
};


Color bgColor;

Color fgGradientUpper(33, 33, 33, 255);
Color fgGradientLower(66, 66, 66, 255);


int get_integer(char* str) {
    int res = 0;
    while (*str) {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}

/** 从argv[]复制到变量中 */
int get_options(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            char* key = argv[i] + 1;
            if (!strcmp(key, "width")) {
                imageWidth = get_integer(argv[++i]);
            } else
            if (!strcmp(key, "height")) {
                imageHeight = get_integer(argv[++i]);
            }
        } else
        if (inAudioFile == NULL) {
            inAudioFile = argv[i];
        } else
        if (outImageFile == NULL) {
            outImageFile = argv[i];
        } else {
            fprintf(stderr, "oooooooops\n");
            return 0;
        }
    }
    return 1;
}

/** 检查选项的格式 */
int check_options() {
    if (inAudioFile == NULL) {
        fprintf(stderr, "no input file\n");
        return 0;
    }
    if (outImageFile == NULL) {
        fprintf(stderr, "no output file\n");
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    /** 选项处理
    inAudioFile 输入音频文件
    outImageFile 输出图像文件
    imageWidth, imageHeight 图像大小
    bgColorRed, bgColorGreen, bgColorBlue, bgColorAlpha 图像颜色
    fgGradientCenterRed, fgGradientCenterGreen, fgGradientCenterBlue, fgGradientCenterAlpha
    fgGradientOuterRed, fgGradientOuterGreen, fgGradientOuterBlue, fgGradientOuterAlpha
    cheat */
    if (!get_options(argc, argv) || !check_options()) {
        fprintf(stderr, "Error: Unexepect option format\n");
        return 0;
    }
    fprintf(stderr, "imageWidht = %d, imageHeight = %d\n", imageWidth, imageHeight);

    int frameCount = -1;
    int channelCount = -1;
    int frameSize = -1;
    int sampleRate = -1;
    int audioTime = -1;
    const float sampleMin = (float)(SHRT_MIN); // 虽然我不知道这是什么东西！
    const float sampleMax = (float)(SHRT_MAX);
    const float sampleRange = sampleMax - sampleMin;

    // sndfile设置并打开文件
    SF_INFO sfInfo;
    memset(&sfInfo, 0, sizeof(SF_INFO));
    short* frames = NULL;
    SNDFILE* sfFile = sf_open(inAudioFile, SFM_READ, &sfInfo); // 打开文件
    if (sfFile == NULL) {
        fprintf(stderr, "undetected file format.\n");
        return 0;
    }

    // 帧数、声道数的计算
    frameCount = sfInfo.frames; // 帧数
    channelCount = sfInfo.channels; // 声道数
    sampleRate = sfInfo.samplerate; // 取样频率
    audioTime = (int)(1.0 * frameCount / sampleRate); // 歌曲长度(seconds)
    fprintf(stderr, "frameCount = %d, channelCount = %d, sampleRate = %d audioTime = %d\n", frameCount, channelCount, sampleRate, audioTime);

    float framesPerPixel = frameCount / (float)(imageWidth); // 每pixel的帧数
    int framesToSee = (int)(framesPerPixel);
    int framesTimesChannels = framesToSee * channelCount; // 每pixel内的实际数据量

    frames = (short *)malloc(sizeof(short) * framesTimesChannels);
    if (frames == NULL) {
        sf_close(sfFile);
        fprintf(stderr, "Out of memory.(ask for %d bytes)\n", framesTimesChannels);
        return 0;
    }

    // Magick图片
    MagickWandGenesis();
    MagickWand* wand = NewMagickWand();
    DrawingWand* draw = NewDrawingWand();

    // create colors
    PixelWand* bgPixWand = NewPixelWand();
    PixelWand* fgPixWand = NewPixelWand();

    PixelSetRed(bgPixWand, bgColor.red / (double)(UCHAR_MAX));
    PixelSetGreen(bgPixWand, bgColor.green / (double)(UCHAR_MAX));
    PixelSetBlue(bgPixWand, bgColor.blue / (double)(UCHAR_MAX));
    PixelSetAlpha(bgPixWand, bgColor.alpha / (double)(UCHAR_MAX));

    // create image
    MagickNewImage(wand, imageWidth, imageHeight, bgPixWand);
    MagickSetImageOpacity(wand, bgColor.alpha / (double)(UCHAR_MAX));

    // create drawing wand
    DrawSetFillColor(draw, fgPixWand);
    DrawSetFillOpacity(draw, 1);

    // gradient calculations
    double centerY = imageHeight / 2;
    int lineY = imageHeight * 2 / 3;

    // 读取
    for (int x = 0; x < imageWidth; x++) {
        //int start = x * framesPerPixel;
        float minValue = sampleMax;
        float maxValue = sampleMin;
        //sf_seek(sfFile, start, SEEK_SET);
        sf_readf_short(sfFile, frames, framesToSee);
        // pixel内部
        for (int i = 0; i < framesTimesChannels; i++) {
            float value = 0;
            for (int c = 0; c < channelCount; c++)
                value += frames[i + c];
            value /= channelCount;
            minValue = min(minValue, value);
            maxValue = max(maxValue, value);
        }
        float yMinPro = 0.5 - sqrt(fabs((minValue - sampleMin) / sampleRange - 0.5) / 0.5) * 0.5;
        float yMaxPro = 0.5 + sqrt(fabs((maxValue - sampleMin) / sampleRange - 0.5) / 0.5) * 0.5;
        int yMin = yMinPro * imageHeight;
        int yMax = yMaxPro * imageHeight;

        int yTop = centerY;
        int yBottom = centerY;
        Color fgUpper = fgGradientUpper;
        Color fgLower = fgGradientLower;

        PixelSetRed(fgPixWand, fgUpper.dRed);
        PixelSetGreen(fgPixWand, fgUpper.dGreen);
        PixelSetBlue(fgPixWand, fgUpper.dBlue);
        PixelSetAlpha(fgPixWand, fgUpper.dAlpha);
        DrawSetFillColor(draw, fgPixWand);
        while (yBottom >= yMin) DrawPoint(draw, x, yBottom--);

        bool changed = false;
        while (yTop <= yMax) {
            if (!changed && yTop >= lineY) {
                changed = true;
                PixelSetRed(fgPixWand, fgLower.dRed);
                PixelSetGreen(fgPixWand, fgLower.dGreen);
                PixelSetBlue(fgPixWand, fgLower.dBlue);
                PixelSetAlpha(fgPixWand, fgLower.dAlpha);
                DrawSetFillColor(draw, fgPixWand);
            }
            DrawPoint(draw, x, yTop++);
        }
    }
    // save image
    MagickDrawImage(wand, draw);
    MagickWriteImage(wand, outImageFile);

    // clean up
    draw = DestroyDrawingWand(draw);
    DestroyPixelWand(bgPixWand);
    DestroyPixelWand(fgPixWand);
    wand = DestroyMagickWand(wand);
    MagickWandTerminus();

    free(frames);
    sf_close(sfFile);

    return 0;
}

