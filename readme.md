# TD7 - osmGraph

## 1. Structures principales du graphe
Les structures sont définies dans `src/dataStructure/`.

* **WeightedGraph** : C'est le squelette mathématique. Il contient les nœuds et les arêtes avec leurs poids (distances). On s'en sert pour toute la logique de calcul.
* **PositionedGraph** : C'est une extension qui rajoute les coordonnées GPS (x, y) aux nœuds. C'est ce qui permet de calculer les distances et d'afficher le graphe sur une carte.

## 2. Modules du projet
* **Extraction OSM** : Ce module lit le fichier XML `.osm` et ne garde que ce qui nous intéresse (les routes) pour créer le graphe initial.
* **Simplification** : Il nettoie le graphe pour enlever les points inutiles et réduire la taille des données.
* **Visualisation** : C'est l'interface avec Raylib qui permet de voir la carte, de zoomer et d'interagir avec les nœuds (clics pour Dijkstra).

## 3. Étapes de simplification (`simplify.cpp`)
Le but est d'alléger le graphe pour que les calculs soient plus fluides.

### Ce qui est fait :
* **Suppression des nœuds isolés** : On dégage les points qui ne sont reliés à aucune route.
* **Fusion degré 2** : Quand un nœud est juste au milieu d'une rue, on fusionne les deux arêtes pour n'en faire qu'une.
* **Composante géante** : On garde seulement le réseau principal où tout est connecté.

### Impact :
* **Points positifs** : Le Dijkstra devient instantané (on passe de environ 8000 à environ 150 nœuds). Le fichier final est beaucoup plus léger.
* **Points négatifs** : On perd un peu de précision sur la forme exacte des rues (les courbes deviennent des segments plus droits).