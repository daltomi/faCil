/*
 * GCC c99
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Terminal.h"

static const size_t DIGITOS = 255;

#define ImprimirLetras(letras) \
		Imprimir(letras, L"Letra %lc, %d veces, %2.1f%% \n", L'a')


#define ImprimirNumeros(numeros) \
		Imprimir(numeros, L"Numero %lc, %d veces, %2.1f%% \n", L'0')


void AsignarLetrasNumeros(const Texto texto,
                          Texto letras,
                          Texto numeros)
{

	/*
	* Reutilizar la variable miembro 'longitud' como
	* contador de ocurrencias del caracter.
	* */
	TextoAsignarLongitud(letras, 0);
    TextoAsignarLongitud(numeros, 0);

    TextoMemoria m_letras = TextoObtenerMemoria(letras);
	size_t l_letras = TextoObtenerLongitud(letras);

    TextoMemoria m_numeros = TextoObtenerMemoria(numeros);
	size_t l_numeros = TextoObtenerLongitud(numeros);

    const size_t longitud = TextoObtenerLongitud(texto);

	for (size_t i = 0; i < longitud;  i++) {

		wchar_t letra = TextoEsLetra (texto, i); 
		
		if (letra) {

			m_letras[(letra - L'a')]++;
			TextoAsignarLongitud(letras, ++l_letras);

		} else if ( (letra = TextoEsDigito (texto, i))) {
			m_numeros[(letra - L'0')] ++;
			TextoAsignarLongitud(numeros, ++l_numeros);
		}
	}
}

void Imprimir (	const Texto texto,
				const wchar_t * formato,
				const wchar_t codigo) {
	
	const size_t longitud = TextoObtenerLongitud(texto);
	TextoMemoria m_texto = TextoObtenerMemoria(texto);

	for (size_t i = 0; longitud && i < DIGITOS; i++) {
		if (m_texto[i] != L'\0') {
			const float porcentaje = (float)((m_texto[i] * 100 ) / longitud);
			const wchar_t letra = i + codigo;
			TerminalMostrar (formato, letra, m_texto[i], porcentaje);
		}
	}
}

int main () {
	
	setlocale (LC_ALL, "");

	Texto usuario = NULL;
	Texto letras = TextoNuevo (DIGITOS);
	Texto numeros = TextoNuevo (DIGITOS);

	usuario = TerminalLeerTexto (L"Ingrese una línea de texto: ");

	AsignarLetrasNumeros (usuario, letras, numeros);

	ImprimirLetras (letras);
	ImprimirNumeros (numeros);

	TextoLiberarMemoria (& usuario);
	TextoLiberarMemoria (& letras);
	TextoLiberarMemoria (& numeros);
}

/* vim: set ts=4 sw=4 tw=500 noet :*/
