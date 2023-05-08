import cv2
from decimal import * 
img = cv2.imread('./labi.jpg', cv2.IMREAD_GRAYSCALE)
img = cv2.resize(img, (400, 300), interpolation=cv2.INTER_AREA)

for y in range(300):
    for x in range(400):
        if y %2 == 1 and y !=299:
            if x == 0 or x == 399:
                ans = (int(img[y-1][x])/16 + int(img[y+1][x])/16)%16/2
            else:
                D1 = abs(int(img[y-1][x-1])/16 - int(img[y+1][x+1])/16)
                D2 = abs(int(img[y-1][x])/16 - int(img[y+1][x])/16)
                D3 = abs(int(img[y-1][x+1])/16 - int(img[y+1][x-1])/16)
                if D2 <= D1 and D2 <= D3:
                    ans = (int(img[y-1][x])/16 + int(img[y+1][x])/16)%16/2
                elif D1 <= D3:
                    ans = (int(img[y-1][x-1])/16 + int(img[y+1][x]+1)/16)%16/2
                else:
                    ans = (int(img[y-1][x+1])/16 + int(img[y+1][x-1])/16)%16/2
        else:
            ans = int(img[y][x])/16
        img[y][x] = ans * 17
cv2.imshow('Image title', img) 
cv2.waitKey(0)           
cv2.destroyAllWindows()