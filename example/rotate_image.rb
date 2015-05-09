im = GD::Image.new_from_jpeg 'in.jpeg'
im_out = GD::Image.new im.width, im.height
im.copy_rotated im_out, im.width/2, im.height/2, 0, 0, im.width, im.height, 30
im_out.jpeg_file 'rotate.jpeg', 90
im.destroy
im_out.destroy
