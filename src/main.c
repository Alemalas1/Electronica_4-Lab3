/*********************************************************************************************************************
Copyright 2016-2026, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología
Universidad Nacional de Tucuman
http://www.microprocesadores.unt.edu.ar/

Copyright 2016-2026, Esteban Volentini <evolentini@herrera.unt.edu.ar>

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
 ** @brief Programa principal para la prueba del TDA Alumno
 **/

/* === Headers files inclusions
 * ================================================================ */

#include "alumno.h"
#include <stdio.h>

/* === Macros definitions
 * ====================================================================== */

/**
 * @brief Tamaño máximo en bytes del buffer utilizado para almacenar la cadena
 * JSON
 */
#define TAMANO_BUFFER 128

/* === Private data type declarations
 * ========================================================== */

/* === Private function declarations
 * =========================================================== */

/* === Private variable definitions
 * ============================================================ */

/* === Public variable definition
 * ============================================================= */

/* === Private function definitions
 * ============================================================ */

/* === Public function implementation
 * ========================================================== */

/**
 * @brief Función principal del programa
 * @details Prueba la funcionalidad del módulo Alumno. Crea una instancia de
 * Alumno, invoca la serialización a formato JSON y muestra el resultado en la
 * salida estándar. Controla posibles errores de falta de memoria y
 * desbordamiento de buffer.
 * * @return int Retorna 0 si la ejecución fue exitosa, o -1 en caso de error.
 */
int main(void) {
    char json_resultado[TAMANO_BUFFER];
    int bytes_escritos;

    printf("Iniciando prueba del modulo Alumno...\n");
    printf("--------------------------------------\n");

    // Creación de la instancia opaca del alumno
    Alumno mi_alumno = AlumnoCrear("Alejandro", "Perez", 41650146);

    // Verificación de recursos (Heap o estante ocupado)
    if (mi_alumno == NULL) {
        printf("ERROR: No se pudo crear el alumno (Falta de memoria o estante "
               "ocupado).\n");
        return -1;
    }
    printf("Alumno creado exitosamente en memoria.\n");

    // Llamada a la función de serialización
    bytes_escritos = AlumnoSerializar(mi_alumno, json_resultado, TAMANO_BUFFER);

    // Verificación de truncamiento y muestra de resultados
    if (bytes_escritos >= 0) {
        printf("Serializacion exitosa. Se escribieron %d bytes.\n", bytes_escritos);
        printf("JSON resultante:\n");
        printf("%s\n", json_resultado);
    } else {
        printf("ERROR: El buffer de %d bytes es demasiado pequeno para el JSON.\n", TAMANO_BUFFER);
    }

    printf("--------------------------------------\n");
    printf("Fin del programa.\n");

    return 0;
}

/* === End of documentation
 * ==================================================================== */