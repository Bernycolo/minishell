- Fallo en PIPE final -> genera comando -> **SOLUCIONADO**
- Fallo en redirección sin fichero -> genera comando en lugar de error en parseo -> **SOLUCIONADO**

- Fallo en HEREDOC con comillas en el delimitador -> no elimina las comillas

- `ls; echo hola` -> no da error y lo tokeniza ¿es así? -> **ES CORRECTO** DEBE FALLAR AL BUSCAR EL COMANDO `ls;`
- `echo hola\ mundo` -> lo tokeniza como caracteres normales ¿es así? -> **ES CORRECTO**
- `ls && echo hola` -> lo tokeniza como caracteres normales, ¿debe dar error de sintaxis? -> **PARA QUE LO EJECUTE DEBE ESTAR EN MODO BONUS**
- `(ls)` -> lo tokeniza, ¿debe dar error de sintaxis? -> ES CORRECTO, LO DEBE TOKENIZAR PARA BUSCAR EL COMANDO `(ls)`, **PARA QUE LO EJECUTE DEBE ESTAR EN MODO BONUS**
