ParticleFilter
==============
a bare-bones 2d particle filter implemented with OpenFrameworks

![laserScanner](https://raw.githubusercontent.com/Poofjunior/ParticleFilter/master/pics/particleFilter1.png)

Here's a [video](http://www.youtube.com/watch?v=DY-l30yNMYU&list=UUc8qYIxKs4CkRFSN7Vdn-lw)
of the filter in action!

### Current Status
* Main robot can be driven around the map with 'w' 'a' 's' 'd'
* Application can be quit with 'e'
* With some tuning, the particle filter works for various map configurations. 
* Laser is assumed to be perfect. Note that a real laser scanner is noisy, and
  a gaussian noise model of each beam would help with provide this.

### Maps
* Maps are represented as features, where a feature is a connected set of
  segments. A Map is a collection of features, generated from .txt files. 
* A Map of an environment can be drawn out with one or more features by
  writing out the coordinates in a .txt file.

### Particles
* Particles with poses (x, y, theta) can be represented on an xy-plane.

### Laser Scanner
* The laser can measure the distance from an (x,y,theta) to any wall in linear
  time with respect to the number of segments

### Rendering Optimizations
This particle filter is designed to be separate from the visualizaition tool 
(OpenFrameworks in this case). Nevertheless, I needed to pull out a few tricks
in the OpenFrameworks library to render at a reasonable speed. Most notable is
OpenFrameworks' 
[ofFbo](http://www.openframeworks.cc/documentation/gl/ofFbo.html) or 
_frame buffer object_, which draws objects once in a separate buffer and 
renders them when needed. This was just the trick I needded for some faster 
visualization with my integrated graphics chip.

### TODO
* Inkscape svg integration to convert an svg file to a map
* Add Gaussian noise to laser scanner measurements
