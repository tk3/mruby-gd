#include <stdio.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "gd.h"

typedef struct {
    gdImagePtr im;
} mrb_gd_image;

static mrb_gd_image *mrb_gd_image_wrap(mrb_state *mrb, gdImagePtr im)
{
    mrb_gd_image *image = (mrb_gd_image *)mrb_malloc(mrb, sizeof(mrb_gd_image));
    image->im = im;
    return image;
}

static void mrb_gd_image_free(mrb_state *mrb, void *p)
{
    mrb_gd_image *image = (mrb_gd_image *)p;
    if (image->im != NULL) {
        gdImageDestroy(image->im);
    }
    mrb_free(mrb, image);
}

static const mrb_data_type mrb_gd_image_type = {
    "mrb_gd_image", mrb_gd_image_free,
};

static mrb_value mrb_gd_image_initialize(mrb_state *mrb, mrb_value self)
{
    mrb_int height, width;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "ii", &height, &width);

    im = gdImageCreate(height, width);
    if (im == NULL) {
        return self;
    }

    image = mrb_gd_image_wrap(mrb, im);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    return self;
}

static mrb_value mrb_gd_image_new_from_gif_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    FILE *fin;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "z", &filename);

    fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    im = gdImageCreateFromGif(fin);

    fclose(fin);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_png_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    FILE *fin;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "z", &filename);

    fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    im = gdImageCreateFromPng(fin);

    fclose(fin);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_jpeg_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    FILE *fin;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "z", &filename);

    fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    im = gdImageCreateFromJpeg(fin);

    fclose(fin);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_wbmp_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    FILE *fin;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "z", &filename);

    fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    im = gdImageCreateFromWBMP(fin);

    fclose(fin);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_gif_data(mrb_state *mrb, mrb_value self)
{
    char *s;
    mrb_int size;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "s", &s, &size);

    im = gdImageCreateFromGifPtr(size, s);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_png_data(mrb_state *mrb, mrb_value self)
{
    char *s;
    mrb_int size;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "s", &s, &size);

    im = gdImageCreateFromPngPtr(size, s);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_jpeg_data(mrb_state *mrb, mrb_value self)
{
    char *s;
    mrb_int size;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "s", &s, &size);

    im = gdImageCreateFromJpegPtr(size, s);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_wbmp_data(mrb_state *mrb, mrb_value self)
{
    char *s;
    mrb_int size;
    gdImagePtr im;
    mrb_gd_image *image;

    mrb_get_args(mrb, "s", &s, &size);

    im = gdImageCreateFromWBMPPtr(size, s);

    image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_destroy(mrb_state *mrb, mrb_value self)
{
    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);

    if (image->im != NULL) {
        gdImageDestroy(image->im);
        image->im = NULL;
    }

    return self;
}

static mrb_value mrb_gd_image_width(mrb_state *mrb, mrb_value self)
{
    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(0);
    }

    return mrb_fixnum_value(gdImageSX(image->im));
}

static mrb_value mrb_gd_image_height(mrb_state *mrb, mrb_value self)
{
    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(0);
    }

    return mrb_fixnum_value(gdImageSY(image->im));
}

static mrb_value mrb_gd_image_set_pixel(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y, color;
    mrb_gd_image *image;

    mrb_get_args(mrb, "iii", &x, &y, &color);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    gdImageSetPixel(image->im, x, y, color);

    return self;
}

static mrb_value mrb_gd_image_get_pixel(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "ii", &x, &y);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageGetPixel(image->im, x, y);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_image_get_truecolor_pixel(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "ii", &x, &y);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageGetTrueColorPixel(image->im, x, y);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_image_line(mrb_state *mrb, mrb_value self)
{
    mrb_int x1, y1, x2, y2, color;
    mrb_gd_image *image;

    mrb_get_args(mrb, "iiiii", &x1, &y1, &x2, &y2, &color);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    gdImageLine(image->im, x1, y1, x2, y2, color);

    return self;
}

static mrb_value mrb_gd_image_dashed_line(mrb_state *mrb, mrb_value self)
{
    mrb_int x1, y1, x2, y2, color;
    mrb_gd_image *image;

    mrb_get_args(mrb, "iiiii", &x1, &y1, &x2, &y2, &color);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    gdImageDashedLine(image->im, x1, y1, x2, y2, color);

    return self;
}

