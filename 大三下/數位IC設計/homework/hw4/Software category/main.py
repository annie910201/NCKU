import numpy
import cv2

img = cv2.imread('./images/Bleach.png', cv2.IMREAD_GRAYSCALE)
img = cv2.resize(img, (64, 64), interpolation=cv2.INTER_AREA)
img_dat = open("./img.dat", "w")
golden_layer0_dat = open("./layer0_golden.dat", "w")
golden_layer1_dat = open("./layer1_golden.dat", "w")

# img.dat
a=0
img_after_layer_0 = [[0]*64 for i in range(64)]
buf = [0, 0, 0, 0, 0, 0, 0, 0, 0]
for y in range(64):
    for x in range(64):
        ans = img[y][x]
        float_code = float(ans) - int(ans)
        float_code = int(float_code * 10000)
        int_code = int(ans)
        img_dat.write( '{0:09b}'.format(int_code) + '{0:04b}'.format(float_code) + " //data " + str(a) + ": " + str(int_code) + "." + str(float_code) + '\n')
        a = a + 1
# layer0_golden.dat
a = 0
for y in range(64):
    for x in range(64):      
        if x <= 2 and y <= 2:
            buf[0] = float(img[0][0]) * (-0.0625)
        elif y <= 2:
            buf[0] = float(img[0][x-2]) * (-0.0625)
        elif x <= 2:
            buf[0] = float(img[y-2][0]) * (-0.0625)
        else:
            buf[0] = float(img[y-2][x-2]) * (-0.0625)

        if y == 0:
            buf[1] = float(img[y][x]) * (-0.125)
        elif y == 1:
            buf[1] = float(img[y-1][x]) * (-0.125)
        else:
            buf[1] = float(img[y-2][x]) * (-0.125)

        if x >= 61 and y <= 2:
            buf[2] = float(img[0][63]) * (-0.0625)
        elif y <= 2:
            buf[2] = float(img[0][x+2]) * (-0.0625)
        elif x >= 61:
            buf[2] = float(img[y-2][63]) * (-0.0625)
        else:
            buf[2] = float(img[y-2][x+2]) * (-0.0625)

        if x == 0:
            buf[3] = float(img[y][x]) * (-0.25)
        elif x == 1:
            buf[3] = float(img[y][x-1]) * (-0.25)
        else:
            buf[3] = float(img[y][x-2]) * (-0.25)

        buf[4] = float(img[y][x])

        if x == 63:
            buf[5] = float(img[y][x]) * (-0.25)
        elif x == 62:
            buf[5] = float(img[y][x+1]) * (-0.25)
        else:
            buf[5] = float(img[y][x+2]) * (-0.25)

        if x <= 2 and y >= 61:
            buf[6] = float(img[63][0]) * (-0.0625)
        elif y >= 61:
            buf[6] = float(img[63][x-2]) * (-0.0625)
        elif x <= 2:
            buf[6] = float(img[y+2][0]) * (-0.0625)
        else:
            buf[6] = float(img[y+2][x-2]) * (-0.0625)

        if y == 63:
            buf[7] = float(img[y][x]) * (-0.125)
        elif y == 62:
            buf[7] = float(img[y+1][x]) * (-0.125)
        else:
            buf[7] = float(img[y+2][x]) * (-0.125)

        if x >= 61 and y >= 61:
            buf[8] = float(img[63][63]) * (-0.0625)
        elif x >= 61:
            buf[8] = float(img[y+2][63]) * (-0.0625)
        elif y >= 61:
            buf[8] = float(img[63][x+2]) * (-0.0625)
        else:
            buf[8] = float(img[y+2][x+2]) * (-0.0625)

        ans = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + \
            buf[5] + buf[6] + buf[7] + buf[8] - 0.75

        if ans < 0.0:
            ans = 0.0
        img_after_layer_0[y][x] = ans
        # golden_layer0_dat.write(str(ans) + ' ')
        int_code = int(ans)
        float_code = float(ans) - int(ans)
        float_num = 0
        if float_code >= 0.5:
            float_code = float_code - 0.5
            float_num = float_num + 1000
        if float_code >= 0.25:
            float_code = float_code - 0.25
            float_num = float_num + 100
        if float_code >= 0.125:
            float_code = float_code - 0.125
            float_num = float_num + 10
        if float_code >= 0.0625:
            float_num = float_num + 1
                
        golden_layer0_dat.write( '{0:09b}'.format(int_code) + '{0:04d}'.format(float_num) + " //data " + str(a) + ": " + str(ans) + '\n')
        a = a + 1
# layer1_golden.dat
a = 0
for y in range(63):
    for x in range(63):
        if x%2 == 0 and y%2 == 0:
            # golden_layer1_dat.write(str(img[y][x+1]) + ' ')
            ans = max(img_after_layer_0[y][x], img_after_layer_0[y][x+1], img_after_layer_0[y+1][x], img_after_layer_0[y+1][x+1])
            # golden_layer1_dat.write(str(ans) + ' ')
            if float(ans) - int(ans) > 0:
                ans = int(ans) + 1
            else:
                ans = int(ans)
            golden_layer1_dat.write( '{0:09b}'.format(ans) + "0000 //data " + str(a) + ": " + str(ans) + ".0" + '\n')
            a = a + 1
            
img_dat.close()
golden_layer0_dat.close()
golden_layer1_dat.close()
