# cub3D

*This project has been created as part of the 42 curriculum by dchernik and adeestev.*

## Description ##

[GitHub link](https://github.com/danya-chernikov/cub3D)

[Math](https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?node-id=0-1&p=f&t=wUQSFxvh3lKCq6Qz-0)

### What is it ###
**cub3D** is a basic recreational raycasting implementation written in C.
It uses MLX42, which is based on GLFW and OpenGL. The original MiniLibX
library was created, as far as I understand, to make the first steps in
computer graphics less intimidating for beginners. Later, a newer and more
optimized version, [MLX42](https://github.com/42-Fundacion-Telefonica/MLX42)
from Fundación Telefónica, was introduced, and we're fully allowed to use
it in our projects, so we did, why not..

### What was done ###
Our way through this project is reflected in our corresponding Figma project
(the link is provided below in the "Resources" section). There, you can find
almost all the necessary math, although still not everything, as well as some
visualizations that may be useful for better understanding the project's logic.
All these drawings were made manually, either by hand or with a graphic tablet
using Krita. For some mathematical theorems, proofs were also presented and
understood. Not all the mathematics presented there is directly useful for this
specific cub3D raycasting project. Primarily, it was done as a sort of warm up
before starting to implement the raytracer (miniRT project).

### How does it work ###
During the parsing stage, we used the `get_next_line()` function implemented
earlier (the code style of my GNL is awful, but it works pretty well! but I
actually (re)invented it back in the days). Moreover, we added a flag to it so
that the function can indicate whether a system error, such as a malloc() or
read() error, occurred before returning NULL, or whether we simply reached
the end of the file. We read the .cub file line by line, and each line is
stored in a singly linked list. This way, buffer overflow will never happen,
and our program can process very large files. So, yeah, we parse the file
content according to the subject requirements, and the parser works well.

A lot has already been said about the project's inner parts in plenty of
other tutorials, so there is no need to duplicate all of that here. What
we mainly did was follow Lodev's instructions. Before adapting his approach
to our project, we first repeated all, or almost all, of the basic
mathematical concepts behind DDA and raycasting in general.
The first thing we did was develop a set of functions for drawing basic
graphical primitives: a line using Bresenham's algorithm, a line with a
specified thickness, a polygon, a filled polygon using the scanline
algorithm, a circle using Bresenham's algorithm again, and a filled circle.
This gave us a good base for drawing a 2D minimap.

After that, we started implementing the actual game logic around the
minimap: player movement through the map, wall collision, ray emission, FOW
visualization, and player rotation. Once the 2D part became clear enough, we
moved on to the real raycasting part. We implemented ray emission using the
Digital Differential Analyzer technique. Instead of moving the ray pixel by
pixel, DDA moves through the map grid incrementally, jumping from one grid
line to the next. At each step, it decides whether the next crossed grid line
is vertical or horizontal by comparing the current x-side and y-side distances.
This way, the algorithm knows which map cell the ray enters next until it
finally reaches a wall. Then we started drawing walls. For each screen column,
we cast one ray and calculated the height of the corresponding wall slice.
This height is based on the distance from the player to the wall, but not on
the direct Euclidean distance. Instead, we use the perpendicular distance,
which can be understood as the projection of the ray hit distance onto the
camera direction. The final wall slice height is inversely proportional to
this perpendicular distance: the closer the wall is, the taller the slice
becomes and the farther the wall is, the smaller the slice becomes.

Once the basic wall rendering worked and the result looked like a proper 3D
view imitation, we added textures. At this stage, instead of drawing each
wall slice with a single flat color, we started copying pixels from texture
files. First, we choose the correct texture depending on the side of the wall
hit by the ray: north, south, west, or east. This choice is made using the
ray side and the ray step direction. If the ray hit a vertical wall side, we
know it is either the west or east face of the wall cell, if it hit a
horizontal wall side, it is either the north or south face.
After selecting the texture, we calculate the exact point where the ray hit
the wall. From that hit point, we take the fractional part of the coordinate
that runs along the wall. For a vertical wall side, this coordinate is the y
position and for a horizontal wall side it's the x position. This fractional
value tells us where on the texture the ray landed, so we convert it into
`tex_x`, the horizontal coordinate inside the texture.
Then, while drawing the wall slice from top to bottom on the screen, we
calculate the corresponding `tex_y` for each screen pixel. The texture column
is stretched or compressed depending on the projected wall height. For every
screen y coordinate inside the wall slice, we read the pixel at
(`tex_x`, `tex_y`) from `texture->pixels`, convert it to the color format
expected by MLX, and safely put that pixel onto the image. In other words,
each vertical wall slice on the screen becomes a scaled vertical strip taken
from the correct wall texture.

### About Math ###
Strictly speaking, you cannot just immediately start with a university
math topic that you like or need without having a solid understanding of
school math first. Obviously, it is very easy to solve exercises (not
real problems) given in books right after another theory chapter.
Someone can master how to solve integrals or differential equations without
really understanding mathematics, without having any idea how to apply it
in practice, and without developing real problem-solving skills.
But okay, having said all this, I guess I could list some foundational
things that, in my opinion, one should **understand** in order to get
close to cub3D specifically:

1. Pythagorean theorem;
2. Law of cosines;
3. Trigonometry;
4. Vectors: basic operations and calculating a normal vector;
5. Dot product and its properties;
6. Circle equation;
7. Parametric equation of a line;
8. Matrices;
9. Linear transformations, especially rotations.

But again, it is better to start from the beginning. Otherwise, carrying
out this project will be of no use. It will just be a waste of time.

## Instructions ##
If you use an Ubuntu based GNU/Linux distribution, first make sure these
dependencies are installed on your machine:
`build-essential cmake pkg-config libglfw3-dev libgl1-mesa-dev`
`libglu1-mesa-dev xorg-dev`
There may be additional things to install as well. Most of them are required
by the OpenGL libraries used by MLX42. For more info, see the corresponding
manual [page](https://github.com/42-Fundacion-Telefonica/MLX42), specifically
the "Installation" section.
Then, simply clone our repo and run make:

`git clone git@github.com:danya-chernikov/cub3D.git`

`cd cub3D`

`make`

`./cub3D <path_to_map.cub>`

The other make rules are well known from every 42 project.
Our Makefile automatically clones the MLX42 library and builds it using CMake.
All object files are built manually, without extra automation (as it required
by the norm). But ok, we used `addprefix` to save space and avoid unnecessary
object files folder repetition.

## Resources ##

Project's math and some proofs/illustrations:
[Figma](https://www.figma.com/design/MOGITOdwaCYQ11DAqgljlT/cub3D?node-id=0-1&p=f&t=wUQSFxvh3lKCq6Qz-0)

### Books ###
1. "Mathematics for 3D Game Programming and Computer Graphics" - Eric Lengyel
    This is pretty based. "You must know this xd"
    First 4 chapters: the rendering pipeline, vectors, matrices and
    transforms (briefly). Actually from this book I caught some theorems
    and wrote them out in more detail on the blackboard (I also outlined
    the proofs in more detail just to understand them better).
2.  [Mathprofi](https://mathprofi.ru) a website I used to get a basic
    overview of analytical geometry and linear algebra, just to refresh my
    knowledge. It is something like a roadmap: no proofs, just useful and
    easy examples with very accessible explanations. Back in the day, it
    helped me a lot during my first and second years at university.
3. "All 'higher' mathematics" by Krasnov Kiselev Makarenko Shikin Zalyapin
    A more serious and thorough book. I read, or rather just went through,
    only the linear algebra chapter.
4. "Matrix Analysis and Linear Algebra" by Tartyshnikov  
    A serious book. It cannot be read without paper, at least in my case.
    But I want to continue with this book to understand algebra better in
    general.

### Web sites ###
1. [A Fast Voxel Traversal Algorithm for Ray Tracing by John Amanatides and Andrew Woo](http://www.cse.yorku.ca/~amana/research/grid.pdf)
    Classical work. This is a short but very important original source
    on fast ray traversal through a grid.

2. [Lodev's first part](https://lodev.org/cgtutor/raycasting.html)
    Just the first part. More then enough, really.

3. [Super Fast Ray Casting in Tiled Worlds using DDA by javidx9](https://www.youtube.com/watch?v=NbSee-XM7WA&t=1249s)
    I watched half of the video. In general it's a good chanel about
    computer graphics.

4. [Essence of linear algebra by Grant Sanderson](https://www.youtube.com/watch?v=fNk_zzaMoSs&list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab)
    Almost forgot to mention about 3Blue1Brown linear algebra playlist. It needs
    no introduction. Great as always.

5. [MLX42 docs](https://github.com/42-Fundacion-Telefonica/MLX42/tree/master/docs) Obviously.

There are actually more resources. We listed the ones we used most frequently.

### AI Usage ###
The requirement to indicate the use of so-called 'AI' is not relevant
to modern realities. If a person **understands** the topic, nobody will
ever prove that the project was fully generated by AI, or the opposite.
The thesis itself that 'AI' should be used wisely is, of course, wonderful.
In this project, 'AI' was used, as usual, to correct grammar mistakes in
commits. Besides that, I asked it in general about which resources are good
for a deep understanding of the topic, and it suggested several good books.
I asked about GitHub settings and generally about how it works. In general,
I still believe that the brain has to suffer in order to learn something.
This requires time. Sometimes it is very tempting to choose the easy path,
and this creates an illusion of knowledge or understanding, but it is only
an **illusion**. A person who simply copies code generated by an LLM or written
by other people, without understanding how it works, is only harming himself.
A good rule is to use code generation only for those tasks that you can
perform yourself with your eyes closed. But at the learning stage, it's better
not to use it at all. It is one thing when you are already a professional and
an LLM helps you speed up your workflow. It's another thing when you are
nobody in programming and simply copy-paste code from an LLM. For people who
are **programmers**, not coders, and also real **engineers** who have real
development experience, the rules are slightly different. Thus, a person harms
themselves by teaching their brain not to work and not to solve problems
independently (in other words, not to think). The thinking process atrophies.
