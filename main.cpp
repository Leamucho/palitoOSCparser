//
// 2020 Leandro Muñoz
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"


int main()
{
    ofSetupOpenGL(662, 321, OF_WINDOW);
    return ofRunApp(std::make_shared<ofApp>());
}
