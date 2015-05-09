im = GD::Image.new_from_jpeg 'in.jpeg'
im_out = GD::Image.new (im.width/2).floor, (im.height/2).floor
im.copy_resized im_out, 0, 0, 0, 0, im.width/2, im.height/2, im.width, im.height
im_out.jpeg_file 'resized.jpeg', 90
im.destroy
im_out.destroy
