# **Sensor de Presión Transpulmonar Open-Source**

Proyecto de herramienta portatil de medición de la presión transpulmonar basada en arduino: Sensor de Presión Transpulmonar Open-source.

El Sensor de Presión Transpulmonar Open-Source (SPTO) permite la rápida medición de la presión transpulmonar (PL)
mediante captación de presión en vía aérea (Paw) y en vía esofágica (Pes) en pacientes intubados,
particularmente afectados de neumonía bilateral por SARS-COV-2, empleando la propía tubuladura respiratoria  
para la medición de Paw y una sonda nasogástrica con balón esofágico para la medición de Pes.

La precisión del SPTO en su primera versión es de +-0.18cmH2O (teórica) por lo que se comprueba fiabilidad para éste tipo de mediciones.

**El uso del SPTO debe ser realizado por personal médico competente en la materia.**


La monitorización de la ventilación mecánica comprende como base la presión en vía aérea y el flujo.
Para la mayoría de pacientes, éstas dos medidas son suficientes para realizar los ajustes de ventilación. 
Sin embargo, la Presión en vía aérea es sólo una medición indirecta de las presiones en juego
en los componentes principales del sistema respiratorio (simplificando): pulmones y caja torácia.

Para realizar un ajuste preciso de la ventilación mecánica o evaluar la capacidad de reclutamiento pulmonar de los pacientes más graves,
se hace necesario diferenciar la complianza de ambos.

Está asumido que la medición de la Presión Esofágica (Pes) es un buen indicador que sustituye la medición de la presión pleural*.

Mediante la medición de la Paw y la Pes es posible obtener la presión transpulmonar(PL)=Paw-Pes calculada
durante la oclusión en fin de inspiración y espiración. PL representa la presión necesaria para dilatar el parénquima pulmonar.
El SPTO calcula también los diferenciales de Paw y Pes durante la medición.

De éste modo el personal médico tiene una mejor percepción del efecto de la ventilación mecánica y/o de la capacidad de reclutamiento pulmonar del paciente,
pudiendo realizar ajustes precisos del modo ventilatorio.

*Referencias:
1. Talmor D, Sarge T, O’Donnell C, Ritz R, Malhotra, Lisbon A, Loring S. Esophageal and transpulmonary pressures in acute respiratory failure Crit Care Med 2006; 34:1389–1394
2. Gattinoni L, Chiumello D, Carlesso E, Valenza F. Benchto-bedside review: Chest wall elastance in acute lung injury/acute respiratory distress syndrome patients. Critical Care 2004, 8:350-355
3. Hess D, Bigatello L. The chest wall in acute lung injury/acute respiratory distress syndrome. Curr Opin Crit Care 2008;14:94–102
4. Akoumianaki E, Maggiore S, Valenza F, Bellani G, Jubran A, et al. The application of esophageal pressure measurement in patients with respiratory failure. Am J Respir Crit Care Med 2014;189:520-31


#Problemática:

La monitorización de PL es una tecnología que ya incluyen sólo algunos de los ventiladores mecánicos más modernos.

No obstante, las medidas de presión necesarias al cálculo de PL se pueden tomar con la mayoría de equipos electromédicos ya existentes.
Sin embargo, la toma de medidas sin herramientas de cálculo integradas supone un proceso demasiado largo de toma de datos y procesado de los mismos:
un tiempo del que el personal médico no dispone en situación de alta ocupación sumada a medidas de higiene extremas,
como ocurre con los pacientes afectados por SARS-COV-2.

Proponemos un modelo de sensor de presión transpulmonar, portátil y de fácil fabricación basado en Arduino.
Éste prototipo se puede fabricar en poco tiempo con componentes off the shelf y supone dar capacidad al personal médico para monitorizar los pacientes más graves
dándoles un margen de mejora que puede resultar crucial en los casos más críticos.

El desarrollo está basado en torno a sensores/transductores de presión disponibles en el mercado, aunque difíciles de conseguir en las circunstancias actuales.
Recomendamos consultar con personal médico la necesidad de contar con un SPTO antes de realizar compra de material si se va a fabricar una unidad.
No todo el personal médico está familiarizado con la monitorización de la PL y su implicación para la mecánica respiratoria.

No obstante es una tecnología muy accesible que puede ayudar a salvar vidas si se emplea debidamente,
especialmente en aquellos pacientes más graves que necesitan de una monitorización más avanzada de la ventilación mecánica.

Creado por:
Francisco José Parrilla Gómez - Médico especialista en Medicina Intensiva, Servicio de Medicina Intensiva, Hospital del Mar, Parc de Salut Mar, IMIM, GREPAC, Barcelona - concepto, desarrollo, consejo clínico, pruebas
Andrés Parrilla Gómez - Lycée Saint Stanislas, Nantes - concepto, desarrollo, programación
Alvaro Jansà - Fablab Sant Cugat, Barcelona - desarrollo, producción, soporte programación
Marc Estudillo - Ingeniería electromédica, Barcelona - desarrollo, producción
Victor Boutonnet Antelo - Benimakers Makerspace, Valencia - desarrollo, soporte programación, coordinación proyecto

Liberado bajo Licencia Creative Commons Atribución 4.0 Internacional (CC BY 4.0)

