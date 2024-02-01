# -*- coding: utf-8 -*-
"""
Created on Wed Jan 31 13:24:56 2024

@author: adria
"""

import cv2

# Cargar los clasificadores de Haar para rostros y cuerpos
rostro_cascade = cv2.CascadeClassifier('C:/Users/adria/Downloads/haarcascade_frontalface_default.xml')
cuerpo_cascade = cv2.CascadeClassifier('C:/Users/adria/Downloads/haarcascade_fullbody.xml')

# Iniciar la captura de video desde la cámara (0 para la cámara predeterminada)
captura = cv2.VideoCapture(0)

while True:
    # Capturar frame por frame
    ret, frame = captura.read()

    # Convertir la imagen a escala de grises para la detección
    gris = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detección de rostros
    rostros = rostro_cascade.detectMultiScale(gris, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    # Detección de cuerpos enteros
    cuerpos = cuerpo_cascade.detectMultiScale(gris, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))
    


    # Dibujar rectángulos alrededor de los rostros y cuerpos detectados
    for (x, y, w, h) in rostros:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (255, 0, 0), 2)

    for (x, y, w, h) in cuerpos:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 2)

    # Mostrar el frame resultante
    cv2.imshow('Detección de Personas', frame)

    # Salir del bucle si se presiona la tecla 'Enter'
    if cv2.waitKey(1) == 13:
        break

# Liberar la captura de video y cerrar todas las ventanas
captura.release()
cv2.destroyAllWindows()
