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
 ** @brief Implementación del TDA Alumno con soporte de memoria estática y dinámica.
 **/

/* === Headers files inclusions
 * ================================================================ */

#include "alumno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === Macros definitions
 * ====================================================================== */

#ifdef MODO_ESTATICO
/**
 * @brief Tamaño máximo del pool estático de alumnos.
 */
#define MAX_ALUMNOS 10
#endif

/* === Private data type declarations
 * ========================================================== */

/**
 * @brief Atributos internos del Alumno (privados).
 * @details Esta estructura solo es visible dentro de alumno.c.
 * Ningún módulo externo puede acceder a sus campos directamente.
 */
struct Alumno_t {
    char nombre[50];    /**< Nombre del alumno */
    char apellido[50];  /**< Apellido del alumno */
    uint32_t documento; /**< Número de documento del alumno */
};

/* === Private function declarations
 * =========================================================== */

/**
 * @brief Serializa un campo de texto en formato JSON "clave":"valor".
 * @details Función interna usada exclusivamente por AlumnoSerializar.
 * Al ser static no es visible fuera de este archivo.
 *
 * @param[in]  clave     Nombre del campo JSON.
 * @param[in]  valor     Contenido del campo como cadena de texto.
 * @param[out] resultado Buffer donde se escribe el resultado.
 * @param[in]  espacio   Bytes disponibles en el buffer.
 * @return int Caracteres escritos (sin el nulo), o -1 si el espacio es insuficiente.
 */
static int SerializarTexto(const char * clave, const char * valor, char * resultado, int espacio);

/**
 * @brief Serializa un campo numérico en formato JSON "clave":valor.
 * @details Función interna usada exclusivamente por AlumnoSerializar.
 * Al ser static no es visible fuera de este archivo.
 * Los valores numéricos en JSON no llevan comillas.
 *
 * @param[in]  clave     Nombre del campo JSON.
 * @param[in]  valor     Valor entero de 32 bits a serializar.
 * @param[out] resultado Buffer donde se escribe el resultado.
 * @param[in]  espacio   Bytes disponibles en el buffer.
 * @return int Caracteres escritos (sin el nulo), o -1 si el espacio es insuficiente.
 */
static int SerializarNumero(const char * clave, uint32_t valor, char * resultado, int espacio);

/* === Private variable definitions
 * ============================================================ */

#ifdef MODO_ESTATICO
/**
 * @brief Pool estático de estructuras Alumno_t.
 */
static struct Alumno_t pool[MAX_ALUMNOS];

/**
 * @brief Índice del próximo slot disponible en el pool.
 */
static int pool_index = 0;
#endif

/* === Public variable definition
 * ============================================================= */

/* === Private function definitions
 * ============================================================ */

static int SerializarTexto(const char * clave, const char * valor, char * resultado, int espacio) {
    /* Corrección docente: debe haber espacio para al menos el terminador nulo */
    if (espacio <= 1) {
        return -1;
    }
    int escrito = snprintf(resultado, espacio, "\"%s\":\"%s\"", clave, valor);
    if ((escrito >= espacio) || (escrito < 0)) {
        return -1;
    }
    return escrito;
}

static int SerializarNumero(const char * clave, uint32_t valor, char * resultado, int espacio) {
    /* Corrección docente: debe haber espacio para al menos el terminador nulo */
    if (espacio <= 1) {
        return -1;
    }
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
    /* Asignación estática: verificar que queden slots disponibles en el pool */
    if (pool_index < MAX_ALUMNOS) {
        self = &pool[pool_index];
        pool_index++;
    }
#else
    /* Asignación dinámica: solicitar memoria al Heap */
    self = malloc(sizeof(struct Alumno_t));
#endif

    if (self != NULL) {
        /* strncpy es más seguro que strcpy: limita los bytes copiados */
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

    /* Corrección docente: espacio <= 1 para garantizar lugar al terminador nulo */
    if (espacio <= 1) {
        return -1;
    }

    /* Apertura del JSON — strncpy es más seguro que strcpy */
    strncpy(resultado, "{", espacio);
    total = 1;

    /* Campo "nombre" */
    escrito = SerializarTexto("nombre", alumno->nombre, resultado + total, espacio - total);
    if (escrito < 0) {
        return -1;
    }
    total += escrito;

    /* Separador entre campos */
    if (espacio - total <= 1) {
        return -1;
    }
    strncpy(resultado + total, ",", espacio - total);
    total += 1;

    /* Campo "apellido" */
    escrito = SerializarTexto("apellido", alumno->apellido, resultado + total, espacio - total);
    if (escrito < 0) {
        return -1;
    }
    total += escrito;

    /* Separador entre campos */
    if (espacio - total <= 1) {
        return -1;
    }
    strncpy(resultado + total, ",", espacio - total);
    total += 1;

    /* Campo "documento" */
    escrito = SerializarNumero("documento", alumno->documento, resultado + total, espacio - total);
    if (escrito < 0) {
        return -1;
    }
    total += escrito;

    /* Cierre del JSON */
    if (espacio - total <= 1) {
        return -1;
    }
    strncpy(resultado + total, "}", espacio - total);
    total += 1;

    return total;
}

/* === End of documentation
 * ==================================================================== */