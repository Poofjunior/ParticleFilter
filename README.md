ParticleFilter
==============
a bare-bones 2d particle filter implemented with OpenFrameworks

![laserScanner](https://raw.githubusercontent.com/Poofjunior/ParticleFilter/master/pics/particleFilter1.png)

Here's a [video](http://www.youtube.com/watch?v=DY-l30yNMYU&list=UUc8qYIxKs4CkRFSN7Vdn-lw)
of the filter in action!

### Current Status
* Main robot can be driven around the map with W A S D
* With some tuning, the particle filter works for various map configurations. 
* (Needs some tuning to add in more noise.)
* Maps are represented as features, where a feature is a connected set of
  segments. A Map is a collection of features, generated from .txt files. 
* A Map of an environment can be drawn out with one or more features.
* Particles with poses can be represented on an xy-plane.
* Laser can measure the distance from an (x,y,theta) to any wall in linear
  time with respect to the number of segments

### TODO
* Inkscape svg integration to convert an svg file to a map
