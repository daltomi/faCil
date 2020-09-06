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
#ifndef ERROR_H
#define ERROR_H

#define __GNU_SOURCE__ // asprintf
#include <stdio.h>

#include <syslog.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define Registrar(...) {                            \
    char * msg = NULL;                              \
    awsprintf (&msg, __VA_ARGS__);                   \
    syslog (LOG_ERR, "@Func:%s #Line:%d $Msg:%s",   \
            __func__ , __LINE__ , msg);             \
    free (msg);                                     \
}

#define Informar(...) {								\
    char * msg = NULL;								\
    asprintf (&msg, __VA_ARGS__);					\
    fwprintf(stderr, L"@Func:%s #Line:%d $Msg:%s",	\
            __func__ , __LINE__ , msg);				\
    free (msg);										\
}

#define Comprobar(valor, accion) {		            \
    if ((valor)) {									\
        accion;                                     \
    }                                               \
}

#define ComprobarRegistrar(valor, accion, ...) {    \
    if ((valor)) {									\
        Registrar(__VA_ARGS__);                     \
        accion;                                     \
    }                                               \
}

#define ComprobarInformar(valor, accion, ...) {     \
    if ((valor)) {									\
        Informar(__VA_ARGS__);						\
        accion;                                     \
    }                                               \
}

#define TerminarProgramaSi(valor) {					\
	assert(!(valor));								\
}

#endif

/* vim: set ts=4 sw=4 tw=500 noet :*/