static mrb_value mrb_gd_image_rectangle(mrb_state *mrb, mrb_value self)
{
    mrb_int x1, y1, x2, y2, color;
    mrb_gd_image *image;

    mrb_get_args(mrb, "iiiii", &x1, &y1, &x2, &y2, &color);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    gdImageRectangle(image->im, x1, y1, x2, y2, color);

    return self;
}

static mrb_value mrb_gd_image_filled_rectangle(mrb_state *mrb, mrb_value self)
{
    mrb_int x1, y1, x2, y2, color;
    mrb_gd_image *image;

    mrb_get_args(mrb, "iiiii", &x1, &y1, &x2, &y2, &color);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    gdImageFilledRectangle(image->im, x1, y1, x2, y2, color);

    return self;
}

static mrb_value mrb_gd_image_fill(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y, color;
    mrb_gd_image *image;

    mrb_get_args(mrb, "iii", &x, &y, &color);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImageFill(image->im, x, y, color);

    return self;
}

static mrb_value mrb_gd_image_copy_rotated(mrb_state *mrb, mrb_value self)
{
    mrb_value dst;
    mrb_float dstX, dstY;
    mrb_int srcX, srcY, srcWidth, srcHeight, angle;
    mrb_gd_image *image_src;
    mrb_gd_image *image_dst;

    mrb_get_args(mrb, "offiiiii", &dst, &dstX, &dstY, &srcX, &srcY, &srcWidth, &srcHeight, &angle);

    image_src = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    image_dst = mrb_get_datatype(mrb, dst, &mrb_gd_image_type);
    if (image_src == NULL || image_src->im == NULL || image_dst == NULL || image_dst->im == NULL) {
        return self;
    }

    gdImageCopyRotated(image_dst->im, image_src->im, dstX, dstY, srcX, srcY, srcWidth, srcHeight, angle);

    return self;
}

static mrb_value mrb_gd_image_copy_resized (mrb_state *mrb, mrb_value self)
{
    mrb_value dst;
    mrb_int dstX, dstY, srcX, srcY, dstW, dstH, srcW, srcH;
    mrb_gd_image *image_src;
    mrb_gd_image *image_dst;

    mrb_get_args(mrb, "oiiiiiiii", &dst, &dstX, &dstY, &srcX, &srcY, &dstW, &dstH, &srcW, &srcH);

    image_src = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    image_dst = mrb_get_datatype(mrb, dst, &mrb_gd_image_type);
    if (image_src == NULL || image_src->im == NULL || image_dst == NULL || image_dst->im == NULL) {
        return self;
    }

    gdImageCopyResized(image_dst->im, image_src->im, dstX, dstY, srcX, srcY, dstW, dstH, srcW, srcH);

    return self;
}

