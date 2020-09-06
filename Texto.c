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
#include "Texto.h"


struct Texto{
	size_t longitud;
	wchar_t memoria[];
};

static const size_t TEXTO_LONGITUD = sizeof(struct Texto) + sizeof(wchar_t);

Texto TextoNuevo(const size_t longitud)
{
	TerminarProgramaSi(longitud == 0);

	Texto texto = calloc(longitud, TEXTO_LONGITUD);

	TerminarProgramaSi(texto == NULL);

	texto->longitud = longitud;

	return texto;
}

wchar_t TextoEsLetra(const Texto texto, const size_t posision)
{
	return iswalpha(texto->memoria[posision]) ?
					texto->memoria[posision] :
					TEXTO_NULO;
}

wchar_t TextoEsDigito(const Texto texto, const size_t posision)
{
	return iswdigit(texto->memoria[posision]) ?
					texto->memoria[posision]	:
					TEXTO_NULO;
}

ssize_t TextoContieneLetra(const Texto texto)
{
	for (size_t i = 0; i < texto->longitud; i++)
		Comprobar(TextoEsLetra(texto, i), return (ssize_t)i);

	return -1;
}


ssize_t TextoContieneDigito(const Texto texto)
{
	for (size_t i = 0; i < texto->longitud; i++)
		Comprobar(TextoEsDigito(texto, i), return (ssize_t)i);

	return -1;
}

bool TextoCopiar(Texto destino, const Texto origen)
{
	const bool origen_mayor = (origen->longitud > destino->longitud);

	ComprobarInformar(origen_mayor, return false,
			"El tamaño del texto de origen es mayor que el del destino.\n");

	memcpy(destino, origen, TEXTO_LONGITUD * origen->longitud);

	return true;
}

void TextoAsignarLongitud(Texto texto, const size_t longitud)
{
    texto->longitud = longitud;
}

TextoMemoria TextoObtenerMemoria(const Texto texto)
{
    return texto->memoria;
}

size_t TextoObtenerLongitud(const Texto texto)
{
    return texto->longitud;
}

void TextoLiberarMemoria(Texto *texto)
{
	free(*texto);
	*texto = NULL;
}

/* vim: set ts=4 sw=4 tw=500 noet :*/
