cmake_minimum_required(VERSION 3.10)

project(MyQmlProject LANGUAGES CXX)

# Đặt tiêu chuẩn C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tìm thư viện
find_package(Qt5 COMPONENTS Quick WebSockets REQUIRED)
find_package(yaml-cpp REQUIRED)

# Thêm tất cả các tệp .cpp và .h vào danh sách SOURCES và HEADERS
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)
file(GLOB_RECURSE QML_FILES qml/*.qml)

# Generate MOC files for headers with Q_OBJECT
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Tạo tệp tài nguyên QRC từ các tệp .qml
qt5_add_resources(RESOURCE_FILES
    resources/resources.qrc
)

# Tạo ứng dụng Qt với các tệp nguồn và tài nguyên
add_executable(MyQmlProject
    ${SOURCES}
    ${MOC_SOURCES}  # Thêm MOC files vào
    ${RESOURCE_FILES}
    src/websocket/viewmodel.cpp
)

# Liên kết thư viện Qt với ứng dụng
target_link_libraries(MyQmlProject
    PRIVATE Qt5::Quick
    PRIVATE Qt5::WebSockets
)

# Bao gồm thư mục chứa header
target_include_directories(MyQmlProject
    PRIVATE include
)

# Đảm bảo Qt được liên kết đúng với ứng dụng
target_link_libraries(MyQmlProject
    PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::WebSockets yaml-cpp
)

