# electrical-energy-recovery
Electrical Energy Recovery System with Photovoltaic Panel powered by Supercapacitors

Réalisé par CASTELLANETA Andrea et CROUARD Christale

Ce projet a pour but de créer un système de mesure autonome en alimentation qui communique les résultats de mesure via
un module radio. Il s’agit de dimensionner, caractériser et exploiter le système d’alimentation grâce au circuit intégré SPV1050,
qui récupère l’énergie d’un panneau photovoltaïque pour la stocker dans des supercapacités. Le système alimente alors la carte
Arduino Nano, qui grâce au LDO interne obtient la tension requise. Cette carte, à son tour, est connectée à un capteur de lumière,
dont les données sont envoyées par un module radio à une autre carte Arduino Nano. Ensuite, les performances de ce système
sont analysées en termes de consommation et de récupération d’énergie.

![architecture_globale](https://user-images.githubusercontent.com/101113976/223115336-bb73f394-5ec6-4b90-a9dd-6ccb497cbd1d.png)
