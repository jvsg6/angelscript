# To override these settings, create "custom_settings.cmake"

# invoke parent defaults

include($${PWD}/../default_settings.pri)

CONFIG(debug, debug|release) {
    DESTDIR = $${PWD}/../../debug/demolition
}

CONFIG(release, debug|release){
    DESTDIR = $${PWD}/../../release/demolition
}

ANGELSCRIPT_DIR = /home/egor/tasks/2018/nuclideChainTool/nuclidechaintool/submodules/angelscript


# invoke custom, non-versioned settings
exists($${PWD}/custom_settings.pri) {
        include($${PWD}/custom_settings.pri)
}
