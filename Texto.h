/*
 *  Copyright © 2020 daltomi <daltomi@disroot.org>
 *  
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

/* GCC c99 */

/*
 * Nota: para testear éste módulo ver Terminal.c
 * */
#ifndef TEXTO_H
#define TEXTO_H

#include <wctype.h>
#include <wchar.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Error.h"

typedef wchar_t *TextoMemoria;

typedef struct Texto *Texto;

static const wchar_t TEXTO_NULO = L'\0';

Texto TextoNuevo(const size_t longitud);

void TextoAsignarLongitud(Texto texto, const size_t longitud);

void TextoLiberarMemoria(Texto *texto);

size_t TextoObtenerLongitud(const Texto texto);

bool TextoCopiar(Texto destino, const Texto origen);

TextoMemoria TextoObtenerMemoria(const Texto texto);

wchar_t TextoEsLetra(const Texto texto, const size_t posision);

wchar_t TextoEsDigito(const Texto texto, const size_t posision);

ssize_t TextoContieneLetra(const Texto texto);

ssize_t TextoContieneDigito(const Texto texto);
#endif

/* vim: set ts=4 sw=4 tw=500 noet :*/
