// This file is part of the OGRE project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at https://www.ogre3d.org/licensing.
// SPDX-License-Identifier: MIT

#include "Renderer.h"

int main(int argc, char* argv[])
{
    Renderer app;
    app.initApp();
    app.render();
    app.closeApp();
    return 0;
}
