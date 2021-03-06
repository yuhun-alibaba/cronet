// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ImagePixelLocker_h
#define ImagePixelLocker_h

#include "platform/heap/Heap.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPixmap.h"
#include "wtf/PassRefPtr.h"
#include "wtf/RefPtr.h"

class SkImage;

namespace blink {

class ImagePixelLocker {
public:
    ImagePixelLocker(PassRefPtr<const SkImage>, SkAlphaType);

    const void* pixels() const { return m_pixels; }

private:
    const RefPtr<const SkImage> m_image;
    const void* m_pixels;
    SkAutoPixmapStorage m_pixelStorage;
};

} // namespace blink

#endif
