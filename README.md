# **Open-Source Transpulmonary Pressure Sensor**

Arduino-based Transpulmonary pressure monitoring portable device project:  Open-Source Transpulmonary Pressure Sensor.

This Open-Source Transpulmonary Pressure Sensor (OSTPS) allows for rapid measuring of Transpulmonary Pressure (PL)
through airway pressure (Paw) and esophageal pressure (Pes) capture on intubated patients,
particularly those affected by bilateral pneumonia due to SARS-COV-2, pressures are measured using the respiratory cannula  
for Paw and an esophageal balloon nasogastric probe for Pes.

The OSTPS's accuracy in this first iteration is +-0.18cmH2O (theorical) so its reliability and precision is assumed correct for this type of measurement.

**The use of a OSTPS must be performed by trained medical personnel.**

Mechanical ventilation monitoring, at its basis, encompasses airway pressure and flow.
For most patients, these two measurements are enough to perform ventilation adjustments. 
However, airway pressure is only the resulting measurement of pressures at play in the main respiratory system's components:
lungs and chest wall (simplified).

To perform precise adjustments of mechanical ventilation or evaluating lung recruitability in acutely ill patients,
differentiating these two components compliance is necessary.

It's assumed esophageal pressure (Pes) is representative of pleural pressure*.

Through Paw and Pes measurement it is possible to obtain Transpulmonary Pressure (PL)=Paw-Pes measured
during occlusion at end inspiration and expiration. PL represents the necessary pressure to dilate the lung parenchyma.
This first OSTPS version also calculates Paw and Pes differentials.

Through the use of OSTPS clinicians may get a better perception of patient-ventilator interaction and plan for respiratory strategy
more accurately.

*References:
1. Talmor D, Sarge T, O’Donnell C, Ritz R, Malhotra, Lisbon A, Loring S. Esophageal and transpulmonary pressures in acute respiratory failure Crit Care Med 2006; 34:1389–1394
2. Gattinoni L, Chiumello D, Carlesso E, Valenza F. Benchto-bedside review: Chest wall elastance in acute lung injury/acute respiratory distress syndrome patients. Critical Care 2004, 8:350-355
3. Hess D, Bigatello L. The chest wall in acute lung injury/acute respiratory distress syndrome. Curr Opin Crit Care 2008;14:94–102
4. Akoumianaki E, Maggiore S, Valenza F, Bellani G, Jubran A, et al. The application of esophageal pressure measurement in patients with respiratory failure. Am J Respir Crit Care Med 2014;189:520-31


#Problem:

PL monitorization is an already existing technology only implement in most modern mechanical respirators.

Pressure measurements necessary to calculate PL can be obtained with most electromedical devices nonetheless.
Although, this data acquisition without integrated calculation tools is a lengthy process,
demanding a span of time medical personnel can't spare given the high occupancy rate and hard hygiene measures,
as happens with SARS-COV-2 affected patients.

We propose a Transpulmonary Pressure Sensor model, based on Arduino, easy to build and portable.
This prototype can be produced in short time with off the shelf components, and allows medical personnel to correctly asses acutely ill patients,
giving them supplementary room for improvement which may be crucial for recovery in the most critical cases.

The development of this project is based on already existing pressure sensors/transducers, which may be hard to come by given the actual market situation.
We recommend consulting with target medical personnel the need for a OSTPS before sourcing components to avoid a colapse in supply.
Not all medical personnel is familiar with PL monitoring and its implications for mechanical ventilation, this is a fairly recent technique.

Nonetheless this now very accessible technology can help save lives if used correctly,
especially for those acutely ill patients who need more advanced mechanical ventilation monitoring.

Made possible by:
Francisco José Parrilla Gómez - Critical Care Medicine specialist physician, Intensive Medicine Service, Hospital del Mar, Parc de Salut Mar, IMIM, GREPAC, Barcelona - concept, development, clinical advisor, testing
Andrés Parrilla Gómez - Lycée Saint Stanislas, Nantes - concept, development, programming
Alvaro Jansà - Fablab Sant Cugat, Barcelona - development, production, programming support
Marc Estudillo - Electromedical Engineering, Barcelona - development, production
Victor Boutonnet Antelo - Benimakers Makerspace, Valencia - development, programming support, project coordination

Made available under Creative Commons Licence Attribution 4.0 International (CC BY 4.0).

