# **Sensor de Presi�n Transpulmonar Open-Source**

Proyecto de herramienta portatil de medici�n de la presi�n transpulmonar basada en arduino: Sensor de Presi�n Transpulmonar Open-source.

El Sensor de Presi�n Transpulmonar Open-Source (SPTO) permite la r�pida medici�n de la presi�n transpulmonar (PL)
mediante captaci�n de presi�n en v�a a�rea (Paw) y en v�a esof�gica (Pes) en pacientes intubados,
particularmente afectados de neumon�a bilateral por SARS-COV-2, empleando la prop�a tubuladura respiratoria  
para la medici�n de Paw y una sonda nasog�strica con bal�n esof�gico para la medici�n de Pes.

La precisi�n del SPTO en su primera versi�n es de +-0.18cmH2O (te�rica) por lo que se comprueba fiabilidad para �ste tipo de mediciones.

**El uso del SPTO debe ser realizado por personal m�dico competente en la materia.**


La monitorizaci�n de la ventilaci�n mec�nica comprende como base la presi�n en v�a a�rea y el flujo.
Para la mayor�a de pacientes, �stas dos medidas son suficientes para realizar los ajustes de ventilaci�n. 
Sin embargo, la Presi�n en v�a a�rea es s�lo una medici�n indirecta de las presiones en juego
en los componentes principales del sistema respiratorio (simplificando): pulmones y caja tor�cia.

Para realizar un ajuste preciso de la ventilaci�n mec�nica o evaluar la capacidad de reclutamiento pulmonar de los pacientes m�s graves,
se hace necesario diferenciar la complianza de ambos.

Est� asumido que la medici�n de la Presi�n Esof�gica (Pes) es un buen indicador que sustituye la medici�n de la presi�n pleural*.

Mediante la medici�n de la Paw y la Pes es posible obtener la presi�n transpulmonar(PL)=Paw-Pes calculada
durante la oclusi�n en fin de inspiraci�n y espiraci�n. PL representa la presi�n necesaria para dilatar el par�nquima pulmonar.
El SPTO calcula tambi�n los diferenciales de Paw y Pes durante la medici�n.

De �ste modo el personal m�dico tiene una mejor percepci�n del efecto de la ventilaci�n mec�nica y/o de la capacidad de reclutamiento pulmonar del paciente,
pudiendo realizar ajustes precisos del modo ventilatorio.

*Referencias:
1. Talmor D, Sarge T, O�Donnell C, Ritz R, Malhotra, Lisbon A, Loring S. Esophageal and transpulmonary pressures in acute respiratory failure Crit Care Med 2006; 34:1389�1394
2. Gattinoni L, Chiumello D, Carlesso E, Valenza F. Benchto-bedside review: Chest wall elastance in acute lung injury/acute respiratory distress syndrome patients. Critical Care 2004, 8:350-355
3. Hess D, Bigatello L. The chest wall in acute lung injury/acute respiratory distress syndrome. Curr Opin Crit Care 2008;14:94�102
4. Akoumianaki E, Maggiore S, Valenza F, Bellani G, Jubran A, et al. The application of esophageal pressure measurement in patients with respiratory failure. Am J Respir Crit Care Med 2014;189:520-31


#Problem�tica:

La monitorizaci�n de PL es una tecnolog�a que ya incluyen s�lo algunos de los ventiladores mec�nicos m�s modernos.

No obstante, las medidas de presi�n necesarias al c�lculo de PL se pueden tomar con la mayor�a de equipos electrom�dicos ya existentes.
Sin embargo, la toma de medidas sin herramientas de c�lculo integradas supone un proceso demasiado largo de toma de datos y procesado de los mismos:
un tiempo del que el personal m�dico no dispone en situaci�n de alta ocupaci�n sumada a medidas de higiene extremas,
como ocurre con los pacientes afectados por SARS-COV-2.

Proponemos un modelo de sensor de presi�n transpulmonar, port�til y de f�cil fabricaci�n basado en Arduino.
�ste prototipo se puede fabricar en poco tiempo con componentes off the shelf y supone dar capacidad al personal m�dico para monitorizar los pacientes m�s graves
d�ndoles un margen de mejora que puede resultar crucial en los casos m�s cr�ticos.

El desarrollo est� basado en torno a sensores/transductores de presi�n disponibles en el mercado, aunque dif�ciles de conseguir en las circunstancias actuales.
Recomendamos consultar con personal m�dico la necesidad de contar con un SPTO antes de realizar compra de material si se va a fabricar una unidad.
No todo el personal m�dico est� familiarizado con la monitorizaci�n de la PL y su implicaci�n para la mec�nica respiratoria.

No obstante es una tecnolog�a muy accesible que puede ayudar a salvar vidas si se emplea debidamente,
especialmente en aquellos pacientes m�s graves que necesitan de una monitorizaci�n m�s avanzada de la ventilaci�n mec�nica.

Creado por:
Francisco Jos� Parrilla G�mez - M�dico especialista en Medicina Intensiva, Servicio de Medicina Intensiva, Hospital del Mar, Parc de Salut Mar, IMIM, GREPAC, Barcelona - concepto, desarrollo, consejo cl�nico, pruebas
Andr�s Parrilla G�mez - Lyc�e Saint Stanislas, Nantes - concepto, desarrollo, programaci�n
Alvaro Jans� - Fablab Sant Cugat, Barcelona - desarrollo, producci�n, soporte programaci�n
Marc Estudillo - Ingenier�a electrom�dica, Barcelona - desarrollo, producci�n
Victor Boutonnet Antelo - Benimakers Makerspace, Valencia - desarrollo, soporte programaci�n, coordinaci�n proyecto

Liberado bajo Licencia Creative Commons Atribuci�n 4.0 Internacional (CC BY 4.0)

