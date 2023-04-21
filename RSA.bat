color f0
mode con cols=98 lines=32
echo off
cls
Title Rsa Admin Mode ^| Advanced
::===========================================================================
fsutil dirty query %systemdrive%  >nul 2>&1 || (
echo ==== ERRO ====
echo Este Script requer Privilegios administrativos.
echo Abra o script com clique direito e escolha 'Executar como administrador'
echo.
echo Pressione alguma tecla para sair...
pause >nul
exit
)
::===========================================================================
setlocal EnableExtensions EnableDelayedExpansion
pushd "%~dp0"
cd /d "%~dp0"
start python3 RSA.py
