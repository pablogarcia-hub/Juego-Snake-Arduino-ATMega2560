# Juego-Snake-Arduino-ATMega2560
Juego Snake para Arduino Mega 2560 con pantalla LCD 16x2 y buzzer. Controlado con pulsadores.
# 🎮 Juego Snake en Arduino Mega 2560

Este proyecto implementa el clásico juego *Snake* en un *Arduino Mega 2560* utilizando:
- Pantalla LCD 16x2  
- Pulsadores para el control de la serpiente  
- Buzzer para efectos de sonido  

---

## 📌 Descripción
La serpiente se mueve por el área de juego y debe ir comiendo la “comida” que aparece aleatoriamente en la pantalla.  
Cada vez que come, el puntaje aumenta y la velocidad incrementa, haciendo el juego más desafiante.  

El juego termina cuando la serpiente choca contra los bordes o contra sí misma.  

---

## 🛠️ Hardware Necesario
- Arduino Mega 2560  
- Pantalla LCD 16x2 (Keypad Shield o conexión directa)  
- Pulsadores para el control (arriba, abajo, izquierda, derecha, seleccionar)  
- Buzzer (para efectos de sonido)  

---

## 📟 Conexiones
- *LCD* → conectado en modo paralelo (pines digitales 8, 9, 4, 5, 6, 7)  
- *Pulsadores* → conectados al pin analógico A0 (usando el Keypad Shield típico)  
- *Buzzer* → conectado al pin digital 3  

---

## ▶️ Instrucciones de Juego
- Usa los botones del Keypad Shield para mover la serpiente:  
  - *Arriba, Abajo, Izquierda, Derecha* → controlan el movimiento.  
- Come la comida (*) para aumentar el puntaje.  
- Evita chocar contra los bordes o contigo mismo.  

---

## 📂 Archivos del Proyecto
- Snake_Arduino.ino → Código fuente del juego  
- Proyecto_Snake_Arduino.docx → Informe con la documentación completa  
- README.md → Este archivo con la explicación general  

---

## 👤 Autor
*Pablo García*  
Proyecto académico para el curso de microcontroladores – 2025
 
