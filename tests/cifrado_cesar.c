/*
 * GCC c99
 * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>

#include "../Terminal.h"

#define Cifrar(mensaje, llave) CifradoCesar(mensaje, llave, true)

#define Descifrar(mensaje, llave) CifradoCesar(mensaje, llave, false)

TextoMemoria CifradoCesar(Texto mensaje,
					const unsigned int llave,
					bool cifrar)
{

	static const wchar_t * espaniol = L" áéíóúabcdefghijklmnñopqrstuvwxyz.?";
	static const size_t letras = 35;

	const size_t l_mensaje  = TextoObtenerLongitud(mensaje);
	TextoMemoria m_mensaje = TextoObtenerMemoria(mensaje);

	for (size_t i = 0; i < l_mensaje; i++) {

		Comprobar(TextoEsDigito(mensaje, i), continue);

		const wchar_t * letra = wcschr(espaniol, m_mensaje[i]);

		if (cifrar) {
			m_mensaje[i] = espaniol [(letra - espaniol + llave) % letras];
		} else {
			m_mensaje[i] = espaniol [(letra - espaniol - llave + letras) % letras];
		}
	}

	return m_mensaje;
}


int main ()  {

	setlocale (LC_ALL, "");

	const unsigned int llave = 13;

	Texto mensaje = TerminalLeerTexto(L"Ingrese el mensaje a cifrar: ");

	TerminalMostrar(L"Cifrado: %ls\n", Cifrar(mensaje, llave));

	TerminalMostrar(L"Descifrado: %ls\n", Descifrar(mensaje, llave));

	TextoLiberarMemoria(&mensaje);
}

/* vim: set ts=4 sw=4 tw=500 noet :*/