static mrb_value mrb_gd_color_allocate(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    c = gdImageColorAllocate(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_allocate_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorAllocateAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_closest(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorClosest(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_closest_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorClosestAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_closest_hwb(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorClosestHWB(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_exact(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorExact(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_exact_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorExactAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_resolve(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorResolve(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_resolve_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_gd_image *image;
    int c;

    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    c = gdImageColorResolveAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_truecolor(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    int c;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    c = gdTrueColor(r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_truecolor_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    int c;

    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    c = gdTrueColorAlpha(r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_deallocate(mrb_state *mrb, mrb_value self)
{
    mrb_int color;
    mrb_gd_image *image;

    mrb_get_args(mrb, "i", &color);

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    gdImageColorDeallocate(image->im, color);

    return self;
}

static mrb_value mrb_gd_image_gif_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    FILE *fout;
    mrb_gd_image *image;

    mrb_get_args(mrb, "z", &filename);

    fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImageGif(image->im, fout);

    fclose(fout);

    return self;
}

static mrb_value mrb_gd_image_png_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    FILE *fout;
    mrb_gd_image *image;

    mrb_get_args(mrb, "z", &filename);

    fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImagePng(image->im, fout);

    fclose(fout);

    return self;
}

static mrb_value mrb_gd_image_jpeg_file(mrb_state *mrb, mrb_value self)
{
    mrb_int quality;
    char *filename;
    FILE *fout;
    mrb_gd_image *image;

    mrb_get_args(mrb, "zi", &filename, &quality);

    fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImageJpeg(image->im, fout, quality);

    fclose(fout);

    return self;
}

static mrb_value mrb_gd_image_wbmp_file(mrb_state *mrb, mrb_value self)
{
    mrb_int fg;
    char *filename;
    FILE *fout;
    mrb_gd_image *image;

    mrb_get_args(mrb, "zi", &filename, &fg);

    fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImageWBMP(image->im, fg, fout);

    fclose(fout);

    return self;
}

void mrb_GD_gem_init(mrb_state* mrb)
{
    struct RClass *module_gd;
    struct RClass *class_image;

    module_gd = mrb_define_module(mrb, "GD");
    class_image = mrb_define_class_under(mrb, module_gd, "Image", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_image, MRB_TT_DATA);

    mrb_define_method(mrb, class_image, "initialize", mrb_gd_image_initialize, MRB_ARGS_REQ(2));

    mrb_define_class_method(mrb, class_image, "new_from_gif_file", mrb_gd_image_new_from_gif_file, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_png_file", mrb_gd_image_new_from_png_file, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_jpeg_file", mrb_gd_image_new_from_jpeg_file, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_wbmp_file", mrb_gd_image_new_from_wbmp_file, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_gif_data", mrb_gd_image_new_from_gif_data, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_png_data", mrb_gd_image_new_from_png_data, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_jpeg_data", mrb_gd_image_new_from_jpeg_data, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_wbmp_data", mrb_gd_image_new_from_wbmp_data, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "destroy", mrb_gd_image_destroy, MRB_ARGS_NONE());

    mrb_define_method(mrb, class_image, "gif_file", mrb_gd_image_gif_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "png_file", mrb_gd_image_png_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "jpeg_file", mrb_gd_image_jpeg_file, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_image, "wbmp_file", mrb_gd_image_wbmp_file, MRB_ARGS_REQ(2));

    mrb_define_method(mrb, class_image, "width", mrb_gd_image_width, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_image, "height", mrb_gd_image_height, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_image, "set_pixel", mrb_gd_image_set_pixel, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, class_image, "get_pixel", mrb_gd_image_get_pixel, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_image, "get_truecolor_pixel", mrb_gd_image_get_truecolor_pixel, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_image, "line", mrb_gd_image_line, MRB_ARGS_REQ(5));
    mrb_define_method(mrb, class_image, "dashed_line", mrb_gd_image_dashed_line, MRB_ARGS_REQ(5));
    mrb_define_method(mrb, class_image, "rectangle", mrb_gd_image_rectangle, MRB_ARGS_REQ(5));
    mrb_define_method(mrb, class_image, "filled_rectangle", mrb_gd_image_filled_rectangle, MRB_ARGS_REQ(5));
    mrb_define_method(mrb, class_image, "fill", mrb_gd_image_fill, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, class_image, "copy_rotated", mrb_gd_image_copy_rotated, MRB_ARGS_REQ(8));
    mrb_define_method(mrb, class_image, "copy_resized", mrb_gd_image_copy_resized, MRB_ARGS_REQ(9));

    mrb_define_method(mrb, class_image, "color_allocate", mrb_gd_color_allocate, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, class_image, "color_allocate_alpha", mrb_gd_color_allocate_alpha, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, class_image, "color_closest", mrb_gd_color_closest, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, class_image, "color_closest_alpha", mrb_gd_color_closest_alpha, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, class_image, "color_closest_hwb", mrb_gd_color_closest_hwb, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, class_image, "color_exact", mrb_gd_color_exact, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, class_image, "color_exact_alpha", mrb_gd_color_exact_alpha, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, class_image, "color_resolve", mrb_gd_color_resolve, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, class_image, "color_resolve_alpha", mrb_gd_color_resolve_alpha, MRB_ARGS_REQ(4));
    mrb_define_class_method(mrb, class_image, "truecolor", mrb_gd_truecolor, MRB_ARGS_REQ(3));
    mrb_define_class_method(mrb, class_image, "truecolor_alpha", mrb_gd_truecolor_alpha, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, class_image, "color_deallocate", mrb_gd_color_deallocate, MRB_ARGS_REQ(1));
}

void mrb_GD_gem_final(mrb_state* mrb)
{
}
