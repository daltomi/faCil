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
#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <memory.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <stdarg.h>

#include "Texto.h"

long TerminalLeerEntero(const wchar_t *titulo);

float TerminalLeerReal(const wchar_t *titulo);

Texto TerminalLeerTexto(const wchar_t *titulo);

void TerminalMostrar(const wchar_t *formato, ...);

void TerminalMostrarError(const wchar_t *formato, ...);

#endif	

/* vim: set ts=4 sw=4 tw=500 noet :*/
