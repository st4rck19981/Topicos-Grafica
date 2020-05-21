import cv2

#img1=cv2.imread('cadena.jpg',0)   para escala de grises y le quitas 0 para rgb
img1=cv2.imread('image.jpg',0)
img2=cv2.imread('image2.jpg',0)


#SUMAR
resA=cv2.add(img1,img2)
#al sumar 64+266=291->255
#no debe pasar el limite, si pasa retorna 255
cv2.imshow('Suma Normal',resA)

#Se pone la img1 con su transparencia o alfa=0.5, igual con img2 y el ultimo valor es un beta q sumemos adicionalmente
redAW=cv2.addWeighted(img1,0.5,img2,0.5,0)
cv2.imshow('Suma con un peso y transparencia',redAW)



#RESTAR
#Al restar obtenemos valores cercanos a zero creando una imagen oscura
#Si restamos 65-226 es negativo entonces retorna zero
resultado=cv2.subtract(img1,img2)
#Esto hace que la imagen no sea tan oscura como la primera
#Halla el valor absoluto de la resta   |65-226|
resultado2=cv2.absdiff(img1,img2)
cv2.imshow('Resta Normal',resultado)
cv2.imshow('Resta con Valor Absoluto',resultado2)


cv2.imshow('Imagen 1',img1)
cv2.imshow('Imagen 2',img2)
cv2.waitKey(0)   #Tecla enter para salir
cv2.destroyAllWindows()
