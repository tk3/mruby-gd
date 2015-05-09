mruby-gd
=========
GD Graphics Library for mruby.

Dependences
========
- GD Graphics Library

Building
========

```
 MRuby::Build.new do |conf|
   ...
   conf.gem :github => 'qtkmz/mruby-gd'
   ...
 end
```

Example
========

- Draw a line
```
im = GD::Image.new 100, 150
white = im.color_allocate 255, 255, 255
red = im.color_allocate 255, 0, 0

im.line 20, 50, 80, 50, red

im.dashed_line 20, 100, 80, 100, red

im.jpeg_file 'line.jpeg', 90

im.destroy
```

- Rotate a image (counterclockwise 30 degrees)

```
im = GD::Image.new_from_jpeg_file 'in.jpeg'
im_out = GD::Image.new im.width, im.height
im.copy_rotated im_out, im.width/2, im.height/2, 0, 0, im.width, im.height, 30
im_out.jpeg_file 'rotate.jpeg', 90
im.destroy
im_out.destroy
```

- Resize a image

```
im = GD::Image.new_from_jpeg_file 'in.jpeg'
im_out = GD::Image.new (im.width/2).floor, (im.height/2).floor
im.copy_resized im_out, 0, 0, 0, 0, im.width/2, im.height/2, im.width, im.height
im_out.jpeg_file 'resized.jpeg', 90
im.destroy
im_out.destroy
```

