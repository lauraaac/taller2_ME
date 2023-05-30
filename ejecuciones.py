import csv
import subprocess

# Ejecutar el comando make
try:
    subprocess.run(["make", "clean"], check=True)
    subprocess.run(["make"], check=True)
    print("Make ejecutado exitosamente")
except subprocess.CalledProcessError as e:
    print("Error al ejecutar make:", e)

# Ruta al ejecutable de C++
ejecutable = "./bin/programa.exe"

# Ruta al archivo CSV
archivo_csv = "param.csv"

# Leer el archivo CSV
with open(archivo_csv, 'r') as archivo:
    lector_csv = csv.reader(archivo, delimiter=';')

    # Iterar sobre las filas del archivo CSV
    for fila in lector_csv:
        # Extraer los valores de cada columna
        columna1, columna2, columna3 = fila

        # Llamar al ejecutable de C++ con los argumentos
        try:
            subprocess.run([ejecutable, columna1, columna2, columna3], check=True)
            print("Programa de C++ ejecutado exitosamente para la fila:", fila)
        except subprocess.CalledProcessError as e:
            print("Error al ejecutar el programa de C++ para la fila:", fila)
