@echo off
chcp 65001 > nul
echo ==========================================
echo    SECRET AGENT SYSTEM INSTALLATION
echo ==========================================
echo.

echo Step 1: Checking for previous installations...
if exist spy_usage_history.dat (
    echo Found previous installation data!
    echo Total usage will continue from previous count.
) else (
    echo No previous installations found.
    echo This is a fresh installation.
)

echo.
echo Step 2: Installing system files...
timeout /t 2 /nobreak > nul

if not exist spy_register.exe (
    echo ERROR: spy_register.exe not found!
    echo Please compile the program first.
    pause
    exit /b 1
)

echo.
echo Step 3: Registration in system...
echo Creating system environment...
echo System ready for agent registration.

echo.
echo ==========================================
echo    INSTALLATION COMPLETED!
echo ==========================================
echo.
echo Program installed successfully!
echo.
echo Important information:
echo - You have 5 total launches across all installations
echo - Each session has 60 seconds to enter data
echo - Previous usage counts towards your limit
echo - System files are hidden for security
echo.
echo Run spy_register.exe to start the program
echo Run uninstall_spy_system.bat to remove completely
echo.
pause