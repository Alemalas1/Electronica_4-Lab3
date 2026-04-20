/*********************************************************************************************************************
Copyright 2016-2026, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/

Copyright 2016-2026, Alejandro Malaspina <alejandrotrc1@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file main.c
 ** @brief Programa principal para la prueba del TDA Alumno.
 ** @details Este programa funciona como punto de entrada para demostrar el uso
 ** del módulo Alumno siguiendo el patrón ADT. El main no conoce la estructura
 ** interna: solo utiliza las funciones públicas AlumnoCrear y AlumnoSerializar.
 **/

/* === Headers files inclusions ================================================================ */

#include "alumno.h"
#include <stdio.h>

/* === Macros definitions ====================================================================== */

/**
 * @brief Tamaño máximo en bytes del buffer utilizado para almacenar la cadena JSON.
 */
#define TAMANO_BUFFER 128

/* === Public function implementation ========================================================== */

/**
 * @brief Función principal del programa.
 * @details Crea una instancia de Alumno usando AlumnoCrear, serializa sus datos
 * a formato JSON con AlumnoSerializar e imprime el resultado por pantalla.
 * En ningún momento accede directamente a los campos de la estructura,
 * respetando el encapsulamiento del patrón ADT.
 *
 * @return int Retorna 0 si la ejecución fue exitosa, o -1 en caso de error.
 */
int main(void) {
    char json_resultado[TAMANO_BUFFER];
    int bytes_escritos;

    printf("Iniciando prueba del modulo Alumno...\n");
    printf("--------------------------------------\n");

    /* Creación de la instancia opaca del alumno.
     * El main no sabe ni le importa cómo está implementada la estructura interna. */
    Alumno mi_alumno = AlumnoCrear("Alejandro", "Malaspina", 41650146);

    if (mi_alumno == NULL) {
        printf("ERROR: No se pudo crear el alumno (sin memoria disponible).\n");
        return -1;
    }
    printf("Alumno creado exitosamente en memoria.\n");

    /* Serialización a formato JSON */
    bytes_escritos = AlumnoSerializar(mi_alumno, json_resultado, TAMANO_BUFFER);

    if (bytes_escritos >= 0) {
        printf("Serializacion exitosa. Se escribieron %d bytes.\n", bytes_escritos);
        printf("JSON resultante:\n%s\n", json_resultado);
    } else {
        printf("ERROR: El buffer de %d bytes es insuficiente para el JSON.\n", TAMANO_BUFFER);
        return -1;
    }

    printf("--------------------------------------\n");
    printf("Fin del programa.\n");

    return 0;
}

/* === End of documentation ==================================================================== */