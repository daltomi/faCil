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
#include "Terminal.h"
#include <errno.h>

static void TerminalIngresarDatos(const wchar_t * titulo, Texto * texto)
{
	char * ansi = NULL;

	TerminalMostrar(L"%ls", titulo);

	getline(&ansi, &(size_t){0}, stdin);

	/* Se copia el salto de línea('\n') inclusive, luego,
	 * se lo reemplazará con el null char('\0').
	 * */
	const size_t longitud = mbstowcs(NULL, ansi, 0);

	*texto = TextoNuevo(longitud);

    TextoMemoria memoria = TextoObtenerMemoria(*texto);

	mbstowcs(memoria, ansi, longitud);

	memoria[longitud - 1] = TEXTO_NULO;

	free(ansi);
}


Texto TerminalLeerTexto(const wchar_t * titulo)
{
	Texto texto;
	TerminalIngresarDatos (titulo, & texto);
	return texto;
}


long TerminalLeerEntero(const wchar_t * titulo)
{
	long entero;

	for(;;)
	{
		wchar_t *fin = NULL;
		Texto texto = NULL;

		TerminalIngresarDatos(titulo, &texto);
		
		errno = 0;

		entero = wcstol(TextoObtenerMemoria(texto), &fin, 10);
	
		Comprobar(!*fin && errno != ERANGE, TextoLiberarMemoria(&texto); break);

		TerminalMostrarError(L" * Error '%ls' no es un entero.\n", TextoObtenerMemoria(texto));
		
		TextoLiberarMemoria(&texto);
	}

	return entero;
}


float TerminalLeerReal(const wchar_t *titulo)
{
	float real;
	
	for(;;)
	{
		Texto texto = NULL;
		wchar_t *fin = NULL;

		TerminalIngresarDatos(titulo, &texto);

		errno = 0;

		real = wcstof(TextoObtenerMemoria(texto), &fin);

		Comprobar(!*fin && errno != ERANGE, TextoLiberarMemoria(&texto); break);

		TerminalMostrarError(L" * Error '%ls' no es un real.\n", TextoObtenerMemoria(texto));

		TextoLiberarMemoria(&texto);
	}

	return real;
}


void TerminalMostrar(const wchar_t *formato, ...)
{
	TerminarProgramaSi(formato == NULL);

	va_list lista;

	va_start(lista, formato);
	vwprintf(formato, lista);
	va_end(lista);
}


void TerminalMostrarError(const wchar_t *formato, ...)
{
	TerminarProgramaSi(formato == NULL);

	va_list lista;

	va_start(lista, formato);
	vfwprintf(stderr, formato, lista);
	va_end(lista);

}

#ifdef TEST_TERMINAL

int main(void)
{
	setlocale(LC_ALL, "");

	Texto texto = NULL;
	Texto copia = NULL;
	int entero;
	float real;

	texto	= TerminalLeerTexto(L"Ingrese un texto: ");
	copia	= TextoNuevo( TextoObtenerLongitud(texto));

	TextoAsignarLongitud(copia, 12);

	TextoCopiar(copia, texto);

	entero	= TerminalLeerEntero(L"Ingrese un entero: ");
	real	= TerminalLeerReal(L"Ingrese un real: ");

	TerminalMostrar(L"------------------------------\n");

	TerminalMostrar(L"Texto         : %ls\n", TextoObtenerMemoria(texto));
	TerminalMostrar(L"Copia Texto   : %ls\n", TextoObtenerMemoria(copia));
	TerminalMostrar(L"Entero        : %d\n", entero);
	TerminalMostrar(L"Real          : %.3f\n", real);

	TextoLiberarMemoria(&texto);
	TextoLiberarMemoria(&copia);

	return EXIT_SUCCESS;
}
#elif TEST_CIFRADO
#include "tests/cifrado_cesar.c"
#elif TEST_FRECUENCIA
#include "tests/frecuencia.c"
#else
#error "No se indico el tipo de ejemplo a compilar."
#endif

