cd /d "D:\reg_edit\reg_edit" &msbuild "reg_edit.vcxproj" /t:sdvViewer /p:configuration="Debug" /p:platform=Win32
exit %errorlevel% 