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
    mrb_get_args(mrb, "ii", &height, &width);

    gdImagePtr im = gdImageCreate(height, width);
    if (im == NULL) {
        return self;
    }

    mrb_gd_image *image = mrb_gd_image_wrap(mrb, im);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    return self;
}

static mrb_value mrb_gd_image_new_from_gif(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr im = gdImageCreateFromGif(fin);

    fclose(fin);

    mrb_gd_image *image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_png(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr im = gdImageCreateFromPng(fin);

    fclose(fin);

    mrb_gd_image *image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_jpeg(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr im = gdImageCreateFromJpeg(fin);

    fclose(fin);

    mrb_gd_image *image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_wbmp(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr im = gdImageCreateFromWBMP(fin);

    fclose(fin);

    mrb_gd_image *image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_tiff(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr im = gdImageCreateFromTiff(fin);

    fclose(fin);

    mrb_gd_image *image = mrb_gd_image_wrap(mrb, im);

    return mrb_obj_value(Data_Wrap_Struct(mrb, mrb_class_ptr(self), &mrb_gd_image_type, image));
}

static mrb_value mrb_gd_image_new_from_bmp(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr im = gdImageCreateFromBmp(fin);

    fclose(fin);

    mrb_gd_image *image = mrb_gd_image_wrap(mrb, im);

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

static mrb_value mrb_gd_image_fill(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y, color;
    mrb_get_args(mrb, "iii", &x, &y, &color);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
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
    mrb_get_args(mrb, "offiiiii", &dst, &dstX, &dstY, &srcX, &srcY, &srcWidth, &srcHeight, &angle);

    mrb_gd_image *image_src = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    mrb_gd_image *image_dst = mrb_get_datatype(mrb, dst, &mrb_gd_image_type);
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
    mrb_get_args(mrb, "oiiiiiiii", &dst, &dstX, &dstY, &srcX, &srcY, &dstW, &dstH, &srcW, &srcH);

    mrb_gd_image *image_src = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    mrb_gd_image *image_dst = mrb_get_datatype(mrb, dst, &mrb_gd_image_type);
    if (image_src == NULL || image_src->im == NULL || image_dst == NULL || image_dst->im == NULL) {
        return self;
    }

    gdImageCopyResized(image_dst->im, image_src->im, dstX, dstY, srcX, srcY, dstW, dstH, srcW, srcH);

    return self;
}

static mrb_value mrb_gd_color_allocate(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_get_args(mrb, "iii", &r, &g, &b);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    int c = gdImageColorAllocate(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_allocate_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorAllocateAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_closest(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_get_args(mrb, "iii", &r, &g, &b);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorClosest(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_closest_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorClosestAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_closest_hwb(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_get_args(mrb, "iii", &r, &g, &b);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorClosestHWB(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_exact(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_get_args(mrb, "iii", &r, &g, &b);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorExact(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_exact_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorExactAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_resolve(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_get_args(mrb, "iii", &r, &g, &b);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorResolve(image->im, r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_resolve_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return mrb_fixnum_value(-1);
    }

    int c = gdImageColorResolveAlpha(image->im, r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_truecolor(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b;
    mrb_get_args(mrb, "iii", &r, &g, &b);

    int c = gdTrueColor(r, g, b);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_truecolor_alpha(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, alpha;
    mrb_get_args(mrb, "iiii", &r, &g, &b, &alpha);

    int c = gdTrueColorAlpha(r, g, b, alpha);

    return mrb_fixnum_value(c);
}

static mrb_value mrb_gd_color_deallocate(mrb_state *mrb, mrb_value self)
{
    mrb_int color;
    mrb_get_args(mrb, "i", &color);

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }

    gdImageColorDeallocate(image->im, color);

    return self;
}

static mrb_value mrb_gd_image_gif_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
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
    mrb_get_args(mrb, "z", &filename);

    FILE *fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
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
    mrb_get_args(mrb, "zi", &filename, &quality);

    FILE *fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
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
    mrb_get_args(mrb, "zi", &filename, &fg);

    FILE *fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImageWBMP(image->im, fg, fout);

    fclose(fout);

    return self;
}

static mrb_value mrb_gd_image_tiff_file(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImageTiff(image->im, fout);

    fclose(fout);

    return self;
}

static mrb_value mrb_gd_image_bmp_file(mrb_state *mrb, mrb_value self)
{
    mrb_int compression;
    char *filename;
    mrb_get_args(mrb, "zi", &filename, &compression);

    FILE *fout = fopen(filename, "wb");
    if (fout == NULL) {
        return self;
    }

    mrb_gd_image *image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    if (image == NULL || image->im == NULL) {
        return self;
    }
    gdImageBmp(image->im, fout, compression);

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

    mrb_define_class_method(mrb, class_image, "new_from_gif", mrb_gd_image_new_from_gif, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_png", mrb_gd_image_new_from_png, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_jpeg", mrb_gd_image_new_from_jpeg, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_wbmp", mrb_gd_image_new_from_wbmp, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_tiff", mrb_gd_image_new_from_tiff, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, class_image, "new_from_bmp", mrb_gd_image_new_from_bmp, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "destroy", mrb_gd_image_destroy, MRB_ARGS_NONE());

    mrb_define_method(mrb, class_image, "gif_file", mrb_gd_image_gif_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "png_file", mrb_gd_image_png_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "jpeg_file", mrb_gd_image_jpeg_file, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_image, "wbmp_file", mrb_gd_image_wbmp_file, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_image, "tiff_file", mrb_gd_image_tiff_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "bmp_file", mrb_gd_image_bmp_file, MRB_ARGS_REQ(2));

    mrb_define_method(mrb, class_image, "width", mrb_gd_image_width, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_image, "height", mrb_gd_image_height, MRB_ARGS_NONE());
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
