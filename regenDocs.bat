@echo off
echo Generando documentacion con Doxygen...

cd "./docs"
:: Ejecutamos Doxygen
doxygen Doxyfile

echo.
echo Documentacion terminada.
pause