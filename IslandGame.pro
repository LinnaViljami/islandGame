TEMPLATE = subdirs

SUBDIRS += \
    UI \
    Tests \
    GameLogic

UI.depends = GameLogic
