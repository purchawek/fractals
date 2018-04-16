# Fractals

Program rendering some recognizable fractals in real time.

![Mandelbrot set](/images/mandelbrot.png)

![Julia set](/images/julia.png)

##### supported fractals:
- [x] Julia sets
- [x] Mandelbrot set
- [ ] Burning Ship Fractal
- [ ] some other 

##### Requirements:

Application is written in C++ for performance reasons. It requires **SFML** for rendering with **OpenGL** and also **SFGUI** for the GUI.

Another requirement is **PURlib**, which is my library used for parsing program parameters. More information is available [here](http://github.com/purchawek/purlib)

##### Building:

`make` - that's all for now

##### Running:

`./build/main --help` - for details


##### TODOs
*   MORE FRACTALS
*   a better Makefile
*   flexible and easy way for defining new shaders
*   better gui (color selection, shader selection, more config options, help popup etc)
*   installer so it becomes an application
*   total code refactor and cleanup
*   find some way for testing this
*   documentation
