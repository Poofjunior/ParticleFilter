ParticleFilter
==============

a 2d particle filter implemented with OpenFrameworks

a work in progress:

### Current Status
* Maps are represented as features, where a feature is a connected set of
  segments. A Map is a collection of features, generated from .txt files. 
* particles with poses can be represented on an xy-plane.
* laser can measure the distance from an (x,y,theta) to any wall in linear
  time with respect to the number of segments

### TODO
* fininsh implementing the algorithm
