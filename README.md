
# Multiplicación de Matrices: Clásica vs. Por Bloques

Este repositorio contiene implementaciones de **multiplicación de matrices** utilizando dos enfoques:

- Multiplicación de matrices clásica.
- Multiplicación de matrices utilizando bloques (*blocking/tiling*).

El proyecto permite comparar el comportamiento de ambas implementaciones y analizar el impacto de la **jerarquía de memoria y la caché** mediante `Valgrind/Cachegrind`.

---

## 🛠️ 1. Compilación

Para compilar los programas se utiliza **GCC/G++** con el nivel de optimización `-O2`.

### Versión clásica

```bash
g++ -O2 multiplicacioMatricesVan.cpp -o clasica_val
````

### Versión por bloques

```bash
g++ -O2 multiplicacionMatricesXbloquesVan.cpp -o bloques_val
```

Después de la compilación se obtendrán los siguientes ejecutables:

```text
clasica_val
bloques_val
```

---

## 🚀 2. Ejecución

Ambos programas reciben parámetros mediante la línea de comandos.

### Multiplicación clásica

La versión clásica recibe:

| Parámetro | Descripción                  |
| --------- | ---------------------------- |
| `N`       | Tamaño de la matriz cuadrada |

Ejemplo con matrices de `1024 × 1024`:

```bash
./clasica_val 1024
```

### Multiplicación por bloques

La versión por bloques recibe:

| Parámetro | Descripción                  |
| --------- | ---------------------------- |
| `N`       | Tamaño de la matriz cuadrada |
| `B`       | Tamaño del bloque            |

Ejemplo con matrices de `1024 × 1024` y bloques de `16 × 16`:

```bash
./bloques_val 1024 16
```

---

## 🔬 3. Perfilado de Memoria con Cachegrind

Para analizar el comportamiento de las implementaciones respecto a la **jerarquía de memoria**, se utiliza `Valgrind` junto con la herramienta `Cachegrind`.

Cachegrind permite simular el comportamiento de las cachés y obtener información relacionada con los accesos y fallos de caché durante la ejecución.

### Requisito

Verifica que `Valgrind` esté instalado:

```bash
valgrind --version
```

En sistemas basados en Fedora, puede instalarse mediante:

```bash
sudo dnf install valgrind
```

---

## 📊 4. Experimento 1: Multiplicación Clásica

Ejecutar Cachegrind sobre la implementación clásica:

```bash
valgrind \
  --tool=cachegrind \
  --cache-sim=yes \
  --cachegrind-out-file=cachegrind.clasica.out \
  ./clasica_val 1024
```

El resultado del perfilado se almacenará en:

```text
cachegrind.clasica.out
```

---

## 📊 5. Experimento 2: Multiplicación por Bloques

Ejecutar Cachegrind sobre la implementación por bloques:

```bash
valgrind \
  --tool=cachegrind \
  --cache-sim=yes \
  --cachegrind-out-file=cachegrind.bloques.out \
  ./bloques_val 1024 16
```

El resultado se almacenará en:

```text
cachegrind.bloques.out
```

---

## 📈 6. Visualización de los Resultados

Los archivos generados por Cachegrind pueden analizarse utilizando `cg_annotate`:

### Multiplicación clásica

```bash
cg_annotate cachegrind.clasica.out
```

### Multiplicación por bloques

```bash
cg_annotate cachegrind.bloques.out
```

También es posible utilizar una interfaz gráfica como `kcachegrind` para visualizar los resultados de forma más detallada.

```bash
kcachegrind cachegrind.clasica.out
```

> **Nota:** El nombre de los paquetes y la disponibilidad de `kcachegrind` pueden variar según la distribución de Linux.

---

## 🧪 7. Parámetros de los Experimentos

Para realizar una comparación consistente entre ambas implementaciones, se puede mantener constante el tamaño de la matriz y modificar el tamaño del bloque.

Ejemplo:

```text
N = 1024
B = 8
B = 16
B = 32
B = 64
```

Esto permite estudiar cómo el tamaño del bloque afecta el comportamiento de la caché y el rendimiento de la multiplicación.

---

## 📁 8. Archivos Generados

Después de realizar los experimentos, se tendrán archivos similares a:

```text
.
├── multiplicacioMatricesVan.cpp
├── multiplicacionMatricesXbloquesVan.cpp
├── clasica_val
├── bloques_val
├── cachegrind.clasica.out
└── cachegrind.bloques.out
```

---

## 🎯 9. Objetivo

El objetivo del experimento es **comparar la multiplicación clásica con la multiplicación por bloques**, observando cómo el acceso a memoria y el aprovechamiento de la caché pueden afectar el rendimiento.

En particular, el perfilado permite analizar:

* Accesos a memoria.
* Lecturas y escrituras en caché.
* Fallos de caché (*cache misses*).
* Comportamiento de la jerarquía de memoria.
* Efecto del tamaño de bloque.
* Diferencias entre ambas implementaciones.

---

## ⚡ Resumen de Comandos

### Compilar

```bash
g++ -O2 multiplicacioMatricesVan.cpp -o clasica_val
g++ -O2 multiplicacionMatricesXbloquesVan.cpp -o bloques_val
```

### Ejecutar

```bash
./clasica_val 1024
./bloques_val 1024 16
```

### Perfilado

```bash
valgrind --tool=cachegrind --cache-sim=yes \
  --cachegrind-out-file=cachegrind.clasica.out \
  ./clasica_val 1024
```

```bash
valgrind --tool=cachegrind --cache-sim=yes \
  --cachegrind-out-file=cachegrind.bloques.out \
  ./bloques_val 1024 16
```

### Analizar

```bash
cg_annotate cachegrind.clasica.out
cg_annotate cachegrind.bloques.out
```

