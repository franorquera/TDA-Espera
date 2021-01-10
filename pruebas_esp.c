#include "espera.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void prueba_crear_espera() {
    esp_t* esp = espera_crear(strcmp, NULL);
    print_test("Se puede crear la espera", esp);
    print_test("Prueba esp la cantidad de elementos es 0", cantidad_espera(esp) == 0);
    print_test("Prueba esp la cantidad de elementos urgentes es 0", cantidad_urgencia(esp) == 0);
    print_test("Prueba esp la cantidad de elementos regulares es 0", cantidad_regular(esp) == 0);

    espera_destruir(esp);

}

static void prueba_guardar_urgente() {
    esp_t* esp = espera_crear(strcmp, NULL);
    
    char *clave1 = "A";
    char *clave2 = "B";
    char *clave3 = "C";

    print_test("Se puede crear la espera", esp);
    print_test("Prueba esp insertar clave1", guardar_urgente(esp, clave1));
    print_test("Prueba esp insertar clave2", guardar_urgente(esp, clave2));
    print_test("Prueba esp insertar clave3", guardar_urgente(esp, clave3));
    print_test("Prueba esp la cantidad de elementos es 3", cantidad_espera(esp) == 3);
    print_test("Prueba esp la cantidad de elementos urgentes es 3", cantidad_urgencia(esp) == 3);
    print_test("Prueba esp la cantidad de elementos regulares es 0", cantidad_regular(esp) == 0);

    print_test("Prueba esp retirar clave1", retirar_urgente(esp) == clave1);
    print_test("Prueba esp retirar clave2", retirar_urgente(esp) == clave2);
    print_test("Prueba esp retirar clave3", retirar_urgente(esp) == clave3);
    print_test("Prueba esp la cantidad de elementos es 0", cantidad_espera(esp) == 0);
    print_test("Prueba esp la cantidad de elementos urgentes es 0", cantidad_urgencia(esp) == 0);
    print_test("Prueba esp la cantidad de elementos regulares es 0", cantidad_regular(esp) == 0);

    espera_destruir(esp);
}

static void prueba_guardar_regular() {
    esp_t* esp = espera_crear(strcmp, NULL);

    char *clave1 = "A", *valor1 = "guau";
    char *clave2 = "B", *valor2 = "miau";
    char *clave3 = "C", *valor3 = "mu";

    print_test("Se puede crear la espera", esp);
    print_test("Prueba esp insertar clave1", guardar_regular(esp, clave1, valor1));
    print_test("Prueba esp insertar clave2", guardar_regular(esp, clave2, valor2));
    print_test("Prueba esp insertar clave3", guardar_regular(esp, clave3, valor3));
    print_test("Prueba esp la cantidad de elementos es 3", cantidad_espera(esp) == 3);
    print_test("Prueba esp la cantidad de elementos urgentes es 0", cantidad_urgencia(esp) == 0);
    print_test("Prueba esp la cantidad de elementos regulares es 3", cantidad_regular(esp) == 3);

    print_test("Prueba esp retirar clave1", retirar_regular(esp, clave1) == valor1);
    print_test("Prueba esp retirar clave2", retirar_regular(esp, clave2) == valor2);
    print_test("Prueba esp retirar clave3", retirar_regular(esp, clave3) == valor3);
    print_test("Prueba esp la cantidad de elementos es 0", cantidad_espera(esp) == 0);
    print_test("Prueba esp la cantidad de elementos urgentes es 0", cantidad_urgencia(esp) == 0);
    print_test("Prueba esp la cantidad de elementos regulares es 0", cantidad_regular(esp) == 0);

    espera_destruir(esp);
}

static void prueba_esp_regular_remplazar() {
    esp_t* esp = espera_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    print_test("Se puede crear la espera", esp);
    print_test("Prueba esp insertar clave1", guardar_regular(esp, clave1, valor1a));
    print_test("Prueba esp obtener clave1 es valor1a", obtener_regular(esp, clave1) == valor1a);
    print_test("Prueba esp insertar clave2", guardar_regular(esp, clave2, valor2a));
    print_test("Prueba esp obtener clave2 es valor2a", obtener_regular(esp, clave2) == valor2a);
    print_test("Prueba esp la cantidad de elementos es 0", cantidad_espera(esp) == 2);

    print_test("Prueba esp insertar clave1 con otro valor", guardar_regular(esp, clave1, valor1b));
    print_test("Prueba esp obtener clave1 es valor1b", obtener_regular(esp, clave1) == valor1b);
    print_test("Prueba esp insertar clave2 con otro valor", guardar_regular(esp, clave2, valor2b));
    print_test("Prueba esp obtener clave2 es valor2b", obtener_regular(esp, clave2) == valor2b);
    print_test("Prueba esp la cantidad de elementos es 2", cantidad_espera(esp) == 2);

    print_test("Prueba esp retirar clave1", retirar_regular(esp, clave1) == valor1b);
    free(valor1b);

    print_test("Prueba esp la cantidad de elementos es 1", cantidad_espera(esp) == 1);

    /* Se destruye la esp (se debe liberar lo que quedó dentro) */
    espera_destruir(esp);
}

void pruebas_espera() {
    prueba_crear_espera();
    prueba_guardar_urgente();
    prueba_guardar_regular();
    prueba_esp_regular_remplazar();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_espera();
    return failure_count() > 0;
}

#endif