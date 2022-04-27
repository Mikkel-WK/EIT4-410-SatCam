# Individual test cases for code:

## Reading data
WIP

## DCT
1. Fill the yccBuffer with a 16x16 pixel array, wherein every Y value is 255. 
2. Invoke DCTToBuffers(TEST2). 
3. Output the dctYBuffer to (16, 16), preferably in a pretty 16x16 format. Every 8x8 block should look like this:
2040, -1, 1, -1, 1, -1, 1, -1
-1, 0, -0, 0, -0, 0, -0, 0
1, -0, 0, -0, 0, -0, 0, -0
-1, 0, -0, 0, -0, 0, -0, 0
1, -0, 0, -0, 0, -0, 0, -0
-1, 0, -0, 0, -0, 0, -0, 0
1, -0, 0, -0, 0, -0, 0, -0
-1, 0, -0, 0, -0, 0, -0, 0
NOTE: -0 may be represented as 0. Not sure how to fix that at present but it changes nothing.

## Quantization (NOT CORRECT ATM)
1. Fill the buffers dctYBuffer, dctCbBuffer, and dctCrBuffer with a 16x16 array, wherein every value is 255.
2. Invoke QuantBuffers(TEST2).
3. Output the dctYBuffer to (16, 16), preferably in a pretty 16x16 format. Every 8x8 block should look like this:
15, 23, 25, 15, 10, 6, 5, 4
21, 21, 18, 13,  9, 4, 4, 4
18, 19, 15, 10,  6, 4, 3, 4
18, 15, 11,  8,  5, 2, 3, 4
14, 11,  6,  4,  3, 2, 2, 3
10,  7,  4,  3,  3, 2, 2, 2
5,   3,  3,  2,  2, 2, 2, 2
3,   2,  2,  2,  2, 2, 2, 2

4. Output the dctCbBuffer and dctCrBuffer to (16, 16), preferably in a pretty 16x16 format. Every 8x8 block should look like this:
15, 14, 10, 5, 2, 2, 2, 2
15, 12,  9, 3, 2, 2, 2, 2
10,  9,  4, 2, 2, 2, 2, 2
5,   3,  2, 2, 2, 2, 2, 2
2,   2,  2, 2, 2, 2, 2, 2
2,   2,  2, 2, 2, 2, 2, 2
2,   2,  2, 2, 2, 2, 2, 2
2,   2,  2, 2, 2, 2, 2, 2

## Differential DC
1. Populate, in dctYBuffer, the position (0,0) with 228, and the positions (8,0), (16,0), (24,0), (0,8), (8,8), (16,8), and (24,8) with values ranging from 200 to 255.
2. Invoke DiffDCBuffers(TESTWIDE). 
3. Output previously explained positions. The output at (8,0) should be the (8,0) value subtracted with the (0,0) value, the output at (16,0) should be the (16,0) value subtracted with the (8,0) value, and so on. Note that this process is restarted at (0,1), and thusly position (0,1) should not be modified.

## Zigzag
1. Populate, in dctYBuffer, the 8x8 blocks starting at (0,0), (8,0), (0,8), and (8,8) with the following array:
0,   1,  5,  6, 14, 15, 27, 28
2,   4,  7, 13, 16, 26, 29, 42
3,   8, 12, 17, 25, 30, 41, 43
9,  11, 18, 24, 31, 40, 44, 53
10, 19, 23, 32, 39, 45, 52, 54
20, 22, 33, 38, 46, 51, 55, 60
21, 34, 37, 47, 50, 56, 59, 61
35, 36, 48, 49, 57, 58, 62, 63

2. Invoke ZigzagBuffers(TEST2).
3. Output the dctYBuffer to (16, 16), preferably in a pretty 16x16 format. Every 8x8 block should look like this:
0,   1,  2,  3,  4,  5,  6,  7
8,   9, 10, 11, 12, 13, 14, 15
16, 17, 18, 19, 20, 21, 22, 23
24, 25, 26, 27, 28, 29, 30, 31
32, 33, 34, 35, 36, 37, 38, 39
40, 41, 42, 43, 44, 45, 46, 47
48, 49, 50, 51, 52, 53, 54, 55
56, 57, 58, 59, 60, 61, 62, 63