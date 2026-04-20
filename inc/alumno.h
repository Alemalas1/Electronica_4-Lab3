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

#ifndef ALUMNO_H_
#define ALUMNO_H_

/** @file alumno.h
 ** @brief Definición de la estructura de datos y funciones para gestionar
 *alumnos
 **/

/* === Headers files inclusions
 * ====================================================================================
 */

#include <stdint.h>

/* === Header for C++ compatibility
 * ================================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions
 * ===================================================================================
 */

/* === Public data type declarations
 * ===============================================================================
 */

/**
 * @brief Estructura opaca para representar a un Alumno.
 * El usuario del módulo no conoce los campos internos (encapsulamiento).
 */
typedef struct Alumno_t * Alumno;

/* === Public variable declarations
 * ================================================================================
 */

/* === Public function declarations
 * ================================================================================
 */

/**
 * @brief Crea una nueva instancia de Alumno.
 * * @param nombre Puntero a la cadena con el nombre del alumno.
 * @param apellido Puntero a la cadena con el apellido del alumno.
 * @param documento Número de documento del alumno.
 * @return Alumno Puntero a la estructura creada o NULL si no hay memoria.
 */
Alumno AlumnoCrear(const char * nombre, const char * apellido, uint32_t documento);

/**
 * @brief Serializa los datos del alumno en formato JSON.
 * * @param alumno Puntero a la instancia del alumno a serializar.
 * @param resultado Buffer donde se almacenará la cadena JSON resultante.
 * @param tamaño Espacio total disponible en el buffer resultado.
 * @return int Cantidad de caracteres escritos o -1 en caso de error de espacio.
 */
int AlumnoSerializar(Alumno alumno, char * resultado, int tamaño);

/* === End of conditional blocks
 * ===================================================================================
 */

#ifdef __cplusplus
}
#endif

#endif /* ALUMNO_H_ */