import cv2
import numpy as np

image=cv2.imread('image4.jpg')

person=cv2.imread('perfil.jpg')
person=cv2.resize(person,(400,400),interpolation=cv2.INTER_CUBIC)
T=np.float32([[1,0,550],[0,1,50]])
person=cv2.warpAffine(person,T,(1000,500))

mask=np.zeros((500,1000),dtype=np.uint8)
mask=cv2.circle(mask,(750,250),200,(255),-1)

temp1=cv2.bitwise_and(person,person,mask=mask)
temp2=cv2.bitwise_and(image,image,mask=cv2.bitwise_not(mask))
salida=(cv2.bitwise_or(temp1,temp2))

cv2.imshow('Salida',salida)
cv2.imshow('Temp1',temp1)
cv2.imshow('Temp2',temp2)

cv2.waitKey(0)
cv2.destroyAllWindows()