#pragma once

struct OGConfig;

class OGApplication
{
public:
    static const int DEFAUL_FRAMERATE = 60;
    static const int DEFAUL_SCREEN_WIDTH = 800;
    static const int DEFAUL_SCREEN_HEIGHT = 600;
    static const char* DEFAUL_LANGUAGE;
    static const char* DEFAUL_LEVEL_NAME;

    static const char* RESOURCES_DIR;
    static const char* PROPERTIES_DIR;
    static const char* FILE_CONFIG;

public:   
    int run(int argc, char** argv);

private:
    bool initialize(int argc, char** argv, OGConfig& config);
};
