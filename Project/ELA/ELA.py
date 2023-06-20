import cv2
from decimal import * 
img = cv2.imread('./labi.jpg', cv2.IMREAD_GRAYSCALE)
img = cv2.resize(img, (400, 300), interpolation=cv2.INTER_AREA)

for y in range(300):
    for x in range(400):
        if y %2 == 1 and y !=299:
            print(str(img[y-1][x]))
            if x == 0 or x == 399:
                b = int(img[y-1][x]/16)
                # print(str(b))
                e = int(img[y+1][x]/16)
                ans = ((b+e))/2
            else:
                a = int(img[y-1][x-1]/16)
                b = int(img[y-1][x]/16)
                c = int(img[y-1][x+1]/16)
                d = int(img[y+1][x-1]/16)
                e = int(img[y+1][x]/16)
                f = int(img[y+1][x+1]/16)
                D1 = abs(a-f)
                D2 = abs(b-e)
                D3 = abs(c-d)
                if D2 <= D1 and D2 <= D3:
                    ans = ((b+e))/2
                elif D1 <= D3:
                    ans = ((a+f))/2
                else:
                    ans = ((c+d))/2
            # ans = 0
        else:
            ans = int(img[y][x]/16)
        img[y][x] = ans * 16
cv2.imshow('Image title', img) 
cv2.waitKey(0)           
cv2.destroyAllWindows()