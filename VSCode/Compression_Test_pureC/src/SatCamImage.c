/*
 * SatCamImage.h - Library for using the data stream from SatCam to build into a JPEG file with compression
 * Created by person, month date, 2022
*/

/* Include header file */
#include "SatCamImage.h"

/* Markers for JPEG creation */
BYTE SOI[2] = {0xff, 0xd8}; /* Start of Image Marker */
BYTE SOS[2] = {0xff, 0xda}; /* Start of Scan Marker */
BYTE EOI[2] = {0xff, 0xd9}; /* End of Image Marker */

int TestInput() {

}

/*
 * Function: BuildJFIFHeader
 * Purpose: Builds JFIF header with some basic variables, then puts in custom values
 * Input: Header pointer, Unit, XDensity, YDensity, XThumbnail, YThumbnail
 * Output: Error code
*/
int BuildJFIFHeader(JFIFHEADER* headerptr, 
                    BYTE unit, 
                    BYTE xDensity[2], 
                    BYTE yDensity[2], 
                    BYTE xThumbnail, 
                    BYTE yThumbnail) {
    /* Write constants to header */
    BYTE app[2] = {0xff, 0xe0};
    memcpy(headerptr->APP0, &app, 2);

    BYTE id[5] = {0x4a, 0x46, 0x49, 0x46, 0x00};
    memcpy(headerptr->ID, &id, 5);

    BYTE version[2] = {0x01, 0x02};
    memcpy(headerptr->Version, &version, 2);

    /* Write custom values to header */
    headerptr->Unit = unit;
    memcpy(headerptr->XDensity, &xDensity, 2);
    memcpy(headerptr->YDensity, &yDensity, 2);
    headerptr->XThumbnail = xThumbnail;
    headerptr->YThumbnail = yThumbnail;

    /* Write Length of application segment to header */
    uint16_t length = 16 + (3*xThumbnail*yThumbnail);
    BYTE lengthArr[2] = {length >> 8, length};
    memcpy(headerptr->Length, &lengthArr, 2);

    return 1;
}

/*
int BuildEXIFHeader(EXIFHEADER* headerptr) {


    return 1;
}*/

/* Function: DestroyJFIFHeader
 * Purpose: Destroy header after use
 * Input: Header pointer
 * Output: Error code
*/
int DestroyJFIFHeader(JFIFHEADER* headerptr) {
    free(headerptr);

    return 1;
}

/*
 * Function: ReadDataToBuffer
 * Purpose: Read data from RAM, sanitise (remove alpha data)
 * Input: Address in RAM of data, length of data, amount of pixels
 * Output: Byte array with pixel data, no alpha
*/
BYTE* ReadDataToBuffer(long* dataAddr, size_t dataLen, size_t pixelLen) {
    BYTE* pixelBuffer = malloc(pixelLen);
    
    for(unsigned int i = 0; i < dataLen; i++) {
        if(i % 4 == 0) {
            continue;
        }

        *(pixelBuffer + i) = *(dataAddr + i);
    }

    return pixelBuffer;
}

BYTE* RGBToYCBCR(BYTE* pixelArr, size_t arrLen) {
    BYTE* yccBuffer = malloc(arrLen);

    BYTE r, g, b;
    BYTE y, cb, cr;

    /*
    double transMatrix[] = 
    {
        46.742, 157.243, 15.874,
        -25.765, -86.674, 112.439,
        112.439, -102.129, -10.310
    };
    */

   // Source: https://ebookcentral.proquest.com/lib/aalborguniv-ebooks/reader.action?docID=867675
   // Using BT.709 standard
   int transMatrix[] = 
   {
       47, 157, 16,
       -26, -87, 112,
       112, -102, -10
   };

    for(unsigned int i = 0; i < arrLen; i + 3) {
        b = *(pixelArr + i);
        g = *(pixelArr + (i + 1));
        r = *(pixelArr + (i + 2));

        // Note: var >> 8 is the same as var/256
        y = 16 + (((transMatrix[0]*r) + (transMatrix[1]*g) + (transMatrix[2]*b)) >> 8);
        cb = 128 + (((transMatrix[3]*r) + (transMatrix[4]*g) + (transMatrix[5]*b)) >> 8);
        cr = 128 + (((transMatrix[6]*r) + (transMatrix[7]*g) + (transMatrix[8]*b)) >> 8);

        *(yccBuffer + i) = y;
        *(yccBuffer + (i + 1)) = cb;
        *(yccBuffer + (i + 2)) = cr;
    }

    return yccBuffer;
}

BYTE* YCBCRToRGB(BYTE* yccArr, size_t arrLen) {
    BYTE* rgbBuffer = malloc(arrLen);

    BYTE r, g, b;
    BYTE y, cb, cr;

    /*
    double transMatrix[] = 
    {
        298.082, 0, 458.942,
        298.082, -54.592, -136.425,
        298.082, 540.775, 0
    };
    */

    // Source: https://ebookcentral.proquest.com/lib/aalborguniv-ebooks/reader.action?docID=867675
    // Using BT.709 standard
    int transMatrix[] =
    {
        298, 0, 459,
        298, -55, -136,
        298, 541, 0
    };

    for(unsigned int i = 0; i < arrLen; i + 3) {
        y = *(yccArr + i);
        cb = *(yccArr + (i + 1));
        cr = *(yccArr + (i + 2));

        r = (transMatrix[0]*(y-16) + transMatrix[1]*(cb-128) + transMatrix[2]*(cr-128)) >> 8;
        g = (transMatrix[3]*(y-16) + transMatrix[4]*(cb-128) + transMatrix[5]*(cr-128)) >> 8;
        b = (transMatrix[6]*(y-16) + transMatrix[7]*(cb-128) + transMatrix[8]*(cr-128)) >> 8;

        *(rgbBuffer + i) = b;
        *(rgbBuffer + (i + 1)) = g;
        *(rgbBuffer + (i + 2)) = r;
    }

    return rgbBuffer;
}

SBYTE* LevelShiftArr(BYTE* arr, size_t arrLen) {
    SBYTE* shiftedBuffer = malloc(arrLen);

    for(unsigned int i = 0; i < arrLen; i++) {
        *(shiftedBuffer + i) = *(arr + i) - 128;
    }

    return shiftedBuffer;
}


BYTE* QuantToBuffer() {
    BYTE* quantBuffer = malloc(1);

    

    return quantBuffer;
}

int WriteToJPEG() {


    /*
     * Checklist for making JPEG file
     * 
     * Order of headers
     * SOI (not included in JPEG header)
     * APP0-14
     * DQT
     * SOF0
     * DHT
     * DRI
     * SOS
     * RST0-7 ad nauseam
     * EOI
    */
}
