TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

FORMS	= options.ui

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}


