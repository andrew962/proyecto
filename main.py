import numpy as np
import sys

# Método de Gauss-Seidel
def gauss_seidel():
    datos = input_datos()
    print(datos.get('a'), datos.get('b'))
    A = datos.get('a')
    B = datos.get('b')
    X0 = datos.get('x')

    tolera = 0.00001
    iteramax = 100

    # PROCEDIMIENTO

    # Gauss-Seidel
    tamano = np.shape(A)
    n = tamano[0]
    m = tamano[1]
    #  valores iniciales
    X = np.copy(X0)
    diferencia = np.ones(n, dtype=float)
    errado = 2 * tolera

    itera = 0
    while not (errado <= tolera or itera > iteramax):
        # por fila
        for i in range(0, n, 1):
            # por columna
            suma = 0
            for j in range(0, m, 1):
                # excepto diagonal de A
                if (i != j):
                    suma = suma - A[i, j] * X[j]

            nuevo = (B[i] + suma) / A[i, i]
            diferencia[i] = np.abs(nuevo - X[i])
            X[i] = nuevo
        errado = np.max(diferencia)
        itera = itera + 1

    # Respuesta X en columna
    X = np.transpose([X])

    # revisa si NO converge
    if (itera > iteramax):
        X = 0
    # revisa respuesta
    verifica = np.dot(A, X)

    # SALIDA
    print('respuesta X: ')
    print(X)
    # print('verificar A.X=B: ')
    # print(verifica)
    menu()

# Método de Gauss
def gauss():

    n = int(input('Tamaño de matriz: '))
    a = np.zeros((n, n + 1))
    x = np.zeros(n)
    print('Ingrese los coeficientes de la matriz:')
    for i in range(n):
        for j in range(n + 1):
            a[i][j] = float(input('a[' + str(i) + '][' + str(j) + ']='))
    print(a)
    # Applying Gauss Elimination
    for i in range(n):
        if a[i][i] == 0.0:
            sys.exit('Divicion entre 0.')

        for j in range(i + 1, n):
            ratio = a[j][i] / a[i][i]

            for k in range(n + 1):
                a[j][k] = a[j][k] - ratio * a[i][k]

    # Back Substitution
    x[n - 1] = a[n - 1][n] / a[n - 1][n - 1]

    for i in range(n - 2, -1, -1):
        x[i] = a[i][n]

        for j in range(i + 1, n):
            x[i] = x[i] - a[i][j] * x[j]

        x[i] = x[i] / a[i][i]

    # Displaying solution
    print('\nSolucion requerida es: ')
    for i in range(n):
        print('X%d = %0.2f' % (i, x[i]), end='\t')

    menu()

# Método de Jacobi
def jacobi():
    datos = input_datos()
    print(datos.get('a'), datos.get('b'))
    A = datos.get('a')
    B = datos.get('b')
    X = datos.get('x')
    tamano = np.shape(A)
    print(tamano)
    n = tamano[0]
    m = tamano[1]
    diferencia = np.ones(n, dtype=float)
    errado = np.max(diferencia)
    xnuevo = np.copy(X)

    itera = 0
    iteramax = 100
    tolera = 1e-4
    print(itera, X)
    while not (errado <= tolera or itera > iteramax):

        for i in range(0, n, 1):
            nuevo = B[i]
            for j in range(0, m, 1):
                if (i != j):  # excepto diagonal de A
                    nuevo = nuevo - A[i, j] * X[j]
            nuevo = nuevo / A[i, i]
            # print(round(nuevo, 2))
            xnuevo[i] = nuevo
        diferencia = np.abs(xnuevo - X)
        errado = np.max(diferencia)
        print(itera, xnuevo)
        X = np.copy(xnuevo)
        itera = itera + 1
    # Vector en columna
    X = np.transpose([X])

    # No converge
    if (itera > iteramax):
        X = itera

    ncond = np.linalg.cond(A)
    # respuesta = jacobi(A, B, tolera, X)
    verifica = np.dot(A, X)
    # SALIDA
    print('numero de condicion:', ncond)
    print('respuesta con Jacobi')
    print(X)
    # print('verificando:')
    # print(verifica)

    menu()

# Introduccion de datos
def input_datos():
    # Tamaño de matriz
    n = int(input('Tamaño de matriz: '))
    a = np.zeros((n, n))
    print('Ingrese los coeficientes de la matriz:')
    for i in range(n):
        # print(i)
        for j in range(n):
            a[i][j] = float(input('a[' + str(i + 1) + '][' + str(j + 1) + ']='))
    print(a)
    # Valores independientes o constantes
    print('Valores independientes o constantes:')
    b = np.zeros(n)
    for i in range(n):
        b[i] = float(input('b[' + str(i + 1) + ']='))
    print(b)
    # Valores iniciales
    print('Valores iniciales:')
    x = np.zeros(n)
    for i in range(n):
        x[i] = float(input('x[' + str(i + 1) + ']='))
    print(x)
    r = dict();
    r['a'] = a
    r['b'] = b
    r['x'] = x
    return r

#Menu
def menu():
    print("\nMenu")
    print("1 - Gauss")
    print("2 - Seidel")
    print("3 - Jacobi")
    print("4 - Salir")
    m = int(input("Elija una opcion (número): "))
    if m == 1:
        gauss()
    elif  m == 2:
        gauss_seidel()
    elif  m == 3:
        jacobi()
    elif  m == 4:
        # datos = input_datos()
        # print(datos.get('a'),datos.get('b'))
        sys.exit()

# Ejecucion principal
if __name__ == '__main__':
    menu()
