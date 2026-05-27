# Arquitectura inicial de minishell

## 1. Objetivo del proyecto

Implementar un shell mínimo compatible con bash en los casos requeridos por el subject, con:

- Soporte de comandos externos
- Builtins
- Pipes
- Redirecciones
- Variables de entorno
- Manejo correcto de señales y exit status

La arquitectura se diseña para ser **modular, defendible y extensible**.

---

## 2. Módulos principales

### 2.1. Core / Minishell

**Responsabilidades:**

- Bucle principal del shell
- Mostrar el prompt
- Leer la línea con `readline`
- Gestionar el estado global (exit status, entorno, etc.)
- Coordinar parser → executor

**Ficheros:**

- `src/minishell.c`
- `include/minishell.h`

---

### 2.2. Parser

**Responsabilidades:**

- Tokenizar la línea de entrada
- Clasificar tokens (palabras, pipes, redirecciones, etc.)
- Gestionar comillas
- Expandir variables de entorno
- Validar sintaxis básica
- Construir la estructura final de comandos (`t_cmd`)

**Ficheros:**

- `src/parser/*.c`
- `include/parser.h`

---

### 2.3. Executor

**Responsabilidades:**

- Recibir una lista de `t_cmd`
- Crear pipes cuando sea necesario
- Aplicar redirecciones
- Ejecutar builtins o comandos externos
- Gestionar `fork`, `execve`, `wait`, exit status

**Ficheros:**

- `src/executor/*.c`
- `include/executor.h`

---

### 2.4. Env (entorno)

**Responsabilidades:**

- Representar el entorno como estructura interna
- Obtener, setear y eliminar variables de entorno
- Sincronizar con `envp` cuando sea necesario
- Soportar `export`, `unset`, etc.

**Ficheros:**

- `src/env/*.c`
- `include/env.h`

---

### 2.5. Signals

**Responsabilidades:**

- Configurar el comportamiento de `SIGINT`, `SIGQUIT`, etc.
- Diferenciar comportamiento en:
  - prompt
  - ejecución de comandos
  - heredocs (más adelante)
- Integrarse correctamente con `readline`

**Ficheros:**

- `src/signals/*.c`
- `include/signals.h`

---

## 3. Flujo general de ejecución

```text
input (línea de usuario)
    ↓
tokenizer (parser léxico)
    ↓
tokens clasificados (t_token)
    ↓
parser semántico (con comillas, expansión, redirecciones)
    ↓
lista de comandos (t_cmd)
    ↓
executor
    ↓
procesos / builtins / redirecciones / pipes
    ↓
exit status actualizado
```
