# taller2_ME

Los que vieron modelos con Astaiza sabrán que este fue un código que realizamos con él. :v

## Instrucciones:

* Compile usando comando **make**, con windows o mac se joden :v (Es broma, se puede instalar make de forma limitada en esos sistemas).
  * Para usar Makefile en Windows, instalar Chocolatey con Powershell a través del comando `Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))` y luego usar el comando `choco install make`
  * Para usar Makefile en Mac, instalar brew con el comando `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"` y luego ejecutar el comando `brew install make`
* Ejecute con **./programa.out param1 param2 param3**
* El programa requiere **param1 param2 y param3** como parametros del **programa.out** como entrada y genera **_result.txt_**

### Uso de script de python

* Puede usar **ejecuciones.py** para ejecutar multiples veces **programa.out**
* El script de python requiere que esté en la misma ruta un archivo **param.csv** de tamaño _nx3_ para _n_ ejecuciones del mismo **con limitador ";"**
* Cada una de las filas del archivo **param.csv** será una ejecución de **programa.out** las salidas se acumularán en el archivo **_result.txt_**

