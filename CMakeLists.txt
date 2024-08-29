cmake_minimum_required(VERSION 3.10)
   project(YourProjectName)

   set(wxWidgets_USE_GTK3 ON)
   find_package(wxWidgets REQUIRED COMPONENTS core base)
   include(${wxWidgets_USE_FILE})

   add_executable(YourExecutableName 
       GUIProject/MainFrame.cpp
       GUIProject/App.cpp
   )

   target_link_libraries(YourExecutableName ${wxWidgets_LIBRARIES})
   
