# Seguimiento académico - Laboratorio 09

Aplicación Qt 6 Widgets/C++20 que registra actividades académicas y carga un CSV heredado. La solución separa Modelo, Vista y Controlador, y aplica:

- **Factory Method:** cada creador concreta (`TareaCreator`, `ExamenCreator`, `ProyectoCreator`) encapsula la creación y validación de su producto.
- **Adapter:** `CsvRepositorioAdapter` traduce `CsvLegacySource` a la interfaz `IRepositorio` sin modificar el componente CSV heredado.

## Requisitos

- Qt 6 (Core, Widgets y Test)
- CMake 3.21 o superior
- Compilador C++20

## Compilación y pruebas

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Ejecutar la aplicación:

```bash
./build/seguimiento_academico
```

El archivo de ejemplo está en `data/actividades_legacy.csv`. Los diagramas están en `docs/` y el informe entregable es `docs/informe_lab09.pdf`.

## Estructura

`src/model` contiene entidades, fábrica, repositorios y el adaptador. `src/controller` coordina las acciones y emite señales. `src/view` contiene únicamente la interfaz Qt y conecta sus eventos con el controlador. `tests` prueba modelo y controlador sin iniciar la GUI.

## Decisiones

Factory Method se justifica porque agregar un tipo de actividad requiere un nuevo creador/producto, sin modificar la vista. Adapter se prefiere frente a modificar el CSV heredado porque conserva una fuente externa estable y limita el cambio al borde del sistema. El modelo no depende de Qt Widgets ni de la vista. El costo introducido es el número adicional de clases/interfaces; se compensa con pruebas aisladas y menor acoplamiento.

## Entrega

Integrante registrado en el informe: Ronald Camani. La carpeta de trabajo original no era un repositorio Git, por lo que la URL de commit queda pendiente de reemplazarse al publicar el proyecto.
