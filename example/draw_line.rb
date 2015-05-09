im = GD::Image.new 100, 150
white = im.color_allocate 255, 255, 255
red = im.color_allocate 255, 0, 0

im.line 20, 50, 80, 50, red

im.dashed_line 20, 100, 80, 100, red

im.jpeg_file 'line.jpeg', 90

im.destroy
