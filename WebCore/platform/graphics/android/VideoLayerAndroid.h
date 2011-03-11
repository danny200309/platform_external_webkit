/*
 * Copyright 2011 The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VideoLayerAndroid_h
#define VideoLayerAndroid_h

#if USE(ACCELERATED_COMPOSITING)

#include "GLUtils.h"
#include "LayerAndroid.h"
#include <jni.h>

namespace android {
class SurfaceTexture;
}

namespace WebCore {

class VideoLayerAndroid : public LayerAndroid {

public:
    VideoLayerAndroid();
    explicit VideoLayerAndroid(const VideoLayerAndroid& layer);

    virtual bool isVideo() const { return true; }
    virtual LayerAndroid* copy() const { return new VideoLayerAndroid(*this); }

    // The following 3 functions are called in UI thread only.
    virtual bool drawGL(SkMatrix& matrix);
    void setSurfaceTexture(sp<SurfaceTexture> texture, int textureName, bool updateTexture);
    GLuint createPauseTexture();

private:
    void init();
    // Surface texture for showing the video is actually allocated in Java side
    // and passed into this native code.
    GLuint m_textureId;
    sp<android::SurfaceTexture> m_surfaceTexture;
    bool m_useSurfTex;

    // Texture for showing the paused image will be created at native side.
    // TODO: instead using a shared texture, we could make a texture pool to
    // show different screen shots for different videos
    static GLuint m_pauseTextureId;
    static bool m_createdPauseTexture;
};

} // namespace WebCore

#endif // USE(ACCELERATED_COMPOSITING)

#endif // VideoLayerAndroid_h
