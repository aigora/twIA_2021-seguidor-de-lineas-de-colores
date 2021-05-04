#  Vehículo Autónomo
Vehículo autónomo  gobernado por un ordenador con el  objetivo de seguir lineas de colores
## Integrantes del equipo
Javier Robinat, 
Álvaro Rico , 
Carlos Miguel Martín, 
Joan Bellido, 
Pablo Manuel Sánchez

## Objetivos del trabajo
Ampliar nuestros conocimientos sobre los sensores que vamos a utilizar además de practicar y mejorar nuestra habilidad a la hora de crear y manejar código en el lenguaje de C

## Hardware
Identificamos el chasis y los compenentes electrónicos

### Chasis
El chasis está formado por contrachapado, cuenta con multitud de agujeros de diferentes tamaños con el objetivo de poder acoplar todos los elementos necesarios.
En primer lugar decidimos montar dos ruedas que van conectadas a través de dos motores que se conectan a su vez a una batería formada por 4 pilas y a un interruptor.
Seguidamente colocamos una tercera rueda que actúa como auxiliar y cuyo giro es de 360º.
![image](https://user-images.githubusercontent.com/61272141/117010129-c73f3600-acec-11eb-8004-abe25de5663f.png)
![image](https://user-images.githubusercontent.com/61272141/117010314-f81f6b00-acec-11eb-8434-5c17844dfd44.png)

### Componentes electrónicos
El vehículo esta compuesto por diversos componentes electrónicos que se detallarán a continuación. Cabe remarcar que algunos de ellos pueden verse variados debido al problema actual de abastecimiento.

#### Arduino
En primer lugar encontramos el arduino. Esta es la placa principal del proyecto y la encargada de coordinar el resto de componentes/sensores que constituyen el prototipo. 
En nuestro caso estamos empleando ELEGOO UNO R3, es una placa electrónica de alta calidad 100% funcional y compatible con Arduino IDE.
ELEGOO UNO R3 usa un ATMEGA16U2 como Chip de interfaz serie y un ATmega328P como microcontrolador haciéndolo más rápido en las transferencias y almacenamiento de datos y con más tienda de memoria. Soporta entrade de 5v USB y también 7v – 12v.
Incluye un fusible reseteable PTC que puede proteger ls placa de cortocircuitos causados por errores de conexión.
ELEGOO UNO R3 coloca pines SDA y SCL junto al AREF. Además, hay dos pasadores colocados cerca del pasador RESET. Uno es el IOREF que permite que los blindajes se adapten al voltaje provisto desde la placa y el otro está reservado para propósitos futuros. El ELEGOO R3 funciona con todos los escudos existentes y puede adaptarse a los nuevos escudos que utilizan estos pines adicionales.

Caracteristicas:

* Microcontrolador ATmega328P

* Voltaje de entrada: 7-12V

* 5V de corriente eléctrica: 500MA

* Corriente eléctrica 3.3V: 50MA

* 14 pines de I/O digitales (6 salidas PWM)

* 8 entradas analógicas

* Memoria Flash de 32k

* 16Mhz Clock Speed
![image](https://user-images.githubusercontent.com/61272141/117012393-2f8f1700-acef-11eb-97a6-3ca5477210dc.png)

#### L298N
Es un driver dual basado en el chip L298N. Permite controlar dos motores de corriente continua (DC) o un motor bipolar. Cuenta, como la mayoría de los componentes, con sistemas de seguridad y diodos de protección, encargados de impedir que cargas superiores a las soportadas circulen por el componente. Incluye también un regulador de tipo LM7805, encargado de alimentar la parte lógica del módulo con 5v constantes. El módulo cuenta con cuatro salidas para los motores (OUT 1, OUT 2, OUT 3, OUT 4) a las cuales puedes conectar dos motores DC con sus respectivos positivos y negativos. Tras estos encontramos los pines de control. Se pueden dividir en pines de control de módulo ( IN1, IN2, IN3, IN4) y pines ENA y ENB. Estos segundos se conectaran al Arduino para variar la velocidad de los motores mediante la programación, o bien se les colocará un jumper de alimentación, de forma que la velocidad no se podrá modificar. En cuanto a la alimentación, encontramos tres pines, +12v, GND, +5v. Gracias al regulador LM7805 integrado, encontramos dos posibles métodos de conexión:

* Con el jumper activado. Se podrán conectar voltajes de entre 6v y 12v al pin +12v. Como el jumper se encuentra activo, en el pin +5v obtendremos 5v de salida, que utilizaremos para alimentar el Arduino.
* Con el jumper desactivado. Se podrán conectar voltajes al pin +12v de entre 12v y 35v. Pero, a diferencia del método anterior, tendremos que alimentar la parte lógica del      módulo conectándole 5v externos adicionales a través del pin +5v.
![image](https://user-images.githubusercontent.com/61272141/117013065-cf4ca500-acef-11eb-9b72-57aa7cf134b2.png)




