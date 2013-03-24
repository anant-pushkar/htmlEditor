project(text_editor)
 
find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})
 
set(tutorial4_SRCS 
  main.cpp
  mainwindow.cpp
)
 
kde4_add_executable(text_editor ${tutorial4_SRCS})
 
target_link_libraries(text_editor ${KDE4_KDEUI_LIBS} 
                                ${KDE4_KIO_LIBS})
 
install(TARGETS text_editor DESTINATION ${BIN_INSTALL_DIR})
install(FILES tutorial3ui.rc 
        DESTINATION ${DATA_INSTALL_DIR}/text_editor)