#include <node.h>
#include <v8.h>

#include <cstdio>

#include "SkCanvas.h"
#include "SkData.h"
#include "SkForceLinking.h"
#include "SkGraphics.h"
#include "SkImageEncoder.h"
#include "SkImageInfo.h"
#include "SkStream.h"
#include "SkSurface.h"

using namespace v8;

Handle<Value> Draw(const Arguments& args) {
  HandleScope scope;
  SkPaint p;
  p.setColor(SK_ColorRED);
  p.setAntiAlias(true);
  p.setStyle(SkPaint::kStroke_Style);
  p.setStrokeWidth(10);

  // Force the image encoders/decoders to be linked.
  SkForceLinking(false);

  // Initialize the library.
  SkAutoGraphics init;

  // Create the canvas to draw on.
  SkImageInfo info = SkImageInfo::MakeN32(300, 300, kPremul_SkAlphaType);
  SkAutoTUnref<SkSurface> surface(SkSurface::NewRaster(info));
  SkCanvas* canvas(surface->getCanvas());

  // Draw on the canvas.
  canvas->drawColor(SK_ColorWHITE);

  SkPaint paint;
  paint.setColor(SK_ColorRED);
  paint.setAntiAlias(true);
  paint.setStyle(SkPaint::kStroke_Style);
  paint.setStrokeWidth(10);

  canvas->drawLine(20, 20, 100, 100, paint);

  // Write out the image as a PNG.
  SkAutoTUnref<SkImage> image(surface->newImageSnapshot());
  SkAutoTUnref<SkData> data(image->encode(SkImageEncoder::kPNG_Type, 100));
  if (NULL == data.get()) {
      printf("Failed to encode\n");
      ThrowException(Exception::TypeError(String::New("Failed to encode.")));
      return scope.Close(Undefined());
  }
  SkFILEWStream stream("line.png");
  stream.write(data->data(), data->size());

  return scope.Close(String::New("Success!"));
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("draw"),
      FunctionTemplate::New(Draw)->GetFunction());
}

NODE_MODULE(hello, init)
