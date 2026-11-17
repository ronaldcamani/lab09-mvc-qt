---
title: "Aplicación de patrones de diseño y arquitectura MVC con Qt"
author: "Ronald Camani"
date: "17 de noviembre de 2026"
geometry: margin=2.2cm
fontsize: 11pt
toc: true
---

# 1. Identificación

| Campo | Valor |
|---|---|
| Universidad | Universidad Nacional de San Agustín de Arequipa |
| Curso | Tecnología de Objetos |
| Práctica | Laboratorio N.° 09 |
| Integrante | Ronald Camani |
| Fecha | 17/11/2026 |
| Qt | Qt 6 Widgets, Core y Test |
| C++ | C++20 |
| CMake | 4.2.3 |
| URL del commit evaluado | Pendiente: la carpeta de trabajo inicial no era un repositorio Git |

# 2. Objetivo y alcance

Se construyó una aplicación de seguimiento académico capaz de crear actividades de tipo tarea, examen y proyecto, listar las actividades y cargar registros desde un CSV con formato heredado. El diseño mantiene una separación explícita entre Modelo, Vista y Controlador.

# 3. Arquitectura MVC

## Modelo

El Modelo está formado por `Actividad`, sus especializaciones, `IRepositorio`, `RepositorioActividades`, `CsvLegacySource`, `CsvRepositorioAdapter` y los creadores del Factory Method. Administra datos y reglas de validación, pero no conoce `QWidget`, `MainWindow` ni detalles de presentación.

## Vista

`MainWindow` presenta el formulario, la lista y los botones. No modifica colecciones del Modelo: solo emite acciones al Controlador mediante señales y conexiones Qt.

## Controlador

`ActividadController` recibe eventos, elige el creador adecuado, solicita operaciones al repositorio y notifica resultados mediante `actividadesActualizadas`, `operacionCompletada` y `errorOcurrido`.

![Diagrama de clases](docs/clases.png)

# 4. Factory Method

## Problema concreto

La GUI original tendría que instanciar clases concretas y repetir validaciones para cada tipo. Esto acopla la presentación a la jerarquía de actividades y hace que agregar una nueva clase obligue a editar la vista.

## Solución

`ActividadCreator::crear` valida datos y delega `crearProducto` a `TareaCreator`, `ExamenCreator` o `ProyectoCreator`. El Controlador solo selecciona el creador a partir del tipo solicitado; la creación concreta queda encapsulada.

## Consecuencias

El beneficio es que la vista no conoce constructores concretos y un nuevo producto se incorpora extendiendo la jerarquía. El costo es introducir una clase creadora por variante y una indirección adicional.

# 5. Adapter

## Problema concreto

`CsvLegacySource` expone registros con nombres y estructura antigua (`clase`, `nombre`, `asignatura`, `fecha`, `encargado`), mientras que la aplicación necesita `IRepositorio`.

## Solución

`CsvRepositorioAdapter` implementa `IRepositorio`, convierte cada `LegacyRecord` a `ActividadData`, selecciona el creador correspondiente y delega el almacenamiento al repositorio interno. La fuente heredada no se modifica.

## ¿Cuándo es preferible?

Adapter es preferible cuando el componente heredado es estable, externo, compartido o riesgoso de modificar. También permite retirar la integración gradualmente. Modificar el legado sería razonable solo si el equipo controla su contrato y el cambio no rompe consumidores.

# 6. Flujos

![Diagrama de secuencia](docs/secuencia.png)

En el flujo de creación, la Vista envía datos al Controlador; el Factory crea la actividad, el repositorio la conserva y el Controlador devuelve una lista actualizada. En el flujo de carga, el Adapter lee el CSV, traduce los registros y entrega objetos compatibles con la misma interfaz del repositorio.

# 7. Pruebas y validación

Las pruebas se ejecutan sin iniciar la GUI con Qt Test:

| Prueba | Evidencia |
|---|---|
| Creación de tipos | Cada creador produce `Tarea`, `Examen` y `Proyecto` |
| Validación | Un título vacío lanza `std::invalid_argument` |
| Adapter CSV | Dos registros heredados se convierten y almacenan |
| Controlador | La señal de actualización contiene la actividad creada |

Comandos:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

# 8. Comparación antes/después

| Métrica | Antes | Después |
|---|---:|---:|
| Vista conoce clases concretas de actividad | 3 | 0 |
| Vista conoce detalles CSV | Sí | No |
| Componentes con acceso a la colección | Vista y lógica de creación | Repositorio |
| Puntos de creación duplicados | 3 o más | 1 operación Factory |
| Pruebas de modelo/controlador sin GUI | No | 4 casos |

Las cifras son métricas simples de dependencias estáticas del diseño, no una medición de rendimiento. El beneficio se verificó con compilación y pruebas automatizadas.

# 9. Respuestas de análisis

**¿Qué problema concreto justifica Factory Method?** La creación de productos de varias clases y la necesidad de impedir que la GUI dependa de constructores concretos. Factory Method centraliza validación y permite agregar variantes mediante extensión.

**¿Cuándo Adapter es preferible a modificar el componente heredado?** Cuando el formato heredado es externo, estable, compartido o no se puede cambiar sin riesgo. El Adapter traduce el contrato en un único punto y preserva compatibilidad.

**¿Qué dependencias no debe tener el Modelo en MVC?** No debe depender de `MainWindow`, `QWidget`, controles visuales ni reglas de interacción. Puede depender de tipos de datos y servicios de persistencia abstraídos, pero su lógica debe ser utilizable sin iniciar la GUI.

**¿Qué costo introduce cada patrón y cómo se verificó su beneficio?** Factory Method agrega creadores y una indirección; Adapter agrega una interfaz y una traducción de datos. El beneficio se verificó comparando dependencias antes/después y ejecutando pruebas del Modelo y Controlador sin GUI.

# 10. Referencias

1. Gamma, E., Helm, R., Johnson, R. y Vlissides, J. (1994). *Design Patterns: Elements of Reusable Object-Oriented Software*. Addison-Wesley.
2. Fowler, M. (2002). *Patterns of Enterprise Application Architecture*. Addison-Wesley.
3. The Qt Company. (2026). *Signals & Slots*. https://doc.qt.io/qt-6/signalsandslots.html
4. The Qt Company. (2026). *Qt 6 documentation*. https://doc.qt.io/qt-6/
5. Stroustrup, B. y Sutter, H. (Eds.). (2026). *C++ Core Guidelines*. https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
