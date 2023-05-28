# taller2_ME

Los que vieron modelos con Astaiza sabrán que este fue un código que realizamos con él. :v

## Instrucciones:

* Compile usando comando **make**, con windows o mac se joden :v (Es broma, se puede instalar make de forma limitada en esos sistemas).
  * Para usar Makefile en Windows, instalar Chocolatey con Powershell a través del comando `Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))` y luego usar el comando `choco install make`
  * Para usar Makefile en Mac, instalar brew con el comando `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"` y luego ejecutar el comando `brew install make`
* Ejecute con `/programa.out param1 param2 param3 param4` donde estos parametros son **media_entre_llegadas**, **media_atencion**, **num_esperas_requerido** y **num_servidores** respectivamente. 
* El programa requiere **param1 param2, param3 y param4** como parametros del **programa.out** como entrada, genera **_result.txt_** y **_result.csv_** como salidas.

### Uso de script de python

* Puede usar **ejecuciones.py** para ejecutar multiples veces **programa.out**
* El script de python requiere que esté en la misma ruta un archivo **param.csv** de tamaño _nx4_ para _n_ ejecuciones del mismo **con limitador ";"**
* Cada una de las filas del archivo **param.csv** será una ejecución de **programa.out** las salidas se acumularán en el archivo **_result.txt_** y **_result.csv_**.
