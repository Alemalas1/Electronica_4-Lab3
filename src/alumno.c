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

/** @file alumno.c
 ** @brief Implementación del TDA Alumno con soporte de memoria estática y
 *dinámica
 **/

/* === Headers files inclusions
 * ================================================================ */

#include "alumno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === Macros definitions
 * ====================================================================== */

/* === Private data type declarations
 * ========================================================== */

/**
 * @brief Atributos del Alumno (Privados)
 */
struct Alumno_t {
    char apellido[50];
    char nombre[50];
    uint32_t documento;
};

/* === Private function declarations
 * =========================================================== */

/**
 * @brief Serializa un campo de texto en formato "clave":"valor"
 */
static int SerializarTexto(const char * clave, const char * valor, char * resultado, int espacio);

/**
 * @brief Serializa un campo numérico en formato "clave":valor
 */
static int SerializarNumero(const char * clave, uint32_t valor, char * resultado, int espacio);

/* === Private variable definitions
 * ============================================================ */

#ifdef MODO_ESTATICO
/**
 * @brief Instancia única para asignación estática de memoria
 */
static struct Alumno_t instancia_unica;

/**
 * @brief Bandera para controlar el uso de la instancia estática
 */

static int ocupado = 0;
#endif
/* === Public variable definition
 * ============================================================= */

/* === Private function definitions
 * ============================================================ */

static int SerializarTexto(const char * clave, const char * valor, char * resultado, int espacio) {
    int escrito = snprintf(resultado, espacio, "\"%s\":\"%s\"", clave, valor);
    if ((escrito >= espacio) || (escrito < 0)) {
        return -1;
    }
    return escrito;
}

static int SerializarNumero(const char * clave, uint32_t valor, char * resultado, int espacio) {
    int escrito = snprintf(resultado, espacio, "\"%s\":%u", clave, valor);
    if ((escrito >= espacio) || (escrito < 0)) {
        return -1;
    }
    return escrito;
}

/* === Public function implementation
 * ========================================================== */

Alumno AlumnoCrear(const char * nombre, const char * apellido, uint32_t documento) {
    Alumno self = NULL;

#ifdef MODO_ESTATICO
    if (ocupado == 0) {
        self = &instancia_unica;
        ocupado = 1;
    }
#else
    self = malloc(sizeof(struct Alumno_t));
#endif

    if (self != NULL) {
        memset(self->nombre, 0, sizeof(self->nombre));
        strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);

        memset(self->apellido, 0, sizeof(self->apellido));
        strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);

        self->documento = documento;
    }
    return self;
}

int AlumnoSerializar(Alumno alumno, char * resultado, int espacio) {
    int total = 0;
    int escrito;

    // Verificación solicitada por corrección docente: espacio <= 1
    if (espacio <= 1) {
        return -1;
    }

    // Inicialización del buffer con el carácter de apertura
    strncpy(resultado, "{", espacio);
    total = 1;

    // Serialización del campo Nombre
    escrito = SerializarTexto("nombre", alumno->nombre, resultado + total, espacio - total);
    if (escrito < 0)
        return -1;
    total += escrito;

    // Coma y Apellido
    if (total >= espacio - 1)
        return -1;
    strncat(resultado, ",", espacio - total - 1);
    total += 1;

    escrito = SerializarTexto("apellido", alumno->apellido, resultado + total, espacio - total);
    if (escrito < 0)
        return -1;
    total += escrito;

    // Coma y Documento
    if (total >= espacio - 1)
        return -1;
    strncat(resultado, ",", espacio - total - 1);
    total += 1;

    escrito = SerializarNumero("documento", alumno->documento, resultado + total, espacio - total);
    if (escrito < 0)
        return -1;
    total += escrito;

    // Llave de cierre
    if (total >= espacio - 1)
        return -1;
    strncat(resultado, "}", espacio - total - 1);
    total += 1;

    return total;
}

/* === End of documentation
 * ==================================================================== */