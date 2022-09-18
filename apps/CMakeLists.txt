configure_file(LMS.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/LMS.desktop)
configure_file(Spotify.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/Spotify.desktop)
configure_file(WhatsApp.desktop.cmake ${CMAKE_CURRENT_BINARY_DIR}/WhatsApp.desktop)

install(FILES
    lms.svg
    spotify.svg
    whatsapp.png
    DESTINATION ${SHARE_PREFIX}/icons/)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LMS.desktop
    ${CMAKE_CURRENT_BINARY_DIR}/Spotify.desktop
    ${CMAKE_CURRENT_BINARY_DIR}/WhatsApp.desktop
    DESTINATION ${SHARE_PREFIX}/apps/)

