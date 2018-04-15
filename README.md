# Fractals

Program rendering some recognizable fractals in real time.

##### supported fractals:
- [x] Julia sets
- [ ] Mandelbrot set
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
*	MORE FRACTALS
*       a better Makefile
*	total code refactor and cleanup
*	consider deleting the old cpu-based renderer
*	find some way for testing this
*	documentation
