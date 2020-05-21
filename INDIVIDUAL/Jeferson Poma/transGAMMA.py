import cv2
import numpy as np

img=cv2.imread('image.jpg',0)
gamma=2
img1=np.power(img,gamma)

gamma=3
img2=np.power(img,gamma)

gamma=4
img3=np.power(img,gamma)
#la funcion power eleva los numeros a gamma
#si gamma=3 y x=[1,2,3,4] entonces power(x,gamma)=[1,8,27,64]
#si tenemos un pixel lo elevamos a 4 modulo 256  -> 17**4%256=19
#print(img[110][110])
#print(img3[110][110])


cv2.imshow('Original',img)
cv2.imshow('Gamma 2',img1)
cv2.imshow('Gamma 3',img2)
cv2.imshow('Gamma 4',img3)

cv2.waitKey(0)
cv2.destroyAllWindows()
