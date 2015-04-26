#include <stdio.h>
#include "mruby.h"
#include "mruby/variable.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "gd.h"

static void mrb_gd_image_free(mrb_state *mrb, void *p)
{
    gdImagePtr image = (gdImagePtr)p;
    if (image != NULL) {
        gdImageDestroy(image);
    }
}

static const mrb_data_type mrb_gd_image_type = {
    "mrb_gd_image", mrb_gd_image_free,
};

static mrb_value mrb_gd_image_initialize(mrb_state *mrb, mrb_value self)
{
    mrb_int height, width;
    mrb_get_args(mrb, "ii", &height, &width);

    gdImagePtr image = gdImageCreate(height, width);
    if (image == NULL) {
        return self;
    }

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

    gdImagePtr image = gdImageCreateFromGif(fin);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    fclose(fin);

    return self;
}

static mrb_value mrb_gd_image_new_from_png(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr image = gdImageCreateFromPng(fin);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    fclose(fin);

    return self;
}

static mrb_value mrb_gd_image_new_from_jpeg(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr image = gdImageCreateFromJpeg(fin);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    fclose(fin);

    return self;
}

static mrb_value mrb_gd_image_new_from_wbmp(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr image = gdImageCreateFromWBMP(fin);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    fclose(fin);

    return self;
}

static mrb_value mrb_gd_image_new_from_tiff(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr image = gdImageCreateFromTiff(fin);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    fclose(fin);

    return self;
}

static mrb_value mrb_gd_image_new_from_bmp(mrb_state *mrb, mrb_value self)
{
    char *filename;
    mrb_get_args(mrb, "z", &filename);

    FILE *fin = fopen(filename, "rb");
    if (fin == NULL) {
        return self;
    }

    gdImagePtr image = gdImageCreateFromBmp(fin);

    DATA_PTR(self) = image;
    DATA_TYPE(self) = &mrb_gd_image_type;

    fclose(fin);

    return self;
}

static mrb_value mrb_gd_image_fill(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y, color;
    mrb_get_args(mrb, "iii", &x, &y, &color);

    gdImagePtr image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    gdImageFill(image, x, y, color);

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

    gdImagePtr image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    gdImageGif(image, fout);

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

    gdImagePtr image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    gdImagePng(image, fout);

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

    gdImagePtr image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    gdImageJpeg(image, fout, quality);

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

    gdImagePtr image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    gdImageWBMP(image, fg, fout);

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

    gdImagePtr image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    gdImageTiff(image, fout);

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

    gdImagePtr image = mrb_get_datatype(mrb, self, &mrb_gd_image_type);
    gdImageBmp(image, fout, compression);

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

    mrb_define_method(mrb, class_image, "gif_file", mrb_gd_image_gif_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "png_file", mrb_gd_image_png_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "jpeg_file", mrb_gd_image_jpeg_file, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_image, "wbmp_file", mrb_gd_image_wbmp_file, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, class_image, "tiff_file", mrb_gd_image_tiff_file, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, class_image, "bmp_file", mrb_gd_image_bmp_file, MRB_ARGS_REQ(2));

    mrb_define_method(mrb, class_image, "fill", mrb_gd_image_fill, MRB_ARGS_REQ(3));
}

void mrb_GD_gem_final(mrb_state* mrb)
{
}
