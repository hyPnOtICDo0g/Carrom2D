# Install Build dependencies

iex "& {$(irm get.scoop.sh)} -RunAsAdmin"
scoop bucket add versions
scoop install 7zip gow mingw-winlibs-llvm -s
iwr https://www.transmissionzero.co.uk/files/software/development/GLUT/freeglut-MinGW.zip -O freeglut.zip
7z x freeglut.zip freeglut\include\GL freeglut\lib\x64\libfreeglut_static.a
mv .\freeglut\include\GL "$(scoop prefix mingw-winlibs-llvm)\include"
mv .\freeglut\lib\x64\libfreeglut_static.a "$(scoop prefix mingw-winlibs-llvm)\lib"

# Build windows binary

make -B -j $(Get-CimInstance Win32_ComputerSystem).NumberOfLogicalProcessors
cd bin && sha256sum Carrom2D-windows-amd64.exe > Carrom2D-windows-amd64.exe.sha256
